#include "stdafx.h"
#include "CurveSinCmpLoopBack.h"
#include "StrategyMgr.h"
#include "DlgLoopBackLog.h"
#include "StockDataMgr.h"
#include "Log.h"
CCurveSinCmpLoopBack::CCurveSinCmpLoopBack()
{

}


CCurveSinCmpLoopBack::~CCurveSinCmpLoopBack()
{

}

BOOL CCurveSinCmpLoopBack::Init(void)
{
	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);
	pStockExpDayTable=StockDataMgr()->GetStockDayTable(strStockExp);

	if(!pStockDayTable || !pStockExpDayTable )
		return FALSE;
	
	mLoopBackStockBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDate);
	mLoopBackStockEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDate);

	mLoopBackExpBeginPos=pStockExpDayTable->GetNearestStockDayIndex(strBeginDate);
	mLoopBackExpEndPos=pStockExpDayTable->GetNearestStockDayIndex(strEndDate);

	if(mLoopBackStockBeginPos==-1 || mLoopBackStockEndPos==-1)
		return FALSE;

	if(mLoopBackExpBeginPos==-1 || mLoopBackExpEndPos==-1)
		return FALSE;

	ParseCmpMethodParas();

	CString strTitle;
	strTitle.Format("%s  回测  %s -- %s ",pStockDayTable->GetStockCode(),strBeginDate,strEndDate);

	doSendLogTitle(strTitle);
	

	return TRUE;
}

BOOL CCurveSinCmpLoopBack::doLoopBack(void)
{
	int mNums=0;

	if(mLoopBackExpBeginPos<mCmpMethodNums)
		return FALSE;
	mLoopBackExpPos=mLoopBackExpBeginPos-mCmpMethodNums;

	int mLoopBackExpNextPos=mLoopBackExpBeginPos;	//mLoopBackExpPos+mCmpMethodNums-1;

	while(mLoopBackExpNextPos<=mLoopBackExpEndPos)
	{
		strLoopBackingBeginDate=pStockExpDayTable->GetStockDayDateByIndex(mLoopBackExpPos);
		strLoopBackingEndDate=pStockExpDayTable->GetStockDayDateByIndex(mLoopBackExpNextPos);

		CString strInfo;
		strInfo.Format("回测 %s--%s  ",strLoopBackingBeginDate,strLoopBackingEndDate);
		doSendLogInfo(strInfo);

		Vec_HistoryResultList vecHistoryResultList;
		vecHistoryResultList=CalcExpCurveSinCmpMethod(mLoopBackExpPos,mLoopBackExpNextPos);

		SaleDestStock(strLoopBackingEndDate);		//卖出检测的最后一天股票

		if(vecHistoryResultList.size()>1)
		{
			doHandleExpHistoryResultList(vecHistoryResultList);
			mNums++;
			PrintfDebug("Now handle Nums=%d\n",mNums);
		}
		else
		{
			strInfo.Format("回测 %s--%s  没发现符合数据",strLoopBackingBeginDate,strLoopBackingEndDate);
			doSendLogInfo(strInfo);
		}
		PrintfDebug("---------------------------\n");
		mLoopBackExpPos++;
		mLoopBackExpNextPos++;
	}
		
	

	return TRUE;
}

