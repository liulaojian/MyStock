#pragma once
#include <vector>
#include "KLineDataBean.h"
//π…∆±OBVÀ„∑®¿‡

class CStockOBVData:public KLineBaseData
{
public:
	CStockOBVData() {}
	virtual ~CStockOBVData() {}
	std::vector<double> vec_obv;
	std::vector<double> vec_maobv;
	int mMaN;
	CString strStockCode;
};


class CStockOBVArithmetic
{
public:
	CStockOBVArithmetic();
	virtual ~CStockOBVArithmetic();

	static CStockOBVData* CalcOBVData(CString strStockCode,CString strDateTime,int mNums,int mType,int mMaN);


	static std::vector<double> CalcMA(int n,std::vector<double> vecobv);

};