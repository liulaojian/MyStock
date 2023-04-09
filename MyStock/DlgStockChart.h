#pragma once

#include "resource.h"
#include "afxwin.h"

#include "StockChartStatic.h"
#include "StockDayTable.h"
class CStockChartStatic;

// CDlgStockChart 对话框
#define IDC_STATIC_STOCK_CHART		10000

class CDlgStockChart : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStockChart)

public:
	CDlgStockChart(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgStockChart();

// 对话框数据
	enum { IDD = IDD_DLG_STOCK_CHART };

	CStockDayTable * GetStockDayTable(void);

	void SetStockDayTable(CStockDayTable *pTable);

	void SetBeginDate(CString strVal);
	void SetEndDate(CString strVal);

	BOOL Init(void);

private:
	CStockChartStatic *pStockChartStatic;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuSaveBmp();
};
