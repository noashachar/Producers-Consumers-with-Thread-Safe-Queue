#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "bounded-buffer.h"
#include "unbounded-buffer.h"

typedef struct {
    int num_producers;
    BoundedBuffer* producer_queues;
    UnboundedBuffer* queue_S;
    UnboundedBuffer* queue_N;
    UnboundedBuffer* queue_W;
} DispatcherArgs;

void* dispatcher_worker(void* ptr);

#endif
