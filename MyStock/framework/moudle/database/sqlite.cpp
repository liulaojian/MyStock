#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

//#include <afxcoll.h>
#include "sqlite\sqlite3.h"
#include "sqlite.h"
#include "Cppsqlite3.h"
//#pragma comment(lib, "Sqlite3.lib")
#include <vector>
#include <map>
#include <string>
using namespace std;

void Sqlite::Open(string name)
{
    m_db.open(name.data());
}
void Sqlite::Close()
{
    m_db.close();
}
bool Sqlite::ExecDML(string sql)
{
    int ret = m_db.execDML(sql.data());
    if(ret < 0)return false;
    return true;
}
int Sqlite::ExecScalar(string sql)
{
    int ret = -1;
    try
    {
        ret = m_db.execScalar(sql.data());
    }
    catch(string ex)
    {
        return -1;
    }
    return ret;
}
bool Sqlite::ExecQuery(string sql, vector<string> &fieldName, vector<string> &fieldValue)
{
    //CStringArray fieldName;CStringArray rowValue;
    CppSQLite3Query q = m_db.execQuery(sql.data());
    fieldName.clear();
    fieldValue.clear();
    for(int i = 0; i < q.numFields(); i++)
    {
        fieldName.push_back(q.fieldName(i));
    }
    while(!q.eof())
    {
        for(int i = 0; i < q.numFields(); i++)
        {
            fieldValue.push_back(q.fieldValue(i));
        }
        q.nextRow();
    }
    return true;
}
bool Sqlite::CreateTable(string tableName, vector<pair<string, string> > &fieldName)
{
    string sql;
    if(m_db.tableExists(tableName.data()))return true;
    sql = string("create table ") + tableName + " (";
    if(fieldName.size() <= 0)return false;
    vector<pair<string, string> >::iterator it;
    for(it = fieldName.begin(); it != fieldName.end(); it++)
    {
        //sql+=(*it+" string,");
        sql += it->first + "  ";
        sql += it->second + " ,";
    }
    sql[sql.size() - 1] = ')';
    sql += ";";
    //  sql.Format("create table UserTable (domain string, ip string,port int,time string);");
    int ret = m_db.execDML(sql.data());
    if(ret < 0)return false;
    return true;
}
bool Sqlite::DeleteTable(string tableName)
{
    string sql;
    sql = string("drop table ") + tableName + ";";

    if(!m_db.tableExists(tableName.data()))return true;
    int ret = m_db.execDML(sql.data());
    if(ret < 0)return false;
    return true;
}

bool Sqlite::InsertRow(string tableName, vector<string> &fieldName, vector<string> &fieldValue)
{
//  sql.Format("insert into UserTable ('domain','ip','port','time') values('%s','%s',%d,'%s');",domain,ip,port,t1);
    string sql;
    sql = string("insert into ") + tableName + " (";
    if(fieldName.size() <= 0)return false;
    vector <string>::iterator it;
    for(it = fieldName.begin(); it != fieldName.end(); it++)
    {
        sql += ("'" + *it + "',");
    }
    sql[sql.size() - 1] = ')';
    sql += " values(";

    for(it = fieldValue.begin(); it != fieldValue.end(); it++)
    {
        sql += ("'" + *it + "',");
    }
    sql[sql.size() - 1] = ')';
    sql += ";";
    //printf("sql: %s\n", sql.data());
    int ret = m_db.execDML(sql.data());
    if(ret < 0)return false;
    return true;
}

bool Sqlite::UpdateRow(string tableName, string key, string keyValue, vector<string> &fieldName, vector<string> &fieldValue)
{
    string sql;
    if(fieldName.size() <= 0)return false;
    if(fieldName.size() != fieldValue.size())return false;
    sql = string("update ") + tableName + " set ";
    vector <string>::iterator it;
    vector <string>::iterator it1;
    it1 = fieldValue.begin();
    for(it = fieldName.begin(); it != fieldName.end(); it++)
    {
        sql += (*it + " = '" + *it1 + "',");
        it1++;
    }
    sql[sql.size() - 1] = ' ';
    if(key.data() && keyValue.data())
    {
        sql += (string("where ") + key + " = '" + keyValue + "'");
    }
    sql += ";";
    int ret = m_db.execDML(sql.data());
    if(ret < 0)return false;
    return true;
}

bool Sqlite::UpdateRow2(string tableName, string key, string keyValue, string key2, string keyValue2,vector<string> &fieldName, vector<string> &fieldValue)
{
    string sql;
    if(fieldName.size() <= 0)return false;
    if(fieldName.size() != fieldValue.size())return false;
    sql = string("update ") + tableName + " set ";
    vector <string>::iterator it;
    vector <string>::iterator it1;
    it1 = fieldValue.begin();
    for(it = fieldName.begin(); it != fieldName.end(); it++)
    {
        sql += (*it + " = '" + *it1 + "',");
        it1++;
    }
    sql[sql.size() - 1] = ' ';
    if(key.data() && keyValue.data())
    {
        sql += (string("where ") + key + " = '" + keyValue + "'"+" and "+key2+" = '"+keyValue2+ "'");
    }
    sql += ";";
    int ret = m_db.execDML(sql.data());
    if(ret < 0)return false;
    return true;
}

