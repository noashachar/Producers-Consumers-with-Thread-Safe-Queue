#ifndef PRODUCER_H
#define PRODUCER_H

#include "bounded-buffer.h"

typedef struct {
    int id, num_products;
    BoundedBuffer* q;
} ProducerArgs;

void* producer_worker(void* ptr);

#endif
