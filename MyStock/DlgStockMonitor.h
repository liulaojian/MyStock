#pragma once

#include "DlgMonitorCallBack.h"
#include "afxcmn.h"
#include "zbTypeDef.h"

// DlgStockMonitor �Ի���

enum
{
	MONITOR_COLUMN_ID=0,				//ID
	MONITOR_COLUMN_STOCK_CODE,			//��ƱCode	
	MONITOR_COLUMN_STOCK_NAME,			//��Ʊ����
	MONITOR_COLUMN_STOCK_MIN5_ENDPRICE,		//5�����������۸�
	MONITOR_COLUMN_STOCK_MIN5_LASTTIME,		//5�����������ʱ��
	MONITOR_COLUMN_MONITOR_LASTTIMER,		//����μ��ִ��ʱ��
	MONITOR_COLUMN_MONITOR_CAPTURED,		//����Ƿ񲶻���Ҫ��
	MONITOR_COLUMN_MONITOR_INFO,			//�����Ϣ
};

enum
{
	MONITOR_TIMER_EVENT_REFRESH=0x2000
};


class DlgStockMonitor : public CDlgMonitorCallBack
{
	DECLARE_DYNAMIC(DlgStockMonitor)

public:
	DlgStockMonitor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgStockMonitor();

// �Ի�������
	enum { IDD = IDD_DLG_MONITOR };

	void SetStockCodeList(Vec_CString vecList) {vecStockCodeList=vecList;}

	void SetDayNums(int val) {mDayNums=val;}

	void SetUpPercent(float f_val) {f_up_percent=f_val;}

	void SetDownPercent(float f_val) {f_down_percent=f_val;}
public:

	BOOL Init(void);
	
	bool RefreshData(void);

private:
	int mDayNums;
	float f_up_percent;
	float f_down_percent;
	Vec_CString vecStockCodeList;

	Vec_MonitorResultInfo vecMonitorResultInfo;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mStockListCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRclickListStock(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUpdateMenuStockChart(CCmdUI *pCmdUI);
	afx_msg void OnMenuDfcfWebOpen();
};
