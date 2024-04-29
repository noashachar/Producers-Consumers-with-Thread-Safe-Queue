#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "producer.h"
#include "bounded-buffer.h"
#include "dispatcher.h"
#include "read-config.h"
#include "co-editor.h"
#include "screen-manager.h"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <config-file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL)); // seed = time()

    // read numbers from config file

    char* conf_path = argv[1];

    int num_conf_numbers;
    int *conf_numbers = find_numbers(conf_path, &num_conf_numbers);

    if (conf_numbers == NULL) {
        fprintf(stderr, "could not read conf-file\n");
        exit(EXIT_FAILURE);
    }

    if (num_conf_numbers % 3 != 1) {
        fprintf(stderr, "invalid conf-file\n");
        exit(EXIT_FAILURE);
    }

    int num_producers = num_conf_numbers / 3;
    int *next_conf_num = conf_numbers;

    // get our producers ready

    BoundedBuffer *prod_queues = malloc(sizeof(BoundedBuffer) * num_producers);
    ProducerArgs *prod_args = malloc(sizeof(ProducerArgs) * num_producers);
    pthread_t *prod_threads = malloc(sizeof(pthread_t) * num_producers);

    for (int i = 0; i < num_producers; i++) {

        int id              = *next_conf_num++;
        int num_products    = *next_conf_num++;
        int queue_size      = *next_conf_num++;

        bb_init(&prod_queues[i], queue_size);
        prod_args[i] = (ProducerArgs) { id, num_products, &prod_queues[i] };
    }

    // get our dispatcher ready

    UnboundedBuffer queue_S;
    UnboundedBuffer queue_N;
    UnboundedBuffer queue_W;
    DispatcherArgs dispatcher_args = { num_producers, prod_queues, &queue_S, &queue_N, &queue_W };

    ub_init(&queue_S);
    ub_init(&queue_N);
    ub_init(&queue_W);
    pthread_t dispatcher_thread;

    // get our co-editors ready

    int co_editors_queue_size = *next_conf_num++;
    BoundedBuffer co_editors_queue;
    bb_init(&co_editors_queue, co_editors_queue_size);

    pthread_t co_editor_S_thread;
    pthread_t co_editor_N_thread;
    pthread_t co_editor_W_thread;

    CoEditorArgs co_editor_S_args = { &queue_S, &co_editors_queue };
    CoEditorArgs co_editor_N_args = { &queue_N, &co_editors_queue };
    CoEditorArgs co_editor_W_args = { &queue_W, &co_editors_queue };

    // get our screen manager ready

    pthread_t screen_manager_thread;
    ScreenManagerArgs screen_manager_args = { &co_editors_queue };

    // fire all threads

    for (int i = 0; i < num_producers; i++) {
        pthread_create(&prod_threads[i], NULL, producer_worker, (void*) &prod_args[i]);
    }

    pthread_create(&dispatcher_thread, NULL, dispatcher_worker, (void*) &dispatcher_args);

    pthread_create(&co_editor_S_thread, NULL, co_editor_worker, (void*) &co_editor_S_args);
    pthread_create(&co_editor_N_thread, NULL, co_editor_worker, (void*) &co_editor_N_args);
    pthread_create(&co_editor_W_thread, NULL, co_editor_worker, (void*) &co_editor_W_args);

    pthread_create(&screen_manager_thread, NULL, screen_manager_worker, (void*) &screen_manager_args);

    // join all threads

    for (int i = 0; i < num_producers; i++) {
        pthread_join(prod_threads[i], NULL);
    }

    pthread_join(dispatcher_thread, NULL);

    pthread_join(co_editor_S_thread, NULL);
    pthread_join(co_editor_N_thread, NULL);
    pthread_join(co_editor_W_thread, NULL);

    pthread_join(screen_manager_thread, NULL);

    // destroy all queues

    for (int i = 0; i < num_producers; i++) {
        bb_destroy(&prod_queues[i]);
    }

    ub_destroy(&queue_S);
    ub_destroy(&queue_N);
    ub_destroy(&queue_W);

    bb_destroy(&co_editors_queue);

    // free heap

    free(conf_numbers);

    free(prod_queues);
    free(prod_args);
    free(prod_threads);

    return 0;
}