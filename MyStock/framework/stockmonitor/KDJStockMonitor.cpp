#include "stdafx.h"
#include "KDJStockMonitor.h"
#include "StockDataMgr.h"
#include "StockKDJSniper.h"
#include "StockKDJMulSniper.h"
#include "StockK60KDJSniper.h"
#include "StockK60KDJMulSniper.h"
#include "StockNewK60KDJMulSniper.h"
#include "StockK60CCISniper.h"
#include "StockK60SARSniper.h"
#include "Log.h"
#include "StockLoopBackDataMgr.h"

#include "CommonMacro.h"

CKDJStockMonitor::CKDJStockMonitor(Vec_CString vecStockList):CStockMonitor(vecStockList)
{
	mPos=0;
	pCurLoopBackStockMin5Data=NULL;
	mStockSniperType=STOCK_SNIPER_K60MIN_KDJ_ZERO_CCI_ZERO;
	mMonitorLogNums=0;
}

CKDJStockMonitor::~CKDJStockMonitor()
{

}

BOOL CKDJStockMonitor::Init(void)
{
	__super::Init();

	bMonitorRun=FALSE;
	mPos=0;
	mMin5LoopBackNowPos=0;
	stRrocessTimer.Startup(3000);		//3Ãë
	return TRUE;
}



static UINT  RunMonitorProc(LPVOID pParam)
{
	
	CKDJStockMonitor *pKDJStockMonitor;
	pKDJStockMonitor=(CKDJStockMonitor *)pParam;

	while(TRUE)
	{
		pKDJStockMonitor->Process();
		if(pKDJStockMonitor->GetLoopBackMode())
			::Sleep(10);
		else
			::Sleep(1000);
		if(!pKDJStockMonitor->GetMonitorRun())
			break;
	}

	return 0;
}


