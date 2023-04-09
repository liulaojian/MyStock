#include "stdafx.h"
#include "StockWRAnalysize.h"
#include "CommonMacro.h"
CStockWRAnalysize::CStockWRAnalysize(CString strCode)
{
	strStockCode=strCode;
}


CStockWRAnalysize::~CStockWRAnalysize()
{

}


BOOL  CStockWRAnalysize::AnalysisStock(CString strEndDate)
{
	CStockDayTable *pStockDayTable=NULL;
	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);

	if(!pStockDayTable)
		return FALSE;
	CStocWRData* pStocWRData=NULL;
	pStocWRData=CStockWRArithmetic::CalcWRData(strStockCode,strEndDate,125,K_LINE_DAY,10,6);
	if(pStocWRData==NULL)
	{
		return FALSE;
	}

	int length=pStocWRData->vec_wr1.size();

	double f_now_wr1=pStocWRData->vec_wr1[length-1];
	double f_last_wr1=pStocWRData->vec_wr1[length-2];


	double f_now_wr2=pStocWRData->vec_wr2[length-1];
	double f_last_wr2=pStocWRData->vec_wr2[length-2];

	BOOL bOK1=FALSE;
	if(f_now_wr2>70 && f_now_wr2<85)
	{
		if(f_last_wr2>f_now_wr2)
		{
			if(f_now_wr1>70 && f_now_wr1<85)
			{
				if(f_last_wr1>f_now_wr1)
					bOK1=TRUE;
			}
			
		}
	}

	if(!bOK1)
	{
		SAFE_DELETE(pStocWRData);
		return FALSE;
	}

	SAFE_DELETE(pStocWRData);
	return TRUE;
}