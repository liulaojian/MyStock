
#pragma once

#include <vector>

typedef struct
{
	CString strStockCode;
	CString strStockName;
	int mPara1;
	int mPara2;
	int mPara3;
	CString strDateTime;
	
} TriAngleData;

typedef std::vector<TriAngleData *> Vec_TriAngleData;



typedef struct
{
	CString strStockCode;
	CString strStockName;
	double fPara0;
	double fPara1;
	double fPara2;
	double fPara3;
	double fPara4;
	double fPara5;
	double fPara6;
	double fPara7;
	double fPara8;

	double fRsi1;
	double fRsi2;
	double fRsi3;
	double fMinRsi1;
	double fMinRsi2;
	double fMinRsi3;
	int    mMinRsi3Interval;

	int    mPara6;
	int    mPara7;
	int    mPara8;
	int    mPara9;
	int    mPara10;
	int    mMaxDis;
	int    mContiDownNums;
	int    mContiVolDownNums;
	int    mNowIsMaxPriceNums;
	int    mNextGrow;
	double fNextGrow;
	double fNowGrow;
	double fNowMaxGrow;
	double fLast3Grow;
	double fVolumePer;
	double fVolumePerForM5;
	double fVolumePerForM20;
	double fVolumePerForM30;
	BOOL   bM5CrossM10;
	int   mStepIndex;
	int mBigIncreaseNums;
	int mRsi1BigNums;

	int mVolM5ContiUpNums;
	int mVolM10ContiUpNums;
	int mPriceM5ContiUpNums;



	CString strDateTime;
	std::vector<double> vec_rsi_1;
	std::vector<double> vec_begin_value;
	std::vector<double> vec_close_value;
	std::vector<double> vec_high_value;
	std::vector<double> vec_low_value;
	std::vector<double> vec_price_m5;
	std::vector<double> vec_price_m10;
	std::vector<double> vec_price_m20;

	std::vector<double> vec_volume_m5;
	std::vector<double> vec_volume_m10;
	std::vector<double> vec_volume_value;


	std::vector<double> vec_boll_up;
	std::vector<double> vec_boll_middle;
	std::vector<double> vec_boll_bottom;

	double fcustomtotalvalue;
	int mUserCalcedValue;
	int mTemp;
	int mCalcuSel;
	BOOL bCalcuOk;
	BOOL bShow;
} TanAngleData;

typedef std::vector<TanAngleData *> Vec_TanAngleData;

typedef struct
{
	CString strStockCode;
	CString strStockName;
	
	double f_pre_rsi1;
	double f_pre_rsi2;
	double f_pre_rsi3;

	double f_later_rsi1;
	double f_later_rsi2;
	double f_later_rsi3;

	double f_m5_m10_per;

	CString strDateTime;

	CString strMinDateTime;
	CString strMaxDateTime;
	

} RsiAlgData;

typedef std::vector<RsiAlgData *> Vec_RsiAlgData;


typedef struct
{
	CString strStockCode;
	CString strStockName;

	
	CString strDateTime;

} LongAveGroupAlgData;

typedef std::vector<LongAveGroupAlgData *> Vec_LongAveGroupAlgData;



typedef struct
{
	CString strStockCode;
	CString strStockName;

	int   mStepNums;			//step 个数
	double fCurStepPer;			//当前step per		
	double fAveStepPer;			//平均Step per
	double fTotalStepPer;		//总共Step per

	double f_p4_per;
	double f_p3_per;
	double f_p2_per;
	double f_p1_per;
	double f_now_per;

	int m20ContiNums;

	int m60ContiNums;

	int m120ContiNums;


	CString strDateTime;

} StepStepAlgData;

typedef std::vector<StepStepAlgData *> Vec_StepStepAlgData;

typedef struct
{
	CString strDateTime;			//日期
	int mStockExpStatus;			//指数状态
	std::vector<double> vec_exp_rsi_1_value;			//指数rsi1
	std::vector<double> vec_exp_rsi_2_value;			//指数rsi2
	std::vector<double> vec_exp_rsi_3_value;			//指数rsi3
	Vec_TanAngleData vecTanAngleData;
	CString strResult;
} CalcuData;		//演算数据结构


