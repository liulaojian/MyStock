#include "stdafx.h"
#include <stdio.h>
#include "ThreeLowFilterAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include <math.h> 
#include "CommonMacro.h"
#include "StockBOLLArithmetic.h"

CThreeLowFilterAlg::CThreeLowFilterAlg()
{

}


CThreeLowFilterAlg::~CThreeLowFilterAlg()
{

}



Vec_ThreeLowData  CThreeLowFilterAlg::doFilter(CTime mDropOffTime,Vec_DropOffData & vecDropOffData)
{
	Vec_ThreeLowData vecThreeLowData;

	DropOffData * pDropOffData=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	CStockKDJData *pStockKDJData=NULL;
	CStockRSIData* pStockRSIData=NULL;
	for(int i=0;i<vecDropOffData.size();i++)
	{
		pDropOffData=vecDropOffData[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(pDropOffData->strStockCode);

		strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);

		if(pStockRSIData)
		{
			SAFE_DELETE(pStockRSIData);
		}
		pStockRSIData=NULL;

		if(pStockKDJData)
		{
			SAFE_DELETE(pStockKDJData);
		}
		pStockKDJData=NULL;


		pStockKDJData=CStockKDJArithmetic::CalcKDJData(pDropOffData->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
		if(pStockKDJData==NULL)
			continue;

		pStockRSIData=CStockRSIArithmetic::CalcRSIData(pDropOffData->strStockCode,strNowDate,125,K_LINE_DAY,6,12,24); 
		if(!pStockRSIData)
			continue;


		int rsi_size=pStockRSIData->vec_rsi_1_value.size();

		double f_rsi_1=pStockRSIData->vec_rsi_1_value[rsi_size-1];
		double f_rsi_2=pStockRSIData->vec_rsi_2_value[rsi_size-1];
		double f_rsi_3=pStockRSIData->vec_rsi_3_value[rsi_size-1];

		if(pDropOffData->strStockCode=="SZ000799")
		{

			int a=0;
			a++;
		}
		
	
		std::vector<double> vec_price_ma5,vec_price_ma10,vec_price_ma20,vec_price_ma60,vec_price_ma120;
		vec_price_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
		vec_price_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
		vec_price_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
		vec_price_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);
		vec_price_ma120=CStockKDJArithmetic::CalcMA(120,pStockKDJData->vec_close_price);

		int mSize=pStockKDJData->vec_close_price.size();

		
		double f_now_price=pStockKDJData->vec_close_price[mSize-1];
		double f_p_price=pStockKDJData->vec_close_price[mSize-2];
		double f_p2_price=pStockKDJData->vec_close_price[mSize-3];
		double f_p3_price=pStockKDJData->vec_close_price[mSize-4];

		double f_now_per=(f_now_price-f_p_price)*100.0/f_p_price;
		double f_p_per=(f_p_price-f_p2_price)*100.0/f_p2_price;
		double f_p2_per=(f_p2_price-f_p3_price)*100.0/f_p3_price;

		double f_now_low_price=pStockKDJData->vec_low_price[mSize-1];
		double f_p_low_price=pStockKDJData->vec_low_price[mSize-2];
		double f_p2_low_price=pStockKDJData->vec_low_price[mSize-3];
		double f_p3_low_price=pStockKDJData->vec_low_price[mSize-4];

		double f_now_begin_price=pStockKDJData->vec_open_price[mSize-1];
		double f_p_begin_price=pStockKDJData->vec_open_price[mSize-2];
		double f_p2_begin_price=pStockKDJData->vec_open_price[mSize-3];

		BOOL bOk=FALSE;
		if(f_now_per<0.0 && f_p_per<0.0 && f_p2_per<0.0)
		{

			double f_per=f_now_per+f_p_per+f_p2_per;
			if(f_per<-3.5)
			{
				bOk=TRUE;
			}
		}

		/*if(f_now_begin_price<f_p_low_price)
		{
			if(f_p_begin_price<f_p2_low_price)
			{
				if(f_p2_begin_price<f_p3_low_price)
				{
					bOk=TRUE;
				}

			}

		}*/

		if(!bOk)
			continue;
		bOk=FALSE;
		printf("%s \n",pDropOffData->strStockCode);
		if(f_now_low_price<f_p_low_price)
		{
			if(f_p_low_price<f_p2_low_price)
			{
				bOk=TRUE;
			}

		}

		if(!bOk)
			continue;

		printf("%s %.2f %.2f %.2f\n",pDropOffData->strStockCode,f_p2_per,f_p_per,f_now_per);
		ThreeLowData *pThreeLowData=new ThreeLowData();
		pThreeLowData->strStockCode=pDropOffData->strStockCode;
		pThreeLowData->strStockName=pDropOffData->strStockName;
		pThreeLowData->f_now_per=f_now_per;
		pThreeLowData->f_p1_per=f_p_per;
		pThreeLowData->f_p2_per=f_p2_per;
		pThreeLowData->f_rsi_1=f_rsi_1;
		pThreeLowData->f_rsi_2=f_rsi_2;
		pThreeLowData->f_rsi_3=f_rsi_3;
		pThreeLowData->strDateTime=strNowDate;
		vecThreeLowData.push_back(pThreeLowData);

	}

	return vecThreeLowData;


}