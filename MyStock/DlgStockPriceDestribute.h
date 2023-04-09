#pragma once
#include "afxwin.h"

#include "StockProfitLossArithmetic.h"
// CDlgStockPriceDestribute 对话框

enum
{
	STOCKPRICE_DESTRIBUTE_240=0,
	STOCKPRICE_DESTRIBUTE_20,
	STOCKPRICE_DESTRIBUTE_30,
	STOCKPRICE_DESTRIBUTE_40,
	STOCKPRICE_DESTRIBUTE_60,
	STOCKPRICE_DESTRIBUTE_120,
};

class CDlgStockPriceDestribute : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStockPriceDestribute)

public:
	CDlgStockPriceDestribute(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgStockPriceDestribute();

// 对话框数据
	enum { IDD = IDD_DLG_STOCK_PRICE_DESTRIBUTE };

	void SetStockProfitLossData(CStockProfitLossData *pData) {pStockProfitLossData=pData;}

	BOOL AnalysisStockProfitLossData(void);

private:
	CStockProfitLossData *pStockProfitLossData;
	int mDestributeDayNums;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit mEditStockUp;
	CEdit mEditStockDown;
	virtual BOOL OnInitDialog();
	CComboBox mCmbDayNums;
	afx_msg void OnBnClickedBtnRecalc();
};
