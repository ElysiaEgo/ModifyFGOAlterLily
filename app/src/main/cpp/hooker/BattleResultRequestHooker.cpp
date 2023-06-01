//
// Created by heqyo on 2023/2/4.
//

#include "BattleResultRequestHooker.h"

extern bool battleWin;
extern void ToastFromJni(const char *msg);

struct Params {
    Il2CppString *Scores; // string
    Il2CppString *Action = nullptr; // string
    Il2CppArray *VoicePlayedArray; // int[][]
    Il2CppArray *AliveUniqueIds; // int[]
    Il2CppArray *RaidResult; // RaidResult[]
    Il2CppArray *SuperBossResult; // SuperBossResult[]
    int32_t ElapsedTurn;
    Il2CppArray *UsedTurnArray;// int[]
    int32_t RecordType;
    Il2CppObject *RecordJson; // Dictionary
    Il2CppObject *FirstNpPlayList; // List
    Il2CppObject *UsedEquipSkillDict; // Dictionary
    Il2CppObject *SvtCommonFlagDict; // Dictionary
    Il2CppArray *SkillShiftUniqueIdArray; // int[]
    Il2CppArray *SkillShiftNpcSvtIdArray; // long[]
    Il2CppArray *CalledEnemyUniqueIdArray; // int[]
};

Params cache;

uint32_t cachedScoresHandle;
uint32_t cachedActionHandle;
uint32_t cachedVoicePlayedArrayHandle;
uint32_t cachedAliveUniqueIdsHandle;
uint32_t cachedRaidResultHandle;
uint32_t cachedSuperBossResultHandle;
uint32_t cachedUsedTurnArrayHandle;
uint32_t cachedRecordJsonHandle;
uint32_t cachedFirstNpPlayListHandle;
uint32_t cachedUsedEquipSkillDictHandle;
uint32_t cachedSvtCommonFlagDictHandle;
uint32_t cachedSkillShiftUniqueIdArrayHandle;
uint32_t cachedSkillShiftNpcSvtIdArrayHandle;
uint32_t cachedCalledEnemyUniqueIdArrayHandle;

