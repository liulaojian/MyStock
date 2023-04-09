#include "stdafx.h"
#include "StockMonitor.h"

CStockMonitor::CStockMonitor(CString strCode,CString strExpCode)
{
	strStockCode=strCode;
	strExpStockCode=strExpCode;

	pStockMin5Table=NULL;
	pStockDayTable=NULL;

	pExpStockMin5Table=NULL;
	pExpStockDayTable=NULL;

	pDlgMonitorCallBack=NULL;

	bMonitorRun=FALSE;
	bLoopBackMode=FALSE;

	::InitializeCriticalSection(&dataLock);
	
}

CStockMonitor::CStockMonitor(Vec_CString vecStockList)
{
	vecStockCodeList=vecStockList;
	pStockMin5Table=NULL;
	pStockDayTable=NULL;

	pExpStockMin5Table=NULL;
	pExpStockDayTable=NULL;

	pDlgMonitorCallBack=NULL;

	bMonitorRun=FALSE;

	::InitializeCriticalSection(&dataLock);
}

CStockMonitor::~CStockMonitor()
{
	::DeleteCriticalSection(&dataLock);

}

BOOL CStockMonitor::Init(void)
{
	CStockMonitorData *pStockMonitorData=NULL;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		pStockMonitorData=new CStockMonitorData(vecStockCodeList[i]);
		vecStockMonitorDataList.push_back(pStockMonitorData);
	}
	return TRUE;
}

CStockMonitorData * CStockMonitor::GetStockMonitorData(CString strStockCode)
{
	CStockMonitorData *pStockMonitorData=NULL;
	LockData();
	for(int i=0;i<vecStockMonitorDataList.size();i++)
	{
		pStockMonitorData=vecStockMonitorDataList[i];
		if(!pStockMonitorData)
			continue;
		if(pStockMonitorData->GetStockCode()==strStockCode)
		{
			UnlockData();
			return pStockMonitorData;
		}
	}
	UnlockData();
	return NULL;
}

BOOL CStockMonitor::SendJsonInfo(CString strJsonInfo)
{
	if(!pDlgMonitorCallBack)
		return FALSE;
	if(!pDlgMonitorCallBack->GetSafeHwnd())
		return FALSE;

	MonitorLogInfo *pMonitorLogInfo=new MonitorLogInfo();
	pMonitorLogInfo->strCode=strStockCode;
	pMonitorLogInfo->strLogTag="json";
	pMonitorLogInfo->strLogInfo=strJsonInfo;
	pDlgMonitorCallBack->PushMonitorLogInfo(pMonitorLogInfo);

	return TRUE;
}


BOOL  CStockMonitor::SendLogInfo(CString strInfo)
{
	if(!pDlgMonitorCallBack)
		return FALSE;
	if(!pDlgMonitorCallBack->GetSafeHwnd())
		return FALSE;

	MonitorLogInfo *pMonitorLogInfo=new MonitorLogInfo();
	pMonitorLogInfo->strCode=strStockCode;
	pMonitorLogInfo->strLogTag="info";
	pMonitorLogInfo->strLogInfo=strInfo;
	pDlgMonitorCallBack->PushMonitorLogInfo(pMonitorLogInfo);
	return TRUE;
}


BOOL CStockMonitor::SendResultInfo(MonitorResultInfo *pResultInfo)
{
	if(!pDlgMonitorCallBack)
		return FALSE;
	if(!pDlgMonitorCallBack->GetSafeHwnd())
		return FALSE;

	if(!pResultInfo)
		return FALSE;

	pDlgMonitorCallBack->PushMonitorResultInfo(pResultInfo);

	return TRUE;
}