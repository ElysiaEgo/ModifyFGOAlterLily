//
// Created by heqyo on 2023/2/4.
//

#include "FrameRateHooker.h"
#include "../logging.h"

extern bool highFrameRate;

void (*backupset_targetFrameRate)(int32_t value);
void fakeset_targetFrameRate(int32_t value) {
//    LOGD("set_targetFrameRate called")
    backupset_targetFrameRate(highFrameRate ? 120 : value);
}