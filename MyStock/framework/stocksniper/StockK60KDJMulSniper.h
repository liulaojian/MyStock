#pragma once
#include <vector>
#include "StockSniper.h"
#include "StockKDJMulSniper.h"

class CStockK60KDJMulSniper:public CStockSniper
{
public:
	CStockK60KDJMulSniper(CString strStockCode);
	virtual ~CStockK60KDJMulSniper();


	virtual BOOL SniperAnalyze(BOOL bLoopBackMode);

	virtual CString GetSniperAnalyzeResult(void);

public:

	KDJMulSniperInfo AnalyzeKDJ(std::vector<double> vec_calc_k,std::vector<double> vec_calc_d,std::vector<double> vec_calc_j,int mWidth);

private:

	CString strResultInfo;

};