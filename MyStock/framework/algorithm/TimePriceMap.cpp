#include "stdafx.h"
#include <stdio.h>
#include "TimePriceMapAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include <math.h> 
#include "CommonMacro.h"

CTimePriceMapAlg::CTimePriceMapAlg()
{


}

CTimePriceMapAlg::~CTimePriceMapAlg()
{


}

BOOL IsTimePriceMapSmooth(CString  strStockCode,std::vector<double> vec_close_price,std::vector<double> vec_ave_price)
{
	if(vec_close_price.size()!=vec_ave_price.size())
		return FALSE;
	int size=vec_close_price.size();

	std::vector<double> vec_ave_rang;
	for(int i=0;i<size;i++)
	{
		double f_rang;
		f_rang=(vec_close_price[i]-vec_ave_price[i])*100.0/vec_ave_price[i];
		vec_ave_rang.push_back(f_rang);
	}

	int m_match_nums=0;
	for(int i=0;i<size;i++)
	{
		double f_rang=vec_ave_rang[i];
		f_rang=abs(f_rang);
		if(f_rang<0.3)
			m_match_nums++;

	}

	printf(" %s m_match_nums=%d\n",(LPCSTR)strStockCode,m_match_nums);
	if(m_match_nums>32)
		return TRUE;

	return FALSE;
}

Vec_TimePriceMapData  CTimePriceMapAlg::doFilter(CTime mDropOffTime)
{
	Vec_TimePriceMapData vecTimePriceMapData;

	StockCode * pStockCode=NULL;
	CStockMin5Table *pStockMin5Table=NULL;
	CString strNowDate;
	CString strNowDateTime;
	Vec_StockCodeList vecStockCodeList=StockDataMgr()->GetStockCodeList();
	CStockKDJData *pStockKDJData=NULL;

	for(int i=0;i<vecStockCodeList.size();i++)
	{
		pStockCode=vecStockCodeList[i];
		if(StockDataMgr()->IsExpStock(pStockCode->strStockCode))
			continue;
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(pStockCode->strStockCode);
		strNowDateTime=pStockMin5Table->GetNearestStockDayDate(mDropOffTime);
		strNowDate=strNowDateTime;
		strNowDateTime+=" 1500";
		if(pStockKDJData)
		{
			SAFE_DELETE(pStockKDJData);
		}
		pStockKDJData=NULL;

		pStockKDJData=CStockKDJArithmetic::CalcKDJData(pStockCode->strStockCode,strNowDateTime,192,K_LINE_5IN,9,3,3);
		if(pStockKDJData==NULL)
			continue;

		std::vector<double> vec_close_price_now_day;

		std::vector<double> vec_ave_price_now_day;

		int size=pStockKDJData->vec_close_price.size();


		double f_total_volume_price=0.0;
		double f_total_volume=0.0;
		for(int i=size-48;i<size;i++)
		{
			vec_close_price_now_day.push_back(pStockKDJData->vec_close_price[i]);
			f_total_volume_price+=pStockKDJData->vec_volume_price[i];
			f_total_volume+=pStockKDJData->vec_volume[i];
			double f_ave_price=f_total_volume_price/f_total_volume;
			vec_ave_price_now_day.push_back(f_ave_price);
		}

		if(IsTimePriceMapSmooth(pStockCode->strStockCode,vec_close_price_now_day,vec_ave_price_now_day))
		{
			TimePriceMapData *pTimePriceMapData=new TimePriceMapData();
			pTimePriceMapData->strStockCode=pStockCode->strStockCode;
			pTimePriceMapData->strStockName=pStockCode->strStockName;

			pTimePriceMapData->strDateTime=strNowDate;
			pTimePriceMapData->mPara1=0;
			pTimePriceMapData->bPreDown=FALSE;
			vecTimePriceMapData.push_back(pTimePriceMapData);

		}
	}


	return vecTimePriceMapData;
}