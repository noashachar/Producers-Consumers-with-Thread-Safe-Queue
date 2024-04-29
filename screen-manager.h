#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "bounded-buffer.h"

typedef struct {
    BoundedBuffer* queue;
} ScreenManagerArgs;

void* screen_manager_worker(void* ptr);

#endif
