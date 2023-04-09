#pragma once
#include "zbTypeDef.h"
#include "StockProfitLossArithmetic.h"
#include "StockDataMgr.h"

class CStockM5M20Analysize
{
public:
	CStockM5M20Analysize(CString strCode);

	virtual ~CStockM5M20Analysize();

public:
	BOOL  AnalysisStock(CString strEndDate,BOOL bForMin,double & f_bander_chip_per,double & f_this_now_down_per,double & f_max_now_dif_per);

	BOOL IsMinStockProfitLossData(CStockProfitLossData* pStockProfitLossData);

	BOOL IsMaxStockProfitLossData(CStockProfitLossData* pStockProfitLossData);

	BOOL IsMiddleStockProfitLossData(CStockProfitLossData* pStockProfitLossData);

	double CalcStockProfitLossDataDownPer(CStockProfitLossData* pStockProfitLossData);

	//¹ÀËã×¯¼Ò³ïÂë
	double CalcBankerChip(CStockDayTable *pStockDayTable,int mMaxPos,int mNowPos,long long mTotalStockVolume);


	
private:
	CString strStockCode;


};