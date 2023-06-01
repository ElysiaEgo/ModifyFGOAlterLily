//
// Created by heqyo on 2023/2/4.
//

#include "ProtectionHooker.h"

extern void ToastFromJni(const char *msg);
ModuleAddress tprt = {nullptr, nullptr};
ModuleAddress unity = {nullptr, nullptr};

ModuleAddress findLibAddress(const char *libname) {
    ModuleAddress lib{};
    std::ifstream maps;
    maps.open("/proc/self/maps", std::ios::in);
    std::string s;
    while (getline(maps, s)) {
        if (s.find(libname) != std::string::npos) {
//            LOGD("%s", s.c_str())
            char *_;
            lib.start = (void *) std::strtoll(s.substr(0,
                                                       s.find_first_of('-')).c_str(), &_, 16);
            lib.end = (void *) std::strtoll(s.substr(s.find_first_of('-') + 1,
                                                     s.find_first_of(' ')).c_str(), &_, 16);
            break;
        }
    }
    maps.close();
    return lib;
}

void (*backupCheckPath)();
void fakeCheckPath() {
//    LOGD("check disabled")
}

int (*backupPthread_create)(pthread_t *thread,
                                   const pthread_attr_t *attr,
                                   void *(*start_routine)(void *),
                                   void *arg);
int fakePthread_create(pthread_t *thread,
                       const pthread_attr_t *attr,
                       void *(*start_routine)(void *),
                       void *arg) {
    if (tprt.start != nullptr &&
    (void *) start_routine > tprt.start &&
    (void *) start_routine < tprt.end) {
        LOGD("0x%p", (void *) start_routine)
        LOGD("tprt pthread_create")
        LOGD("try to stop thread create")
        ToastFromJni("反作弊已关闭");
        return EPERM;
    }
    return backupPthread_create(thread, attr, start_routine, arg);
}