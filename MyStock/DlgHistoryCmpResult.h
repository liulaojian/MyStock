#pragma once
#include "afxcmn.h"


// CDlgHistoryCmpResult 对话框

#include "HistoryCmpMethod.h"
#include "StockDayTable.h"

enum
{
	RESULT_COLUMN_ID=0,				//ID
	RESULT_COLUMN_STOCK_CODE,			
	RESULT_COLUMN_STOCK_NAME,
	RESULT_COLUMN_STOCK_DAY_BEGIN,
	RESULT_COLUMN_STOCK_DAY_END,
};

enum
{
	RESULT_TIMER_EVENT_REFRESH=0x2000
};



class CDlgHistoryCmpResult : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHistoryCmpResult)

public:
	CDlgHistoryCmpResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgHistoryCmpResult();

// 对话框数据
	enum { IDD = IDD_DLG_HISTORYCMPRESULT };

public:
	bool RefreshData(void);

	void SetStockDayTable(CStockDayTable *pTable)  {pStockDayTable=pTable;}
	void SetHistoryResultList(Vec_HistoryResultList vecList) {vecHistoryResultList=vecList;}

	void SetTitle(CString strVal) {strTitle=strVal;}

private:
	CStockDayTable *pStockDayTable;
	Vec_HistoryResultList vecHistoryResultList;

	CString strTitle;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mResultListCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRclickListResult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUpdateMenuStockChart(CCmdUI *pCmdUI);
	afx_msg void OnMenuStockChart();
};
