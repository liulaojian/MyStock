#pragma once

#include "KLineDataBean.h"
//��ƱCCI�㷨��

//��CCI��(TYP-TYP��N�ռ��ƶ�ƽ��)/(0.015*TYP��N��ƽ�����Է���)
//TYP��ֵ��(��߼�+��ͼ�+���̼�)/3

//ƽ�����Է���   ���е����۲�ֵ������ƽ��ֵ��ƫ��ľ���ֵ��ƽ��

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


	//�����CCI������ 
	//strStockCode ��Ʊ����
	//strDateTime  ����
	//mNums  �����ٽ����� ��������
	//mN CCI�㷨�ڵ�N
	static CStockCCIData* CalcCCIData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN);



};
