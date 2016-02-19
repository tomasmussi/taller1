#include "custom_tda.h"
#include <stdio.h>

void custom_tda_create(custom_tda_t* self, int processor_num, char* letters, int* current_index, mutex_t* mutex) {
    self->processor_num = processor_num;
    self->letters = letters;
    self->current_index = current_index;
    self->mutex = mutex;
}
void custom_tda_destroy(custom_tda_t* self) {

}

void custom_tda_run(void* data) {
    custom_tda_t* self = (custom_tda_t*)data;
    char keepPrinting = 1;

    while (keepPrinting) {
        mutex_lock(self->mutex);

        char letter = self->letters[*self->current_index];
        if (letter) {
            printf("[thread %d] Letter %c\n", self->processor_num, letter);
            ++(*self->current_index);
        }
        else {
            printf("[thread %d] String end detected\n", self->processor_num);
            keepPrinting = 0;
        }

        mutex_unlock(self->mutex);
    }
}


