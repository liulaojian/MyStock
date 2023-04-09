#pragma once
#include <vector>
#include "StockSniper.h"

class CStockK60KDJSniper:public CStockSniper
{
public:
	CStockK60KDJSniper(CString strStockCode);
	virtual ~CStockK60KDJSniper();

	virtual BOOL SniperAnalyze(BOOL bLoopBackMode);

	virtual CString GetSniperAnalyzeResult(void);

public:
//	BOOL  CalcExpMa20Ma60(BOOL bLoopBackMode);

	

private:
	CString strResultInfo;

	

	//double  f_exp_ma60_per;
	//double  f_exp_ma20_per;
	
};