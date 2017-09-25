#include "Redis.h"

Redis::Redis(string ip , int port){
	this->p_con = RedisConnect(ip , port) ;
	if(p_con == NULL){
		//日志操作
	}
}

Redis::~Redis(){
	if(p_con != NULL){
		RedisFree();
	}	
}

redisContext * Redis::RedisConnect(string ip , int port){
	return redisConnect(ip.c_str() , port) ;
}

void Redis::RedisFree(){
	redisFree(p_con);
}

redisReply * Redis::RedisCommand(string str) {
	//命令结果先要进行判断处理
	//如果正确命令返回
	//否则写入日志返回NULL
	return (redisReply * )redisCommand(p_con , str.c_str());
}

redisReply * Redis::RedisCommand(string str , string val) {
	return (redisReply * )redisCommand(p_con , str.c_str() , val.c_str());
}

void Redis:: ReplyFree(redisReply * reply){
	freeReplyObject(reply) ;
}

redisContext * Redis::GetRedisCon(){
	return p_con ;
}
