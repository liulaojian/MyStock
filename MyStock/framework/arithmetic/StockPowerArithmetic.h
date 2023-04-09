#pragma once

//��Ʊ����ֵ�㷨��

#include "StockDayTable.h"
#include "StockMin5Table.h"
#include "zbTypeDef.h"

typedef struct 
{
	CString  strStockCode;		//��Ʊ����
	CString  strBeginDate;		//��ʼ����
	CString  strEndDate;		//��������
	CString  strMinPriceDate;	//��ͼ۸�����
	CString  strMaxPriceDate;	//��߼۸�����
	float	 f_min_max_power;	//��ͼ۸� -- ��߼۸� ������
	float    f_max_end_power;	//��߼۸����� -- ������� ������
	float    f_power_percent;	//�����㷨���ٷֱ�
}StockPowerArithmeticInfo;
typedef std::vector<StockPowerArithmeticInfo *> Vec_StockPowerArithmeticInfo;

typedef struct 
{
	CString  strStockCode;		//��Ʊ����
	CString  strBeginDate;		//��ʼ����
	CString  strEndDate;		//��������
	double   f_5_power;
	double   f_10_power;
	double   f_20_power;
	double   f_40_power;
	double   f_60_power;
	double   f_120_power;
	double   f_240_power;
	double   f_date_power;
}StockPowerPeriodInfo;
typedef std::vector<StockPowerPeriodInfo *> Vec_StockPowerPeriodInfo;




class CStockPowerArithmetic
{
public:
	CStockPowerArithmetic(CString strCode);
	virtual ~CStockPowerArithmetic();

	BOOL  Init(void);

	StockPowerArithmeticInfo * CalcStockPowerArithmeticInfo(CString strBeginDate,CString strEndDate);

	StockPowerArithmeticInfo * CalcLastStockPowerArithmeticInfo(int mLastNums);

	BOOL NewCalcStockPowerValue(CString strBeginDate,CString strEndDate,double &f_power_val);

	BOOL NewCalcStockPowerValue(int mBeginPos,int mEndPos,double &f_power_val);

	BOOL NewCalcLastStockPowerValue(int mLastNums,double &f_power_val);

	BOOL NewCalcLastStockPowerValue(CString strEndDate,int mN,double &f_power_val);

	StockPowerPeriodInfo * NewCalcStockPeriodInfo(CString strBeginDate,CString strEndDate);

	StockPowerPeriodInfo * NewCalcStockPeriodInfo(int mLastNums);

	Vec_CString FindSimilarStockPowerPeriodInfo(StockPowerPeriodInfo *pStockPowerPeriodInfo);


protected:
	CString strStockCode;
	CStockMin5Table *pStockMin5Table;
	CStockDayTable *pStockDayTable;

	



};
