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

	//�����ļ���Ʊ���ݣ�����ָ�����ݽ����޲�����Ҫ��ͣ��ʱ�޲�)
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

	//��ȡ���Ĺ�Ʊ����
	CString GetLastStockDate(void);
	CString GetLastStockDateByReverse(int index);


	//��ȡ���Ĺ�ƱEnd Price
	float GetLastStockEndPrice(void);

	//��ȡ��Ʊ���n--m���������ڣ����ֵ  n>m,���û�з���-1.0
	float GetLastDayNumsStockMinPrice(int mDayNums,int mNoUseDayNums);
	
	//��ȡ��Ʊָ�����ڵ��Ƿ�(�ٷֱȸ�ʽ)
	float GetStockEndPriceIncrease(CString strDate);

	//��ȡ��Ʊָ�����ڵĳɽ����Ƿ�(�ٷֱȸ�ʽ)
	float GetStockVolumeIncrease(CString strDate);

	//��ȡ��Ʊָ������ǰN�յ�ƽ���Ƿ�(�ٷֱȸ�ʽ)
	float GetStockEndPricePreAveIncrease(CString strDate,int mNums);

	//��ȡ��Ʊָ������ǰN�յ�ƽ���ɽ����Ƿ�(�ٷֱȸ�ʽ)
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