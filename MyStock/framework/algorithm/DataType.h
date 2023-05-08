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

	float f_max_cci_value;
	int m_max_cci_num;

	float f_max_cci_value_after_up_100;
	int  m_max_cci_value_after_up_100_num;

	int m_cci_up_100_num;

	int m_cci_down_100_num;

	float f_now_cci_value;

	float f_max_cci_index_cr_value;

	float f_cci_up_100_index_cr_value;

	float f_cci_down_100_index_cr_value;

	float f_vr_per_increase_bw_up100_max;		//vr值从cci up 100 -> max 每周期增长值

	int m_nums_bw_up100_max;				//从cci up 100 -> max 周期数

	float f_vr_per_increase_bw_up100_now;		//vr值从cci up 100 -> now 每周期增长值

	int m_nums_bw_up100_now;				//从cci up 100 -> now 周期数

} CCIVRAngleData;


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
	int   m_min_rsi_day;
	
	float f_max_rsi1;
	float f_max_rsi2;
	float f_max_rsi3;
	int   m_max_rsi_day;

	float cr;
	float f_min_cr;
	float f_max_cr;
	int   m_min_cr_day;
	int   m_max_cr_day;

	float mfi;
	float f_min_mfi;
	float f_max_mfi;
	int   m_min_mfi_day;
	int   m_max_mfi_day;


	float vr;
	float f_min_vr;
	float f_max_vr;
	int m_min_vr_day;
	int m_max_vr_day;
	bool b_vr_upcross;

	float f_boll_up_per[5];
	float f_up_shadow_line_per[5];
	float f_down_shadow_line_per[5];
	float f_ma5_per[5];
	float f_close_increase_per[5];

	double f_cr_ma1[5];
	double f_cr_ma2[5];
	double f_cr_ma3[5];
	double f_cr_ma4[5];

	CCIVRAngleData m_ccivr_data;

	float f_total_value;
	int   m_low_ave_5_nums;

} RSIData;

typedef std::vector<RSIData> Vec_RSIData;

typedef std::vector<RSIData*> PVecRSIData;


