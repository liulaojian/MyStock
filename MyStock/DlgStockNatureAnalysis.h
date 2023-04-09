#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"
#include "StockDayTable.h"
#include "afxwin.h"
#include "StockNatureAnalysisArithmetic.h"

enum
{
	ANALY_COLUMN_ID=0,				//ID
	ANALY_COLUMN_STOCK_DATE,			
	ANALY_COLUMN_STOCK_END_PRICE,
	ANALY_COLUMN_STOCK_INCREASE,
	ANALY_COLUMN_STOCK_PREAVE3DAY_INCREASE,
	ANALY_COLUMN_STOCK_VOLUME_INCREASE,
	ANALY_COLUMN_STOCK_PREAVE3DAY_VOLUME_INCREASE,
	ANALY_COLUMN_STOCK_EXP_END_PRICE,
	ANALY_COLUMN_STOCK_EXP_INCREASE,
	ANALY_COLUMN_STOCK_EXP_PREAVE3DAY_INCREASE,
	ANALY_COLUMN_STOCK_EXP_VOLUME_INCREASE,
	ANALY_COLUMN_STOCK_EXP_PREAVE3DAY_VOLUME_INCREASE,

};



enum
{
	ANALY_EVENT_REFRESH_DATA=0x2000
};


class CDlgStockNatureAnalysis : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStockNatureAnalysis)

public:
	CDlgStockNatureAnalysis(CString strCode,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgStockNatureAnalysis();

// 对话框数据
	enum { IDD = IDD_DLG_STOCK_NATURE_ANALYSIZE };


	void SetExpStockCode(CString strVal) {strExpStockCode=strVal;}
	void SetBeginDate(CString strVal) {strBeginDate=strVal;}
	void SetEndDate(CString strVal) {strEndDate=strVal;}

	bool RefreshData(void);

	BOOL CalcStockAnalysisInfoList(void);

	BOOL JudgeExpIncrease(float f_exp_increase);

	

private:
	CStockDayTable *pExpStockDayTable;
	CStockDayTable *pStockDayTable;

	CString strStockCode;
	CString strExpStockCode;


	CString strBeginDate;
	CString strEndDate;

	int  mBeginPos;
	int  mEndPos;

	int  mExpBeginPos;
	int  mExpEndPos;

	Vec_StockAnalysisInfo vecStockAnalysisInfo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl mDateTimeBegin;
	CDateTimeCtrl mDateTimeEnd;
	CListCtrl mStockListCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CComboBox mCmbExpInCrease;
	afx_msg void OnBnClickedBtnAnalysis();
	CListBox mListBoxGatherInfo;
};
