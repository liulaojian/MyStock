#pragma once
#include "zbTypeDef.h"
#include "StockProfitLossArithmetic.h"
#include "StockDataMgr.h"

class CStockMiddleUpAnalysize
{
public:
	CStockMiddleUpAnalysize(CString strCode);
	virtual ~CStockMiddleUpAnalysize();


public:
	BOOL  AnalysisStock(CString strEndDate,double & f_bander_chip_per);

	BOOL IsMinStockProfitLossData(CStockProfitLossData* pStockProfitLossData);

	BOOL IsMaxStockProfitLossData(CStockProfitLossData* pStockProfitLossData);

	BOOL IsMiddleStockProfitLossData(CStockProfitLossData* pStockProfitLossData);

	double CalcStockProfitLossDataDownPer(CStockProfitLossData* pStockProfitLossData);

	//¹ÀËã×¯¼Ò³ïÂë
	double CalcBankerChip(CStockDayTable *pStockDayTable,int mMaxPos,int mNowPos,long long mTotalStockVolume);


private:
	CString strStockCode;


};