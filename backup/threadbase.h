#ifndef THREADBASE_H_
#define THREADBASE_H_

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <iostream>
#include <cstring>
using namespace std;

class ThreadBase {
public: 
	/*	Description		- Default constructor.
	 */
	ThreadBase() : m_ThreadHandle (0) {
		m_ThreadName[0] = 0 ;
		pthread_attr_init(&m_ThreadAttribute);
	}
	virtual ~ThreadBase() {
		pthread_attr_destroy(&m_ThreadAttribute);
	}
	char* GetThreadName() {
		return m_ThreadName;
	}

	bool Start(const char* thread_name) {
		int err = pthread_create(&m_ThreadHandle, &m_ThreadAttribute, &Dispatch, this);
		
		// err will contain error code in case thread is not created
		if (err) {
			std::cerr << "BaseThread: failed to Start." << std::endl;
			if(err == EINVAL){
				cout<<"Error Details: In valid thread attributes \n";
			}
			else if(err == EAGAIN){
				cout<<"Error Details: Insufficient resources to create another thread or Limit on no of threads encounterted \n";
			}
			else if(err == EDEADLK){
				cout<<"Error Details: Deadlock \n";
			}
			else if(err == ESRCH){
				cout<<"Error Details: No such thread id \n";
			}
			return false;
		}
		//Give it a name 
		strcpy(m_ThreadName,thread_name);
		//std::cout<<"in "<<this->GetThreadName()<< " Start \n";
		return true;
	}

	virtual void OnRun() {
		std::cout << GetThreadName() <<" says: Hello" << std::endl;
	}

	virtual void Run() {
		OnRun();

	}

	void Join()
	{
		void * ret;
		if(pthread_join(m_ThreadHandle, &ret)!=0){
			std::cout<<"Cannot join threads, Error \n";
		}
	}

private:
	pthread_t 			m_ThreadHandle;
	/*	Description		- Handle the POSIX thread's attributes.
	 */
	pthread_attr_t     	m_ThreadAttribute;
	/*	Description		- Storing the thread's name.
	 */
	char 				m_ThreadName[64];
	/*	Description		- Helper function to start the thread.
	 */
	static
	void *Dispatch(void *arg) {
		ThreadBase *pThread(static_cast<ThreadBase *>(arg));
		//std::cout<<"in "<<pThread->GetThreadName()<< " Dispatch \n";
		pThread->Run();
		return NULL;
	}
};

#endif /* THREADBASE_H_ */
