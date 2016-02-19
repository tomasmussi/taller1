#include "common_thread.h"
#include "common_mutex.h"

typedef struct {
    int processor_num;
    char* letters;
    int* current_index;
    mutex_t* mutex;
} custom_tda_t;


void custom_tda_create(custom_tda_t* self, int processor_num, char* letters, int* current_index, mutex_t* mutex);
void custom_tda_destroy(custom_tda_t* self);
void custom_tda_run(void* data);

