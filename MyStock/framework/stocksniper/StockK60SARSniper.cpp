#include "stdafx.h"
#include "StockK60SARSniper.h"
#include "StockDataMgr.h"
#include "StockKDJArithmetic.h"
#include "StockCCIArithmetic.h"
#include "StockMACDArithmetic.h"
#include "StockSARArithmetic.h"
#include "CommonMacro.h"
#include "StockLoopBackDataMgr.h"
#include "Log.h"
#include "Convert.h"
CStockK60SARSniper::CStockK60SARSniper(CString strStockCode):CStockSniper(strStockCode)
{

	strResultInfo="";
}


CStockK60SARSniper::~CStockK60SARSniper()
{

}

BOOL CStockK60SARSniper::SniperAnalyze(BOOL bLoopBackMode)
{
	CStockMin5Table *pStockMin5Table=NULL;


	if(StockDataMgr()->IsExpStock(strStockCode))
		return FALSE;

	if(pStockMonitorData==NULL)
		return FALSE;

	if(bLoopBackMode)
		pStockMin5Table=StockLoopBackDataMgr()->GetStockMin5Table(strStockCode);
	else
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);

	if(!pStockMin5Table)
		return FALSE;

	CString strDateTime=pStockMin5Table->GetLastStockMin5DataDateTime();

	CStockSARData* pStockSARData=NULL;
	pStockSARData=CStockSARArithmetic::CalcSARData(strStockCode,strDateTime,125,K_LINE_60MIN,4);
	if(!pStockSARData)
		return FALSE;


	CString strTime="";
	CString strDate="";
	CStringArray arryVal;
	StringSplit(strDateTime,arryVal,' ');
	if(arryVal.GetSize()==2)
	{
		strDate=arryVal.GetAt(0);
		strTime=arryVal.GetAt(1);
	}
	else
		return FALSE;

	CString strTemp=strTime.Left(2);
	int mHour=atoi((LPCSTR)strTemp);
	strTemp=strTime.Right(2);
	int mMin=atoi((LPCSTR)strTemp);

	int  mKLineMin;
	mKLineMin=60;

	int mTotalMin;

	if(mHour>=9 && mHour<=11)
	{
		mTotalMin=mHour*60+mMin-(9*60+30);

	}
	else
	{
		mTotalMin=(mHour-13)*60+mMin+120;
	}

	if(mTotalMin<0)
		return FALSE;

	if(mTotalMin%60!=0)
		return FALSE;

	int mLength=pStockSARData->vec_sar.size();
	int mCloseLength=pStockSARData->vec_close_price.size();

	double f_now_sar=pStockSARData->vec_sar[mLength-1];
	double f_last_sar;

	double f_now_close=pStockSARData->vec_close_price[mCloseLength-1];
	double f_last_close;

	StockSarData * pStockSarData=NULL;
	
	pStockSarData=pStockMonitorData->GetLastStockSarData();
	if(pStockSarData)
	{
		f_last_sar=pStockSarData->f_sar;
		f_last_close=pStockSarData->f_close;
	}
	else
	{
		f_last_sar=pStockSARData->vec_sar[mLength-2];
		f_last_close=pStockSARData->vec_close_price[mCloseLength-2];
	}

	BOOL  bNowRed=FALSE;
	if( f_now_sar<f_now_close )
		bNowRed=TRUE;
	else
		bNowRed=FALSE;

	

	
	BOOL bPreGreedNowRed=FALSE;		

	if( f_now_sar<f_now_close )
	{
	  if(f_last_sar>f_last_close)
	  {
		  if(pStockMonitorData->IsLastTwoContinueGreen())
			bPreGreedNowRed=TRUE;
	  }
	}
	else
		bPreGreedNowRed=FALSE;

	BOOL bPreRedNowGreen=FALSE;		

	if( f_now_sar>f_now_close )
	{
		if(f_last_sar<f_last_close)
			bPreRedNowGreen=TRUE;
		
	}
	else
		bPreRedNowGreen=FALSE;

	pStockSarData=new StockSarData();
	pStockSarData->strDateTime=strDateTime;
	pStockSarData->f_sar=f_now_sar;
	pStockSarData->f_close=f_now_close;
	if(bNowRed)
		pStockSarData->mSarColor=SAR_COLOR_RED;
	else
		pStockSarData->mSarColor=SAR_COLOR_GREEN;
	pStockMonitorData->AddStockSarData(pStockSarData);


	BOOL bOK1=FALSE;
	if(bPreGreedNowRed||bPreRedNowGreen)
	{
		//double f_range;
		//f_range=(f_now_close-f_last_close)*100.0/f_last_close;
		//if(f_range<4.0)
			bOK1=TRUE;
	}
	


	if(!bOK1)
	{
		SAFE_DELETE(pStockSARData);
		return FALSE;
	}

	/*if(!CalcExpMa20Ma60(bLoopBackMode))
	{
		SAFE_DELETE(pStockSARData);
		return FALSE;
	}*/

	

	CString strStockName;
	strStockName=StockDataMgr()->GetStockName(pStockSARData->strStockCode);
	if(bLoopBackMode)
	{
		double f_range=0.0;
		int mPeriodNums=8;
		CalcNext4PeridRange(strDateTime,K_LINE_60MIN,mPeriodNums,f_range);
		if(bPreGreedNowRed)
			strResultInfo.Format("%s  %s SAR ÂÌµ½ºì »Ø²â%dÕÇ·ù %.2f ",pStockSARData->strStockCode,strStockName,mPeriodNums,f_range);

		//if(bPreRedNowGreen)
		//	strResultInfo.Format("%s  %s SAR ºìµ½ÂÌ ",pStockSARData->strStockCode,strStockName);
	}
	else
		strResultInfo.Format("%s  %s 60·ÖÖÓKÏß SAR",pStockSARData->strStockCode,strStockName);
	SAFE_DELETE(pStockSARData);
	return TRUE;

}


BOOL  CStockK60SARSniper::CalcExpMa20Ma60(BOOL bLoopBackMode)
{
	CString strExpStockCode;

	CStockMin5Table *pStockMin5Table=NULL;

	strExpStockCode="SH000001";		//StockDataMgr()->GetExpCodeByBoardType(StockDataMgr()->GetStockBoard(strStockCode));

	if(bLoopBackMode)
		pStockMin5Table=StockLoopBackDataMgr()->GetStockMin5Table(strExpStockCode);
	else
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(strExpStockCode);

	if(!pStockMin5Table)
		return FALSE;

	CString strDateTime=pStockMin5Table->GetLastStockMin5DataDateTime();


	CStockKDJData *pStockKDJData=NULL;


	pStockKDJData=CStockKDJArithmetic::CalcKDJData(strExpStockCode,strDateTime,125,K_LINE_60MIN,9,3,3);


	if(pStockKDJData==NULL)
		return FALSE;

	int mLength=pStockKDJData->vec_close_price.size();

	double f_toatl_val=0.0;
	for(int i=mLength-4;i<=mLength-1;i++)
	{
		double f_now_val,f_pre_val,f_rang;

		f_now_val=pStockKDJData->vec_close_price[i];
		f_pre_val=pStockKDJData->vec_close_price[i-1];
		f_rang=(f_now_val-f_pre_val)*100.0/f_pre_val;
		f_toatl_val+=f_rang;
	}

	f_exp_4_total_per=f_toatl_val;

	SAFE_DELETE(pStockKDJData);
	return TRUE;
}



CString CStockK60SARSniper::GetSniperAnalyzeResult(void)
{
	return strResultInfo;
}