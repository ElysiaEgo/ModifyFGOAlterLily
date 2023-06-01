//
// Created by heqyo on 2023/2/4.
//

#include "TprtHooker.h"

#include <jni.h>

void (*backupTp2SdkInitEx)();
void fakeTp2SdkInitEx(int gameId, Il2CppString *appKey) {
//    LOGD("Tp2SdkInitEx %s %d", Il2CppStringToStdString(appKey).c_str(), gameId)
}

void (*backupTp2UserLogin)();
void fakeTp2UserLogin(Il2CppObject *_null, Il2CppString *openId) {
//    LOGD("Tp2UserLogin")
}

void (*backupTp2SetGameStatus)(void *status);
void fakeTp2SetGameStatus(void *status) {
//    LOGD("Tp2SetGameStatus")
}