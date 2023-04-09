#pragma once

#include "DlgLoopBackCallBack.h"
#include "afxwin.h"
#include "resource.h"
// CDlgLoopBackLog 对话框

enum
{
	TIMER_EVENT_LOG=0x2000
};

class CDlgLoopBackLog : public CDlgLoopBackCallBack
{
	DECLARE_DYNAMIC(CDlgLoopBackLog)

public:
	CDlgLoopBackLog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLoopBackLog();

// 对话框数据
	enum { IDD = IDD_DLG_LOOPBACK_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox mListLog;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
