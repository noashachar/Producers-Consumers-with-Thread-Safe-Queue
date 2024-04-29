#include "co-editor.h"
#include <stdbool.h>
#include <time.h>
#include <string.h>

// 100 million nanoseconds = 0.1 seconds
struct timespec tenth_second = { .tv_sec = 0, .tv_nsec = 100 * 1000000L };  

void sleep_for_tenth_second() {
    nanosleep(&tenth_second, (struct timespec *)NULL);
}

void* co_editor_worker(void* ptr) {
    CoEditorArgs *args = ptr;

    while (true) {
        char *msg = ub_remove(args->queue_in);
        
        if (strcmp(msg, "DONE") == 0) {
            bb_insert(args->queue_out, "DONE");
            break;
        }
        else {
            sleep_for_tenth_second();
            bb_insert(args->queue_out, msg);
        }
    }

    return NULL;
}

