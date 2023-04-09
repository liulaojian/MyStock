#pragma once
#include <string>
#include <vector>
#include "zbTypeDef.h"
#include "sqlite.h"

#include "StockDayTable.h"
#include "StockMin5Table.h"

#define STOCKDATA_DATABASE 			"stockdata.db"


typedef struct
{
	std::string		strDate;
	float  fBeginPrice;		//���̼۸�
	float  fMaxPrice;		//��߼۸�
	float  fMinPrice;		//��ͼ۸�
	float  fEndPrice;		//���̼۸�
	long   mTotalVolume;		//�ɽ���
	float  fTotalPrice;		//�ɽ����
} DbStockDayData;
typedef std::vector<DbStockDayData *> Vec_DbStockDayData;

typedef struct
{
	CString strStockCode;
	Vec_DbStockDayData  vecDbStockDayData;
} DbStockDayTable;
typedef std::vector<DbStockDayTable *> Vec_DbStockDayTable;


typedef struct
{
	std::string	 strDateTime;
	float  fBeginPrice;		//���̼۸�
	float  fMaxPrice;		//��߼۸�
	float  fMinPrice;		//��ͼ۸�
	float  fEndPrice;		//���̼۸�
	long   mTotalVolume;		//�ɽ���
	float  fTotalPrice;		//�ɽ����
} DbStock5MinData;
typedef std::vector<DbStock5MinData *> Vec_DbStock5MinData;

typedef struct
{
	CString strStockCode;
	Vec_DbStock5MinData  vecDbStock5MinData;
} DbStock5MinTable;
typedef std::vector<DbStock5MinTable *> Vec_DbStock5MinTable;

class CStockDataInfoDb
{
public:
	CStockDataInfoDb();
	virtual ~CStockDataInfoDb();

public:
	static CStockDataInfoDb* GetInstance();
	
	CString GetStockDayTableName(CString strStockCode);
	CString GetStockMin5TableName(CString strStockCode);

	//�����ݿ�
	bool DataBaseOpen(void);
	
	//�ر����ݿ�
	bool DataBaseClose(void);

	//���ݿ��ձ��Ƿ����
	BOOL IsDbDayTableExist(CString strStockCode);

	//���ݿ�5���ӱ��Ƿ����
	BOOL IsDbMin5TableExist(CString strStockCode);

	BOOL  IsDatabaseOpe(void) {return bDatabaseOpen;}

	//�����ձ�
	bool CreateDayTable(std::string strTableName);

	//����5���ӱ�
	bool CreateMin5Table(std::string strTableName);

	//������
	bool CreateTable(void);

	//��������������
	bool StockDay_Table_InsertVec(CString strStockCode,Vec_DbStockDayData vecDbStockDayData);

	//�����ݲ�ѯ
	bool StockDay_Table_Query(CString strStockCode, Vec_DbStockDayData &vecDbStockDayData);

	//������ɾ��
	bool StockDay_Table_Delete(CString strStockCode,CString strDate);

	//�����ݸ���
	bool StockDay_Table_Update(CString strStockCode,DbStockDayData * pDbStockDayData);

	//5����������������
	bool StockMin5_Table_InsertVec(CString strStockCode,Vec_DbStock5MinData vecDbStock5MinData);

	//5�������ݲ�ѯ
	bool StockMin5_Table_Query(CString strStockCode, Vec_DbStock5MinData &vecDbStock5MinData);

	//5��������ɾ��
	bool StockMin5_Table_Delete(CString strStockCode,CString strDateTime);

	//5�������ݸ���
	bool StockMin5_Table_Update(CString strStockCode,DbStock5MinData * pDbStock5MinData);

	//��Vec_StockDayData �������б� ת��Ϊ  Vec_DbStockDayData �����ݿ��б�
	Vec_DbStockDayData  ConvertVecStockDayDataToVecDbStockDayData(Vec_StockDayData vecStockDayData );

	//��Vec_StockMin5Data �������б� ת��Ϊ  Vec_DbStock5MinData �����ݿ��б�
	Vec_DbStock5MinData ConvertVecStockMin5DataToVecDbStock5MinData(Vec_StockMin5Data vecStockMin5Data);
	
private:
	static CStockDataInfoDb* s_pIntance;
	
	Sqlite mDatabase;

	BOOL bDatabaseOpen;

};


#define StockDataInfoDb()	CStockDataInfoDb::GetInstance()