#pragma once
#include "afxwin.h"


// CDlgSFSel 对话框

class CDlgSFSel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSFSel)

public:
	CDlgSFSel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSFSel();

// 对话框数据
	enum { IDD = IDD_DLG_SF_SEL };

	int GetSFSel(void) {return mSFSel;}
private:
	int mSFSel;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mCmbSFSel;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
