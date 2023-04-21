#pragma once
#include "afxcmn.h"

#include "StockDataMgr.h"
#include "afxwin.h"
#include "afxdtctl.h"

#include "StockProfitLossArithmetic.h"
#include "afxmenubutton.h"
#include "TanAngleAlg.h"
#include "DataType.h"

#include "IndustryDataMgr.h"

enum
{
	DROPOFF_COLUMN_ID=0,				//ID
	DROPOFF_COLUMN_STOCK_CODE,			
	DROPOFF_COLUMN_STOCK_NAME,
	DROPOFF_COLUMN_MAX_MULTIPLE,
	DROPOFF_COLUMN_AVE_MULTIPLE,
	DROPOFF_COLUMN_MAX_DATE,
	DROPOFF_COLUMN_MIN_DATE,
	DROPOFF_COLUMN_MAX_PASS_DAY,
	DROPOFF_COLUMN_FILTERNUMS,
	DROPOFF_COLUMN_SPECNUMS,
	DROPOFF_COLUMN_INFO,
};

enum
{
	DROPOFF2_COLUMN_ID=0,				//ID
	DROPOFF2_COLUMN_STOCK_CODE,			
	DROPOFF2_COLUMN_STOCK_NAME,
	DROPOFF2_COLUMN_SPECNUMS,
};

enum
{
	DROPOFF_EVENT_REFRESH_DATA=0x2000,
	DROPOFF_EVENT_REFRESH_DATA_SECOND=0x2001,

};

#define MAX_PARA_MODE_STRICT  0

#define MAX_PARA_MODE_LOOSE  1



// CDlgDropOff 对话框



class CDlgDropOff : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDropOff)

