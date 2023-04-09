#include "stdafx.h"
#include "StockNatureAnalysisArithmetic.h"
#include "StockDataMgr.h"
CStockNatureAnalysisArthmetic::CStockNatureAnalysisArthmetic(CString strCode)
{
	strStockCode=strCode;
	strExpStockCode="SH000001";
	pStockMin5Table=NULL;
	pStockDayTable=NULL;
	pExpStockDayTable=NULL;
	strBeginDate="";
	strEndDate="";
}

CStockNatureAnalysisArthmetic::~CStockNatureAnalysisArthmetic()
{

}


BOOL  CStockNatureAnalysisArthmetic::Init(void)
{
	if(strBeginDate==""||strEndDate=="")
	{
		return FALSE;
	}

	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);
	pExpStockDayTable=StockDataMgr()->GetStockDayTable(strExpStockCode);
	pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);
	if(!pStockDayTable||!pExpStockDayTable)
		return FALSE;

	mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDate);
	mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1||mEndPos==-1)
		return FALSE;

	mExpBeginPos=pExpStockDayTable->GetNearestStockDayIndex(strBeginDate);
	mExpEndPos=pExpStockDayTable->GetNearestStockDayIndex(strEndDate);
	if(mExpBeginPos==-1||mExpEndPos==-1)
		return FALSE;


	return TRUE;
}

Vec_CString CStockNatureAnalysisArthmetic::BuildAnalysisResultListString(void)
{
	Vec_CString vecResult;

	Vec_StockAnalysisInfo vecStockAnalysisInfo;

	vecStockAnalysisInfo=BuildStockAnalysisInfoList(EXP_FILTER_ALL);

	CString strInfo=BuildAnalysisResultString(vecStockAnalysisInfo);

	CString strResultInfo;
	strResultInfo.Format(" %s  %s ","全部数据中",strInfo);
	vecResult.push_back(strResultInfo);
	CFreeVector<Vec_StockAnalysisInfo>::freeVector(vecStockAnalysisInfo);


	vecStockAnalysisInfo=BuildStockAnalysisInfoList(EXP_FILTER_BIG_RISE);
	strInfo=BuildAnalysisResultString(vecStockAnalysisInfo);
	strResultInfo.Format(" %s  %s ","指数涨幅>=3%的数据中",strInfo);
	vecResult.push_back(strResultInfo);
	CFreeVector<Vec_StockAnalysisInfo>::freeVector(vecStockAnalysisInfo);

	vecStockAnalysisInfo=BuildStockAnalysisInfoList(EXP_FILTER_MIDDLE_RISE);
	strInfo=BuildAnalysisResultString(vecStockAnalysisInfo);
	strResultInfo.Format(" %s  %s ","指数涨幅>=1.5%同时<3%的数据中",strInfo);
	vecResult.push_back(strResultInfo);
	CFreeVector<Vec_StockAnalysisInfo>::freeVector(vecStockAnalysisInfo);

	vecStockAnalysisInfo=BuildStockAnalysisInfoList(EXP_FILTER_SMALL_RISE);
	strInfo=BuildAnalysisResultString(vecStockAnalysisInfo);
	strResultInfo.Format(" %s  %s ","指数涨幅>=0.5%同时<1.5%的数据中",strInfo);
	vecResult.push_back(strResultInfo);
	CFreeVector<Vec_StockAnalysisInfo>::freeVector(vecStockAnalysisInfo);

	vecStockAnalysisInfo=BuildStockAnalysisInfoList(EXP_FILTER_MILL_RISE);
	strInfo=BuildAnalysisResultString(vecStockAnalysisInfo);
	strResultInfo.Format(" %s  %s ","指数涨幅>=0.2%同时<0.5%的数据中",strInfo);
	vecResult.push_back(strResultInfo);
	CFreeVector<Vec_StockAnalysisInfo>::freeVector(vecStockAnalysisInfo);

	vecStockAnalysisInfo=BuildStockAnalysisInfoList(EXP_FILTER_MIRO_RISE_FALL);
	strInfo=BuildAnalysisResultString(vecStockAnalysisInfo);
	strResultInfo.Format(" %s  %s ","指数涨幅>-0.2%同时<0.2%的数据中",strInfo);
	vecResult.push_back(strResultInfo);
	CFreeVector<Vec_StockAnalysisInfo>::freeVector(vecStockAnalysisInfo);

	vecStockAnalysisInfo=BuildStockAnalysisInfoList(EXP_FILTER_MILL_FALL);
	strInfo=BuildAnalysisResultString(vecStockAnalysisInfo);
	strResultInfo.Format(" %s  %s ","指数涨幅>-0.5%同时<=-0.2%的数据中",strInfo);
	vecResult.push_back(strResultInfo);
	CFreeVector<Vec_StockAnalysisInfo>::freeVector(vecStockAnalysisInfo);

	vecStockAnalysisInfo=BuildStockAnalysisInfoList(EXP_FILTER_SMALL_FALL);
	strInfo=BuildAnalysisResultString(vecStockAnalysisInfo);
	strResultInfo.Format(" %s  %s ","指数涨幅>-1.5%同时<=-0.5%的数据中",strInfo);
	vecResult.push_back(strResultInfo);
	CFreeVector<Vec_StockAnalysisInfo>::freeVector(vecStockAnalysisInfo);


	vecStockAnalysisInfo=BuildStockAnalysisInfoList(EXP_FILTER_MIDDLE_FALL);
	strInfo=BuildAnalysisResultString(vecStockAnalysisInfo);
	strResultInfo.Format(" %s  %s ","指数涨幅>-3%同时<=-1.5%的数据中",strInfo);
	vecResult.push_back(strResultInfo);
	CFreeVector<Vec_StockAnalysisInfo>::freeVector(vecStockAnalysisInfo);

	vecStockAnalysisInfo=BuildStockAnalysisInfoList(EXP_FILTER_BIG_FALL);
	strInfo=BuildAnalysisResultString(vecStockAnalysisInfo);
	strResultInfo.Format(" %s  %s ","指数涨幅<=-3.0%的数据中",strInfo);
	vecResult.push_back(strResultInfo);
	CFreeVector<Vec_StockAnalysisInfo>::freeVector(vecStockAnalysisInfo);


	return vecResult;
}

