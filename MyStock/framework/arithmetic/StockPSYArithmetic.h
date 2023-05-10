#pragma once

#include <vector>
#include "KLineDataBean.h"

class CStockPSYData :public KLineBaseData
{
public:
	CStockPSYData() {}
	virtual ~CStockPSYData() {}
	std::vector<float> vec_psy;
	std::vector<float> vec_mpsy;
	int mN;
	int mN2;
	CString strStockCode;
};


class CStockPSYArithmetic
{
public:
	CStockPSYArithmetic();
	virtual ~CStockPSYArithmetic();

	static CStockPSYData* CalcPSYData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN, int mN2);
	static std::vector<float> CalcMA(int n, std::vector<float> vecpsy);
};