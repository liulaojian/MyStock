#include "stdafx.h"
#include "StockM20M40Analysize.h"
#include "StockKDJArithmetic.h"
#include "StockCCIArithmetic.h"
#include "StockMACDArithmetic.h"

#include "CommonMacro.h"
#include "Convert.h"


CStockM20M40Analysize::CStockM20M40Analysize(CString strCode)
{
	strStockCode=strCode;
}

CStockM20M40Analysize::~CStockM20M40Analysize()
{

}


double CStockM20M40Analysize::CalcStockProfitLossDataDownPer(CStockProfitLossData* pStockProfitLossData)
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

BOOL  CStockM20M40Analysize::AnalysisStock(CString strEndDate)
{
	CStockDayTable *pStockDayTable=NULL;
	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);

	if(!pStockDayTable)
		return FALSE;

	if(StockDataMgr()->IsExpStock(strStockCode))
		return FALSE;

	CStockKDJData *pStockKDJData=NULL;

	/*CString strDateEndTime;
	strDateEndTime=strEndDate;
	strDateEndTime+=" 1500";*/

	pStockKDJData=CStockKDJArithmetic::CalcKDJData(strStockCode,strEndDate,125,K_LINE_DAY,9,3,3);

	if(pStockKDJData==NULL)
		return FALSE;


	int mLength=pStockKDJData->m_length;

	/*
	std::vector<double> vec_ma5,vec_ma10,vec_ma20,vec_ma40;
	vec_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
	vec_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
	vec_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
	vec_ma40=CStockKDJArithmetic::CalcMA(40,pStockKDJData->vec_close_price);

	int mM5Length=vec_ma5.size();
	int mM20Length=vec_ma20.size();
	int mM40Length=vec_ma40.size();

	double f_now_m5_val=vec_ma5[mM5Length-1];
	double f_p_m5_val=vec_ma5[mM5Length-5];

	double f_now_m20_val=vec_ma20[mM20Length-1];
	double f_p_m20_val=vec_ma20[mM20Length-5];

	double f_now_m40_val=vec_ma40[mM40Length-1];


	if(f_p_m5_val<f_p_m20_val)
	{
		if(f_now_m5_val>f_now_m20_val)
		{
			if(f_now_m20_val>f_now_m40_val)
			{
				SAFE_DELETE(pStockKDJData);
				return TRUE;
			}
		}
	}
	*/

	double f_now_j=pStockKDJData->vec_j[mLength-1];
	double f_p_j=pStockKDJData->vec_j[mLength-2];
	if(f_now_j<-0.0 )	//&& (f_now_j>f_p_j)
	{

		
		int mPos=pStockDayTable->GetStockDayIndex(strEndDate);
		if(mPos<=30)
		{
			SAFE_DELETE(pStockKDJData);
			return FALSE;
		}
		Vec_StockProfitLossData  vecStockProfitLossData;
		int mBeginPos=mPos-10;
		for(int i=0;i<=10;i++)
		{

			CString strNowDate=pStockDayTable->GetStockDayDateByIndex(mBeginPos+i);
			if(strNowDate=="")
				continue;
			CStockProfitLossData* pStockProfitLossData=NULL;
			pStockProfitLossData=CStockProfitLossArithmetic::CalcProfitLossData(strStockCode,strNowDate,240,50);
			if(pStockProfitLossData)
			{
				
				pStockProfitLossData->CalcVolumeSectionRange();
				vecStockProfitLossData.push_back(pStockProfitLossData);
			}
		}


		double f_max_val=-99999.0;
		double f_max_val_of_down_per=-999.0;
		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			CStockProfitLossData* pStockProfitLossData=NULL;
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
				continue;
			CStockDayData* pStockDayData=pStockDayTable->GetStockDayDataByDate(pStockProfitLossData->strEndDate);
			if(!pStockDayData)
				continue;

			if(pStockDayData->GetEndPrice()>f_max_val)
			{
				f_max_val=pStockDayData->GetEndPrice();
				f_max_val_of_down_per=CalcStockProfitLossDataDownPer(pStockProfitLossData);
			}
		}
		
		if(f_max_val_of_down_per<0.0)
		{
			SAFE_DELETE(pStockKDJData);
			return FALSE;
		}
		
		CStockProfitLossData* pNowStockProfitLossData=NULL;
		pNowStockProfitLossData=vecStockProfitLossData[vecStockProfitLossData.size()-1];

		double f_now_val_of_down_per=CalcStockProfitLossDataDownPer(pNowStockProfitLossData);

		double f_down_per_dif=(f_max_val_of_down_per-f_now_val_of_down_per);

		if(f_down_per_dif>30.0)		//12
		{
			PrintfDebug("%s  dif=%.2f\n",strStockCode,f_down_per_dif);
			SAFE_DELETE(pStockKDJData);
			return TRUE;
		}
		
	}

	SAFE_DELETE(pStockKDJData);

	return FALSE;
}