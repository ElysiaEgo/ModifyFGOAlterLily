//
// Created by heqyo on 2023/4/1.
//

#ifndef MODIFYFGO_ALTER_LILY_FOLLOWERLISTREQUESTHOOKER_H
#define MODIFYFGO_ALTER_LILY_FOLLOWERLISTREQUESTHOOKER_H

#include "../il2cpp/il2cpp-appdata.h"
#include "../logging.h"

extern void (*backupBeginFollowerListRequest)(void *thisObject, int32_t questId, int32_t questPhase);

void fakeBeginFollowerListRequest(void *thisObject, int32_t questId, int32_t questPhase);

#endif //MODIFYFGO_ALTER_LILY_FOLLOWERLISTREQUESTHOOKER_H
