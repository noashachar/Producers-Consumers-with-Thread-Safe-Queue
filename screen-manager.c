#include "screen-manager.h"
#include <stdio.h>
#include <string.h>

void* screen_manager_worker(void* ptr) {
    ScreenManagerArgs* args = ptr;

    int num_active_sources = 3;
    while (num_active_sources) {
        char *msg = bb_remove(args->queue);

        if (strcmp(msg, "DONE") == 0) {
            num_active_sources--;
        }
        else {
            printf("%s\n", msg);
            free(msg);
        }
    }

    printf("%s\n", "DONE");

    return NULL;
}

