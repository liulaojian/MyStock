#pragma once
#include <vector>
#include "KLineDataBean.h"
//π…∆±SARÀ„∑®¿‡

class CStockASIData:public KLineBaseData
{
public:
	CStockASIData() {}
	virtual ~CStockASIData() {}
	std::vector<double> vec_asi;
	std::vector<double> vec_maasi;
	int mN;
	CString strStockCode;
};

class CStockASIArithmetic
{
public:
	CStockASIArithmetic();
	virtual ~CStockASIArithmetic();

	static CStockASIData* CalcASIData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN);

	static std::vector<double> CalcMA(int n,std::vector<double> vecrsi);
};