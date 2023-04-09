#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgDays 对话框

class CDlgDays : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDays)

public:
	CDlgDays(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDays();

// 对话框数据
	enum { IDD = IDD_DLG_DAYS };

	int GetDayNums(void) {return mDayNums;}

private:
	int mDayNums;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit mEditDays;
	CSpinButtonCtrl mSpinDays;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
