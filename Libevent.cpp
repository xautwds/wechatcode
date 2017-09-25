#include "Libevent.h"
#include <iostream>

using namespace std ;
//构造event_base	
Libevent::Libevent(){
	pbase = event_base_new() ;
	if(pbase == NULL){
		//创建失败
	}
}

bool Libevent::AddEvent(int fd , short flag , EventCallBack cb , void * arg){
	struct event * newevent ;
	if(arg == NULL){
		newevent = event_new(pbase , fd , flag , cb , (void *) pbase) ;
	}
	else{
		newevent = event_new(pbase , fd , flag , cb , arg) ;	
	}

	if(newevent == NULL){
		//错误
		return false ;
	}
	
	event_add(newevent , NULL) ;
	cout << "event add success " << fd << endl ;
	
	return true ;
}

bool Libevent::EventRun(){
	int res = event_base_dispatch(pbase) ;
	if(res == -1){
		return false ;
	}	
	return true ;
}

Libevent::~Libevent(){
	
}


void do_accept(evutil_socket_t listener, short , void *arg)
{
	struct event_base *base = (struct event_base *)arg;
	
	evutil_socket_t fd;
	struct sockaddr_in sin;
    socklen_t slen;
	fd = accept(listener, (struct sockaddr *)&sin, &slen);
	
	if (fd < 0) {
   		 perror("accept");
	     return;
	}
	if (fd > FD_SETSIZE) {
        perror("fd > FD_SETSIZE\n");
		return ;
	}

    printf("ACCEPT: fd = %u\n", fd);
	
	struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, read_cb, NULL, error_cb, arg);
	bufferevent_enable(bev, EV_READ|EV_WRITE|EV_PERSIST);
}

void read_cb(struct bufferevent *bev, void *arg)
{
	#define MAX_LINE    256
    char line[MAX_LINE+1];
	int n;
	evutil_socket_t fd = bufferevent_getfd(bev);
   	while (n = bufferevent_read(bev, line, MAX_LINE), n > 0) {
		
		//添加逻辑
		arg = NULL ;  //
		line[n] = '\0';
	    printf("fd=%u, read line: %s\n", fd, line);
		bufferevent_write(bev, line, n);
	}
}

void write_cb(struct bufferevent *bev, void *arg) {
	//一般不需要直接调用这个
	bev = NULL ;
	arg = NULL ;
}

void error_cb(struct bufferevent *bev, short event, void *arg)
{
    evutil_socket_t fd = bufferevent_getfd(bev);
	printf("fd = %u, ", fd);
	arg = NULL ;  //一般不需要这个
	if (event & BEV_EVENT_TIMEOUT) {
		printf("Timed out\n"); //if bufferevent_set_timeouts() called
	 }
	else if (event & BEV_EVENT_EOF) {
		printf("connection closed\n");
	}
    else if (event & BEV_EVENT_ERROR) {
	    printf("some other error\n");
	}
	bufferevent_free(bev);
}
