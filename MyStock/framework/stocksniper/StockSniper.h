#pragma once
#include <vector>

#include "StockMonitorData.h"
// 股票狙击类
class CStockSniper
{

public:
	CStockSniper(CString strCode);
	virtual ~CStockSniper();

	virtual BOOL SniperAnalyze(BOOL bLoopBackMode)=0;

	virtual CString GetSniperAnalyzeResult(void)=0;

public:
	//计算四周期后的涨幅，用于回测
	BOOL CalcNext4PeridRange(CString strDateTime,int mKLineType,int mPeriodNums,double & fNextRange);
	void SetStockMonitorData(CStockMonitorData *pMonitorData) {pStockMonitorData=pMonitorData;}
protected:
	CString strStockCode;

	CStockMonitorData *pStockMonitorData;
};