public:
	CDlgDropOff(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDropOff();



public:
	BOOL CalcDropOffStock(void);

	BOOL CalcDropOffStockDayData(CStockDayTable*pStockDayTable,CString  strStockCode,CString  strStockName,Vec_StockDayData vecStockDayData );

	BOOL RefreshData(void);
	BOOL RefreshData_Second(void);
	BOOL FakeFilter(void);
	BOOL FilterByReserve(void);
	BOOL FilterByMerge(void);
	BOOL  DoFilter4(void);
	double  AnalysisStockProfitLossData(CStockProfitLossData* pStockProfitLossData);

	BOOL CalcRsiStock(void);

	BOOL DoCalcStockChip(void);
	BOOL DoCalcMultiHead(void);
	BOOL DoCalcDownShadowLine(void);

	BOOL DoCalcMenuPriceVolumeM5M10(void);

	BOOL DoFilterKDJ(void);
	BOOL DoFilterKDJ2(void);

	BOOL DoFilterM5M10M20Up(void);
	BOOL DoFilterSerialKeepDown(void);

	BOOL DoFilterTanAngle(void);
	BOOL DoFilterSingleTanAngle(void);
	BOOL DoFilterMulTanAngle(void);

	BOOL DoFilterCMMatch(void);

	BOOL DoFilterTanMatch(void);
	BOOL DoFilterTanMatch2(void);
	BOOL DoFilterTanMatch3(void);
	BOOL DoFilterTanMatch4(void);
	BOOL DoFilterTanMatch5(void);
	BOOL DoFilterTanMatch6(void);
	BOOL DoFilterTanMatch7(void);
	BOOL DoFilterTanMatch8(void);
	BOOL DoFilterTanMatch9(void);
	BOOL DoFilterRsiMatch(void);
	BOOL DoFilterMulTanMatch(void);

	BOOL DoFilterKLinePregnant(void);		//K线身怀六甲
	
	BOOL DoFilterNextGrowMatch(void);

	BOOL DoFilterLimitUpMatch(void);
	BOOL DoFilterTimePriceMapMatch(void);

	BOOL DoFilterKLineMapMatch(void);		//k线算法
	BOOL DoFilterKLineBadFilter(void);		//k线算法走势变坏检查
	BOOL DoFilterKLineIndustry(void);		//k线算法行业
	BOOL DoFilterKLineNineTurn(void);		//k线算法9转

	BOOL DoFilterLongAveGroup(void);
	BOOL DoFilterKLineMatch(void);
	BOOL DoFilterThreeLow(void);
	BOOL DoFilterOneLine(void);

	BOOL DoIndustyInfoStat(void);		//行业信息统计
	BOOL DoFilterIndustyInfo(IndustryData* pIndustryData);		//行业选择
	BOOL DoReverseFilterIndustyInfo(IndustryData* pIndustryData);		//行业选择


	BOOL DoFiterVPMFIEqu(void);
	BOOL DoFiterVPLimDrop(void);

	BOOL DoFiterVPMFIEquLess75(void);

	BOOL DoFiterVPMFILowVale(int mMfiLowValue,int mMfiLowDay,bool bIsMfiCurMaxEqu,int mMfiDifCurMax);

	BOOL DoFiterVPVREqu(void);

	BOOL DoFilterReverseMLine(void);
	//计算上涨系数 量
	int CalcUpCoeff_Vol_1(std::vector<double> & vec_vol,std::vector<double> & vec_vol_ma5,std::vector<double> & vec_vol_ma10,std::vector<double> & vec_price);

	//计算上涨系数 量
	int CalcUpCoeff_Vol_2(std::vector<double> & vec_vol,std::vector<double> & vec_vol_ma5,std::vector<double> & vec_vol_ma10,std::vector<double> & vec_price);


	//计算上涨系数 量
	int CalcUpCoeff_Vol_3(std::vector<double> & vec_vol,std::vector<double> & vec_vol_ma5,std::vector<double> & vec_vol_ma10,std::vector<double> & vec_price);


	//计算上涨系数 量
	int CalcUpCoeff_Vol_4(std::vector<double> & vec_vol,std::vector<double> & vec_vol_ma5,std::vector<double> & vec_vol_ma10,std::vector<double> & vec_price);


	//计算上涨系数 量
	int CalcUpCoeff_Vol_Addition_1(std::vector<double> & vec_vol,std::vector<double> & vec_price,double rsi_1);

	//计算上涨系数 价
	int CalcUpCoeff_Price_1(std::vector<double> & vec_price,std::vector<double> & vec_price_ma5,std::vector<double> & vec_price_ma10);



private:
	KLineDesData *  CalcKLineDesData(double f_begin,double f_close,double f_high,double f_low);

	int  mKLineSelMode;

private:
	Vec_StockCodeList  vecStockCodeList;
	CWinThread *pThread;
	Vec_DropOffData  vecDropOffData;
	Vec_DropOffData  vecDropOffData_Reserve;
	Vec_DropOffData  vecDropOffData_Merge;

	Vec_DropOffData  vecDropOffData_Second;

	Vec_RSIData   vecRSIData;

	float fDivMulti;
	float fAveDivMulti;

	bool bUseAve;
	bool bUseMax;
	bool bUseAve10Day;
	bool bUseAve5Day;
	bool bUsePreDate;
	int  mMinNums;
	int  mDayNums;
	int  mMaxDayNums;

	bool bReserveFilter;
	bool bMergeFilter;

	bool bExperFilter4;

	int  mMaxParaMode;


private:
	float fStockChipLow;
	float fStockChipHigh;
	int mStockChipConti;

private:
	int mBackDays;
	int mMaxAngle;
	double f_max_volume_multiple;
	bool bIgnoreM5;
	bool bUseM120;
	bool bUseAllUp;
	int mMaxInsBack;
	double f_max_ins_thes;
	int mKLineType = 0;
	Vec_TanAngleData vecTanAngleData;
	Vec_KLineFilterData vecKLineFilterData;
	Vec_ThreeLowData vecThreeLowData;
	int mMulDays;

	Vec_BOLLFilterData vecBOLLFilterData;
private:
	float f_rsi1_low;
	float f_rsi1_high;

	float f_rsi2_low;
	float f_rsi2_high;

	float f_rsi3_low;
	float f_rsi3_high;

	int m_risi_dist;
private:
	Vec_CalcuData  vecCalcuData;
	BOOL doAddCalcu(void);		//加入演算
private:
	int mKdjNums;

	int mKdjMuls;

	int mRsiPreNums;

private:
	int m_m5_m10_period;
	int m_m5_m10_20_25_nums;
	int m_m5_m10_big25_nums;
	int m_close_m10_10_20_nums;
	int m_close_m10_20_25_nums;
	int m_close_m10_big25_nums;
private:
	CMenu* pFunMenu;
	BOOL  bExtWinHide;

private:
	double f_AveVolMulMin;

	double f_AveVolMulMax;

	BOOL bIgnorM5Angle;

	BOOL bUseContiUpNums;
public:

// 对话框数据
	enum { IDD = IDD_DLG_DROPOFF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl mListCtrlItem;
	//afx_msg void OnBnClickedBtnBegin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	CButton mCheckDate;
	CDateTimeCtrl mDataTimeDropOff;
	afx_msg void OnClickedCheckDate();
	//afx_msg void OnBnClickedBtnExperFilter();
	//afx_msg void OnBnClickedBtnExperFilter2();
	afx_msg void OnBnClickedBtnExperFilter3();
	CButton mCheckReserveFilter;
	afx_msg void OnBnClickedBtnExperFilter4();
	afx_msg void OnBnClickedBtnExperFilter5();
	CMFCMenuButton mFunButtonMenu;
	afx_msg void OnBnClickedBtnDropOff();
	CButton mCheckMergeFilter;
	CListCtrl mSecondListCtrlItem;
	afx_msg void OnBnClickedBtnClearLeft();
	afx_msg void OnBnClickedBtnClearRight();
	afx_msg void OnBnClickedBtnAddToRight();
	afx_msg void OnBnClickedBtnAddToLeft();
	afx_msg void OnBnClickedBtnShowHide();
	afx_msg void OnBnClickedBtnKdjFilter();
	afx_msg void OnBnClickedBtn3mUp();
	afx_msg void OnRclickListItem(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMenuToRight();
	afx_msg void OnBnClickedBtnNextGroup();
	//afx_msg void OnBnClickedBtnAddCalcu();
	//afx_msg void OnBnClickedBtnCalcu();
	afx_msg void OnBnClickedBtnAddToLeftxor();
	afx_msg void OnMenuAngleDetail();
	afx_msg void OnBnClickedBtnAddToLeftxor2();
	afx_msg void OnBnClickedBtnAddToLeftxor3();
	afx_msg void OnMenuNextGrowp();
	afx_msg void OnMenuNextGrowp3();
	afx_msg void OnMenuNextGrowp8();
	afx_msg void OnMenuShellWeb();
	afx_msg void OnMenuKLineAnalyze();
	afx_msg void OnBnClickedBtnBackFlow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMenuPvDetail();
	afx_msg void OnBnClickedBtnVpSel();
};
