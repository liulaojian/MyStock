#pragma once

#include "KLineDataBean.h"
//股票CCI算法类

//　CCI：(TYP-TYP的N日简单移动平均)/(0.015*TYP的N日平均绝对方差)
//TYP赋值：(最高价+最低价+收盘价)/3

//平均绝对方差   所有单个观测值与算术平均值的偏差的绝对值的平均

class CStockCCIData:public KLineBaseData
{
public:
	CStockCCIData() {}
	virtual ~CStockCCIData() {}
	
	std::vector<double> vec_cci_value;

	int mN;

	CString strStockCode;
};

class CStockCCIArithmetic
{

public:

	CStockCCIArithmetic();
	virtual ~CStockCCIArithmetic();


	//计算出CCI的数据 
	//strStockCode 股票代码
	//strDateTime  日期
	//mNums  共多少交易日 包含日期
	//mN CCI算法内的N
	static CStockCCIData* CalcCCIData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN);



};
