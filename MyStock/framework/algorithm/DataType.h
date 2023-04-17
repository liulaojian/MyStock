#pragma once

#include <vector>

typedef struct
{
	CString strStockCode;
	CString strStockName;
	float fMaxMultiple;
	float fAveMultiple;
	CString strMaxDate;
	CString strMinDate;
	int  mMaxValuePassDay;
	double fDownTotalRang;
	int mFilterNums;
	int mSpecNums;
	CString strInfo;
} DropOffData;

typedef std::vector<DropOffData *> Vec_DropOffData;


typedef struct
{
	CString strStockCode;
	CString strStockName;
	float rsi_1;
	float rsi_2;
	float rsi_3;
	float f_min_rsi1;
	float f_min_rsi2;
	float f_min_rsi3;
	float cr;
	float f_min_cr;

	float mfi;
	float f_min_mfi;

	float f_total_value;
	int   m_low_ave_5_nums;

} RSIData;

typedef std::vector<RSIData> Vec_RSIData;