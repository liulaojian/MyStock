#pragma once
#include "afxdtctl.h"
#include "afxwin.h"

#include "StockDayTable.h"
// CDlgCalcPower �Ի���

class CDlgCalcPower : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCalcPower)

public:
	CDlgCalcPower(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCalcPower();

// �Ի�������
	enum { IDD = IDD_DLG_CALC_POWER };

	void SetStockCode(CString strVal) {strStockCode=strVal;}
	CString GetStockCode(void) {return strStockCode;}

	void SetBeginDate(CString strVal) {strBeginDate=strVal;}
	CString GetBeginDate(void) {return strEndDate;}

	void SetEndDate(CString strVal) {strEndDate=strVal;}
	CString GetEndDate(void) {return strEndDate;}

private:
	CString strStockCode;
	CStockDayTable *pStockDayTable;
	CString strBeginDate;
	CString strEndDate;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl mBeginDateCtrl;
	CDateTimeCtrl mEndDateCtrl;
	CEdit mResultEdit;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnCalc();
	CEdit mEditStockDays;
};
