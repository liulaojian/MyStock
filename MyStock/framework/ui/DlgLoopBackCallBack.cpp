#include "stdafx.h"
#include "DlgLoopBackCallBack.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CDlgLoopBackCallBack, CDialogEx)

CDlgLoopBackCallBack::CDlgLoopBackCallBack(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
	: CDialogEx(nIDTemplate, pParent)
{
	::InitializeCriticalSection(&loopBackLogInfoLock);
}

CDlgLoopBackCallBack::~CDlgLoopBackCallBack()
{
	::DeleteCriticalSection(&loopBackLogInfoLock);
}




BEGIN_MESSAGE_MAP(CDlgLoopBackCallBack, CDialogEx)
END_MESSAGE_MAP()




void CDlgLoopBackCallBack::OnOK()
{
	CDialogEx::OnOK();
}



void CDlgLoopBackCallBack::PushRLoopBackLogInfo(LoopBackLogInfo *pLogInfo)
{
	LockLoopBackLogInfo();
	quQueueLoopBackLogInfo.push(pLogInfo);
	UnlockLoopBackLogInfo();
}

LoopBackLogInfo * CDlgLoopBackCallBack::PopLoopBackLogInfo(void)
{
	LoopBackLogInfo * pLoopBackLogInfo;
	LockLoopBackLogInfo();
	pLoopBackLogInfo=quQueueLoopBackLogInfo.pop();
	UnlockLoopBackLogInfo();
	return pLoopBackLogInfo;
}