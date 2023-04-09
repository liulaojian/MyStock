#pragma once
#ifndef  SQLITE3
#define  SQLITE3

#include "sqlite\sqlite3.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//此类用来对查询结果进行相关的操作例如取得函数列数和对应行列的结果
class ResultInfo
{
	//private:
public:
	char **azResult;//用于存储查询结果
	int row;//查询结果的行数
	int col;//查询结果的列数

public:
	ResultInfo();
	~ResultInfo();
	//获得行数
	int getRowNum();
	//获得列数
	int getColNum();
	//获得结果数目
	int getResultNum();
	//获取对应行列的结果
	char *getAt(int row,int col);
	friend class SQLiteDB;//声明友元

};

//此类封装了对数据库的相关操作包括创建、查询和删除功能
class SQLiteDB
{

private:
	sqlite3* pDB;
	int flag;

public:

	//功能说明  :连接数据库。如果数据库已经存在，则打开现有数据库，如果不存在，则新创建一个数据库
	//参数说明  :string DBName 数据库名称
	//返回值说明:bool类型  true 数据库打开成功
	//                     false 数据库打开失败
	bool openDB(string DBName);

	//功能说明  :在指定的数据库中执行sql语句(非select语句!)
	//参数说明  :string sql 执行的sql语句
	//返回值说明:int类型 	-1 sql语句执行失败，同时输出错误信息
	//                      0 sql语句执行成功，返回结果
	int execute(string sql);

	//功能说明  :在指定的数据库中执行文件中的sql语句(文件中不能含有select语句!)
	//主要是在创建多个表 和 在批量插入数据的时候用
	//参数说明  :string sql 执行的sql语句
	//返回值说明:int类型 	-1 sql语句执行失败，同时输出错误信息
	//                      0 sql语句执行成功，返回结果
	int executeSQLFromFile(string fileName);

	//功能说明  :在指定的数据库中执行select的sql语句
	//参数说明  :string sql 执行的sql语句
	//返回值说明:Result类型 NULL sql语句执行失败，同时输出错误信息
	//                      rs   sql语句执行成功，返回Result类对象rs
	ResultInfo* executeSelect(string sql);	

	//功能说明   :关闭数据库。
	//参数说明   :void 无
	//返回值说明 :bool类型 true 数据库关闭成功
	//                     false 数据库关闭失败
	bool closeDB();
	~SQLiteDB();
};
#endif