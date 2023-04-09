#include "stdafx.h"
#include "StockDayData.h"

CStockDayData::CStockDayData()
{
	strDate="";		
	fBeginPrice=0.0;		
	fMaxPrice=0.0;
	fMinPrice=0.0;
	fEndPrice=0.0;
	mTotalVolume=0;		
	fTotalPrice=0.0;		

}


CStockDayData::~CStockDayData()
{

}