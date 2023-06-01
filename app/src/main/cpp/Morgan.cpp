//
// Created by goEval on 2022/8/12.
//

#include "Morgan.h"
#include "il2cpp/il2cpp-types.h"

#define DO_API(r, n, p) r (*n) p
#include "il2cpp/il2cpp-api-functions.h"
#undef DO_API

#define DO_FUNC(a, n, c, m) Func c##_##m = {false, a, n, #c, #m, 0}
#define DO_FUNC_POINTER(m, p) Func m = {true, "", "", "", "", p}
#include "il2cpp/il2cpp-functions.h"
#undef DO_FUNC
#undef DO_FUNC_POINTER

#include "hooker/TprtHooker.h"
#include "hooker/BattleResultRequestHooker.h"
#include "hooker/FollowerListRequestHooker.h"
#include "hooker/ProtectionHooker.h"
#include "hooker/FrameRateHooker.h"
#include "hooker/TimeScaleHooker.h"

HookFunType hook_func = nullptr;
void *il2cpp_handle = nullptr;
JavaVM *_jvm = nullptr;
bool battleWin = true;
bool highFrameRate = true;
float timescale = 1.0;

void init_il2cpp_api() {
#define DO_API(r, n, p) n = (r (*) p) dlsym(il2cpp_handle, #n)

#include "il2cpp/il2cpp-api-functions.h"

#undef DO_API
}

bool installHook(Func methodInfo, void *replace, void**backup) {
#define CHECKNULL(var) {    \
    if ((var) == nullptr) { \
        LOGD("failed to find %s when finding %s.%s", #var, methodInfo.className, methodInfo.methodName) \
        return false;       \
    }                       \
}
    auto domain = il2cpp_domain_get();
    CHECKNULL(domain)
    auto assembly = il2cpp_domain_assembly_open(domain, methodInfo.assemblyName);
    CHECKNULL(domain)
    auto assemblyImage = il2cpp_assembly_get_image(assembly);
    CHECKNULL(domain)
    auto klass = il2cpp_class_from_name(assemblyImage, methodInfo.namespaceName, methodInfo.className);
    CHECKNULL(domain)
    auto method = il2cpp_class_get_method_from_name(klass, methodInfo.methodName, -1);
    CHECKNULL(domain)
    hook_func((void *) (method->methodPointer), replace, backup);
    return true;
#undef CHECKNULL
}

void ToastFromJni(const char *msg) {
    JNIEnv *env = nullptr;
    _jvm->AttachCurrentThread(&env, nullptr);
    _jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    // different classloader, this leads to to real UnityPlayer
    auto UnityPlayerClass = env->FindClass("com/unity3d/player/UnityPlayer");
    auto currentActivityFieldID = env->GetStaticFieldID(UnityPlayerClass, "currentActivity",
                                                        "Landroid/app/Activity;");
    auto currentActivity = env->GetStaticObjectField(UnityPlayerClass, currentActivityFieldID);
    auto ToastClass = env->FindClass("android/widget/Toast");
    auto makeTextMethod = env->GetStaticMethodID(ToastClass, "makeText", "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
    auto showMethod = env->GetMethodID(ToastClass, "show", "()V");
    auto ToastObject = env->CallStaticObjectMethod(ToastClass, makeTextMethod, currentActivity, env->NewStringUTF(msg), 1);
    env->CallVoidMethod(ToastObject, showMethod);
}

void (*backupIl2cppInit)(const char *domain_name);

void fakeIl2cppInit(const char *domain_name) {
    backupIl2cppInit(domain_name);
    init_il2cpp_api();
    auto isChina = installHook(app::Tp2Sdk_Tp2SdkInitEx, (void *) fakeTp2SdkInitEx,
                (void **) &backupTp2SdkInitEx);
    installHook(app::Tp2Sdk_Tp2UserLogin, (void *) fakeTp2UserLogin,
                (void **) &backupTp2UserLogin);
    installHook(app::Tp2Sdk_Tp2SetGamestatus, (void *) fakeTp2SetGameStatus,
                (void **) &backupTp2SetGameStatus);
    installHook(app::BattleResultRequest_beginRequest, (void *) fakeBeginRequest,
                (void **) &backupBeginRequest);
    installHook(app::Application_set_targetFrameRate, (void *) fakeset_targetFrameRate,
                (void **) &backupset_targetFrameRate);
    installHook(app::FollowerListRequest_beginRequest, (void *) fakeBeginFollowerListRequest,
                (void **) &backupBeginFollowerListRequest);
    if (isChina)
        installHook(app::Time_set_timeScale, (void *) fakesset_timeScale,
                (void **) &backupset_timeScale);
    ToastFromJni("初始化完成");
}

void on_library_loaded(const char *name, void *handle) {
    if (std::string(name).ends_with("libil2cpp.so")) {
        LOGD("il2cpp loaded")
        void *il2cppInit = dlsym(handle, "il2cpp_init");
        LOGD("il2cpp init:%p", il2cppInit)
        il2cpp_handle = handle;
        hook_func(il2cppInit, (void *) fakeIl2cppInit, (void **) &backupIl2cppInit);
    }
    if (std::string(name).ends_with("libtprt.so")) {
        tprt = findLibAddress("libunity.so");
    }
    if (std::string(name).ends_with("libunity.so")) {
        unity = findLibAddress("libunity.so");
#ifdef __AARCH64EL__
        // arm64-v8a
        hook_func((void *) ((char *)unity.start + 0x6D6760), (void *) fakeCheckPath, (void **) backupCheckPath);
#else
        // armeabi-v7a
        hook_func((void *) ((char *)unity.start + 0x6DCCF0), (void *) fakeCheckPath, (void **) backupCheckPath);
#endif
    }
}

extern "C" [[gnu::visibility("default")]] [[gnu::used]]
jint JNI_OnLoad(JavaVM *jvm, void *) {
    _jvm = jvm;
    JNIEnv *env = nullptr;
    jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    return JNI_VERSION_1_6;
}

extern "C" [[gnu::visibility("default")]] [[gnu::used]]
NativeOnModuleLoaded native_init(const NativeAPIEntries *entries) {
    hook_func = entries->hook_func;
    hook_func((void *) pthread_create, (void *) fakePthread_create,
              (void **) &backupPthread_create);
    return on_library_loaded;
}

extern "C"
JNIEXPORT void JNICALL
Java_io_github_heqyoufree_modifyfgo_1alter_1lily_imgui_ImGuiView_setBattleWin(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jboolean value) {
    LOGD("battleWin set to %s", value ? "true" : "false")
    battleWin = value;
}
extern "C"
JNIEXPORT void JNICALL
Java_io_github_heqyoufree_modifyfgo_1alter_1lily_imgui_ImGuiView_setHighFrameRate(JNIEnv *env,
                                                                                  jobject thiz,
                                                                                  jboolean value) {
    LOGD("highFrameRate set to %s", value ? "true" : "false")
    highFrameRate = value;
    backupset_targetFrameRate(60);
}
extern "C"
JNIEXPORT void JNICALL
Java_io_github_heqyoufree_modifyfgo_1alter_1lily_imgui_ImGuiView_setAccelerate(JNIEnv *env, jobject thiz,
                                                                        jfloat value) {
    LOGD("timescale set to %f", value)
    timescale = value;
    backupset_timeScale(value);
}