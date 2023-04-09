#pragma once

#include "StockDayTable.h"
#include "afxdtctl.h"

class CDlgCalcPowerRange : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCalcPowerRange)

public:
	CDlgCalcPowerRange(CString strCode,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCalcPowerRange();

// �Ի�������
	enum { IDD = IDD_DLG_CALC_POWER_RANGE };



private:
	CStockDayTable *pStockDayTable;
	CString strStockCode;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl mHighDateCtrl;
	CDateTimeCtrl mLowDateCtrl;
	virtual BOOL OnInitDialog();
};
