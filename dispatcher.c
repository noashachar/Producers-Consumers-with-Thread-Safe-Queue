#include "dispatcher.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char *cat_name[] = { "SPORTS", "NEWS", "WEATHER" };

typedef UnboundedBuffer Queue;


Queue *which_queue(char *msg, Queue* queue_S, Queue* queue_N, Queue* queue_W) {
    
    for (int i = 0; i < 3; i++) {
        if (strstr(msg, cat_name[i])) {
            switch (*cat_name[i]) {
                case 'S': return queue_S;
                case 'N': return queue_N;
                case 'W': return queue_W;
            }
        }
    }

    fprintf(stderr, "category not found for msg `%s`\n", msg);
    exit(EXIT_FAILURE);
}

void* dispatcher_worker(void* ptr) {
    DispatcherArgs* args = ptr;

    int not_finished = args->num_producers;

    while (not_finished) {
        for (int i = 0; i < args->num_producers; i++) {
            char *msg;
            if (!bb_try_remove(&args->producer_queues[i], &msg)) {
                continue;
            }
            if (!strcmp(msg, "DONE")) {
                not_finished--;
                continue;
            }
            Queue *q = which_queue(msg, 
                args->queue_S, args->queue_N, args->queue_W
            );
            ub_insert(q, msg);
        }
    }

    ub_insert(args->queue_S, "DONE");
    ub_insert(args->queue_N, "DONE");
    ub_insert(args->queue_W, "DONE");

    return NULL;
}
