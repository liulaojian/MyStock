#pragma once
#include "afxwin.h"

enum
{
	UPDATE_EVENT_UPDATE_MIN5_DATA=0x2000,
	UPDATE_EVENT_SAVE_DATA_TO_DB=2001,
};

class CDlgUpdateStockData : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgUpdateStockData)

public:
	CDlgUpdateStockData(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUpdateStockData();

// �Ի�������
	enum { IDD = IDD_DLG_UPDATE_STOCK_DATA };

private:
	int mUpdateStockPos;

	BOOL  UpdateStock5MinTable(CString strStockCode);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnUpdate5minData();
	CListBox mListStock;
	afx_msg void OnBnClickedBtnSavedb();
};
