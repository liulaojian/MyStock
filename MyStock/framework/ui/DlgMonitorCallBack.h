#pragma once

#include "afxdtctl.h"
#include "T_Queue.h"
#include <vector>
#include "zbTypeDef.h"

typedef struct 
{
	CString  strCode;
	CString  strLogTag;
	CString  strLogInfo;
}MonitorLogInfo;


typedef struct 
{
	CString  strStockCode;
	CString  strLastStockMin5EndPrice;
	CString  strLastStockMin5DateTime;
	CString  strLastMonitorTime;
	CString  strCaptureInfo;
	CString  strMonitorInfo;
}MonitorResultInfo;

typedef std::vector<MonitorResultInfo *> Vec_MonitorResultInfo;

class CDlgMonitorCallBack: public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMonitorCallBack)

public:
	CDlgMonitorCallBack(UINT nIDTemplate,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMonitorCallBack();

public:

	void PushMonitorLogInfo(MonitorLogInfo *pLogInfo);
	MonitorLogInfo * PopMonitorLogInfo(void);

	void PushMonitorResultInfo(MonitorResultInfo *pResultInfo);
	MonitorResultInfo * PopMonitorResultInfo(void);



	void SetMonitorStockCodeList(Vec_CString vecList) { vecMonitorStockCodeList=vecList;}
	Vec_CString GetMonitorStockCodeList(void) {return vecMonitorStockCodeList;}
protected:
	Vec_CString vecMonitorStockCodeList;

protected:

	CQueue<MonitorResultInfo *> quQueueMonitorResultInfo;
	CRITICAL_SECTION monitorResultInfoLock;
	inline void TryLockMonitorResultInfo() 
	{ ::TryEnterCriticalSection(&monitorResultInfoLock); }
	inline void LockMonitorResultInfo() 
	{ ::EnterCriticalSection(&monitorResultInfoLock); }
	inline void UnlockMonitorResultInfo() 
	{ ::LeaveCriticalSection(&monitorResultInfoLock); }


	CQueue<MonitorLogInfo *> quQueueMonitorLogInfo;

	CRITICAL_SECTION monitorLogInfoLock;

	inline void TryLockMonitorLogInfo() 
	{ ::TryEnterCriticalSection(&monitorLogInfoLock); }
	inline void LockMonitorLogInfo() 
	{ ::EnterCriticalSection(&monitorLogInfoLock); }
	inline void UnlockMonitorLogInfo() 
	{ ::LeaveCriticalSection(&monitorLogInfoLock); }

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:


};