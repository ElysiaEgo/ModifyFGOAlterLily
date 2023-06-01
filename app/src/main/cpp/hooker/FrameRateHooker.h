//
// Created by heqyo on 2023/2/4.
//
#pragma once
#ifndef MODIFYFGO_ALTER_LILY_FRAMERATEHOOKER_H
#define MODIFYFGO_ALTER_LILY_FRAMERATEHOOKER_H

#include <cstdint>

extern void (*backupset_targetFrameRate)(int32_t value);

void fakeset_targetFrameRate(int32_t value);

#endif //MODIFYFGO_ALTER_LILY_FRAMERATEHOOKER_H
