#pragma once

#include "KLineDataBean.h"
//��ƱRSI�㷨��
/*
1 RSIֵ��0-100֮��ʳ�̬���䣬��6��RSIֵΪ80����ʱ�����гʳ�������������Mͷ���г����սϴ󣻵�6��RSIֵ��20����ʱ�����гʳ�������������Wͷ���г���������
2 RSIһ��ѡ��6�ա�12�ա�24����Ϊ�ο����ڣ�����Խ��Խ��������(����RSI)������Խ��Խ�������ԣ�(����RSI)��������RSI��������ͻ������RSIʱ���������󣻵�����RSI���϶��µ�������RSIʱ����������
�����RSIָ��Ĵ���Ϊ
LC := REF(CLOSE,1);��LCΪ�������̼ۡ�
RSI$1:SMA(MAX(CLOSE-LC,0),N1,1)/SMA(ABS(CLOSE-LC),N1,1)*100;��ABSΪ�����ֵ������
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

	//�����RSI������ 
	//strStockCode ��Ʊ����
	//strDateTime  ����
	//mNums  �����ٽ����� ��������
	//mN1 RSI�㷨�ڵ�N1
	//mN2 RSI�㷨�ڵ�N2
	//mN3 RSI�㷨�ڵ�N3
	static CStockRSIData* CalcRSIData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN1,int mN2,int mN3);

	static std::vector<double> CalcRSI(int n,KLineBaseData *pKLineBaseData);



};