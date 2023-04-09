#pragma once
#include <vector>
#include "StockSniper.h"

class CStockK60CCISniper:public CStockSniper
{
public:
	CStockK60CCISniper(CString strStockCode);
	virtual ~CStockK60CCISniper();

	virtual BOOL SniperAnalyze(BOOL bLoopBackMode);

	virtual CString GetSniperAnalyzeResult(void);

public:
	BOOL  CalcExpMa20Ma60(BOOL bLoopBackMode);

	BOOL  CalcSamplePowerIsOk(double f_cci_sample,double f_10_sample,double f_20_sample,double f_40_sample,double f_60_sample,double f_120_sample,double f_240_sample,double f_range);

private:
	CString strResultInfo;

	double  f_exp_ma60_per;
	double  f_exp_ma20_per;
	double  f_exp_ma10_per;
	double  f_exp_ma5_per;
	double  f_exp_4_total_per;		//指数 4个周期内 的平均涨幅
	//double  f_exp_12_ave_per;	//指数12个周期内 的平均涨幅（12/3）

	double f_10_power,f_20_power,f_40_power,f_60_power,f_120_power,f_240_power;
	double f_min_cci_val;

};