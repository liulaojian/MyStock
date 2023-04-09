#include "stdafx.h"
#include <stdio.h>
#include "BollFilterAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include <math.h> 
#include "CommonMacro.h"
#include "StockBOLLArithmetic.h"


CBollFilterAlg::CBollFilterAlg()
{

}


CBollFilterAlg::~CBollFilterAlg()
{

}


Vec_BOLLFilterData CBollFilterAlg:: doFilter(CTime mDropOffTime,Vec_DropOffData & vecDropOffData)
{
	Vec_BOLLFilterData vecBOLLFilerData;


	DropOffData * pDropOffData=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	CStockKDJData *pStockKDJData=NULL;
	CStockBOLLData *pStockBOLLData=NULL;
	for(int i=0;i<vecDropOffData.size();i++)
	{
		pDropOffData=vecDropOffData[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(pDropOffData->strStockCode);

		strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		if(pStockKDJData)
		{
			SAFE_DELETE(pStockKDJData);
		}
		pStockKDJData=NULL;


		pStockKDJData=CStockKDJArithmetic::CalcKDJData(pDropOffData->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
		if(pStockKDJData==NULL)
			continue;


		if(pStockBOLLData)
		{
			SAFE_DELETE(pStockBOLLData);
		}
		pStockBOLLData=NULL;

		pStockBOLLData=CStockBOLLArithmetic::CalcBOLLData(pDropOffData->strStockCode,strNowDate,125,K_LINE_DAY,20);
		if(!pStockBOLLData)
			continue;

		int mSize=pStockKDJData->vec_close_price.size();
		int mBollSize=pStockBOLLData->vec_boll.size();

		BOOL bOk=TRUE;
		for(int j=mBollSize-11;j<mBollSize;j++)
		{
			double f_now_boll_up=pStockBOLLData->vec_up[j];

			double f_p_boll_up=pStockBOLLData->vec_up[j-1];

			if(f_p_boll_up>=f_now_boll_up)
			{
				bOk=FALSE;
				break;
			}

		}

		if(!bOk)
			continue;

		double f_now_boll_up=pStockBOLLData->vec_up[mBollSize-1];

		double f_now_price_high=pStockKDJData->vec_high_price[mSize-1];

		double f_now_price_low=pStockKDJData->vec_low_price[mSize-1];

		bOk=FALSE;
		if(f_now_boll_up>f_now_price_low&& f_now_boll_up<f_now_price_high)
		{
			bOk=TRUE;
		}
		if(!bOk)
			continue;

		double f_p_boll_up=pStockBOLLData->vec_up[mBollSize-2];

		double f_p_price_high=pStockKDJData->vec_high_price[mSize-2];

		double f_p_price_low=pStockKDJData->vec_low_price[mSize-2];

		bOk=FALSE;
		if(f_p_boll_up>f_p_price_low&& f_p_boll_up<f_p_price_high)
		{
			bOk=TRUE;
		}
		if(!bOk)
			continue;

		printf("%s \n",pDropOffData->strStockCode);

		
		BOLLFilterData *pBOLLFilterData=new BOLLFilterData();
		pBOLLFilterData->strStockCode=pDropOffData->strStockCode;
		pBOLLFilterData->strStockName=pDropOffData->strStockName;

		pBOLLFilterData->strDateTime=strNowDate;
		pBOLLFilterData->mPara0=0;
		vecBOLLFilerData.push_back(pBOLLFilterData);

	}
	return vecBOLLFilerData;

}