#include "stdafx.h"
#include "SuperFallStockMonitor.h"
#include "StockDataMgr.h"
#include "Log.h"
CSuperFallStockMonitor::CSuperFallStockMonitor(CString strCode,CString strExpCode):CStockMonitor(strCode,strExpCode)
{
	
}

CSuperFallStockMonitor::~CSuperFallStockMonitor()
{

}


BOOL CSuperFallStockMonitor::Init(void)
{
	pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);
	pExpStockMin5Table=StockDataMgr()->GetStockMin5Table(strExpStockCode);

	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);
	pExpStockDayTable=StockDataMgr()->GetStockDayTable(strExpStockCode);

	if(pStockMin5Table==NULL || pStockDayTable==NULL)
		return FALSE;

	if(pExpStockMin5Table==NULL || pExpStockDayTable==NULL)
		return FALSE;

	bMonitorRun=TRUE;

	stRrocessTimer.Startup(3000);

	return TRUE;
}


static UINT  RunMonitorProc(LPVOID pParam)
{
	CSuperFallStockMonitor *pSuperFallStockMonitor;
	pSuperFallStockMonitor=(CSuperFallStockMonitor *)pParam;

	while(TRUE)
	{
		pSuperFallStockMonitor->Process();
		::Sleep(1000);
		if(!pSuperFallStockMonitor->GetMonitorRun())
			break;
	}
		

	return 0;
}

BOOL CSuperFallStockMonitor::beginMonitor(void)
{

	AfxBeginThread(RunMonitorProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);

	return TRUE;
}



BOOL CSuperFallStockMonitor::Process(void)
{

	if(stRrocessTimer.TimeOver())
	{
		BOOL bStockMin5DataRecvOk=FALSE;
		BOOL bExpStockMin5DataRecvOk=FALSE;

		if(!pStockMin5Table->AddNearestStockData(pStockMin5Table->GetNearestStockDataFormHttp(100)))
		{
			PrintfDebug("Get Http Data Error %s \n",pStockMin5Table->GetStockCode());
		}
		else
			bStockMin5DataRecvOk=TRUE;

		if(!pExpStockMin5Table->AddNearestStockData(pExpStockMin5Table->GetNearestStockDataFormHttp(100)))
		{
			PrintfDebug("Get Http Data Error %s \n",pExpStockMin5Table->GetStockCode());
		}
		else
			bExpStockMin5DataRecvOk=TRUE;

		if(bExpStockMin5DataRecvOk && bStockMin5DataRecvOk)
		{
			doMonitor();
		}

		stRrocessTimer.Startup(1000*240);
	}
	return TRUE;
}


BOOL CSuperFallStockMonitor::doMonitor(void)
{
	

	return TRUE;
}