#pragma once


#include <vector>

#include "StockDayTable.h"
#include "StockMin5Table.h"

//��Ʊ��׼�㷨 ������

enum
{
	K_LINE_DAY=0,				//ID
	K_LINE_5IN=1,
	K_LINE_15IN=2,
	K_LINE_30IN=3,
	K_LINE_60MIN=4,
};


class KLineBaseData
{
public:
	KLineBaseData() {}
	virtual ~KLineBaseData() {}
	std::vector<long> vec_time;			//ʱ��
	std::vector<double> vec_open_price;	//���̼� 
	std::vector<double> vec_high_price;	//��߼�
	std::vector<double> vec_low_price;	//��ͼ�
	std::vector<double> vec_close_price;	//������
	std::vector<double> vec_avg_price;	//ƽ���۸�
	std::vector<long> vec_volume;	//������
	std::vector<double> vec_volume_price;	////�����ܼ۸�
	int m_length;	//����
	int m_type;		//���� 
} ;
typedef std::vector<KLineBaseData *> Vec_KLineBaseData;

class CKLineDataBean
{
public:
	CKLineDataBean();
	virtual ~CKLineDataBean();

	//����Ʊ������ת��Ϊ K�߻������� strDate �� ���ڣ�mNums���� ��ǰmNums�� ������strDate)
	static KLineBaseData * ConvStockDayDataToArithmeticBaseData(CStockDayTable *pStockDayTable,CString strDate,int mNums);

	//����Ʊ5��������ת��Ϊ K�߻�������(5����) strDate �� ���ڣ�mNums���� ��ǰmNums�� ������strDate)
	static KLineBaseData * ConvStockDayDataToArithmeticBaseDataMin5(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums);

	//����Ʊ����5��������ת��Ϊ K�߻�������(��������) strDate �� ���ڣ�mNums���� ��ǰmNums�������������ݣ�5���ӵ�N��) ������strDate)
	static KLineBaseData * ConvStockDayDataToArithmeticBaseDataMulMin5(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums,int mPerNums,int mType);


	//����Ʊ15��������ת��Ϊ K�߻�������(15����) strDate �� ���ڣ�mNums���� ��ǰmNums�� ��5���ӵ�3��)������strDate)
	static KLineBaseData * ConvStockDayDataToArithmeticBaseDataMin15(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums);

	//����Ʊ30��������ת��Ϊ K�߻�������(30����) strDate �� ���ڣ�mNums���� ��ǰmNums�� ��5���ӵ�6��)������strDate)
	static KLineBaseData * ConvStockDayDataToArithmeticBaseDataMin30(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums);

	//����Ʊ30��������ת��Ϊ K�߻�������(60����) strDate �� ���ڣ�mNums���� ��ǰmNums�� ��5���ӵ�12��)������strDate)
	static KLineBaseData * ConvStockDayDataToArithmeticBaseDataMin60(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums);

	static KLineBaseData *NewKLineBaseData(int mArithType);

	//����ֵҪ����������������Ҫ�� �������ڲ��� 15 30 60 ����������
	static double CalcDateTimeCorrect(CString strDateTime,int mType,std::vector<double> vec_value);


	//��������ֵ
	static BOOL CalcPowerValue(std::vector<double> vec_close,std::vector<double> vec_volume_price,int mN,double & f_power_val);
};