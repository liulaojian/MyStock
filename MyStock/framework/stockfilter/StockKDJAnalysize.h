#pragma once
#include "zbTypeDef.h"
#include "StockProfitLossArithmetic.h"
#include "StockDataMgr.h"

class CStockKDJAnalysize
{
public:
	CStockKDJAnalysize(CString strCode);

	virtual ~CStockKDJAnalysize();

public:
	BOOL  AnalysisStock(CString strEndDate,double fMacdMul);
	double CalcStockProfitLossDataDownPer(CStockProfitLossData* pStockProfitLossData);


private:
	CString strStockCode;


};