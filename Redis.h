#ifndef __REDIS_H__
#define __REDIS_H__
#include <hiredis/hiredis.h>
#include <string>

using namespace std ;

class Redis{
public:
	Redis(string ip , int port) ;
	~Redis() ;

	//对数据进行操作
	redisReply * RedisCommand(string str) ; 
	redisReply * RedisCommand(string str , string val) ;	
	
	void ReplyFree(redisReply * reply) ;

	//释放链接的redis服务器空间
	void RedisFree() ;

	//得到rediscon
	redisContext * GetRedisCon() ; 

private:
	//链接redis服务器
	redisContext * RedisConnect(string ip , int port) ;

	redisContext * p_con ; 
};
#endif
