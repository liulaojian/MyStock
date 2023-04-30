#pragma once
#include <vector>
#include "KLineDataBean.h"

class CStockCRData :public KLineBaseData
{
public:
	CStockCRData() {}
	virtual ~CStockCRData() {}
	std::vector<float> vec_cr;
	std::vector<float> vec_ma1;
	std::vector<float> vec_ma2;
	std::vector<float> vec_ma3;
	std::vector<float> vec_ma4;
	int mCRNum;
	CString strStockCode;
};


class CStockCRArithmetic
{
public:
	CStockCRArithmetic();
	virtual ~CStockCRArithmetic();

	static CStockCRData* CalcCRData(CString strStockCode, CString strDateTime, int mNums, int mType, int mCrNum);
	static std::vector<float> CalcMA(int n, std::vector<float> veccr);
};