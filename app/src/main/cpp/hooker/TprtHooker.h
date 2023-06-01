//
// Created by heqyo on 2023/2/4.
//
#pragma once
#ifndef MODIFYFGO_ALTER_LILY_TPRTHOOKER_H
#define MODIFYFGO_ALTER_LILY_TPRTHOOKER_H

#include "../logging.h"
#include "../il2cpp/il2cpp-types.h"
#include "../utf8/Il2CppStringConverter.h"

extern void (*backupTp2SdkInitEx)();
void fakeTp2SdkInitEx(int gameId, Il2CppString *appKey);

extern void (*backupTp2UserLogin)();
void fakeTp2UserLogin(Il2CppObject *_null, Il2CppString *openId);

extern void (*backupTp2SetGameStatus)(void *status);
void fakeTp2SetGameStatus(void *status);

#endif //MODIFYFGO_ALTER_LILY_TPRTHOOKER_H
