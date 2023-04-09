#pragma once
#include "afxwin.h"


// CDlgKLineModeSel 对话框

class CDlgKLineModeSel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgKLineModeSel)

public:
	CDlgKLineModeSel(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgKLineModeSel();

// 对话框数据
	enum { IDD = IDD_DLG_KLINE_MODE };

	int GetKLineMode(void) {return mKLineMode;}

private:
	int mKLineMode;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mCmbKLineMode;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