void (*backupBeginRequest)(void *thisObject,
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
                      Il2CppArray *calledEnemyUniqueIdArray) {
    LOGD("battleId=%" PRId64 "", battleId)
    LOGD("battleResult=%d", battleResult)
    Params newParams = {
            scores,
            action,
            voicePlayedArray,
            aliveUniqueIds,
            raidResult,
            superBossResult,
            elapsedTurn,
            usedTurnArray,
            recordType,
            recordJson,
            firstNpPlayList,
            usedEquipSkillDict,
            svtCommonFlagDict,
            skillShiftUniqueIdArray,
            skillShiftNpcSvtIdArray,
            calledEnemyUniqueIdArray,
    };
    int32_t newWinResult = 1;
    int32_t newBattleResult = 1;

    if (battleWin && cache.Action != nullptr && !Il2CppStringToStdString(cache.Action).empty()) {
        LOGD("cachedAction not null")
        if (battleResult == 3) {
            LOGD("replace battle log")
            ToastFromJni("撤退胜利成功");
            newWinResult = 1;
            newBattleResult = 1;
            newParams = cache;
        } else if (battleResult == 1) {
            LOGD("cache battle log")
            ToastFromJni("战斗日志已更新");
            newBattleResult = battleResult;
            newWinResult = winResult;
            il2cpp_gchandle_free(cachedScoresHandle);
            cachedScoresHandle = il2cpp_gchandle_new(&scores->object, true);
            il2cpp_gchandle_free(cachedActionHandle);
            cachedActionHandle = il2cpp_gchandle_new(&action->object, true);
            il2cpp_gchandle_free(cachedAliveUniqueIdsHandle);
            cachedAliveUniqueIdsHandle = il2cpp_gchandle_new(&aliveUniqueIds->obj, true);
            il2cpp_gchandle_free(cachedVoicePlayedArrayHandle);
            cachedVoicePlayedArrayHandle = il2cpp_gchandle_new(&voicePlayedArray->obj, true);
            il2cpp_gchandle_free(cachedRaidResultHandle);
            cachedRaidResultHandle = il2cpp_gchandle_new(
                    reinterpret_cast<Il2CppObject *>(raidResult), true);
            il2cpp_gchandle_free(cachedSuperBossResultHandle);
            cachedSuperBossResultHandle = il2cpp_gchandle_new(
                    reinterpret_cast<Il2CppObject *>(superBossResult), true);
            il2cpp_gchandle_free(cachedUsedTurnArrayHandle);
            cachedUsedTurnArrayHandle = il2cpp_gchandle_new(&usedTurnArray->obj, true);
            il2cpp_gchandle_free(cachedRecordJsonHandle);
            cachedRecordJsonHandle = il2cpp_gchandle_new(recordJson, true);
            il2cpp_gchandle_free(cachedFirstNpPlayListHandle);
            cachedFirstNpPlayListHandle = il2cpp_gchandle_new(firstNpPlayList, true);
            il2cpp_gchandle_free(cachedUsedEquipSkillDictHandle);
            cachedUsedEquipSkillDictHandle = il2cpp_gchandle_new(usedEquipSkillDict, true);
            il2cpp_gchandle_free(cachedSvtCommonFlagDictHandle);
            cachedSvtCommonFlagDictHandle = il2cpp_gchandle_new(svtCommonFlagDict, true);
            il2cpp_gchandle_free(cachedSkillShiftUniqueIdArrayHandle);
            cachedSkillShiftUniqueIdArrayHandle = il2cpp_gchandle_new(&skillShiftUniqueIdArray->obj,
                                                                      true);
            il2cpp_gchandle_free(cachedSkillShiftNpcSvtIdArrayHandle);
            cachedSkillShiftNpcSvtIdArrayHandle = il2cpp_gchandle_new(&skillShiftNpcSvtIdArray->obj,
                                                                      true);
            il2cpp_gchandle_free(cachedCalledEnemyUniqueIdArrayHandle);
            cachedCalledEnemyUniqueIdArrayHandle = il2cpp_gchandle_new(&calledEnemyUniqueIdArray->obj,
                                                                       true);;
            cache = newParams;
        }
    } else {
        LOGD("cachedAction null")
        if (battleResult == 1) {
            LOGD("cache battle log")
            ToastFromJni("战斗日志已缓存");
            cachedScoresHandle = il2cpp_gchandle_new(&scores->object, true);
            cachedActionHandle = il2cpp_gchandle_new(&action->object, true);
            cachedAliveUniqueIdsHandle = il2cpp_gchandle_new(&aliveUniqueIds->obj, true);
            cachedVoicePlayedArrayHandle = il2cpp_gchandle_new(&voicePlayedArray->obj, true);
            cachedRaidResultHandle = il2cpp_gchandle_new(
                    reinterpret_cast<Il2CppObject *>(raidResult), true);
            cachedSuperBossResultHandle = il2cpp_gchandle_new(
                    reinterpret_cast<Il2CppObject *>(superBossResult), true);
            cachedUsedTurnArrayHandle = il2cpp_gchandle_new(&usedTurnArray->obj, true);
            cachedRecordJsonHandle = il2cpp_gchandle_new(recordJson, true);
            cachedFirstNpPlayListHandle = il2cpp_gchandle_new(firstNpPlayList, true);
            cachedUsedEquipSkillDictHandle = il2cpp_gchandle_new(usedEquipSkillDict, true);
            cachedSvtCommonFlagDictHandle = il2cpp_gchandle_new(svtCommonFlagDict, true);
            cachedSkillShiftUniqueIdArrayHandle = il2cpp_gchandle_new(&skillShiftUniqueIdArray->obj,
                                                                      true);
            cachedSkillShiftNpcSvtIdArrayHandle = il2cpp_gchandle_new(&skillShiftNpcSvtIdArray->obj,
                                                                      true);
            cachedCalledEnemyUniqueIdArrayHandle = il2cpp_gchandle_new(&calledEnemyUniqueIdArray->obj,
                                                                       true);
            cache = newParams;
        } else {
            ToastFromJni("战斗日志未缓存，请先正常通关一次");
        }
        newBattleResult = battleResult;
        newWinResult = winResult;
    }
    LOGD("newBattleResult=%d", newBattleResult)
    LOGD("backupBeginRequest")
    backupBeginRequest(thisObject,
                       battleId,
                       newBattleResult,
                       newWinResult,
                       newParams.Scores,
                       newParams.Action,
                       newParams.VoicePlayedArray,
                       newParams.AliveUniqueIds,
                       newParams.RaidResult,
                       newParams.SuperBossResult,
                       newParams.ElapsedTurn,
                       newParams.UsedTurnArray,
                       newParams.RecordType,
                       newParams.RecordJson,
                       newParams.FirstNpPlayList,
                       newParams.UsedEquipSkillDict,
                       newParams.SvtCommonFlagDict,
                       newParams.SkillShiftUniqueIdArray,
                       newParams.SkillShiftNpcSvtIdArray,
                       newParams.CalledEnemyUniqueIdArray);
}