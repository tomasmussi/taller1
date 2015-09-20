#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

class Thread {
private:
	pthread_t thread;
public:
	Thread();
	virtual ~Thread();
	static void* starter(void *data);
	void start();
	void join();
	virtual void run() = 0;
};

#endif /* THREAD_H_ */
