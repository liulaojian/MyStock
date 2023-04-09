#pragma once

#include "DlgMonitorCallBack.h"
#include "afxcmn.h"
#include "zbTypeDef.h"

// DlgStockMonitor 对话框

enum
{
	MONITOR_COLUMN_ID=0,				//ID
	MONITOR_COLUMN_STOCK_CODE,			//股票Code	
	MONITOR_COLUMN_STOCK_NAME,			//股票名称
	MONITOR_COLUMN_STOCK_MIN5_ENDPRICE,		//5分钟数据最后价格
	MONITOR_COLUMN_STOCK_MIN5_LASTTIME,		//5分钟数据最后时间
	MONITOR_COLUMN_MONITOR_LASTTIMER,		//最近次监控执行时间
	MONITOR_COLUMN_MONITOR_CAPTURED,		//监控是否捕获到需要的
	MONITOR_COLUMN_MONITOR_INFO,			//监控信息
};

enum
{
	MONITOR_TIMER_EVENT_REFRESH=0x2000
};


class DlgStockMonitor : public CDlgMonitorCallBack
{
	DECLARE_DYNAMIC(DlgStockMonitor)

public:
	DlgStockMonitor(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgStockMonitor();

// 对话框数据
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mStockListCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRclickListStock(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUpdateMenuStockChart(CCmdUI *pCmdUI);
	afx_msg void OnMenuDfcfWebOpen();
};
