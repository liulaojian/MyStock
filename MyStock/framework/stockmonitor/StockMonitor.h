#pragma once

#include "StockMin5Table.h"
#include "StockDayTable.h"

#include "DlgMonitorCallBack.h"
#include "zbTypeDef.h"

#include "StockMonitorData.h"
//股票监控基类
class CStockMonitor
{
public:
	CStockMonitor(CString strCode,CString strExpCode);
	CStockMonitor(Vec_CString vecStockList);
	
	virtual ~CStockMonitor();

	virtual BOOL Init(void);

	virtual BOOL beginMonitor(void)=0;

	virtual BOOL Process(void)=0;

	BOOL GetMonitorRun(void) {return bMonitorRun;}

	void SetMonitorRun(BOOL bVal) {bMonitorRun=bVal;}

	void StopMonitor(void) {bMonitorRun=FALSE;}

	void SetDlgMonitorCallBack(CDlgMonitorCallBack *pDlg) {pDlgMonitorCallBack=pDlg;}

	CDlgMonitorCallBack * GetDlgMonitorCallBack(void) {return pDlgMonitorCallBack;}

public:
	CString GetStockCode(void) {return strStockCode;}
	CString GetExpStockCode(void) {return strExpStockCode;}

	void SetLoopBackMode(BOOL bVal) {bLoopBackMode=bVal;}

	BOOL GetLoopBackMode(void) {return bLoopBackMode;}

	CStockMonitorData * GetStockMonitorData(CString strStockCode);

public:
	BOOL SendJsonInfo(CString strJsonInfo);
	BOOL SendLogInfo(CString strInfo);
	BOOL SendResultInfo(MonitorResultInfo *pResultInfo);

	inline void TryLockData() 
	{ ::TryEnterCriticalSection(&dataLock); }
	inline void LockData() 
	{ ::EnterCriticalSection(&dataLock); }
	inline void UnlockData() 
	{ ::LeaveCriticalSection(&dataLock); }

protected:
	CString strStockCode;
	CString strExpStockCode;

	CStockMin5Table *pStockMin5Table;
	CStockDayTable *pStockDayTable;
	
	CStockMin5Table *pExpStockMin5Table;

	CStockDayTable *pExpStockDayTable;

	CDlgMonitorCallBack *pDlgMonitorCallBack;
	BOOL bMonitorRun;

	BOOL  bLoopBackMode;		//是否回测
	Vec_CString vecStockCodeList;
	Vec_StockMonitorData vecStockMonitorDataList;

	CRITICAL_SECTION dataLock;

};