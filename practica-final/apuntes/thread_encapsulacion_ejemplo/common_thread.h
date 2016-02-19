#ifndef THREAD__H
#define THREAD__H

#include <pthread.h>

typedef void* thread_run_data_t;
typedef void (*thread_run_func_t)(thread_run_data_t run_data);

typedef struct {
    pthread_t thread;
    thread_run_func_t run_func;
    thread_run_data_t run_data;
} thread_t;

void thread_create(thread_t *self, thread_run_func_t run_func, thread_run_data_t run_data);
void thread_destroy(thread_t *self);
void thread_start(thread_t *self);
void thread_join(thread_t *self);

#endif

