#pragma once
#include <vector>
#include "KLineDataBean.h"

class CStockDMIData :public KLineBaseData
{
public:
	CStockDMIData() {}
	virtual ~CStockDMIData() {}
	std::vector<float> vec_pdi;
	std::vector<float> vec_mdi;
	std::vector<float> vec_adx;
	std::vector<float> vec_adxr;
	int mN1;
	int mN2;
	CString strStockCode;
};


class CStockDMIArithmetic
{
public:
	CStockDMIArithmetic();
	virtual ~CStockDMIArithmetic();

	static CStockDMIData* CalcDMIData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN1,int mN2);
	static std::vector<float> CalcMA(int n, std::vector<float> veccr);
};