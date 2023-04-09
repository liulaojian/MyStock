#pragma once

//股票盈亏算法类

#include "StockDayTable.h"
#include "StockMin5Table.h"
#include "zbTypeDef.h"



typedef struct 
{
	long mVolume;
	double fMinPrice;
	double fMaxPrice;
	double fEndPrice;
	CString strDate;
}ProfitLossInfo;
typedef	std::vector<ProfitLossInfo * > Vec_ProfitLossInfoList;




class CStockProfitLossData
{
public:
	CStockProfitLossData() {}
	virtual ~CStockProfitLossData() {}

	std::vector<ProfitLossInfo*> vec_profitloss;

	long long mTotalStockVolume;

	CString strStockCode;
	CString strBeginDate;
	CString strEndDate;

	std::vector<double> vec_up_range;

	std::vector<double> vec_down_range;

public:
	long long GetStockVolumeBwPrice(double f_low_price,double f_high_price,int mLastDayNums=0);
	
	
	//计算出目前股价的百分比波段
	BOOL CalcVolumeSectionRange(int mLastDayNums=0);

	
};

typedef	std::vector<CStockProfitLossData * > Vec_StockProfitLossData;

class CStockProfitLossArithmetic
{
public:
	CStockProfitLossArithmetic();
	virtual ~CStockProfitLossArithmetic();
	
	static CStockProfitLossData* CalcProfitLossData(CString strStockCode,CString strDate,int mNums,int mPeridDays);
	
};