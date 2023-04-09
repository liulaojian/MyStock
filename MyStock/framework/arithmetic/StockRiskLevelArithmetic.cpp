#include "stdafx.h"
#include "StockRiskLevelArithmetic.h"
#include "StockDataMgr.h"
CStockRiskLevelArithmetic::CStockRiskLevelArithmetic(CString strCode)
{
	strStockCode=strCode;
	pStockMin5Table=NULL;
	pStockDayTable=NULL;
}

CStockRiskLevelArithmetic::~CStockRiskLevelArithmetic()
{

}



BOOL  CStockRiskLevelArithmetic::Init(void)
{
	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);
	pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);

	if(!pStockDayTable || !pStockMin5Table)
		return FALSE;

	return TRUE;
}