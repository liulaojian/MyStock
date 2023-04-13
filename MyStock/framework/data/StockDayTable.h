#pragma once

#include <vector>

#include "StockDayData.h"

#define INVALID_INCREASE	-999.0
#define INVALID_VOLUME	-1.0
typedef std::vector<CStockDayData *> Vec_StockDayData;

class CStockDayTable
{
public:
	CStockDayTable(CString strCode);
	virtual ~CStockDayTable();


public:

	BOOL  LoadFromDayFile(CString strDatFilePath);

	//加载文件股票数据，利用指数数据进行修补（主要是停牌时修补)
	BOOL  LoadFromDayFileRepairDate(CString strDatFilePath,CStockDayTable *pExpStockDayTable);

	BOOL  LoadFromVec(Vec_StockDayData vecData);

	BOOL  LoadFormDb(void);

	BOOL  SaveToDb(void);

	Vec_StockDayData  GetStockDayDataList(void) {
		return vecStockDayData;
	}
	int GetStockDayDataListSize(void) {return vecStockDayData.size();}

	CStockDayData * GetLastStockDayData(void);

	CString GetStockCode(void) { return strStockCode;}

	CString GetStockBeginDate(void);

	CString GetStockEndDate(void);


	CString GetStockDayDateReverseIndex(int index);
	
	CString GetStockDayDateByIndex(int index);

	CStockDayData* GetNextStockDayDataByDate(CString strDate);
	CStockDayData* GetStockDayDataByDate(CString strDate);

	BOOL IsNextStockDayDataExist(CString strDate);


	CString  GetNearestStockDayDate(CTime mDateTime);

	int GetStockDayIndexByDateReverse(CString strDate);
	CString GetStockDayDatePreOfIndexReverse(CString strDate,int prenums);

	int  GetStockDayIndex(CString strDate);
	int GetNearestStockDayIndex(CString strDate);

	CString GetStockDayDatePreOfIndex(CString strDate,int prenums);

	CString GetStockDayDateAftOfIndex(CString strDate,int aftnums);


	float GetMinLowPriceBwDates(CString strBeginDate,CString strEndDate);

	float GetMaxHighPriceBwDates(CString strBeginDate,CString strEndDate);

	float GetMinVolumeBwDates(CString strBeginDate,CString strEndDate);

	float GetMaxVolumeBwDates(CString strBeginDate,CString strEndDate);

	Vec_StockDayData GetStockDayDataListBwDates(CString strBeginDate,CString strEndDate);
	Vec_StockDayData GetStockDayDataListBwIndex(int mBeginPos,int  mEndPos);

	CStockDayData * GetStockDayDataByIndex(int index);

	BOOL  AddOrUpdateStockDayData(CStockDayData *pAddStockDayData);

	//获取最后的股票日期
	CString GetLastStockDate(void);
	CString GetLastStockDateByReverse(int index);


	//获取最后的股票End Price
	float GetLastStockEndPrice(void);

	//获取股票最后n--m个交易日内，最低值  n>m,如果没有返回-1.0
	float GetLastDayNumsStockMinPrice(int mDayNums,int mNoUseDayNums);
	
	//获取股票指定日期的涨幅(百分比格式)
	float GetStockEndPriceIncrease(CString strDate);

	//获取股票指定日期的成交额涨幅(百分比格式)
	float GetStockVolumeIncrease(CString strDate);

	//获取股票指定日期前N日的平均涨幅(百分比格式)
	float GetStockEndPricePreAveIncrease(CString strDate,int mNums);

	//获取股票指定日期前N日的平均成交额涨幅(百分比格式)
	float GetStockVolumePreAveIncrease(CString strDate,int mNums);


	inline void TryLockData() 
	{
		::TryEnterCriticalSection(&dataLock);
	}
	inline void LockData() 
	{ 
		::EnterCriticalSection(&dataLock); 
	}
	inline void UnlockData() 
	{ 
		::LeaveCriticalSection(&dataLock);
	}

private:
	Vec_StockDayData vecStockDayData;

	CString strStockCode;
	CRITICAL_SECTION dataLock;
};