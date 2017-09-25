#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
	int sock_fd = socket(AF_INET , SOCK_STREAM , 0);
	struct sockaddr_in ser_addr;  
	      
	memset(&ser_addr, 0, sizeof(ser_addr));  
	ser_addr.sin_family = AF_INET;  
    inet_aton("127.0.0.1", (struct in_addr *)&ser_addr.sin_addr);  
	ser_addr.sin_port = htons(8888);

	sock_fd = socket(AF_INET, SOCK_STREAM, 0); 

	connect(sock_fd ,(struct sockaddr *) &ser_addr , sizeof(ser_addr)) ;	

	printf("connect success ....... \n") ;

	send(sock_fd , "1" , 1 , 0) ;
	send(sock_fd , "23" , 2 , 0) ;
	while(1){
		
	}
	
	return 0;
}
