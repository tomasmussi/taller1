#ifndef LOCK_H_
#define LOCK_H_

#include "common_Mutex.h"

class Lock {

private:
	Mutex *mutex;

public:
	Lock(Mutex *mutex);
	~Lock();
};

#endif /* LOCK_H_ */
