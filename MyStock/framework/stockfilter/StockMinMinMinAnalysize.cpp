#include "stdafx.h"
#include "StockMinMinMinAnalysize.h"

#include "CommonMacro.h"
#include "Convert.h"


CStockMinMinMinAnalysize::CStockMinMinMinAnalysize(CString strCode)
{
	strStockCode=strCode;
}

CStockMinMinMinAnalysize::~CStockMinMinMinAnalysize()
{

}


double CStockMinMinMinAnalysize::CalcStockProfitLossDataDownPer(CStockProfitLossData* pStockProfitLossData)
{
	double f_duty_up_0_2,f_duty_up_2_4,f_duty_up_4_6,f_duty_up_6_8,f_duty_up_8_10,f_duty_up_10;
	double f_duty_down_0_2,f_duty_down_2_4,f_duty_down_4_6,f_duty_down_6_8,f_duty_down_8_10,f_duty_down_10;

	f_duty_up_0_2=pStockProfitLossData->vec_up_range[0]+pStockProfitLossData->vec_up_range[1];
	f_duty_up_2_4=pStockProfitLossData->vec_up_range[2]+pStockProfitLossData->vec_up_range[3];
	f_duty_up_4_6=pStockProfitLossData->vec_up_range[4]+pStockProfitLossData->vec_up_range[5];
	f_duty_up_6_8=pStockProfitLossData->vec_up_range[6]+pStockProfitLossData->vec_up_range[7];
	f_duty_up_8_10=pStockProfitLossData->vec_up_range[8]+pStockProfitLossData->vec_up_range[9];

	f_duty_up_10=0.0;
	for(int j=10;j<=49;j++)
	{
		f_duty_up_10+=pStockProfitLossData->vec_up_range[j];
	}


	f_duty_down_0_2=pStockProfitLossData->vec_down_range[0]+pStockProfitLossData->vec_down_range[1];
	f_duty_down_2_4=pStockProfitLossData->vec_down_range[2]+pStockProfitLossData->vec_down_range[3];
	f_duty_down_4_6=pStockProfitLossData->vec_down_range[4]+pStockProfitLossData->vec_down_range[5];
	f_duty_down_6_8=pStockProfitLossData->vec_down_range[6]+pStockProfitLossData->vec_down_range[7];
	f_duty_down_8_10=pStockProfitLossData->vec_down_range[8]+pStockProfitLossData->vec_down_range[9];


	f_duty_down_10=0.0;

	for(int j=10;j<=49;j++)
	{
		f_duty_down_10+=pStockProfitLossData->vec_down_range[j];
	}

	double f_duty_down_0_10=f_duty_down_0_2+f_duty_down_2_4+f_duty_down_4_6+f_duty_down_6_8+f_duty_down_8_10;

	double f_duty_down_total=f_duty_down_0_10+f_duty_down_10;


	return f_duty_down_total;

}


double CStockMinMinMinAnalysize::CalcStockProfitLossDataUp0_20Per(CStockProfitLossData* pStockProfitLossData)
{
	double f_duty_up_20=0.0;
	for(int j=0;j<20;j++)
	{
		f_duty_up_20+=pStockProfitLossData->vec_up_range[j];
	}

	return f_duty_up_20;
}

BOOL  CStockMinMinMinAnalysize::AnalysisStock(CString strEndDate)
{
	CStockDayTable *pStockDayTable=NULL;
	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);

	if(!pStockDayTable)
		return FALSE;

	if(StockDataMgr()->IsExpStock(strStockCode))
		return FALSE;

	CStockProfitLossData* pStockProfitLossData=NULL;
	pStockProfitLossData=CStockProfitLossArithmetic::CalcProfitLossData(strStockCode,strEndDate,240,50);
	if(pStockProfitLossData)
	{
		pStockProfitLossData->CalcVolumeSectionRange();
		
		double f_total_down_per=CalcStockProfitLossDataDownPer(pStockProfitLossData);

		double f_0_20_up_per=CalcStockProfitLossDataUp0_20Per(pStockProfitLossData);

		if(f_total_down_per<0.5 && f_0_20_up_per<25.0)
		{
			PrintfDebug("%s  f_0_20_up_per=%.2f\n",pStockProfitLossData->strStockCode,f_0_20_up_per);
			return TRUE;
		}
	}

	
	return FALSE;
}