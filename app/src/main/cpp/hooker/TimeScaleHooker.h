//
// Created by heqyo on 2023/2/6.
//
#pragma once
#ifndef MODIFYFGO_ALTER_LILY_TIMESCALEHOOKER_H
#define MODIFYFGO_ALTER_LILY_TIMESCALEHOOKER_H

#include <cstdint>

extern void (*backupset_timeScale)(float value);

void fakesset_timeScale(float value);

#endif //MODIFYFGO_ALTER_LILY_TIMESCALEHOOKER_H
