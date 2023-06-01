//
// Created by heqyo on 2023/2/5.
//
#ifndef MODIFYFGO_ALTER_LILY_IL2CPP_FUNCTIONS_H
#define MODIFYFGO_ALTER_LILY_IL2CPP_FUNCTIONS_H

struct Func {
    bool isPointer;
    const char *assemblyName;
    const char *namespaceName;
    const char *className;
    const char *methodName;
    long offset;
};
#endif //MODIFYFGO_ALTER_LILY_IL2CPP_FUNCTIONS_H

namespace app {
    // Tp2
    DO_FUNC("Assembly-CSharp", "", Tp2Sdk, Tp2SdkInitEx);
    DO_FUNC("Assembly-CSharp", "", Tp2Sdk, Tp2UserLogin);
    DO_FUNC("Assembly-CSharp", "", Tp2Sdk, Tp2SetGamestatus);
    DO_FUNC_POINTER(PthreadCreate, (long) pthread_create);
    // PatchCheck
    DO_FUNC_POINTER(PathCheck64, 0x6D6760);
    // BattleResult
    DO_FUNC("Assembly-CSharp", "", BattleResultRequest, beginRequest);
    // FollwerList
    DO_FUNC("Assembly-CSharp", "", FollowerListRequest, beginRequest);
    // FrameRate
    DO_FUNC("UnityEngine.CoreModule", "UnityEngine", Application, set_targetFrameRate);
    // Accelerate
    DO_FUNC("UnityEngine.CoreModule", "UnityEngine", Time, set_timeScale);
}

