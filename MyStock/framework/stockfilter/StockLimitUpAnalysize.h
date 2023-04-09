#pragma once
#include "zbTypeDef.h"
#include "StockProfitLossArithmetic.h"
#include "StockDataMgr.h"

class CStockLimitUpAnalysize
{
public:
	CStockLimitUpAnalysize(CString strCode);
	virtual ~CStockLimitUpAnalysize();


public:
	BOOL  AnalysisStock(CString strEndDate,BOOL bForMin,double & f_bander_chip_per,double & f_this_now_down_per,double & f_this_min_down_per);

	BOOL IsMinStockProfitLossData(CStockProfitLossData* pStockProfitLossData);

	BOOL IsMaxStockProfitLossData(CStockProfitLossData* pStockProfitLossData);

	BOOL IsMiddleStockProfitLossData(CStockProfitLossData* pStockProfitLossData);

	double CalcStockProfitLossDataDownPer(CStockProfitLossData* pStockProfitLossData);

	//¹ÀËã×¯¼Ò³ïÂë
	double CalcBankerChip(CStockDayTable *pStockDayTable,int mMaxPos,int mNowPos,long long mTotalStockVolume);


private:
	CString strStockCode;


};