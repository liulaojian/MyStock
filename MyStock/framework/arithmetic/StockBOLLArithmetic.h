#pragma once
#include <vector>
#include "KLineDataBean.h"
//π…∆±BOLLÀ„∑®¿‡

class CStockBOLLData:public KLineBaseData
{
public:
	CStockBOLLData() {}
	virtual ~CStockBOLLData() {}
	std::vector<double> vec_boll;
	std::vector<double> vec_up;
	std::vector<double> vec_down;
	int mN;
	CString strStockCode;
};


class CStockBOLLArithmetic
{
public:
	CStockBOLLArithmetic();
	virtual ~CStockBOLLArithmetic();

	static CStockBOLLData *CalcBOLLData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN1);

	static void CalcCloseAverage(int n,std::vector<double> closePrice,std::vector<double> &data);

};