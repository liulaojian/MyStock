
// MyStockDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

#include "StockDataMgr.h"
#include "DlgStockChart.h"
#include "DlgLoopBackLog.h"
#include "DlgStockMonitor.h"
#include "DlgPowerArithResult.h"
#include "DlgStockMonitorKDJ.h"
#include "DlgSniperLoopBack.h"

enum
{
	COLUMN_ID=0,				//ID
	COLUMN_STOCK_CODE,			
	COLUMN_STOCK_NAME,
	COLUMN_STOCK_DAY_BEGIN,
	COLUMN_STOCK_DAY_END,
	COLUMN_STOCK_MIN_BEGIN,
	COLUMN_STOCK_MIN_END,
};

enum
{
	TIMER_EVENT_REFRESH_DATA=0x2000
};


// CMyStockDlg 对话框
class CMyStockDlg : public CDialogEx
{
// 构造
public:
	CMyStockDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYSTOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	bool RefreshData(void);



private:
	Vec_StockCodeList vecStockCodeList;
	CDlgStockChart *pDlgStockChart;
	CDlgLoopBackLog *pDlgLoopBackLog;
	DlgStockMonitor *pDlgStockMonitor;
	//CDlgPowerArithResult *pDlgPowerArithResult;
	CDlgStockMonitorKDJ *pDlgStockMonitorKDJ;
	CDlgSniperLoopBack *pDlgSniperLoopBack;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mStockListCtrl;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedBtnLoopback();
	afx_msg void OnBnClickedBtnMonitor();
	afx_msg void OnBnClickedBtnPowerArith();
	afx_msg void OnBnClickedBtnSetting();
	afx_msg void OnBnClickedBtnUpdatedata();
	afx_msg void OnBnClickedBtnMonitorLoopback();
	afx_msg void OnBnClickedBtnStaticAnalysis();
	afx_msg void OnBnClickedBtnStockMethod();
};
