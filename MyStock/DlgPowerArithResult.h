#pragma once
#include "afxcmn.h"
#include <vector>
#include "StockPowerArithmetic.h"
#include "afxdtctl.h"
#include "StockDayTable.h"
#include "afxwin.h"
#include "scriptcontrol1.h"
#include "afxmenubutton.h"


enum
{
	POWER_COLUMN_ID=0,				//ID
	POWER_COLUMN_STOCK_CODE,			
	POWER_COLUMN_STOCK_NAME,
	POWER_COLUMN_STOCK_BEGIN_DATE,
	POWER_COLUMN_STOCK_END_DATE,
	POWER_COLUMN_STOCK_POWER_5_PERCENT,
	POWER_COLUMN_STOCK_POWER_10_PERCENT,
	POWER_COLUMN_STOCK_POWER_20_PERCENT,
	POWER_COLUMN_STOCK_POWER_40_PERCENT,
	POWER_COLUMN_STOCK_POWER_60_PERCENT,
	POWER_COLUMN_STOCK_POWER_120_PERCENT,
	POWER_COLUMN_STOCK_POWER_240_PERCENT,
	POWER_COLUMN_STOCK_POWER_DATE_PERCENT,
};


enum
{
	SORT_BY_CUSTOM_DATE=0,
	SORT_BY_POWER_10,
	SORT_BY_POWER_20,
	SORT_BY_POWER_40,
	SORT_BY_POWER_60,
	SORT_BY_POWER_120,
	SORT_BY_POWER_240,
	SORT_BY_POWER_10_AND_20,
	SORT_BY_POWER_10_AND_20_AND_40,
	SORT_BY_POWER_10_AND_20_40_60,
	SORT_BY_POWER_20_AND_40,
	SORT_BY_POWER_20_AND_40_60_120_240,
	SORT_BY_POWER_40_AND_60,
	SORT_BY_POWER_40_AND_60_120,
	SORT_BY_POWER_60_AND_120,
	SORT_BY_POWER_60_AND_120_240,
};

enum
{
	POWER_EVENT_REFRESH_DATA=0x2000
};

#define POWER_SCRIPT_FILE_NAME		"powercheck.js"

class CDlgPowerArithResult : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPowerArithResult)

public:
	CDlgPowerArithResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPowerArithResult();

// 对话框数据
	enum { IDD = IDD_DLG_POWER_ARITH_RESULT };

public:
	BOOL CalcPowerArithmeticInfo(int mNums);
	
	BOOL Init(void);

	bool RefreshData(void);

private:
	CString LoadScript(CString strScriptFile);
	BOOL  CheckPowerPeriod(StockPowerPeriodInfo *pStockPowerPeriodInfo,CString strScriptFilePath);


	BOOL CheckStockRange(StockPowerPeriodInfo *pStockPowerPeriodInfo,int mId);
private:
	Vec_StockPowerPeriodInfo vecStockPowerPeriodInfo;
	CStockDayTable *pExpStockDayTable;
	int mLastDayNums;		//算法的交易天数
	CString strBeginDate;
	CString strEndDate;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mResultListCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUpdateMenuDfcfWebOpen(CCmdUI *pCmdUI);
	afx_msg void OnMenuDfcfWebOpen();
	afx_msg void OnRclickListPowerResult(NMHDR *pNMHDR, LRESULT *pResult);
	CDateTimeCtrl mBeginDateCtrl;
	CDateTimeCtrl mEndDateCtrl;
	afx_msg void OnBnClickedBtnRecalc();
	afx_msg void OnBnClickedBtnRecalcSort();
	afx_msg void OnUpdateMenuCalcPower(CCmdUI *pCmdUI);
	afx_msg void OnMenuCalcPower();
	afx_msg void OnMenuStockAnalysis();
	afx_msg void OnUpdateMenuStockAnalysis(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuDangerCalc(CCmdUI *pCmdUI);
	afx_msg void OnMenuDangerCalc();
	afx_msg void OnUpdateMenuFindSimilar(CCmdUI *pCmdUI);
	afx_msg void OnMenuFindSimilar();
	CComboBox mCmbSort;
	afx_msg void OnBnClickedBtnFilter();
	CScriptcontrol1 mScriptControl;
	CMFCMenuButton mMenuBtnRange;
	afx_msg void OnBnClickedMenubtnRange();
	afx_msg void OnUpdateMenuStockPriceDestribute(CCmdUI *pCmdUI);
	afx_msg void OnMenuStockPriceDestribute();
	afx_msg void OnBnClickedBtnCalcNoChange();
};
