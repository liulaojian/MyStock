#pragma once
#include <vector>
#include "KLineDataBean.h"
//π…∆±KDJÀ„∑®¿‡

class CStockKDJData:public KLineBaseData
{
public:
	CStockKDJData() {}
	virtual ~CStockKDJData() {}
	std::vector<double> vec_k;
	std::vector<double> vec_d;
	std::vector<double> vec_j;

	int n1;
	int n2;
	int n3;
	CString strStockCode;
};


class CStockKDJArithmetic
{
public:
	CStockKDJArithmetic();
	virtual ~CStockKDJArithmetic();

	static CStockKDJData *CalcKDJData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN1,int mN2,int mN3);

	static std::vector<double> CalcMA(int n,std::vector<double> vecrsi);

	
};


