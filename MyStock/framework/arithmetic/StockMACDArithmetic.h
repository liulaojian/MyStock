#pragma once
#include <vector>
#include "KLineDataBean.h"
//��ƱMACD�㷨��

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


	//�����MACD������ 
	//strStockCode ��Ʊ����
	//strDateTime  ����
	//mNums  �����ٽ����� ��������
	//mShortValue MACD�㷨�ڵĿ����ƶ�N
	//mLongValue MACD�㷨�ڵ������ƶ�N
	//mValue MACD�㷨��N

	static CStockMACDData* CalcMACDData(CString strStockCode,CString strDateTime,int mNums,int mType,int shortValue,int longValue,int mValue);


	static std::vector<double> CalcMA(int n,KLineBaseData *pKLineBaseData);
};