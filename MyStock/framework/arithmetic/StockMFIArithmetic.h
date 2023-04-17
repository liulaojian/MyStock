#pragma once
#include <vector>
#include "KLineDataBean.h"

class CStockMFIData :public KLineBaseData
{
public:
	CStockMFIData() {}
	virtual ~CStockMFIData() {}
	std::vector<float> vec_mfi;
	int mN;
	CString strStockCode;
};


class CStockMFIArithmetic
{
public:
	CStockMFIArithmetic();
	virtual ~CStockMFIArithmetic();

	static CStockMFIData* CalcMFIData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN);
	static std::vector<float> CalcMA(int n, std::vector<float> vecmfi);
};