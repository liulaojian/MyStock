#pragma once
#include "zbTypeDef.h"
#include "StockWRArithmetic.h"
#include "StockDataMgr.h"


class CStockWRAnalysize
{
public:
	CStockWRAnalysize(CString strCode);
	virtual ~CStockWRAnalysize();

	BOOL  AnalysisStock(CString strEndDate);
private:
	CString strStockCode;
};

