#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char** buffer;
    int size;
    int in;
    int out;
    sem_t full;
    sem_t empty;
    pthread_mutex_t mutex;
} BoundedBuffer;

void bb_init(BoundedBuffer* self, int size);
void bb_insert(BoundedBuffer* self, char* item);
char* bb_remove(BoundedBuffer* self);
bool bb_try_remove(BoundedBuffer* self, char** item);
void bb_destroy(BoundedBuffer* self);

#endif // BOUNDED_BUFFER_H
