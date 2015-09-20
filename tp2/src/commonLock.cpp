#include "commonLock.h"

Lock::Lock(Mutex *mutex) {
	this->mutex = mutex;
	this->mutex->lock();
}

Lock::~Lock() {
	this->mutex->unlock();
}

