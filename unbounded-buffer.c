#include "unbounded-buffer.h"

void ub_init(UnboundedBuffer* self) {
    self->first = NULL;
    self->last = NULL;
    pthread_mutex_init(&self->mutex, NULL);
    sem_init(&self->sem, 0, 0);
}

void ub_insert(UnboundedBuffer* self, char* item) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->item = item;
    node->next = NULL;

    pthread_mutex_lock(&self->mutex);

    if (self->last == NULL) {
        self->first = self->last = node;
    } else {
        self->last->next = node;
        self->last = node;
    }

    pthread_mutex_unlock(&self->mutex);
    sem_post(&self->sem);
}

char* ub_remove(UnboundedBuffer* self) {
    sem_wait(&self->sem);
    pthread_mutex_lock(&self->mutex);

    Node* node = self->first;
    self->first = node->next;
    if (self->first == NULL) {
        self->last = NULL;
    }

    pthread_mutex_unlock(&self->mutex);

    char* item = node->item;
    free(node);

    return item;
}

void ub_destroy(UnboundedBuffer* self) {
    pthread_mutex_lock(&self->mutex);
    while (self->first != NULL) {
        Node* next = self->first->next;
        free(self->first);
        self->first = next;
    }
    pthread_mutex_unlock(&self->mutex);
    sem_destroy(&self->sem);
    pthread_mutex_destroy(&self->mutex);
}
