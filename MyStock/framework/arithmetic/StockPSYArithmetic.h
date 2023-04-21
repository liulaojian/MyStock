#pragma once

#include <vector>
#include "KLineDataBean.h"

class CStockPSYData :public KLineBaseData
{
public:
	CStockPSYData() {}
	virtual ~CStockPSYData() {}
	std::vector<float> vec_psy;
	int mN;
	CString strStockCode;
};


class CStockPSYArithmetic
{
public:
	CStockPSYArithmetic();
	virtual ~CStockPSYArithmetic();

	static CStockPSYData* CalcPSYData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN);
	static std::vector<float> CalcMA(int n, std::vector<float> vecpsy);
};