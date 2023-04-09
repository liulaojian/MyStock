//曲线Sin法 比较   


#pragma once
#include <vector>
#include "HistoryCmpMethod.h"

class CCurveSinCmpMethod :public CHistoryCmpMethod
{
public:
	CCurveSinCmpMethod();
	virtual ~CCurveSinCmpMethod();

public:
	virtual BOOL Init(void);
	virtual BOOL TraverseData(void);


private:
	BOOL CreateAimSinValVec(void);
	BOOL CreateAimStockDayDataVec(void);
	Vec_StockDayData CreateHistoryStockDayVec(CString strBegin,CString strEnd);
	std::vector<double> CreateHistoryStockSinValVec(Vec_StockDayData vecStockDayData);

	BOOL JudgeSinVal(std::vector<double> vecSinVal);


	BOOL  ParseCmpMethodParas(void);

private:
	double  f_x_scale;			//X  单位基数
	double  f_gate_percent;			//最后比较时的百分比阀值
	int     mEquGateNums;

	std::vector<double> vecAimSinVal;
	Vec_StockDayData vecAimStockDayData;

	
};