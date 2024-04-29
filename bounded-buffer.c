#include "bounded-buffer.h"

void bb_init(BoundedBuffer* self, int size) {
    self->buffer = (char**) malloc(sizeof(char*) * size);
    self->size = size;
    self->in = 0;
    self->out = 0;
    sem_init(&self->full, 0, 0);
    sem_init(&self->empty, 0, size);
    pthread_mutex_init(&self->mutex, NULL);
}

void bb_insert(BoundedBuffer* self, char* item) {
    sem_wait(&self->empty);
    pthread_mutex_lock(&self->mutex);

    self->buffer[self->in] = item;
    self->in = (self->in + 1) % self->size;

    pthread_mutex_unlock(&self->mutex);
    sem_post(&self->full);
}

char* bb_remove(BoundedBuffer* self) {
    sem_wait(&self->full);
    pthread_mutex_lock(&self->mutex);

    char* item = self->buffer[self->out];
    self->out = (self->out + 1) % self->size;

    pthread_mutex_unlock(&self->mutex);
    sem_post(&self->empty);

    return item;
}

bool bb_try_remove(BoundedBuffer* self, char** item) {
    if (sem_trywait(&self->full) != 0) {
        return false;
    }

    pthread_mutex_lock(&self->mutex);

    *item = self->buffer[self->out];
    self->out = (self->out + 1) % self->size;

    pthread_mutex_unlock(&self->mutex);
    sem_post(&self->empty);

    return true;
}

void bb_destroy(BoundedBuffer* self) {
    pthread_mutex_destroy(&self->mutex);
    sem_destroy(&self->full);
    sem_destroy(&self->empty);
    free(self->buffer);
}
