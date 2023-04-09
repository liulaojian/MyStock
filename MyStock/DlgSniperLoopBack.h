#pragma once


#include "DlgMonitorCallBack.h"
#include "afxcmn.h"
#include "zbTypeDef.h"
#include "afxwin.h"
#include "afxdtctl.h"

#include "DlgStockMonitorKDJ.h"


class CDlgSniperLoopBack : public CDlgMonitorCallBack
{
	DECLARE_DYNAMIC(CDlgSniperLoopBack)

public:
	CDlgSniperLoopBack(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSniperLoopBack();

// 对话框数据
	enum { IDD = IDD_DLG_SNIPER_LOOPBACK };

protected:

	//CKDJStockMonitor *pKDJStockMonitor;
	Vec_KDJStockMonitor vecKDJStockMonitor;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mCmbSniperType;
	CDateTimeCtrl mLoopBackDateTimeCtrl;
	CListBox mListInfo;
	CListBox mListResult;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnBegin();
};
