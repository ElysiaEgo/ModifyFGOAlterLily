//
// Created by heqyo on 2023/2/4.
//
#pragma once
#ifndef MODIFYFGO_ALTER_LILY_BATTLERESULTREQUESTHOOKER_H
#define MODIFYFGO_ALTER_LILY_BATTLERESULTREQUESTHOOKER_H

#include "../il2cpp/il2cpp-appdata.h"
#include "../logging.h"
#include "../utf8/Il2CppStringConverter.h"

extern void (*backupBeginRequest)(void *thisObject,
                           int64_t battleId,
                           int32_t battleResult,
                           int32_t winResult,
                           Il2CppString *scores,
                           Il2CppString *action,
                           Il2CppArray *voicePlayedArray,
                           Il2CppArray *aliveUniqueIds,
                           Il2CppArray *raidResult,
                           Il2CppArray *superBossResult,
                           int32_t elapsedTurn,
                           Il2CppArray *usedTurnArray,
                           int32_t recordType,
                           Il2CppObject *recordJson,
                           Il2CppObject *firstNpPlayList,
                           Il2CppObject *usedEquipSkillDict,
                           Il2CppObject *svtCommonFlagDict,
                           Il2CppArray *skillShiftUniqueIdArray,
                           Il2CppArray *skillShiftNpcSvtIdArray,
                           Il2CppArray *calledEnemyUniqueIdArray);

void fakeBeginRequest(void *thisObject,
                      int64_t battleId,
                      int32_t battleResult,
                      int32_t winResult,
                      Il2CppString *scores,
                      Il2CppString *action,
                      Il2CppArray *voicePlayedArray,
                      Il2CppArray *aliveUniqueIds,
                      Il2CppArray *raidResult,
                      Il2CppArray *superBossResult,
                      int32_t elapsedTurn,
                      Il2CppArray *usedTurnArray,
                      int32_t recordType,
                      Il2CppObject *recordJson,
                      Il2CppObject *firstNpPlayList,
                      Il2CppObject *usedEquipSkillDict,
                      Il2CppObject *svtCommonFlagDict,
                      Il2CppArray *skillShiftUniqueIdArray,
                      Il2CppArray *skillShiftNpcSvtIdArray,
                      Il2CppArray *calledEnemyUniqueIdArray);

#endif //MODIFYFGO_ALTER_LILY_BATTLERESULTREQUESTHOOKER_H
