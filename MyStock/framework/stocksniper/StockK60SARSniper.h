#pragma once
#include <vector>
#include "StockSniper.h"

class CStockK60SARSniper:public CStockSniper
{
public:
	CStockK60SARSniper(CString strStockCode);
	virtual ~CStockK60SARSniper();

	virtual BOOL SniperAnalyze(BOOL bLoopBackMode);

	virtual CString GetSniperAnalyzeResult(void);
public:
	BOOL  CalcExpMa20Ma60(BOOL bLoopBackMode);



private:
	CString strResultInfo;
	
	double  f_exp_4_total_per;
};