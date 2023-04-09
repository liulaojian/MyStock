#include "stdafx.h"
#include "DlgMonitorCallBack.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CDlgMonitorCallBack, CDialogEx)

CDlgMonitorCallBack::CDlgMonitorCallBack(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
	: CDialogEx(nIDTemplate, pParent)
{
	::InitializeCriticalSection(&monitorLogInfoLock);
	::InitializeCriticalSection(&monitorResultInfoLock);
	
}

CDlgMonitorCallBack::~CDlgMonitorCallBack()
{
	::DeleteCriticalSection(&monitorLogInfoLock);
	::DeleteCriticalSection(&monitorResultInfoLock);
}




BEGIN_MESSAGE_MAP(CDlgMonitorCallBack, CDialogEx)
END_MESSAGE_MAP()




void CDlgMonitorCallBack::OnOK()
{
	CDialogEx::OnOK();
}



void CDlgMonitorCallBack::PushMonitorLogInfo(MonitorLogInfo *pLogInfo)
{
	LockMonitorLogInfo();
	quQueueMonitorLogInfo.push(pLogInfo);
	UnlockMonitorLogInfo();
}

MonitorLogInfo * CDlgMonitorCallBack::PopMonitorLogInfo(void)
{
	MonitorLogInfo * pMonitorLogInfo;
	LockMonitorLogInfo();
	pMonitorLogInfo=quQueueMonitorLogInfo.pop();
	UnlockMonitorLogInfo();
	return pMonitorLogInfo;
}



void CDlgMonitorCallBack::PushMonitorResultInfo(MonitorResultInfo *pResultInfo)
{
	LockMonitorResultInfo();
	quQueueMonitorResultInfo.push(pResultInfo);
	UnlockMonitorResultInfo();
}

MonitorResultInfo * CDlgMonitorCallBack::PopMonitorResultInfo(void)
{
	MonitorResultInfo *pResultInfo;
	LockMonitorResultInfo();
	pResultInfo=quQueueMonitorResultInfo.pop();
	UnlockMonitorResultInfo();
	return pResultInfo;
}