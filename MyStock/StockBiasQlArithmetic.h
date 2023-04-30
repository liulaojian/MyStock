#pragma once
#include <vector>
#include "KLineDataBean.h"

class CStocBIASQLData :public KLineBaseData
{
public:
	CStocBIASQLData() {}
	virtual ~CStocBIASQLData() {}
	std::vector<float> vec_bias;
	std::vector<float> vec_ql;
	int mN1;
	int mN2;
	CString strStockCode;
};


class CStockBIASQLArithmetic
{
public:
	CStockBIASQLArithmetic();
	virtual ~CStockBIASQLArithmetic();

	static CStocBIASQLData* CalcBiasQlData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN1,int mN2);
	static std::vector<float> CalcMA(int n, std::vector<double> vecvalue);
};