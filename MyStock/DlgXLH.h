#pragma once
#include "afxwin.h"


// CDlgXLH �Ի���

class CDlgXLH : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgXLH)

public:
	CDlgXLH(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgXLH();

// �Ի�������
	enum { IDD = IDD_DIG_XLH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit mEditMachCode;
	virtual BOOL OnInitDialog();
	CEdit mEditXuliehao;
	afx_msg void OnBnClickedBtnMatch();
};
