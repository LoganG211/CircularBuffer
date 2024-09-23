#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../LoganLibrary.h"
#include "pthread.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <bits/pthreadtypes.h>

// Clang format // A-style

#define THREAD_COUNT 2

uint32_t input_value = 0;
pthread_barrier_t barrier;

pthread_mutex_t push_lock;
pthread_mutex_t pop_lock;

int rv;

cb_t cb = {
    .write_idx = 1,
    .read_idx = 1,
};

void *Push(void *arg)
{
    long tid;
    tid = (long)arg;

    while( !cb_is_full(&cb) ) {

        usleep(tid+500000);

        // uint32_t input_value = (uint32_t)(rand());
        uint32_t input_value = (uint32_t)(tid);
        pthread_mutex_lock(&push_lock);
        printf("    th-%ld, val-%d\n", tid, input_value);

        cb_push(&cb, input_value);
        cb_dump(&cb);
        pthread_mutex_unlock(&push_lock);

        printf("\n");
    }
    pthread_barrier_wait(&barrier); //wait for all threads

    printf("\nThread %ld: Beginning POPing\n", tid);

    uint32_t temp = 0;
    while( !cb_is_empty(&cb) ) {
        usleep(tid+500000);

        pthread_mutex_lock(&pop_lock);
        // cb_dump(&cb); // Gives buffer before POP
        cb_pop(&cb, &temp);
        cb_dump(&cb); // Gives new buffer
        printf("\n");
        pthread_mutex_unlock(&pop_lock);
    }
}

void *fill(void *arg)
{
    long tid;
    tid = (long)arg;

    for(int i=0; i<cb_size; i++){

        usleep(tid+500000);

        uint32_t input_value = (uint32_t)(tid);
        pthread_mutex_lock(&push_lock);
        // printf("    th-%ld, val-%d\n", tid, input_value);

        rv = cb_push(&cb, input_value);
        cb_dump(&cb);
        pthread_mutex_unlock(&push_lock);

        printf("\n");
    }
}

void test_threads()
{
    pthread_t threads[THREAD_COUNT];
    cb_init(&cb);

    for(long i=0; i<THREAD_COUNT; i++) {
        printf("\nIn main: creating thread %ld\n", i);
        int rc = pthread_create(&threads[i], NULL, Push, (void *)i);

        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    printf("\n");
    for(int i=0; i<THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_exit(NULL);
}

int full_fill()
{
    pthread_t threads[THREAD_COUNT];
    cb_init(&cb);

    for(long i=0; i<THREAD_COUNT; i++) {
        printf("\nIn main: creating thread %ld\n", i);
        int rc = pthread_create(&threads[i], NULL, fill, (void *)i);

        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    printf("\n");
    for(int i=0; i<THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_exit(NULL);
    return rv;
}

void test_push()
{
    pthread_t threads[THREAD_COUNT];
    cb_init(&cb);

    CU_ASSERT(full_fill() == 0);
    CU_ASSERT(over_fill() == 1);
}

void main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("add_test_suite", 0, 0);

    pthread_mutex_init(&push_lock, NULL);
    pthread_barrier_init(&barrier, NULL, THREAD_COUNT);
    pthread_mutex_init(&pop_lock, NULL);

    CU_add_test(suite, "test_threads", test_threads);
    CU_add_test(suite, "test_push", test_push);

    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&push_lock);
    pthread_mutex_destroy(&pop_lock);

    // CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    // for(long i=0; i<cb_size; i++){
    // printf("In main: creating thread %ld\n", i);
    // rc = pthread_create(&threads[i], NULL, Push, (void *)i);

    // input_value = (uint32_t)(rand());
    // printf("    %ld, %d\n", i, input_value);
    // cb_pop(circularBuffer, &write_idx, &read_idx);
    // cb_dump(circularBuffer, &write_idx, &read_idx);
    // printf("\n");

    // if (rc){
    //     printf("ERROR; return code from pthread_create() is %d\n", rc);
    //     exit(-1);
    // }
    // }
    // pthread_exit(NULL);

    // Single-thread example
    // cb_push(circularBuffer, &write_idx, &read_idx, input_value); // Works
    // cb_push(circularBuffer, &write_idx, &read_idx, input_value);
    // cb_dump(circularBuffer, &write_idx, &read_idx); // Works

    // Multi-thread example
    // pthread_t threads[cb_size];
    // int rc;
    // for(long i=0; i<cb_size; i++){
    //     printf("In main: creating thread %ld\n", i);
    //     rc = pthread_create(&threads[i], NULL, NULL, (void *)i);
    //     if (rc){
    //         printf("ERROR; return code from pthread_create() is %d\n", rc);
    //         exit(-1);
    //     }
    // }
    // pthread_exit(NULL);
}