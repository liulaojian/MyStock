#pragma once
#include <vector>
#include "KLineDataBean.h"
//股票MACD算法类

class CStockMACDData:public KLineBaseData
{
public:
	CStockMACDData() {}
	virtual ~CStockMACDData() {}

	std::vector<double> vec_dif;
	std::vector<double> vec_dea;
	std::vector<double> vec_macd;

	int mShortValue;
	int mLongValue;
	int mValue;

	CString strStockCode;
};


class CStockMACDArithmetic
{
public:
	CStockMACDArithmetic();
	virtual ~CStockMACDArithmetic();


	//计算出MACD的数据 
	//strStockCode 股票代码
	//strDateTime  日期
	//mNums  共多少交易日 包含日期
	//mShortValue MACD算法内的快速移动N
	//mLongValue MACD算法内的慢速移动N
	//mValue MACD算法内N

	static CStockMACDData* CalcMACDData(CString strStockCode,CString strDateTime,int mNums,int mType,int shortValue,int longValue,int mValue);


	static std::vector<double> CalcMA(int n,KLineBaseData *pKLineBaseData);
};