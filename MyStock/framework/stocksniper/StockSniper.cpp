#include "stdafx.h"
#include "StockSniper.h"
#include "StockDataMgr.h"
#include "KLineDataBean.h"
CStockSniper::CStockSniper(CString strCode)
{
	strStockCode=strCode;
	pStockMonitorData=NULL;
}

CStockSniper::~CStockSniper()
{

}



//计算四周期后的涨幅，用于回测
BOOL CStockSniper::CalcNext4PeridRange(CString strDateTime,int mKLineType,int mPeriodNums,double & fNextRange)
{
	CStockMin5Table *pStockMin5Table=NULL;
	pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);
	if(!pStockMin5Table)
		return FALSE;

	int mNowIndex= pStockMin5Table->GetStockMin5Index(strDateTime);

	if(mNowIndex==-1)
		return FALSE;

	CStockMin5Data *pNowStockMin5Data=pStockMin5Table->GetStockMin5DataByIndex(mNowIndex);

	if(pNowStockMin5Data==NULL)
		return FALSE;

	int mNums=0;
	switch(mKLineType)
	{
	case K_LINE_60MIN:
		mNums=mPeriodNums*12;
		break;
	case K_LINE_30IN:
		mNums=mPeriodNums*6;
		break;
	}

	if(mNums==0)
		return FALSE;

	CStockMin5Data *pNextStockMin5Data=pStockMin5Table->GetStockMin5DataByIndex(mNowIndex+mNums);
	if(pNextStockMin5Data==NULL)
		return FALSE;

	double fNowPrice=pNowStockMin5Data->GetEndPrice();

	double fNextPrice=pNextStockMin5Data->GetEndPrice();

	fNextRange=(fNextPrice-fNowPrice)*100.0/fNowPrice;

	return TRUE;
}