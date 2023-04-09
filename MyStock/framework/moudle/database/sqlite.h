#ifndef __MYSQLITEDB
#define __MYSQLITEDB
#include <stdio.h>
#include <stdlib.h>
//#include <afxcoll.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "Cppsqlite3.h"
using namespace std;
class Sqlite
{
public:
	Sqlite(){}
	~Sqlite(){}
	void Open(string name);
	void Close();
	bool ExecDML(string sql);
	int ExecScalar(string sql);
	bool ExecQuery(string sql,vector<string> &fieldName,vector<string> &fieldValue);
	bool CreateTable(string tableName, vector<pair<string, string> > &fieldName);
	//bool CreateTable(string tableName,vector<string> &fieldName);
	bool DeleteTable(string tableName);
	bool InsertRow(string tableName,vector<string> &fieldName,vector<string> &fieldValue);
	bool UpdateRow(string tableName,string key,string keyValue,vector<string> &fieldName,vector<string> &fieldValue);
	bool UpdateRow2(string tableName, string key, string keyValue, string key2, string keyValue2,vector<string> &fieldName, vector<string> &fieldValue);	
	bool UpdateRow3(string tableName, string key, string keyValue, string key2, string keyValue2,string key3, string keyValue3,vector<string> &fieldName, vector<string> &fieldValue);
	bool UpdateRow4(string tableName, string key, string keyValue, string key2, string keyValue2,string key3, string keyValue3,string key4, string keyValue4,vector<string> &fieldName, vector<string> &fieldValue);
	bool DeleteRow(string tableName,string key,string keyValue);
	bool DeleteRow2(string tableName, string key, string keyValue,string key2, string keyValue2);
	bool DeleteRow3(string tableName, string key, string keyValue,string key2, string keyValue2,string key3, string keyValue3);	
	bool DeleteRow4(string tableName, string key, string keyValue,string key2, string keyValue2,string key3, string keyValue3,string key4, string keyValue4);
	bool IsTableExists(string tableName);
private:
	CppSQLite3DB m_db;
};

#endif
