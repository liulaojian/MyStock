#pragma once
#include "Http.h"
#include "StockMin5Table.h"
class CNetStock
{
public:
	CNetStock();
	virtual ~CNetStock();


	CString GetNearestStockMin5HttpData(CString strStockCode,int mNums);


	Vec_StockMin5Data ParseNearestStockMin5HttpData(CString strHttpData,CString strStockCode);

private:
	CHttp  mHttp;



};