#pragma once
#include <vector>
#include "KLineDataBean.h"

class CStockVRData :public KLineBaseData
{
public:
	CStockVRData() {}
	virtual ~CStockVRData() {}
	std::vector<float> vec_vr;
	std::vector<float> vec_mavr;
	int mN;
	int mN2;
	CString strStockCode;
};


class CStockVRArithmetic
{
public:
	CStockVRArithmetic();
	virtual ~CStockVRArithmetic();

	static CStockVRData* CalcVRData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN, int mN2);
	static std::vector<float> CalcMA(int n, std::vector<float> vecmfi);
};