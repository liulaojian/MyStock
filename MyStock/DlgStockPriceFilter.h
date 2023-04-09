#pragma once
#include "afxwin.h"


// CDlgStockPriceFilter �Ի���

class CDlgStockPriceFilter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStockPriceFilter)

public:
	CDlgStockPriceFilter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStockPriceFilter();

// �Ի�������
	enum { IDD = IDD_DLG_STOCK_PRICE_FILTER };

	int GetDayNums(void) {return mDayNums;}
	float GetUpPercent(void) {return f_up_percent;}
	float GetDownPercent(void) {return f_down_percent;}

private:
	int mDayNums;
	float f_up_percent;
	float f_down_percent;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mCmbDayNums;
	CComboBox mCmbUpPercent;
	CComboBox mCmbDownPercent;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
};
