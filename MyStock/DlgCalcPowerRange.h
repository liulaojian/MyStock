#pragma once

#include "StockDayTable.h"
#include "afxdtctl.h"

class CDlgCalcPowerRange : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCalcPowerRange)

public:
	CDlgCalcPowerRange(CString strCode,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCalcPowerRange();

// 对话框数据
	enum { IDD = IDD_DLG_CALC_POWER_RANGE };



private:
	CStockDayTable *pStockDayTable;
	CString strStockCode;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl mHighDateCtrl;
	CDateTimeCtrl mLowDateCtrl;
	virtual BOOL OnInitDialog();
};
