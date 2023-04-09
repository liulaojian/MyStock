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

	//加载文件股票数据，利用指数数据进行修补（主要是停牌时修补)
	BOOL  LoadFromMin5FileRepairDate(CString strDatFilePath,CStockMin5Table *pExpStockMin5Table);


	BOOL LoadFromVec(Vec_StockMin5Data vecData);

	//从http（新浪)获取 最近的5分钟数据
	Vec_StockMin5Data  GetNearestStockDataFormHttp(int mNums);
	float  GetNearestEndPriceFormHttp(int mNums);

	//将从http（新浪)获取 最近的5分钟数据加入到Table List里面
	BOOL  AddNearestStockData(Vec_StockMin5Data vecNearestStockData);

	//是否 StockData已经存在于列表中
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