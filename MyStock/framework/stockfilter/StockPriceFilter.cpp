#include "stdafx.h"
#include "StockPriceFilter.h"
#include "StockDayTable.h"
#include "StockDataMgr.h"

CStockPriceFilter::CStockPriceFilter()
{
	mDayNums=0;
	f_up_percent=0.0;
	f_down_percent=0.0;
}

CStockPriceFilter::~CStockPriceFilter()
{

}


Vec_CString CStockPriceFilter::FilterStock(void)
{
	Vec_CString vecFilteredStockCodeList;
	CString strStockCode;
	CStockDayTable *pStockDayTable=NULL;
	CStockMin5Table *pStockMin5Table=NULL;
	float f_last_end_price;
	float f_min_price;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		strStockCode=vecStockCodeList[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);
		
		
		if(!pStockDayTable)
			continue;

		float f_end_value=-1.0;
		CTime time;
		time = CTime::GetCurrentTime();
		int mHour=time.GetHour();
		if(mHour>=9 && mHour<16)
		{
			if(pStockMin5Table)
				f_end_value=pStockMin5Table->GetNearestEndPriceFormHttp(20);
		}
		if(f_end_value<0.0)
			f_last_end_price=pStockDayTable->GetLastStockEndPrice();
		else
			f_last_end_price=f_end_value;

		if(f_last_end_price<0.0)
			continue;
		f_min_price=pStockDayTable->GetLastDayNumsStockMinPrice(mDayNums,10);
		if(f_min_price<0.0)
			continue;
		float f_percent=(f_last_end_price-f_min_price)*100.0/f_min_price;
		if(f_percent>f_down_percent && f_percent<f_up_percent)
			vecFilteredStockCodeList.push_back(strStockCode);


	}

	return vecFilteredStockCodeList;
}