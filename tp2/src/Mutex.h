#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

class Mutex {
private:
	pthread_mutex_t mutex;
public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();
};

#endif /* MUTEX_H_ */
