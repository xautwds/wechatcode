#ifndef __LIBEVENT_H__
#define __LIBEVENT_H__

#include <event.h>

typedef void (*EventCallBack)(evutil_socket_t sockfd , short event_type , void * arg) ;
void do_accept(evutil_socket_t listener, short event, void *arg);
void read_cb(struct bufferevent *bev, void *arg);
void error_cb(struct bufferevent *bev, short event, void *arg);
void write_cb(struct bufferevent *bev, void *arg);

class Libevent{
public: 
	//创建event
	Libevent() ;

	//添加事件
	bool AddEvent(int fd , short flag , EventCallBack callback , void * arg) ;
	bool AddEndEvent(int fd , short flag , EventCallBack cb , void * arg) ;	
	
	//添加定时器 
	bool AddTimer() ;

	//事件运行
	bool EventRun() ;
	//析构event
	~Libevent() ;

private:
	struct event_base * pbase ;
};


#endif
