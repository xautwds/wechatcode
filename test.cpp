#include "MysqlDB.h"
#include <pthread.h>
#include <unistd.h>
#include <string>
#include "Locker.h"
#include <time.h>
#include <wait.h>
#include <sys/time.h>
#include <stdio.h>
using namespace std ;

cLocker lock ;
void *func(void * arg){
	MysqlDB * pmysql = (MysqlDB *)arg ;
	//pmysql->RollBack();
	for(int i = 200 ; i < 500 ; i++){
		string str("insert into students(id) values (") ;
		char ch[4] ;
		sprintf(ch , "%d" , i) ;
		str += string(ch) ;	
		str += ");";
		//lock.Lock();
		pmysql->ExecSQL(str);
		//lock.UnLock();
		cout << str.c_str() << endl ;
	}
	pmysql = NULL;
	return NULL ;
}

int main(){
	clock_t begin ,end ;
	begin = clock()	;
	
	MysqlDB myDB("127.0.0.1" ,"root" , "root" , "db");
//	MysqlDB myDB2("127.0.0.1" ,"root" , "root" , "db");

//	pthread_t pthread ;
//	pthread_create(&pthread , NULL , func , (void *)&myDB2);
	
	for(int i = 0 ; i < 10000 ; i++){

	//	string str("insert into students(id) values (") ;
	//	
	//	char ch[4] ;
	//	sprintf(ch , "%d" , i) ;
	//	str += string(ch) ;	
	//	
	//	str += ");";
	//	//lock.Lock();
	//	myDB.ExecSQL(str);
	//	//lock.UnLock();
	//	cout << str.c_str() << endl ;
		myDB.ExecSQL("select * from students where id < 10") ;
	}

	//wait(NULL) ;	
	end = clock() ;
	cout << "use1 : " << ((double)end - begin) / CLOCKS_PER_SEC << endl; 
	return 0;
}


/*#include "Redis.h"
#include <iostream>

using namespace std ;
int main(){
	Redis red("127.0.0.1" , 6379);
		
	redisReply * reply = red.RedisCommand("get key1");
	
	cout << "reply ans is " << reply->str << endl ;
	
	return 0;
}*/
