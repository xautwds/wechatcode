#include "Libevent.h"
#include "Socket.h"
#include <iostream>
using namespace std ;

int main(){
	Socket sock("127.0.0.1" , 8888) ;
	Libevent lib;
	int fd = sock.GetListenFD();
	
	lib.AddEvent(fd ,EV_READ | EV_PERSIST ,do_accept , NULL) ; 
	lib.EventRun();
	
	return 0; 
}
