#include "common_mutex.h"

void mutex_create(mutex_t* self) {
	pthread_mutex_init(& self->mutex, NULL);	
}

void mutex_destroy(mutex_t* self) {
	pthread_mutex_destroy(&self->mutex);
}

void mutex_lock(mutex_t* self) {
	pthread_mutex_lock(&self->mutex);
}

void mutex_unlock(mutex_t* self) {
	pthread_mutex_unlock(&self->mutex);
}

