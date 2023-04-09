#pragma once
#include "zbTypeDef.h"
#include "StockDataMgr.h"
#include "StockProfitLossArithmetic.h"
class CStockM20M40Analysize
{
public:
	CStockM20M40Analysize(CString strCode);

	virtual ~CStockM20M40Analysize();

public:
	BOOL  AnalysisStock(CString strEndDate);

	double CalcStockProfitLossDataDownPer(CStockProfitLossData* pStockProfitLossData);

private:
	CString strStockCode;


};