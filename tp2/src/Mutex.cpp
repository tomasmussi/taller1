#include "Mutex.h"
#include <stdlib.h>

Mutex::Mutex() {
	pthread_mutex_init(&this->mutex, NULL);
}

Mutex::~Mutex() {
	pthread_mutex_destroy(&this->mutex);
}

void Mutex::lock(){
	pthread_mutex_lock(&this->mutex);
}

void Mutex::unlock(){
	pthread_mutex_unlock(&this->mutex);
}
