#ifndef __MYSQLDB_H__
#define __MYSQLDB_H__
#include <mysql/mysql.h>
#include <iostream>
#include <string>
using namespace std ;


class MysqlDB{
public:
	//Mysql构造
	MysqlDB(string host , string user , string pwd , string db , int port = 0);
	~MysqlDB();

	//初始化链接
	bool InitMysql(string &host , string &user , string &pwd , string &db , int port = 0) ;

	bool RollBack();
	//执行SQL语句
	bool ExecSQL(string sql) ;

private:
	MYSQL * pMysqlcon ;
	MYSQL_RES * pResult ;
	MYSQL_ROW mRow ;
} ;

#endif
