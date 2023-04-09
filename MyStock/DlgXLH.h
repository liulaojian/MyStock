#pragma once
#include "afxwin.h"


// CDlgXLH 对话框

class CDlgXLH : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgXLH)

public:
	CDlgXLH(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgXLH();

// 对话框数据
	enum { IDD = IDD_DIG_XLH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit mEditMachCode;
	virtual BOOL OnInitDialog();
	CEdit mEditXuliehao;
	afx_msg void OnBnClickedBtnMatch();
};