bool Sqlite::UpdateRow3(string tableName, string key, string keyValue, string key2, string keyValue2,string key3, string keyValue3,vector<string> &fieldName, vector<string> &fieldValue)
{
	string sql;
	if(fieldName.size() <= 0)return false;
	if(fieldName.size() != fieldValue.size())return false;
	sql = string("update ") + tableName + " set ";
	vector <string>::iterator it;
	vector <string>::iterator it1;
	it1 = fieldValue.begin();
	for(it = fieldName.begin(); it != fieldName.end(); it++)
	{
		sql += (*it + " = '" + *it1 + "',");
		it1++;
	}
	sql[sql.size() - 1] = ' ';
	if(key.data() && keyValue.data())
	{
		sql += (string("where ") + key + " = '" + keyValue + "'"+" and "+key2+" = '"+keyValue2+ "'"+" and "+key3+" = '"+keyValue3+ "'");
	}
	sql += ";";
	int ret = m_db.execDML(sql.data());
	if(ret < 0)return false;
	return true;
}

bool Sqlite::UpdateRow4(string tableName, string key, string keyValue, string key2, string keyValue2,string key3, string keyValue3,string key4, string keyValue4,vector<string> &fieldName, vector<string> &fieldValue)
{
	string sql;
	if(fieldName.size() <= 0)return false;
	if(fieldName.size() != fieldValue.size())return false;
	sql = string("update ") + tableName + " set ";
	vector <string>::iterator it;
	vector <string>::iterator it1;
	it1 = fieldValue.begin();
	for(it = fieldName.begin(); it != fieldName.end(); it++)
	{
		sql += (*it + " = '" + *it1 + "',");
		it1++;
	}
	sql[sql.size() - 1] = ' ';
	if(key.data() && keyValue.data())
	{
		sql += (string("where ") + key + " = '" + keyValue + "'"+" and "+key2+" = '"+keyValue2+ "'"+" and "+key3+" = '"+keyValue3+ "'"+" and "+key4+" = '"+keyValue4+ "'");
	}
	sql += ";";
	int ret = m_db.execDML(sql.data());
	if(ret < 0)return false;
	return true;
}

bool Sqlite::DeleteRow(string tableName, string key, string keyValue)
{
    //      sql.Format("delete from UserTable where domain='%s';",domain);
    string sql;
    sql = string("delete from ") + tableName + " ";
    if(key.data() && keyValue.data())
    {
        sql += (string("where ") + key + " = '" + keyValue + "'");
    }
    sql += ";";
    int ret = m_db.execDML(sql.data());
    if(ret < 0)return false;
    return true;
}


bool Sqlite::DeleteRow2(string tableName, string key, string keyValue,string key2, string keyValue2)
{
    //      sql.Format("delete from UserTable where domain='%s';",domain);
    string sql;
    sql = string("delete from ") + tableName + " ";
    if(key.data() && keyValue.data())
    {
        sql += (string("where ") + key + " = '" + keyValue + "'"+" and "+key2+" = '"+keyValue2+ "'");
    }
    sql += ";";
    int ret = m_db.execDML(sql.data());
    if(ret < 0)return false;
    return true;
}

bool Sqlite::DeleteRow3(string tableName, string key, string keyValue,string key2, string keyValue2,string key3, string keyValue3)
{
    //      sql.Format("delete from UserTable where domain='%s';",domain);
    string sql;
    sql = string("delete from ") + tableName + " ";
    if(key.data() && keyValue.data())
    {
        sql += (string("where ") + key + " = '" + keyValue + "'"+" and "+key2+" = '"+keyValue2+ "'" +" and " +key3+" = '"+keyValue3+ "'");
    }
    sql += ";";
    int ret = m_db.execDML(sql.data());
    if(ret < 0)return false;
    return true;
}

bool Sqlite::DeleteRow4(string tableName, string key, string keyValue,string key2, string keyValue2,string key3, string keyValue3,string key4, string keyValue4)
{
	string sql;
    sql = string("delete from ") + tableName + " ";
    if(key.data() && keyValue.data())
    {
        sql += (string("where ") + key + " = '" + keyValue + "'"+" and "+key2+" = '"+keyValue2+ "'" +" and " +key3+" = '"+keyValue3+ "'"+" and " +key4+" = '"+keyValue4+ "'");
    }
    sql += ";";
    int ret = m_db.execDML(sql.data());
    if(ret < 0)return false;
    return true;


}



bool Sqlite::IsTableExists(string tableName)
{
    return m_db.tableExists(tableName.c_str());
}