CString CStockNatureAnalysisArthmetic::BuildAnalysisResultString(Vec_StockAnalysisInfo vecStockAnalysisInfo)
{

	if(vecStockAnalysisInfo.size()==0)
	{
		return "为空";
	}

	float f_ave_increase;
	float f_total_increase=0.0;
	StockAnalysisInfo * pStockAnalysisInfo=NULL;

	for(int i=0;i<vecStockAnalysisInfo.size();i++)
	{
		pStockAnalysisInfo=vecStockAnalysisInfo[i];
		if(!pStockAnalysisInfo)
			continue;

		f_total_increase+=pStockAnalysisInfo->f_stock_increase;

	}
	f_ave_increase=f_total_increase/vecStockAnalysisInfo.size();

	float f_exp_ave_increase;
	float f_exp_total_increase=0.0;
	for(int i=0;i<vecStockAnalysisInfo.size();i++)
	{
		pStockAnalysisInfo=vecStockAnalysisInfo[i];
		if(!pStockAnalysisInfo)
			continue;

		f_exp_total_increase+=pStockAnalysisInfo->f_exp_increase;

	}
	f_exp_ave_increase=f_exp_total_increase/vecStockAnalysisInfo.size();

	CString strTemp0;
	strTemp0.Format("指数平均涨幅 %.2f  股票平均涨幅  %.2f",f_exp_ave_increase,f_ave_increase);

	int mUpNums=0,mDownNums=0;
	int mExpUpNums=0,mExpDownNums=0;
	int mExpUpStockDown=0,mExpDownStockUp=0;
	for(int i=0;i<vecStockAnalysisInfo.size();i++)
	{
		pStockAnalysisInfo=vecStockAnalysisInfo[i];
		if(!pStockAnalysisInfo)
			continue;

		if(pStockAnalysisInfo->f_exp_increase>=0.0)
			mExpUpNums++;
		else
			mExpDownNums++;

		if(pStockAnalysisInfo->f_stock_increase>=0.0)
			mUpNums++;
		else
			mDownNums++;

		if(pStockAnalysisInfo->f_exp_increase>=0.0 && pStockAnalysisInfo->f_stock_increase<0.0)
		{
			mExpUpStockDown++;
		}

		if(pStockAnalysisInfo->f_exp_increase<0.0 && pStockAnalysisInfo->f_stock_increase>=0.0)
		{
			mExpDownStockUp++;
		}
	}
	CString strTemp1;
	strTemp1.Format("     ,     指数上涨次数 %d  下跌次数 %d , 股票上涨次数 %d 下跌次数 %d      ,     指数上涨股票下跌次数  %d  指数下跌股票上涨次数 %d ",mExpUpNums,mExpDownNums,mUpNums,mDownNums,mExpUpStockDown,mExpDownStockUp);
	
	CString strResult="";
	strResult+=strTemp0;
	strResult+=strTemp1;

	return strResult;
}

