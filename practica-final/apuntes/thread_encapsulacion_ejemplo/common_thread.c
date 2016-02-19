#include "common_thread.h"

static void* starter(void* args) {
    thread_t* thread = (thread_t*)args;
    thread->run_func(thread->run_data);
    return NULL;	
}

void thread_create(thread_t *self, thread_run_func_t run_func, thread_run_data_t run_data) {
    self->run_func = run_func;
    self->run_data = run_data;
}

void thread_destroy(thread_t *self) {
}

void thread_start(thread_t *self) {
     pthread_create(&self->thread, NULL, starter, self);
}

void thread_join(thread_t *self) {
    pthread_join(self->thread, NULL);
}

