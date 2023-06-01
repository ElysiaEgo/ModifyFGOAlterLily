//
// Created by heqyo on 2023/2/6.
//

#include "TimeScaleHooker.h"
#include "../logging.h"

extern float timescale;

void (*backupset_timeScale)(float value);
void fakesset_timeScale(float value) {
    backupset_timeScale(timescale);
}