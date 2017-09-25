#include "Socket.h"

Socket::Socket(string ip, int port){
		
	mlistenfd =  socket(AF_INET , SOCK_STREAM ,0 );
	
	struct sockaddr_in hostAddr ; 
	memset((void *)&hostAddr , 0 , sizeof(hostAddr));
	hostAddr.sin_family = AF_INET ;

	hostAddr.sin_port = htons(port) ;
	inet_pton(AF_INET , ip.c_str() , &hostAddr.sin_addr);

	
	int res = bind(mlistenfd, (struct sockaddr *)&hostAddr , sizeof(hostAddr));
	if(res == -1){
		//错误
	}
	
	res = listen(mlistenfd , 5) ;	
	if(res == -1){
		//错误
	}
}

int Socket::GetListenFD(){
	return mlistenfd ;
}

Socket::~Socket(){
	close(mlistenfd);
}