Vec_StockAnalysisInfo CStockNatureAnalysisArthmetic::BuildStockAnalysisInfoList(int mMode)
{
	Vec_StockAnalysisInfo vecStockAnalysisInfo;

	CStockDayData * pStockDayData=NULL;
	CStockDayData * pExpStockDayData=NULL;

	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=pStockDayTable->GetStockDayDataByIndex(i);
		pExpStockDayData=pExpStockDayTable->GetStockDayDataByIndex(i-mBeginPos+mExpBeginPos);

		if(!pStockDayData || !pExpStockDayData)
			continue;

		float f_end_price_increase=pStockDayTable->GetStockEndPriceIncrease(pStockDayData->GetDate());

		if(f_end_price_increase==INVALID_INCREASE)
			continue;

		float f_exp_end_price_increase=pExpStockDayTable->GetStockEndPriceIncrease(pStockDayData->GetDate());

		if(f_exp_end_price_increase==INVALID_INCREASE)
			continue;

		if(JudgeExpIncrease(mMode,f_exp_end_price_increase))
		{
			StockAnalysisInfo *pStockAnalysisInfo=new StockAnalysisInfo();

			pStockAnalysisInfo->strStockCode=strStockCode;
			pStockAnalysisInfo->strStockDate=pStockDayData->GetDate();
			pStockAnalysisInfo->f_exp_end_price=pExpStockDayData->GetEndPrice();
			pStockAnalysisInfo->f_exp_increase=f_exp_end_price_increase;
			pStockAnalysisInfo->f_exp_pre3ave_increase=pExpStockDayTable->GetStockEndPricePreAveIncrease(pStockDayData->GetDate(),3);
			pStockAnalysisInfo->f_exp_volume_increase=pExpStockDayTable->GetStockVolumeIncrease(pStockDayData->GetDate());
			pStockAnalysisInfo->f_exp_pre3ave_volume_increase=pExpStockDayTable->GetStockVolumePreAveIncrease(pStockDayData->GetDate(),3);
			pStockAnalysisInfo->f_stock_end_price=pStockDayData->GetEndPrice();
			pStockAnalysisInfo->f_stock_increase=f_end_price_increase;
			pStockAnalysisInfo->f_stock_pre3ave_increase=pStockDayTable->GetStockEndPricePreAveIncrease(pStockDayData->GetDate(),3);
			pStockAnalysisInfo->f_stock_volume_increase=pStockDayTable->GetStockVolumeIncrease(pStockDayData->GetDate());
			pStockAnalysisInfo->f_stock_pre3ave_volume_increase=pStockDayTable->GetStockVolumePreAveIncrease(pStockDayData->GetDate(),3);
			vecStockAnalysisInfo.push_back(pStockAnalysisInfo);
		}

	}


	return vecStockAnalysisInfo;
}


BOOL CStockNatureAnalysisArthmetic::JudgeExpIncrease(int mMode,float f_exp_increase)
{
	BOOL bOk=FALSE;

	switch(mMode)
	{
	case EXP_FILTER_ALL:
		bOk=TRUE;
		break;

	case EXP_FILTER_BIG_RISE:
		if(f_exp_increase>=3.0)
			bOk=TRUE;
		break;
	case EXP_FILTER_MIDDLE_RISE:
		if(f_exp_increase<3.0 && f_exp_increase>=1.5)
			bOk=TRUE;
		break;

	case EXP_FILTER_SMALL_RISE:
		if(f_exp_increase<1.5 && f_exp_increase>=0.5)
			bOk=TRUE;
		break;

	case EXP_FILTER_MILL_RISE:
		if(f_exp_increase<0.5 && f_exp_increase>=0.2)
			bOk=TRUE;
		break;
	case EXP_FILTER_MIRO_RISE_FALL:

		if(f_exp_increase<0.2 && f_exp_increase>-0.2)
			bOk=TRUE;

		break;
	case EXP_FILTER_MILL_FALL:

		if(f_exp_increase<=-0.2 && f_exp_increase>-0.5)
			bOk=TRUE;


		break;
	case EXP_FILTER_SMALL_FALL:
		if(f_exp_increase<=-0.5 && f_exp_increase>-1.5)
			bOk=TRUE;
		break;
	case EXP_FILTER_MIDDLE_FALL:
		if(f_exp_increase<=-1.5 && f_exp_increase>-3.0)
			bOk=TRUE;
		break;
	case EXP_FILTER_BIG_FALL:
		if(f_exp_increase<=-3.0)
			bOk=TRUE;
		break;


	}

	return bOk;
	
}