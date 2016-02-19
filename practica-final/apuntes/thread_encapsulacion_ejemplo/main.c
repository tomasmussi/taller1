#include "common_thread.h"
#include "common_mutex.h"
#include "custom_tda.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    char* letters = "abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789";
    int current_index = 0;

    custom_tda_t tda1, tda2;
    mutex_t mutex;
    thread_t processor1, processor2;

    mutex_create(&mutex);

    custom_tda_create(&tda1, 1, letters, &current_index, &mutex);
    custom_tda_create(&tda2, 2, letters, &current_index, &mutex);

    thread_create(&processor1, custom_tda_run, (thread_run_data_t) &tda1);
    thread_create(&processor2, custom_tda_run, (thread_run_data_t) &tda2);

    thread_start(&processor1);
    thread_start(&processor2);

    thread_join(&processor1);
    thread_join(&processor2);

    custom_tda_destroy(&tda1);
    custom_tda_destroy(&tda2);

    thread_destroy(&processor1);
    thread_destroy(&processor2);

    return 0;
}

