#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <memory.h>
#include <arpa/inet.h>
#include <string>

using namespace std ;
class Socket{
public:

	//创建socket
	Socket(string ip , int port) ;

	//返回socketfd
	int GetListenFD();
	
	~Socket();

private:
	int mlistenfd ;
} ;


#endif
