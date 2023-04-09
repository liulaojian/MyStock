#pragma once
#include "StockDataMgr.h"


class CStockLoopBackDataMgr
{
public:
	CStockLoopBackDataMgr();
	virtual ~CStockLoopBackDataMgr();

public:
	static CStockLoopBackDataMgr* GetInstance();

	
	void SetLoopBackDayDate(CString strDate) {strLoopBackDayDate=strDate;}

	CString GetLoopBackDayDate(void) {return strLoopBackDayDate;}

	BOOL BuildtLoopBackDayData(void);

	void SetLoopBackMin5DateTime(CString strDateTime) {strLoopBackMin5DateTime=strDateTime;}

	CString GetLoopBackMin5DateTime(void) {return strLoopBackMin5DateTime;}

	BOOL BuildtLoopBackMin5Data(void);
	

	void SetLoopBackNowDateTime(CString strDateTime) {strLoopBackNowDateTime=strDateTime;}
	CString GetLoopBackNowDateTime(void ) {return strLoopBackNowDateTime;}

	CStockDayTable* GetStockDayTable(CString strStockCode);

	CStockDayTable* GetLPStockDayTable(CString strStockCode);

	CStockMin5Table* GetStockMin5Table(CString strStockCode);

	CStockMin5Table* GetLPStockMin5Table(CString strStockCode);

	

	inline void TryLockDayTable() 
	{ ::TryEnterCriticalSection(&dayTableLock); }
	inline void LockDayTable() 
	{ ::EnterCriticalSection(&dayTableLock); }
	inline void UnlockDayTable() 
	{ ::LeaveCriticalSection(&dayTableLock); }

	inline void TryLockLPDayTable() 
	{ ::TryEnterCriticalSection(&dayLPTableLock); }
	inline void LockLPDayTable() 
	{ ::EnterCriticalSection(&dayLPTableLock); }
	inline void UnlockLPDayTable() 
	{ ::LeaveCriticalSection(&dayLPTableLock); }


	inline void TryLockMin5Table() 
	{ ::TryEnterCriticalSection(&min5TableLock); }
	inline void LockMin5Table() 
	{ ::EnterCriticalSection(&min5TableLock); }
	inline void UnlockMin5Table() 
	{ ::LeaveCriticalSection(&min5TableLock); }

	inline void TryLockLPMin5Table() 
	{ ::TryEnterCriticalSection(&min5LPTableLock); }
	inline void LockLPMin5Table() 
	{ ::EnterCriticalSection(&min5LPTableLock); }
	inline void UnlockLPMin5Table() 
	{ ::LeaveCriticalSection(&min5LPTableLock); }


	//获取当前的5分钟回测数据
	CStockMin5Data * GetLoopBackNowMin5Data(CString strStockCode,int mMin5LoopBackNowPos);

private:
	static CStockLoopBackDataMgr* s_pIntance;



	Vec_StockDayTableList  vecStockDayTableList;

	Vec_StockMin5TableList vecStockMin5TableList;


	Vec_StockDayTableList  vecLPStockDayTableList;

	Vec_StockMin5TableList vecLPStockMin5TableList;

	CString strLoopBackDayDate;

	CString strLoopBackMin5DateTime;


	CString strLoopBackNowDateTime;

	


	CRITICAL_SECTION dayTableLock;
	CRITICAL_SECTION min5TableLock;
	
	CRITICAL_SECTION dayLPTableLock;
	CRITICAL_SECTION min5LPTableLock;


};

#define StockLoopBackDataMgr()	CStockLoopBackDataMgr::GetInstance()