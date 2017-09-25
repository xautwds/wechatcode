#ifndef LOCKER_H
#define LOCKER_H 

#include <pthread.h>
#include <semaphore.h>
#include <iostream>

using namespace std ;
class cSem{
public:
	cSem(){
		if(sem_init(&m_sem , 0 , 0) != 0){
			exit(1);
		}	
	}
	~cSem(){
		//sem_destory(&m_sem);
	}

	//信号量加1
	bool Post(){
		return 0 == sem_post(&m_sem);
	}
	//信号量减1
	bool Wait(){
		return 0 == sem_wait(&m_sem);
	}
private:
	sem_t m_sem ;
};

class cLocker{
public:
	cLocker(){
		if(pthread_mutex_init(&m_mutex , NULL) != 0){
			exit(1);
		}
	}
	~cLocker(){
		//pthread_mutex_destory(&m_mutex);
	}

	//定义加锁操作
	bool Lock(){
		return 0 == pthread_mutex_lock(&m_mutex);
	}
	//定义解锁操作
	bool UnLock(){
		return 0 == pthread_mutex_unlock(&m_mutex);
	}
private:
	pthread_mutex_t m_mutex ;
};

class cCond{
public:
	cCond(){
		if(pthread_mutex_init(&m_mutex , 0 ) != 0){
			exit(1);
		}
		if(pthread_cond_init(&m_cond , 0) != 0){
			//pthread_mutex_destory(&m_mutex);
			exit(1);
		}
	}
	~cCond(){
		//pthread_mutex_destory(&m_mutex);
		//pthread_cond_destory(&m_cond);
	}
	//等待条件变量
	bool Wait(){
		int ret = 0 ;
		pthread_mutex_lock(&m_mutex);
		ret = pthread_cond_wait(&m_cond , &m_mutex);
		pthread_mutex_unlock(&m_mutex);
		return ret == 0;	
	}
	//唤醒等待条件变量的线程
	bool Signal(){
		return 0 == pthread_cond_signal(&m_cond);
	}

private:
	pthread_mutex_t m_mutex;
	pthread_cond_t m_cond;
};

#endif
