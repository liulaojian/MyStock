#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgStockChip �Ի���

class CDlgStockChip : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStockChip)

public:
	CDlgStockChip(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStockChip();

// �Ի�������
	enum { IDD = IDD_DLG_STOCKCHIP };


public:
	int GetStockChipLow(void) {return m_StockChipLow;}
	int GetStockChipHight(void) {return m_StockChipHigh;}
	int GetStockChipConti(void) {return m_StockChipConti;}
private:
	int m_StockChipLow;
	int m_StockChipHigh;
	int m_StockChipConti;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mEditChipLow;
	CSpinButtonCtrl mSpinChipLow;
	CEdit mEditChipHigh;
	CSpinButtonCtrl mSpinChipHigh;
	CEdit mEditChipConti;
	CSpinButtonCtrl mSpinConti;
	afx_msg void OnBnClickedOk();
};
