#include "stdafx.h"
#include "StockKDJAnalysize.h"
#include "StockKDJArithmetic.h"
#include "StockCCIArithmetic.h"
#include "StockMACDArithmetic.h"
#include "CommonMacro.h"
#include "Convert.h"
CStockKDJAnalysize::CStockKDJAnalysize(CString strCode)
{
	strStockCode=strCode;
}

CStockKDJAnalysize::~CStockKDJAnalysize()
{

}


BOOL CStockKDJAnalysize:: AnalysisStock(CString strEndDate,double fMacdMul)
{
	CStockDayTable *pStockDayTable=NULL;
	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);

	if(!pStockDayTable)
		return FALSE;
	CStockMACDData* pStockMACDData=NULL;
	pStockMACDData=CStockMACDArithmetic::CalcMACDData(strStockCode,strEndDate,125,K_LINE_DAY,12,26,9);
	if(pStockMACDData==NULL)
	{
		return FALSE;
	}

	int mMACDLength=pStockMACDData->m_length;

	double f_now_macd_val=pStockMACDData->vec_macd[mMACDLength-1];
	double f_l_macd_val=pStockMACDData->vec_macd[mMACDLength-2];
	double f_l_l_macd_val=pStockMACDData->vec_macd[mMACDLength-3];

	if(f_now_macd_val>0.0)
	{
		SAFE_DELETE(pStockMACDData);
		return FALSE;
	}

	BOOL bOK1=FALSE;
	if(f_now_macd_val<f_l_macd_val)
	{
		if(f_l_macd_val<f_l_l_macd_val)
		{
			bOK1=TRUE;
		}
	}


	

	if(!bOK1)
	{
		SAFE_DELETE(pStockMACDData);
		return FALSE;
	}

	
	
	double f_now_price=pStockMACDData->vec_close_price[mMACDLength-1];

	double f_tmp=abs(f_now_macd_val);

	f_tmp=f_tmp*fMacdMul;		//20.0

	BOOL bOK2=FALSE;
	if(f_tmp>=f_now_price)
	{
		bOK2=TRUE;
	}
	
	if(!bOK2)
	{
		SAFE_DELETE(pStockMACDData);
		return FALSE;
	}

	



	BOOL bOK3=FALSE;
	CStockProfitLossData* pNowStockProfitLossData=NULL;
	pNowStockProfitLossData=CStockProfitLossArithmetic::CalcProfitLossData(strStockCode,strEndDate,240,50);

	if(pNowStockProfitLossData)
	{
		pNowStockProfitLossData->CalcVolumeSectionRange();

		double f_now_duty_down_total=CalcStockProfitLossDataDownPer(pNowStockProfitLossData);
		if(f_now_duty_down_total<10.0)
		{
			bOK3=TRUE;
		}
	}

	if(!bOK3)
	{
		SAFE_DELETE(pStockMACDData);
		SAFE_DELETE(pNowStockProfitLossData);
		return FALSE;
	}


	
	SAFE_DELETE(pStockMACDData);
	SAFE_DELETE(pNowStockProfitLossData);
	return TRUE;
	

	
}

double CStockKDJAnalysize::CalcStockProfitLossDataDownPer(CStockProfitLossData* pStockProfitLossData)
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
