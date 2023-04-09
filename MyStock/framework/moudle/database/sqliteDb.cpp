/*
* Copyright (c) 2007,10#507
* All rights reserved.
* 
* �ļ����ƣ�sqliteDB.c
* ժ    Ҫ��sqlite3���ݿ������װ��
* 
* ��ǰ�汾��1.0
* ������ڣ�2007��11��26��
*/
#include "stdafx.h"
#include "SQLiteDB.h"
//������ĳ�����Ϊ2048��ʹsql���ĳ����и���������
char tmp[2048];  //��Ϊsqlite3�Ĳ���Ϊchar*������������Ҫһ�����������string�͵�����
ResultInfo* former_r=NULL;
//�Ƿ��ӡ������Ϣ ���Ե�ʱ����԰�ON��Ϊ1
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
     //   fuckdebug(L"executing ���� for Result release [%s]",CString(*this->azResult));
	//cout<<"executing ���� for Result release "<<azResult<<endl;
	//PRINTED
}

//����˵��  :�������ݿ⡣������ݿ��Ѿ����ڣ�����������ݿ⣬��������ڣ����´���һ�����ݿ�
//����˵��  :string DBName ���ݿ�����
//����ֵ˵��:bool����  true ���ݿ�򿪳ɹ�
//                     false ���ݿ��ʧ��
bool SQLiteDB::openDB(string DBName)
{
	flag=0;
	memset(tmp,0,sizeof(tmp));
	strcpy(tmp,DBName.c_str());
	return ::sqlite3_open(tmp,&pDB)==SQLITE_OK;
}

//����˵��  :��ָ�������ݿ���ִ���ļ��е�sql��䣨�ļ��в��ܺ���select���!��
//����˵��  :string sql ִ�е�sql���
//����ֵ˵��:int���� 	-1 sql���ִ��ʧ�ܣ�ͬʱ���������Ϣ
//                      0 sql���ִ�гɹ������ؽ��

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

//����˵��  :��ָ�������ݿ���ִ��select��sql���
//����˵��  :string sql ִ�е�sql���
//����ֵ˵��:Result���� NULL sql���ִ��ʧ�ܣ�ͬʱ���������Ϣ
//                      rs   sql���ִ�гɹ�������Result�����rs
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
	strcpy(tmp,sql.c_str());//�� stringת��Ϊchar*
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

//����˵��   :�ر����ݿ⡣
//����˵��   :void ��
//����ֵ˵�� :bool���� true ���ݿ�رճɹ�
//                     false ���ݿ�ر�ʧ��
bool SQLiteDB::closeDB()
{
	flag=1;
    if(former_r!=NULL){delete former_r;}
	return sqlite3_close(pDB)!=SQLITE_BUSY;
}
//����˵��   :ȡ�ý��������
//����˵��   :void ��
//����ֵ˵�� :int���� 
int ResultInfo::getResultNum()
{
	return row;
}

//����˵��   :ȡ��ָ��������ֵ��
//����˵��   :int��
//����ֵ˵�� :char����
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


//����˵��  :��ָ�������ݿ���ִ���ļ��е�sql���(�ļ��в��ܺ���select���!)
//����˵��  :string sql ִ�е�sql���
//����ֵ˵��:int���� 	-1 sql���ִ��ʧ�ܣ�ͬʱ���������Ϣ
//                      0 sql���ִ�гɹ������ؽ��
int SQLiteDB::executeSQLFromFile(string fileName)
{
	ifstream f;
	memset(tmp,0,sizeof(tmp));
	strcpy(tmp,fileName.c_str());
	f.open(tmp);
	string sql("");
	//�򿪵�SQL�ű��ļ���󲻳���65536���ַ�
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
	//������ݿ�û�йرգ��ͽ���ر�
	if(flag==0)
		this->closeDB();
}
