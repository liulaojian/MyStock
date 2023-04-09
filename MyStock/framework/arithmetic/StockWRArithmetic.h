#pragma once
#include <vector>
#include "KLineDataBean.h"
//π…∆±KDJÀ„∑®¿‡

class CStocWRData:public KLineBaseData
{
public:
	CStocWRData() {}
	virtual ~CStocWRData() {}
	std::vector<double> vec_wr1;
	std::vector<double> vec_wr2;

	int n1;
	int n2;
	CString strStockCode;
};


class CStockWRArithmetic
{
public:
	CStockWRArithmetic();
	virtual ~CStockWRArithmetic();

	static CStocWRData *CalcWRData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN1,int mN2);

	static std::vector<double> CalcMA(int n,std::vector<double> vecrsi);


};

