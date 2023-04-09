#include "stdafx.h"
#include "NewStockMonitor.h"
#include "StockDataMgr.h"
#include "StockRSIArithmetic.h"
CNewStockMonitor::CNewStockMonitor(CString stockCode)
{
	bInited=FALSE;
	bRun=FALSE;
	strStockCode=stockCode;
	pStockMin5Table=NULL;
}

CNewStockMonitor::~CNewStockMonitor()
{


}

static UINT  NewStockMonitorProc(LPVOID pParam)
{
	CNewStockMonitor *pNewStockMonitor;
	pNewStockMonitor=(CNewStockMonitor *)pParam;
	if(pNewStockMonitor)
		pNewStockMonitor->Run();
	

	return 0;
}

BOOL CNewStockMonitor::Init(void)
{
	if(bInited)
		return FALSE;
	pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);
	st5MinTimer.Startup(3000);
	bRun=TRUE;
	AfxBeginThread(NewStockMonitorProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);

	bInited=TRUE;

	return TRUE;
}


BOOL  CNewStockMonitor::Run(void)
{
	while(bRun)
	{
		if(st5MinTimer.TimeOver())
		{
			pStockMin5Table->AddNearestStockData(pStockMin5Table->GetNearestStockDataFormHttp(300));
			
			CString strDateTime=pStockMin5Table->GetLastStockMin5DataDateTime();


			CStockRSIData* pStockRSIData=NULL;
			pStockRSIData=CStockRSIArithmetic::CalcRSIData(strStockCode,strDateTime,40,K_LINE_30IN,6,12,24);
			int size=pStockRSIData->vec_rsi_1_value.size();
			double rsi_1=pStockRSIData->vec_rsi_1_value[size-1];
			double rsi_2=pStockRSIData->vec_rsi_2_value[size-1];
			double rsi_3=pStockRSIData->vec_rsi_3_value[size-1];

			st5MinTimer.Startup(1000*240);		//240√Î

		}
	
		Sleep(10);
	}
	return TRUE;
}
