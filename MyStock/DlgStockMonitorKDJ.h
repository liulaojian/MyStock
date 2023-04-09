#pragma once

#include "DlgMonitorCallBack.h"
#include "afxcmn.h"
#include "zbTypeDef.h"
#include "afxwin.h"
#include "KDJStockMonitor.h"


enum
{
	KDJMONITOR_TIMER_EVENT_REFRESH=0x2000
};



class CDlgStockMonitorKDJ : public CDlgMonitorCallBack
{
	DECLARE_DYNAMIC(CDlgStockMonitorKDJ)

public:
	CDlgStockMonitorKDJ(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStockMonitorKDJ();

// �Ի�������
	enum { IDD = IDD_DLG_MONITOR_KDJ };


private:
	

	Vec_KDJStockMonitor vecKDJStockMonitor;
	//CKDJStockMonitor *pKDJStockMonitor;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox mListInfo;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnBegin();
	CListBox mListResult;
	CComboBox mCmbSniperType;
};