BOOL  CCurveSinCmpLoopBack::doHandleExpHistoryResultList(Vec_HistoryResultList vecHistoryResultList)
{
	if(vecHistoryResultList.size()<2)
		return FALSE;

	HistoryResult *pHistoryResult=vecHistoryResultList[vecHistoryResultList.size()-2];

	if(pStockExpDayTable->IsNextStockDayDataExist(pHistoryResult->strEndDate))
	{

		float f_increase_perc=CalcNextInCrease(pHistoryResult->strEndDate);

		CStockDayData *pStockDayData=NULL;

		pStockDayData=pStockExpDayTable->GetNextStockDayDataByDate(strLoopBackingEndDate);

		if(pStockDayData)
		{
			CString strNextDate=pStockDayData->GetDate();
			CString strInfo;
			strInfo.Format("预测 %s 涨幅 为 %f ",strNextDate,f_increase_perc);
			doSendLogInfo(strInfo);

		}

		if(f_increase_perc>=0.35)
		{
			BuyDestStock(strLoopBackingEndDate);
		}
		else
		{
			CString strInfo;
			strInfo.Format("回测 %s--%s  预测涨幅 %f 不够百分0.35",strLoopBackingBeginDate,strLoopBackingEndDate,f_increase_perc);
			doSendLogInfo(strInfo);
		}

	}

	return TRUE;
}
//计算下一日的涨幅
float CCurveSinCmpLoopBack::CalcNextInCrease(CString strDate)
{
	
	CStockDayData *pNextStockDayData=NULL;
	CStockDayData *pStockDayData=NULL;
	
	
	pNextStockDayData=pStockExpDayTable->GetNextStockDayDataByDate(strDate);
	pStockDayData=pStockExpDayTable->GetStockDayDataByDate(strDate);

	if(!pStockDayData|| !pNextStockDayData)
		return 0.0;

	float f_dif_val=pNextStockDayData->GetEndPrice()-pStockDayData->GetEndPrice();

	float f_increase_perc=(f_dif_val*100.0)/pStockDayData->GetEndPrice();

	return f_increase_perc;
}

//购买某一日的股票
BOOL CCurveSinCmpLoopBack::BuyDestStock(CString strDate)
{
	CStockDayData *pStockDayData=NULL;
	pStockDayData=pStockDayTable->GetStockDayDataByDate(strDate);
	if(!pStockDayData)
		return FALSE;
	float f_buy_space_fund=f_total_fund*f_buy_space;
	
	float f_stock_val=pStockDayData->GetEndPrice();

	int mBuyNums=f_buy_space_fund/f_stock_val;

	float f_buy_fund=mBuyNums*f_stock_val;

	f_total_fund=f_total_fund-f_buy_fund;

	mStockBuyedNums+=mBuyNums;

	CString strInfo;
	strInfo.Format("买入 %d 股 剩余资金 %f ",mBuyNums,f_total_fund);
	doSendLogInfo(strInfo);

	return TRUE;
}
//卖出某一日的股票
BOOL CCurveSinCmpLoopBack::SaleDestStock(CString strDate)
{
	
	if(mStockBuyedNums==0)
		return FALSE;
	CStockDayData *pStockDayData=NULL;
	pStockDayData=pStockDayTable->GetStockDayDataByDate(strDate);
	if(!pStockDayData)
		return FALSE;

	float f_stock_val=pStockDayData->GetEndPrice();

	float f_sale_fund=mStockBuyedNums*f_stock_val;

	f_total_fund=f_total_fund+f_sale_fund;
	

	CString strInfo;
	strInfo.Format("卖出 %d 股 剩余资金 %f ",mStockBuyedNums,f_total_fund);
	doSendLogInfo(strInfo);

	mStockBuyedNums=0;
	return TRUE;
}

