#include "MysqlDB.h"
#include <iostream>
using namespace std ;

MysqlDB::MysqlDB(string host , string user , string pwd , string db , int port){
	pMysqlcon = mysql_init(NULL) ;
	if(pMysqlcon == NULL){
		//初始化错误
		cout << "Mysql初始化错误" << endl ;
		
	}

	bool res = InitMysql(host , user , pwd , db , port) ;
	if(!res){
		//链接错误
		cout << "Mysql链接错误" << endl ;
	}
	else{
		cout << "Mysql链接成功" << endl ;
	}
}

bool MysqlDB::InitMysql(string & host , string & user , string & pwd , string & db , int port) {
	pMysqlcon = mysql_real_connect(pMysqlcon , host.c_str() , 
			user.c_str() , pwd.c_str() , db.c_str() , port , NULL , 0) ;
	if(pMysqlcon == NULL){
		//链接错误
		return false ;
	}
	return true ;
}

bool MysqlDB::RollBack(){
	mysql_rollback(pMysqlcon) ;
	return true ;
}

bool MysqlDB::ExecSQL(string sql){
	if(mysql_query(pMysqlcon , sql.c_str())){
		//失败
		cout << "sql error " << endl ;
		return false ;	
	}
	else{
		//得到结果集合
		pResult = mysql_use_result(pMysqlcon) ;
		//得到结果次数
		for(unsigned i = 0 ; i < mysql_field_count(pMysqlcon) ; ++i){
			//每次取一行
			mRow = mysql_fetch_row(pResult);
			if(mRow <= 0){
				break ;
			}
			//得到这一行的字段数
			for(unsigned j = 0 ; j < mysql_num_fields(pResult) ; j++){
				cout << mRow[j] << " " ;
			}
			cout << endl ;
		}

	}
	mysql_free_result(pResult);
	return true ;
}

MysqlDB::~MysqlDB(){
	if(pMysqlcon != NULL){
		mysql_close(pMysqlcon) ;
	}
}


