#include "common_Mutex.h"
#include <stdlib.h>
#include <string.h>

Mutex::Mutex() {
	memset(&this->mutex, 0, sizeof(pthread_mutex_t));
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
