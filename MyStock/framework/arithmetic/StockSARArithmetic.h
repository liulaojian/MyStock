#pragma once
#include <vector>
#include "KLineDataBean.h"
//π…∆±SARÀ„∑®¿‡

class CStockSARData:public KLineBaseData
{
public:
	CStockSARData() {}
	virtual ~CStockSARData() {}
	std::vector<double> vec_sar;
	int mN;
	CString strStockCode;
};


class CStockSARArithmetic
{
public:
	CStockSARArithmetic();
	virtual ~CStockSARArithmetic();

	static CStockSARData* CalcSARData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN);
};