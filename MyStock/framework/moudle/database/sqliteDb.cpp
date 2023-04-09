/*
* Copyright (c) 2007,10#507
* All rights reserved.
* 
* 文件名称：sqliteDB.c
* 摘    要：sqlite3数据库操作封装类
* 
* 当前版本：1.0
* 完成日期：2007年11月26日
*/
#include "stdafx.h"
#include "SQLiteDB.h"
//把数组的长度设为2048，使sql语句的长度有更大的灵活性
char tmp[2048];  //因为sqlite3的参数为char*型所以我们需要一个数组来存放string型的数据
ResultInfo* former_r=NULL;
//是否打印调试信息 调试的时候可以把ON置为1
#define ON 0
#define PRINTMSG if(ON){
#define PRINTED  }


ResultInfo::ResultInfo()
{
	//PRINTMSG 
    //    fuckdebug(L"construct azResult [%s]",CString(*this->azResult));
	//cout<<"construct azResult"<<this->azResult<<endl;
	//PRINTED
}

ResultInfo::~ResultInfo()
{
	//PRINTMSG
     //   fuckdebug(L"executing 析构 for Result release [%s]",CString(*this->azResult));
	//cout<<"executing 析构 for Result release "<<azResult<<endl;
	//PRINTED
}

//功能说明  :连接数据库。如果数据库已经存在，则打开现有数据库，如果不存在，则新创建一个数据库
//参数说明  :string DBName 数据库名称
//返回值说明:bool类型  true 数据库打开成功
//                     false 数据库打开失败
bool SQLiteDB::openDB(string DBName)
{
	flag=0;
	memset(tmp,0,sizeof(tmp));
	strcpy(tmp,DBName.c_str());
	return ::sqlite3_open(tmp,&pDB)==SQLITE_OK;
}

//功能说明  :在指定的数据库中执行文件中的sql语句（文件中不能含有select语句!）
//参数说明  :string sql 执行的sql语句
//返回值说明:int类型 	-1 sql语句执行失败，同时输出错误信息
//                      0 sql语句执行成功，返回结果

int SQLiteDB::execute(string sql)
{
		char errMsg[100]("");
		memset(tmp,0,sizeof(tmp));
		strcpy(tmp,sql.c_str());
		::sqlite3_exec(pDB,tmp,0,0,(char **)&errMsg);
		if(strlen(errMsg)!=0)
		{
			//PRINTMSG
            //fuckdebug(L"[%s]",errMsg);
			//cout<<errMsg<<endl;
			//PRINTED
			return -1;
		}
		else 
			return 0;
}

//功能说明  :在指定的数据库中执行select的sql语句
//参数说明  :string sql 执行的sql语句
//返回值说明:Result类型 NULL sql语句执行失败，同时输出错误信息
//                      rs   sql语句执行成功，返回Result类对象rs
/*
int sqlite3_get_table(
  sqlite3*,               An open database 
  const char *sql,        SQL to be executed 
  char ***resultp,        Result written to a char *[]  that this points to 
  int *nrow,              Number of result rows written here 
  int *ncolumn,           Number of result columns written here 
  char **errmsg           Error msg written here 
);
*/
ResultInfo* SQLiteDB::executeSelect(string sql)
{
	char errMsg[128]("");
	memset(tmp,0,sizeof(tmp));
	strcpy(tmp,sql.c_str());//把 string转化为char*
	if (former_r!=NULL)
	{
        delete former_r;
        former_r=NULL;
	}
	ResultInfo *rs = new ResultInfo();
	::sqlite3_get_table(pDB,tmp,&rs->azResult,&rs->row,&rs->col,(char **)&errMsg);
	former_r = rs;
	if(strlen(errMsg)!=0)
	{
		//PRINTMSG
         //   fuckdebug(L"[%s]",errMsg);
		//PRINTED
		return NULL;
	}

	else
		return rs;
}

//功能说明   :关闭数据库。
//参数说明   :void 无
//返回值说明 :bool类型 true 数据库关闭成功
//                     false 数据库关闭失败
bool SQLiteDB::closeDB()
{
	flag=1;
    if(former_r!=NULL){delete former_r;}
	return sqlite3_close(pDB)!=SQLITE_BUSY;
}
//功能说明   :取得结果行数。
//参数说明   :void 无
//返回值说明 :int类型 
int ResultInfo::getResultNum()
{
	return row;
}

//功能说明   :取得指定的行列值。
//参数说明   :int型
//返回值说明 :char类型
char *ResultInfo::getAt(int arow,int acol)
{
	if(arow<=row+1&&acol<=col)
	return azResult[arow*col+acol];
	else return NULL;
}

int ResultInfo::getRowNum()
{
	return row+1;
}

int ResultInfo::getColNum()
{
	return col;
}


//功能说明  :在指定的数据库中执行文件中的sql语句(文件中不能含有select语句!)
//参数说明  :string sql 执行的sql语句
//返回值说明:int类型 	-1 sql语句执行失败，同时输出错误信息
//                      0 sql语句执行成功，返回结果
int SQLiteDB::executeSQLFromFile(string fileName)
{
	ifstream f;
	memset(tmp,0,sizeof(tmp));
	strcpy(tmp,fileName.c_str());
	f.open(tmp);
	string sql("");
	//打开的SQL脚本文件最大不超过65536个字符
	char temp[65536]("");
	while(!f.eof())
	{	
		sql+=temp;
		f.getline(temp,10000);
		
	}
	char errMsg[100];
	::sqlite3_exec(pDB,sql.c_str(),0,0,(char **)&errMsg);
	if(strlen(errMsg)!=0)
	{
		//cout<<errMsg<<endl;
		return -1;
	}
	else 
		return 0;
}

SQLiteDB::~SQLiteDB()
{
	//如果数据库没有关闭，就将其关闭
	if(flag==0)
		this->closeDB();
}