BOOL CKDJStockMonitor::beginMonitor(void)
{
	
	AfxBeginThread(RunMonitorProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
	bMonitorRun=TRUE;

	return TRUE;
}

BOOL CKDJStockMonitor::Process(void)
{

	if(stRrocessTimer.TimeOver())
	{
		BOOL bStockMin5DataRecvOk=FALSE;
		
		CStockMin5Table *pStockMin5Table=NULL;
		
		if(vecStockCodeList.size()==0)
		{
			stRrocessTimer.Startup(2000);
			return FALSE;
		}

		if(mPos>=vecStockCodeList.size())
		{
			mPos=0;
			//if(bLoopBackMode)
			//StockLoopBackDataMgr()->IncMin5LoopBackNowPos();
			mMin5LoopBackNowPos++;
		}

		CString strMonitorStockCode;
		strMonitorStockCode=vecStockCodeList[mPos];

		if(bLoopBackMode)
			pStockMin5Table=StockLoopBackDataMgr()->GetStockMin5Table(strMonitorStockCode);
		else
			pStockMin5Table=StockDataMgr()->GetStockMin5Table(strMonitorStockCode);
		if(!pStockMin5Table)
		{
			stRrocessTimer.Startup(2000);
			return FALSE;
		}


		if(bLoopBackMode)
		{
			CStockMin5Data *pStockMin5Data;
			pStockMin5Data=StockLoopBackDataMgr()->GetLoopBackNowMin5Data(strMonitorStockCode,mMin5LoopBackNowPos);
			if(pStockMin5Data)
			{
				Vec_StockMin5Data vecStockMin5Data;
				vecStockMin5Data.push_back(pStockMin5Data);
				if(!pStockMin5Table->AddNearestStockData(vecStockMin5Data))
				{
					PrintfDebug("Get LoopBack Data Error %s \n",pStockMin5Table->GetStockCode());
				}
				else
					bStockMin5DataRecvOk=TRUE;

				//Day
				/*
				if(bStockMin5DataRecvOk)
				{
					CString strLastDate;
					strLastDate=pStockMin5Table->GetLastStockMin5DataDate();
					if(strLastDate!="")
					{
						CStockDayData *pStockDayData=NULL;
						pStockDayData=pStockMin5Table->BuildStockDayData(strLastDate);

						if(pStockDayData)
						{
							CStockDayTable *pStockDayTable=NULL;
							pStockDayTable=StockLoopBackDataMgr()->GetStockDayTable(pStockMin5Table->GetStockCode());
							pStockDayTable->AddOrUpdateStockDayData(pStockDayData);
						}
					}
				}*/
			
				pCurLoopBackStockMin5Data=pStockMin5Data;
			}
			else
			{
				if(strMonitorStockCode=="SH000001")
				{
					bMonitorRun=FALSE;
					SendLogInfo("½áÊø");
				}
			}
		}
		else
		{
			if(!pStockMin5Table->AddNearestStockData(pStockMin5Table->GetNearestStockDataFormHttp(100)))
			{
				PrintfDebug("Get Http Data Error %s \n",pStockMin5Table->GetStockCode());
			}
			else
				bStockMin5DataRecvOk=TRUE;


			//day
			/*
			if(bStockMin5DataRecvOk)
			{
				CString strLastDate;
				strLastDate=pStockMin5Table->GetLastStockMin5DataDate();
				if(strLastDate!="")
				{
					CStockDayData *pStockDayData=NULL;
					pStockDayData=pStockMin5Table->BuildStockDayData(strLastDate);

					if(pStockDayData)
					{
						CStockDayTable *pStockDayTable=NULL;
						pStockDayTable=StockDataMgr()->GetStockDayTable(pStockMin5Table->GetStockCode());
						pStockDayTable->AddOrUpdateStockDayData(pStockDayData);
					}
				}
			}
			*/


		}

		

		

		if(bStockMin5DataRecvOk)
		{
			doMonitor();
			mPos++;	
		}
		if(bLoopBackMode)
			stRrocessTimer.Startup(10);
		else
			stRrocessTimer.Startup(2000);
	}
	return TRUE;

}

BOOL CKDJStockMonitor::doMonitor(void)
{
	CString strMonitorStockCode;
	strMonitorStockCode=vecStockCodeList[mPos];

	if(bLoopBackMode)
		pStockMin5Table=StockLoopBackDataMgr()->GetStockMin5Table(strMonitorStockCode);
	else
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(strMonitorStockCode);
	if(!pStockMin5Table)
	{
		PrintfDebug("doMonitor pStockMin5Table=NULL \n");
		return FALSE;
	}
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	strDate.Format("%4d-%2d-%2d",st.wYear,st.wMonth,st.wDay);
	strTime.Format("%2d:%2d:%2d",st.wHour,st.wMinute,st.wSecond);

	CString strStockName=StockDataMgr()->GetStockName(strMonitorStockCode);
	CString strInfo="";

	

	if(bLoopBackMode)
	{
		if(mMonitorLogNums%10==0)
		{
			if(pCurLoopBackStockMin5Data)
				strInfo.Format("%s  ¼à¿Ø %s  %s ",pCurLoopBackStockMin5Data->GetDateTime(),strMonitorStockCode,strStockName);
			else
				strInfo.Format("%s  %s  ¼à¿Ø %s  %s ",strDate,strTime,strMonitorStockCode,strStockName);
			SendLogInfo(strInfo);
		}
		
	}
	else
	{
		strInfo.Format("%s  %s  ¼à¿Ø %s  %s ",strDate,strTime,strMonitorStockCode,strStockName);
		SendLogInfo(strInfo);
	}
	mMonitorLogNums++;

	//CStockKDJSniper  mStockKDJSniper(strMonitorStockCode);
	 CStockSniper *pStockSniper=NULL;
	 switch(mStockSniperType)
	 {
	 case STOCK_SNIPER_K60MIN_KDJ_ZERO_CCI_ZERO:
		 pStockSniper=new CStockK60KDJSniper(strMonitorStockCode);
		 break;
	 case STOCK_SNIPER_K60MIN_CCI_MINUS_50:
		 pStockSniper=new CStockK60CCISniper(strMonitorStockCode);
		 break;
	 case STOCK_SNIPER_K60MIN_SAR:
		 pStockSniper=new CStockK60SARSniper(strMonitorStockCode);
		 CStockMonitorData *pStockMonitorData=GetStockMonitorData(strMonitorStockCode);
		 if(pStockMonitorData)
			pStockSniper->SetStockMonitorData(pStockMonitorData);
		 break;
	 }

	if(!pStockSniper)
		 return FALSE;

	if(pStockSniper->SniperAnalyze(bLoopBackMode))
	{

		CString strCaptureInfo=pStockSniper->GetSniperAnalyzeResult();

		if(strCaptureInfo!="")
		{
			MonitorResultInfo *pMonitorResultInfo=new MonitorResultInfo();
			pMonitorResultInfo->strStockCode=strMonitorStockCode;
			CString strTemp=strDate;
			strTemp+=" ";
			strTemp+=strTime;
			pMonitorResultInfo->strLastMonitorTime=strTemp;
			pMonitorResultInfo->strLastStockMin5DateTime=pStockMin5Table->GetLastStockMin5DataDateTime();
			pMonitorResultInfo->strLastStockMin5EndPrice="";
			pMonitorResultInfo->strMonitorInfo="";
			if(bLoopBackMode)
			{
				if(pCurLoopBackStockMin5Data)
					strInfo.Format("%s  %s",pCurLoopBackStockMin5Data->GetDateTime(),strCaptureInfo);
				else
					strInfo.Format("%s  %s  %s",strDate,strTime,strCaptureInfo);
			}
			else
			{
				strInfo.Format("%s  %s  %s",strDate,strTime,strCaptureInfo);
			}
			
			pMonitorResultInfo->strCaptureInfo=strInfo;
			SendResultInfo(pMonitorResultInfo);
			PrintfDebug("doMonitor SendResultInfo \n");
		}

	}
	SAFE_DELETE(pStockSniper);
	return TRUE;
}


