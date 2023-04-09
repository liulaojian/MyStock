#pragma once

#include "KLineDataBean.h"
//股票RSI算法类
/*
1 RSI值于0-100之间呈常态分配，当6日RSI值为80以上时，股市呈超买现象，若出现M头，市场风险较大；当6日RSI值在20以下时，股市呈超卖现象，若出现W头，市场机会增大。
2 RSI一般选用6日、12日、24日作为参考基期，基期越长越有趋势性(慢速RSI)，基期越短越有敏感性，(快速RSI)。当快速RSI由下往上突破慢速RSI时，机会增大；当快速RSI由上而下跌破慢速RSI时，风险增大。
软件中RSI指标的代码为
LC := REF(CLOSE,1);【LC为昨日收盘价】
RSI$1:SMA(MAX(CLOSE-LC,0),N1,1)/SMA(ABS(CLOSE-LC),N1,1)*100;【ABS为求绝对值函数】
RSI$2:SMA(MAX(CLOSE-LC,0),N2,1)/SMA(ABS(CLOSE-LC),N2,1)*100;
RSI$3:SMA(MAX(CLOSE-LC,0),N3,1)/SMA(ABS(CLOSE-LC),N3,1)*100;
*/


class CStockRSIData:public KLineBaseData
{
public:
	CStockRSIData() {}
	virtual ~CStockRSIData() {}

	std::vector<double> vec_rsi_1_value;
	std::vector<double> vec_rsi_2_value;
	std::vector<double> vec_rsi_3_value;

	int mN1;
	int mN2;
	int mN3;

	CString strStockCode;
};
class CStockRSIArithmetic
{

public:

	CStockRSIArithmetic();
	virtual ~CStockRSIArithmetic();

	//计算出RSI的数据 
	//strStockCode 股票代码
	//strDateTime  日期
	//mNums  共多少交易日 包含日期
	//mN1 RSI算法内的N1
	//mN2 RSI算法内的N2
	//mN3 RSI算法内的N3
	static CStockRSIData* CalcRSIData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN1,int mN2,int mN3);

	static std::vector<double> CalcRSI(int n,KLineBaseData *pKLineBaseData);



};