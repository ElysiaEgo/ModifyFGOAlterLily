//
// Created by heqyo on 2023/2/4.
//

#ifndef MODIFYFGO_ALTER_LILY_LSPOSEDAPI_H
#define MODIFYFGO_ALTER_LILY_LSPOSEDAPI_H

#include <cinttypes>

typedef int (*HookFunType)(void *func, void *replace, void **backup);

typedef int (*UnhookFunType)(void *func);

typedef void (*NativeOnModuleLoaded)(const char *name, void *handle);

typedef struct {
    uint32_t version;
    HookFunType hook_func;
    UnhookFunType unhook_func;
} NativeAPIEntries;

#endif //MODIFYFGO_ALTER_LILY_LSPOSEDAPI_H
