#pragma once
#include "zbTypeDef.h"
#include "StockDataMgr.h"
#include "StockProfitLossArithmetic.h"

class CStockMinMinMinAnalysize
{
public:
	CStockMinMinMinAnalysize(CString strCode);

	virtual ~CStockMinMinMinAnalysize();

public:
	BOOL  AnalysisStock(CString strEndDate);

	double CalcStockProfitLossDataDownPer(CStockProfitLossData* pStockProfitLossData);

	double CalcStockProfitLossDataUp0_20Per(CStockProfitLossData* pStockProfitLossData);
private:
	CString strStockCode;


};