#ifndef CO_EDITOR_H
#define CO_EDITOR_H

#include "bounded-buffer.h"
#include "unbounded-buffer.h"

typedef struct {
    UnboundedBuffer* queue_in;
    BoundedBuffer* queue_out;
} CoEditorArgs;

void* co_editor_worker(void* ptr);

#endif
