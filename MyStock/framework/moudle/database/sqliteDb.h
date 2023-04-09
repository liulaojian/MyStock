#pragma once
#ifndef  SQLITE3
#define  SQLITE3

#include "sqlite\sqlite3.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//���������Բ�ѯ���������صĲ�������ȡ�ú��������Ͷ�Ӧ���еĽ��
class ResultInfo
{
	//private:
public:
	char **azResult;//���ڴ洢��ѯ���
	int row;//��ѯ���������
	int col;//��ѯ���������

public:
	ResultInfo();
	~ResultInfo();
	//�������
	int getRowNum();
	//�������
	int getColNum();
	//��ý����Ŀ
	int getResultNum();
	//��ȡ��Ӧ���еĽ��
	char *getAt(int row,int col);
	friend class SQLiteDB;//������Ԫ

};

//�����װ�˶����ݿ����ز���������������ѯ��ɾ������
class SQLiteDB
{

private:
	sqlite3* pDB;
	int flag;

public:

	//����˵��  :�������ݿ⡣������ݿ��Ѿ����ڣ�����������ݿ⣬��������ڣ����´���һ�����ݿ�
	//����˵��  :string DBName ���ݿ�����
	//����ֵ˵��:bool����  true ���ݿ�򿪳ɹ�
	//                     false ���ݿ��ʧ��
	bool openDB(string DBName);

	//����˵��  :��ָ�������ݿ���ִ��sql���(��select���!)
	//����˵��  :string sql ִ�е�sql���
	//����ֵ˵��:int���� 	-1 sql���ִ��ʧ�ܣ�ͬʱ���������Ϣ
	//                      0 sql���ִ�гɹ������ؽ��
	int execute(string sql);

	//����˵��  :��ָ�������ݿ���ִ���ļ��е�sql���(�ļ��в��ܺ���select���!)
	//��Ҫ���ڴ�������� �� �������������ݵ�ʱ����
	//����˵��  :string sql ִ�е�sql���
	//����ֵ˵��:int���� 	-1 sql���ִ��ʧ�ܣ�ͬʱ���������Ϣ
	//                      0 sql���ִ�гɹ������ؽ��
	int executeSQLFromFile(string fileName);

	//����˵��  :��ָ�������ݿ���ִ��select��sql���
	//����˵��  :string sql ִ�е�sql���
	//����ֵ˵��:Result���� NULL sql���ִ��ʧ�ܣ�ͬʱ���������Ϣ
	//                      rs   sql���ִ�гɹ�������Result�����rs
	ResultInfo* executeSelect(string sql);	

	//����˵��   :�ر����ݿ⡣
	//����˵��   :void ��
	//����ֵ˵�� :bool���� true ���ݿ�رճɹ�
	//                     false ���ݿ�ر�ʧ��
	bool closeDB();
	~SQLiteDB();
};
#endif