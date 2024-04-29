#ifndef UNBOUNDED_BUFFER_H
#define UNBOUNDED_BUFFER_H

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

typedef struct Node {
    char* item;
    struct Node* next;
} Node;

typedef struct {
    Node* first;
    Node* last;
    pthread_mutex_t mutex;
    sem_t sem;
} UnboundedBuffer;

void ub_init(UnboundedBuffer* self);
void ub_insert(UnboundedBuffer* self, char* item);
char* ub_remove(UnboundedBuffer* self);
void ub_destroy(UnboundedBuffer* self);

#endif // UNBOUNDED_BUFFER_H
