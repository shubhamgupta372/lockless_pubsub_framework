#ifndef MUTEXCV_H_
#define MUTEXCV_H_

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <iostream>
#include <cstring>
using namespace std;

class Mutex{
public:
	Mutex()
	{
		//plock = PTHREAD_MUTEX_INITIALIZER;
		if (pthread_mutexattr_init(&attr) != 0) {
   			perror("pthread_mutexattr_init() error");
    		exit(1);
  		}
		if(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK) !=0){
			perror("pthread_mutexattr_settype() error");
    		exit(1);
		}
		if (pthread_mutex_init(&plock,&attr) != 0) {
   			perror("pthread_mutex_init() error");
    		exit(1);
  		}
	}
	virtual ~Mutex()
	{
		pthread_mutex_destroy(&plock);
	}
	int lock()
	{
		return pthread_mutex_lock(&plock);
	}
	int unlock()
	{
		return pthread_mutex_unlock(&plock);
	}
protected:
pthread_mutex_t plock;
pthread_mutexattr_t attr;
};

class LockCondwait: public Mutex{
public:
	int wait()
	{
		return pthread_cond_wait(&subCond,&plock);

	}
	int signal()
	{
		return pthread_cond_signal(&subCond);
	}
public:
	pthread_cond_t subCond;

};

#endif