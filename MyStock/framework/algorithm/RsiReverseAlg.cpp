#include "stdafx.h"
#include <stdio.h>
#include "RsiReverseAlg.h"
#include "StockRSIArithmetic.h"
#include "TanAngleAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include "CommonMacro.h"
#include "Convert.h"

CRsiReverseAlg::CRsiReverseAlg()
{


}

CRsiReverseAlg::~CRsiReverseAlg()
{


}


Vec_RsiAlgData  CRsiReverseAlg::doFilter(CTime mDropOffTime)
{
	Vec_RsiAlgData vecRsiAlgData;

	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	Vec_StockCodeList vecStockCodeList=StockDataMgr()->GetStockCodeList();

	
	CStockRSIData* pStockRSIData=NULL;
	CStockKDJData *pStockKDJData=NULL;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		pStockCode=vecStockCodeList[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
		strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		
		if(pStockRSIData)
		{
			SAFE_DELETE(pStockRSIData);
		}

		if(pStockKDJData)
		{
			SAFE_DELETE(pStockKDJData);
		}
		pStockKDJData=NULL;


		if(pStockCode->strStockCode=="SH600759")
		{
			int a=0;
			a++;

		}
		pStockRSIData=NULL;
		pStockRSIData=CStockRSIArithmetic::CalcRSIData(pStockCode->strStockCode,strNowDate,125,K_LINE_DAY,6,12,24); 
		if(!pStockRSIData)
			continue;


		int size=pStockRSIData->vec_rsi_1_value.size();

		pStockKDJData=CStockKDJArithmetic::CalcKDJData(pStockCode->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
		if(pStockKDJData==NULL)
			continue;


		std::vector<double> vec_price_ma5,vec_price_ma10;
		vec_price_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
		vec_price_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);

		int kdj_size=vec_price_ma10.size();

		double f_now_m5=vec_price_ma5[kdj_size-1];
		double f_now_m10=vec_price_ma10[kdj_size-1];

		double f_m5_m10_per=f_now_m5/f_now_m10;

		BOOL bOk1=FALSE;
		int mOk1Index=-1;
		for(int j=size-28;j<size-9;j++)
		{
			if(pStockRSIData->vec_rsi_1_value[j]<15.0)
			{
				bOk1=TRUE;
				mOk1Index=j;
				break;
			}
		}

		

		BOOL bOk2=FALSE;
		int mOk2Index=-1;
	
		
		if(pStockRSIData->vec_rsi_1_value[size-1]<27.0&&pStockRSIData->vec_rsi_1_value[size-1]>20.0)
		{
			bOk2=TRUE;
			mOk2Index=size-1;
		}

		BOOL bOk3=FALSE;
		if(mOk1Index>=0&&mOk2Index>=0)
		{
			double f_ok1_close_value=pStockRSIData->vec_close_price[mOk1Index];
			double f_ok2_close_value=pStockRSIData->vec_close_price[mOk2Index];

			if(f_ok2_close_value<f_ok1_close_value)
			{
				bOk3=TRUE;
			}
		}

		if(bOk3)
		{

			int vec_time_size=pStockRSIData->vec_time.size();
			int diff=0;
			if(vec_time_size>size)
				diff=vec_time_size-size;
			
			CTime time(pStockRSIData->vec_time[mOk1Index+diff]);

			CString strMinDateTime=ConverCTimeToString(time);

			CTime time2(pStockRSIData->vec_time[mOk2Index+diff]);

			CString strMaxDateTime=ConverCTimeToString(time2);



			RsiAlgData *pRsiAlgData=new RsiAlgData();
			
			pRsiAlgData->strStockCode=pStockCode->strStockCode;
			pRsiAlgData->strStockName=pStockCode->strStockName;
			
			pRsiAlgData->strDateTime=strNowDate;
			pRsiAlgData->f_pre_rsi1=pStockRSIData->vec_rsi_1_value[mOk1Index];
			pRsiAlgData->f_pre_rsi2=pStockRSIData->vec_rsi_2_value[mOk1Index];
			pRsiAlgData->f_pre_rsi3=pStockRSIData->vec_rsi_3_value[mOk1Index];

			pRsiAlgData->f_later_rsi1=pStockRSIData->vec_rsi_1_value[mOk2Index];
			pRsiAlgData->f_later_rsi2=pStockRSIData->vec_rsi_2_value[mOk2Index];
			pRsiAlgData->f_later_rsi3=pStockRSIData->vec_rsi_3_value[mOk2Index];

			pRsiAlgData->f_m5_m10_per=f_m5_m10_per;
			pRsiAlgData->strMinDateTime=strMinDateTime;
			pRsiAlgData->strMaxDateTime=strMaxDateTime;
			vecRsiAlgData.push_back(pRsiAlgData);


		}



	}

	return vecRsiAlgData;
}