Vec_HistoryResultList CCurveSinCmpLoopBack::CalcExpCurveSinCmpMethod(int mBeginPos,int mEndPos)
{
	Vec_HistoryResultList vecHistoryResultList;

	float f_x_scale=CalcXScaleAveValue(mBeginPos,mEndPos,mXScaleMode,pStockExpDayTable);

	if(f_x_scale<=0.0)
		f_x_scale=100.0;

	CmpMethodParas mExpCmpMethodParas=BuildCurveSinCmpMethodParas(f_x_scale);

	CString strExpBeginDate=pStockExpDayTable->GetStockDayDateByIndex(mBeginPos);
	CString strExpEndDate=pStockExpDayTable->GetStockDayDateByIndex(mEndPos);

	CCurveSinCmpMethod *pCurveSinCmpMethod=NULL;
	pCurveSinCmpMethod=new CCurveSinCmpMethod();
	pCurveSinCmpMethod->SetCmpMethodParas(mExpCmpMethodParas);
	pCurveSinCmpMethod->SetStockDayTable(pStockExpDayTable);
	pCurveSinCmpMethod->SetBeginDate(strExpBeginDate);
	pCurveSinCmpMethod->SetEndDate(strExpEndDate);
	if(pCurveSinCmpMethod->Init())
	{

		if(pCurveSinCmpMethod->TraverseData())
		{
			vecHistoryResultList=pCurveSinCmpMethod->GetHistoryResultList();
		}
	}

	return vecHistoryResultList;
}
//计算X轴平均值
float CCurveSinCmpLoopBack::CalcXScaleAveValue(int mBeginPos,int mEndPos,int mXScaleMode,CStockDayTable *pTable)	
{
	float f_val=0.0;
	
	CStockDayData *pBeginStockDayData=NULL;
	pBeginStockDayData=pTable->GetStockDayDataByIndex(mBeginPos);
	CStockDayData *pEndStockDayData=NULL;
	pEndStockDayData=pTable->GetStockDayDataByIndex(mEndPos);

	
	
		

		if(pBeginStockDayData!=NULL && pEndStockDayData!=NULL)
		{

			float f_begin_val,f_end_val;
			f_begin_val=pBeginStockDayData->GetEndPrice();
			f_end_val=pEndStockDayData->GetEndPrice();
			f_val=(f_begin_val+f_end_val)/2;
			if(mXScaleMode==X_SCALE_AVE_1_20)
			{
				f_val=f_val/20.0;
				if(f_val>=100.0)
				{
					int mVal=f_val;
					int n=mVal/100;
					mVal=n*100;
					f_val=mVal;
				}
				else if(f_val>=10.0)
				{
					int mVal=f_val;
					int n=mVal/10;
					mVal=n*10;
					f_val=mVal;
				}
				else if(f_val>=1.0)
				{
					int mVal=f_val;
					f_val=mVal;
				}
				else
				{
					int n=f_val/0.1;
					f_val=n*0.1;
				}
			}
			else if(mXScaleMode==X_SCALE_AVE_1_30)
			{
				f_val=f_val/30.0;

				if(f_val>=100.0)
				{
					int mVal=f_val;
					int n=mVal/100;
					mVal=n*100;
					f_val=mVal;
				}
				else if(f_val>=10.0)
				{
					int mVal=f_val;
					int n=mVal/10;
					mVal=n*10;
					f_val=mVal;
				}
				else if(f_val>=1.0)
				{
					int mVal=f_val;
					f_val=mVal;
				}
				else
				{
					int n=f_val/0.1;
					f_val=n*0.1;
				}
			}
			else
			{
				f_val=f_val/40.0;

				if(f_val>=100.0)
				{
					int mVal=f_val;
					int n=mVal/100;
					mVal=n*100;
					f_val=mVal;
				}
				else if(f_val>=10.0)
				{
					int mVal=f_val;
					int n=mVal/10;
					mVal=n*10;
					f_val=mVal;
				}
				else if(f_val>=1.0)
				{
					int mVal=f_val;
					f_val=mVal;
				}
				else
				{
					int n=f_val/0.1;
					f_val=n*0.1;
				}
			}
		}

	
	return f_val;
}

CmpMethodParas CCurveSinCmpLoopBack::BuildCurveSinCmpMethodParas(float f_x_scale)
{
	CmpMethodParas mCmpMethodParas;
	CString strTemp;
	strTemp.Format("%f",f_x_scale);
	mCmpMethodParas["XScale"]=strTemp;

	strTemp.Format("%f",f_gate_percent);
	mCmpMethodParas["GatePercent"]=strTemp;

	strTemp.Format("%d",mEquGateNums);
	mCmpMethodParas["EquGateNums"]=strTemp;

	return mCmpMethodParas;
}

BOOL CCurveSinCmpLoopBack::doSingleCurveSinCmp(void)
{

	return TRUE;
}


BOOL CCurveSinCmpLoopBack::ParseCmpMethodParas(void)
{

	CString strXScaleMode=mapCmpMethodParas["XScaleMode"];
	if(strXScaleMode!="")
		mXScaleMode=atoi((LPCSTR)strXScaleMode);
	else
		mXScaleMode=X_SCALE_AVE_1_20;

	CString strGatePercent=mapCmpMethodParas["GatePercent"];
	if(strGatePercent!="")
		f_gate_percent=atof((LPCSTR)strGatePercent);
	else
		f_gate_percent=50.0f;

	CString strEquGateNums=mapCmpMethodParas["EquGateNums"];
	if(strEquGateNums!="")
		mEquGateNums=atoi((LPCSTR)strEquGateNums);
	else
		mEquGateNums=(mCmpMethodNums)*3/4;
	return TRUE;
}


