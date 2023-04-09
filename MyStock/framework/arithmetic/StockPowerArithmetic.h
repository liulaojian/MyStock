#pragma once

//股票能量值算法类

#include "StockDayTable.h"
#include "StockMin5Table.h"
#include "zbTypeDef.h"

typedef struct 
{
	CString  strStockCode;		//股票代码
	CString  strBeginDate;		//开始日期
	CString  strEndDate;		//结束日期
	CString  strMinPriceDate;	//最低价格日期
	CString  strMaxPriceDate;	//最高价格日期
	float	 f_min_max_power;	//最低价格 -- 最高价格 的能量
	float    f_max_end_power;	//最高价格日期 -- 最后日期 的能量
	float    f_power_percent;	//能量算法最后百分比
}StockPowerArithmeticInfo;
typedef std::vector<StockPowerArithmeticInfo *> Vec_StockPowerArithmeticInfo;

typedef struct 
{
	CString  strStockCode;		//股票代码
	CString  strBeginDate;		//开始日期
	CString  strEndDate;		//结束日期
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
