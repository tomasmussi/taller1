#include "common_Thread.h"
#include <string.h>

Thread::Thread() {
	memset(&this->thread, 0, sizeof(pthread_t));
}

Thread::~Thread() {
}

void* Thread::starter(void *data){
	((Thread*)data)->run();
	return NULL;
}

void Thread::start(){
	pthread_create(& this->thread, NULL, Thread::starter, (void*) this);
}

void Thread::join(){
	pthread_join(this->thread, NULL);
}
