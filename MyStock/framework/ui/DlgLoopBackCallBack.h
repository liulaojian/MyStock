#pragma once

#include "afxdtctl.h"
#include "T_Queue.h"

typedef struct 
{
	CString  strLogTag;
	CString  strLogInfo;
}LoopBackLogInfo;

class CDlgLoopBackCallBack: public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLoopBackCallBack)

public:
	CDlgLoopBackCallBack(UINT nIDTemplate,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLoopBackCallBack();

public:

	void PushRLoopBackLogInfo(LoopBackLogInfo *pLogInfo);

	LoopBackLogInfo * PopLoopBackLogInfo(void);


protected:
	CQueue<LoopBackLogInfo *> quQueueLoopBackLogInfo;

	CRITICAL_SECTION loopBackLogInfoLock;

	inline void TryLockLoopBackLogInfo() 
	{ ::TryEnterCriticalSection(&loopBackLogInfoLock); }
	inline void LockLoopBackLogInfo() 
	{ ::EnterCriticalSection(&loopBackLogInfoLock); }
	inline void UnlockLoopBackLogInfo() 
	{ ::LeaveCriticalSection(&loopBackLogInfoLock); }

protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:


};