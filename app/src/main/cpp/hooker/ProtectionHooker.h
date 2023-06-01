//
// Created by heqyo on 2023/2/4.
//

#ifndef MODIFYFGO_ALTER_LILY_PROTECTIONHOOKER_H
#define MODIFYFGO_ALTER_LILY_PROTECTIONHOOKER_H

#include <pthread.h>
#include <errno.h>
#include <fstream>
#include "../logging.h"

struct ModuleAddress {
    void *start;
    void *end;
};

extern ModuleAddress tprt;
extern ModuleAddress unity;

extern ModuleAddress findLibAddress(const char *libname);

extern void (*backupCheckPath)();
void fakeCheckPath();

extern int (*backupPthread_create)(pthread_t *thread,
                            const pthread_attr_t *attr,
                            void *(*start_routine)(void *),
                            void *arg);
int fakePthread_create(pthread_t *thread,
                       const pthread_attr_t *attr,
                       void *(*start_routine)(void *),
                       void *arg);

#endif //MODIFYFGO_ALTER_LILY_PROTECTIONHOOKER_H
