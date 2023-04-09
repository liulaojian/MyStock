#pragma once

#include <vector>

#include "StockMin5Data.h"
#include "StockDayData.h"
class CNetStock;

typedef std::vector<CStockMin5Data *> Vec_StockMin5Data;
class CStockMin5Table
{
public:
	CStockMin5Table(CString strCode);
	virtual ~CStockMin5Table();

public:
	BOOL  LoadFromMin5File(CString strDataFilePath);

	//�����ļ���Ʊ���ݣ�����ָ�����ݽ����޲�����Ҫ��ͣ��ʱ�޲�)
	BOOL  LoadFromMin5FileRepairDate(CString strDatFilePath,CStockMin5Table *pExpStockMin5Table);


	BOOL LoadFromVec(Vec_StockMin5Data vecData);

	//��http������)��ȡ �����5��������
	Vec_StockMin5Data  GetNearestStockDataFormHttp(int mNums);
	float  GetNearestEndPriceFormHttp(int mNums);

	//����http������)��ȡ �����5�������ݼ��뵽Table List����
	BOOL  AddNearestStockData(Vec_StockMin5Data vecNearestStockData);

	//�Ƿ� StockData�Ѿ��������б���
	BOOL  IsStockDataExist(CStockMin5Data *pStockMin5Data);

	CString GetStockCode(void) { return strStockCode;}

	Vec_StockMin5Data GetStockMin5DataList(void) {return vecStockMin5Data;}

	int  GetStockMin5DataListSize(void) { return vecStockMin5Data.size(); }

	CStockMin5Data * GetLastStockMin5Data(void);

	CStockMin5Data * GetStockMin5DataByIndex(int index);


	CString  GetNearestStockDayDate(CTime mDateTime);

	CString GetLastStockMin5DataDate(void);
	CString GetLastStockMin5DataDateTime(void);


	
	CString GetStockMin5BeginDateTime(void);

	CString GetStockMin5EndDateTime(void);

	
	CStockDayData* BuildStockDayData(CString strStockDate);

	int  GetStockMin5Index(CString strDateTime);

	inline void TryLockData() 
	{ ::TryEnterCriticalSection(&dataLock); }
	inline void LockData() 
	{ ::EnterCriticalSection(&dataLock); }
	inline void UnlockData() 
	{ ::LeaveCriticalSection(&dataLock); }

private:
	Vec_StockMin5Data vecStockMin5Data;
	CNetStock *pNetStock;
	CString strStockCode;
	CRITICAL_SECTION dataLock;
};