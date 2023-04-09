#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"
#include "StockProfitLossArithmetic.h"
#include "scriptcontrol1.h"
#include "afxmenubutton.h"

enum
{
	PRICE_COLUMN_ID=0,				//ID
	PRICE_COLUMN_STOCK_CODE,			
	PRICE_COLUMN_STOCK_NAME,
	PRICE_COLUMN_UP_0_3,
	PRICE_COLUMN_UP_3_6,
	PRICE_COLUMN_UP_6_10,
	PRICE_COLUMN_UP_10,
	PRICE_COLUMN_DOWN_0_3,
	PRICE_COLUMN_DOWN_3_6,
	PRICE_COLUMN_DOWN_6_10,
	PRICE_COLUMN_DOWN_10,
};


enum
{
	PRICE_EVENT_REFRESH_DATA=0x2000
};

class CDlgFindStockDestribute : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFindStockDestribute)

public:
	CDlgFindStockDestribute(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFindStockDestribute();

// 对话框数据
	enum { IDD = IDD_DLG_FIND_STOCK_DESTRIBUYE };
public:

	BOOL CalcStockProfitLossData(void);

	BOOL CalcStockProfitLossDataNoChange(void);

	bool RefreshData(void);
private:
	Vec_StockProfitLossData  vecStockProfitLossData;

	CString strBeginDate;
	CString strEndDate;
	CStockDayTable *pExpStockDayTable;
	int mLastDayNums;

	CStockProfitLossData* GetStockProfitLossData(CString strStockCode);
	BOOL CalcUp0_3(CStockProfitLossData* pStockProfitLossData,double & f_duty);
	BOOL CalcUp3_6(CStockProfitLossData* pStockProfitLossData,double & f_duty);
	BOOL CalcUp6_10(CStockProfitLossData* pStockProfitLossData,double & f_duty);
	BOOL CalcUp10(CStockProfitLossData* pStockProfitLossData,double & f_duty);

	BOOL CalcDown0_3(CStockProfitLossData* pStockProfitLossData,double & f_duty);
	BOOL CalcDown3_6(CStockProfitLossData* pStockProfitLossData,double & f_duty);
	BOOL CalcDown6_10(CStockProfitLossData* pStockProfitLossData,double & f_duty);
	BOOL CalcDown10(CStockProfitLossData* pStockProfitLossData,double & f_duty);


	CString LoadScript(CString strScriptFile);

	BOOL CheckDuty(CString strScript,double f_duty_up_0_2,double f_duty_up_2_4,double f_duty_up_4_6,double f_duty_up_6_8,double f_duty_up_8_10,double f_duty_up_10,
				double f_duty_down_0_2,double f_duty_down_2_4,double f_duty_down_4_6,double f_duty_down_6_8,double f_duty_down_8_10,double f_duty_down_10);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl mBeginDateTimeCtrl;
	CDateTimeCtrl mEndDateTimeCtrl;
	CListCtrl mStockList;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnCalc();
	afx_msg void OnBnClickedBtnFind();
	CScriptcontrol1 mScriptControl;
	afx_msg void OnRclickListStock(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUpdateMenuOpenPriceDestribute(CCmdUI *pCmdUI);
	afx_msg void OnMenuOpenPriceDestribute();
	afx_msg void OnBnClickedBtnFindSingle();
	afx_msg void OnBnClickedBtnFindSingle2();
	afx_msg void OnBnClickedBtnCalcNochange();
	afx_msg void OnBnClickedBtnLookHigh();
	CMFCMenuButton mMenuBtnOther;
	afx_msg void OnBnClickedMenubtnOther();
};
