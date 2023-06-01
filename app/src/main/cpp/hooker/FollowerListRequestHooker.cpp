//
// Created by heqyo on 2023/4/1.
//

#include "FollowerListRequestHooker.h"
#include <string>

extern void ToastFromJni(const char *msg);

void (*backupBeginFollowerListRequest)(void *thisObject, int32_t questId, int32_t questPhase);

void fakeBeginFollowerListRequest(void *thisObject, int32_t questId, int32_t questPhase) {
    ToastFromJni((std::to_string(questId)+'-'+std::to_string(questPhase)).c_str());
    backupBeginFollowerListRequest(thisObject, questId, questPhase);
}