typedef std::vector<CalcuData *> Vec_CalcuData;



typedef struct
{
	CString strStockCode;
	CString strStockName;
	BOOL bPreDown;
	int mPara1;
	float f_macd_per;
	float f_macd_per_2;
	CString strDateTime;

} LimitUpData;

typedef std::vector<LimitUpData *> Vec_LimitUpData;



typedef struct
{
	CString strStockCode;
	CString strStockName;
	BOOL bPreDown;
	int mPara1;
	CString strDateTime;

} TimePriceMapData;

typedef std::vector<TimePriceMapData *> Vec_TimePriceMapData;


#define BOLL_OUT_UP	0
#define BOLL_EMBED_UP 1
#define BOLL_IN_UP_MIDDLE 2
#define BOLL_EMBED_MIDDLE	3
#define BOLL_IN_MIDDLE_BOTTOM	4
#define BOLL_EMBED_BOTTOM	5
#define BOLL_OUT_BOTTOM 6

typedef struct
{
	CString strStockCode;
	CString strStockName;
	double f_total_per;
	double f_up_per_b;
	double f_bottom_per_b;
	double f_body_per_b;

	double f_p4_per;
	double f_p3_per;
	double f_p2_per;
	double f_p1_per;
	double f_now_per;

	int mBollType;

	CString strDateTime;

} KLineFilterData;

typedef std::vector<KLineFilterData *> Vec_KLineFilterData;



typedef struct
{
	CString strStockCode;
	CString strStockName;
	double f_total_per;
	double f_up_per_b;
	double f_bottom_per_b;
	double f_body_per_b;

	double f_begin_price;
	double f_close_price;
	double f_high_price;
	double f_low_price;


	double f_m5_price;
	double f_m10_price;
	double f_m20_price;

	double f_now_volume;
	double f_m5_volume;
	double f_m10_volume;



	double f_rsi_1;
	double f_rsi_2;
	double f_rsi_3;

	double f_p1_rsi_1;
	double f_p1_rsi_2;
	double f_p1_rsi_3;


	CString strDateTime;

} KLineFilterData2;

typedef std::vector<KLineFilterData2*> Vec_KLineFilterData2;

typedef struct
{
	CString strStockCode;
	CString strStockName;

	int   m_continus_price_m5_up_nums;
	int   m_continus_price_m10_up_nums;
	int   m_continus_price_m20_up_nums;

} KLineContinusMNData;

typedef struct
{
	CString strStockCode;
	CString strStockName;
	int mPara0;
	CString strDateTime;

} BOLLFilterData;

typedef std::vector<BOLLFilterData *> Vec_BOLLFilterData;



typedef struct
{
	double f_group_per;
	double f_total_per;
	double f_up_per_b;
	double f_bottom_per_b;
	double f_body_per_b;
} KLineDesData;
typedef std::vector<KLineDesData *> Vec_KLineDesData;




typedef struct
{
	CString strStockCode;
	CString strStockName;
	
	double f_p2_per;
	double f_p1_per;
	double f_now_per;

	double f_rsi_1;
	double f_rsi_2;
	double f_rsi_3;


	CString strDateTime;

} ThreeLowData;

typedef std::vector<ThreeLowData *> Vec_ThreeLowData;


typedef struct
{
	CString strStockCode;
	CString strDateTime;

	double f_now_ave_per;
	double f_m5_m10_per;
	double f_now_m5_per;
	double f_now_m10_per;

} GeneraAnalyzeData;

typedef std::vector<GeneraAnalyzeData *> Vec_GeneraAnalyzeData;


typedef struct
{
	int mDividBegin;
	int mDividEnd;

} GeneraDataDivid;

typedef std::vector<GeneraDataDivid*> Vec_GeneraDataDivid;