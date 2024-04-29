#include "producer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static char *cat_name[] = { "SPORTS", "NEWS", "WEATHER" };

void* producer_worker(void* ptr) {
    ProducerArgs* args = ptr;

    int num_produced[3] = { 0, 0, 0 };

    for (int i = 0; i < args->num_products; i++) {
        int category = rand() % 3;

        char temp_msg[128];
        sprintf(temp_msg, 
            "Producer %d %s %d", 
            args->id, cat_name[category], num_produced[category]
        );

        char* msg = strdup(temp_msg);
        bb_insert(args->q, msg);

        num_produced[category]++;
    }

    bb_insert(args->q, "DONE");

    return NULL;
}
