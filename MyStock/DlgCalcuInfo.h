#pragma once
#include "afxcmn.h"

#include "StockDataMgr.h"
#include "afxwin.h"
#include "afxdtctl.h"

#include "StockProfitLossArithmetic.h"
#include "afxmenubutton.h"
#include "TanAngleAlg.h"
// CDlgCalcuInfo 对话框

enum
{
	CALCUINFO_COLUMN_ID=0,				//ID
	CALCUINFO_COLUMN_STOCK_CODE,
	CALCUINFO_COLUMN_STOCK_NAME,
	CALCUINFO_COLUMN_ANGLE,			
	CALCUINFO_COLUMN_INFO_1,
	CALCUINFO_COLUMN_INFO_2,
	CALCUINFO_COLUMN_INFO_3,
};

enum
{
	CALCUINFOEVENT_REFRESH_DATA=0x4000,
};


class CDlgCalcuInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCalcuInfo)

public:
	CDlgCalcuInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCalcuInfo();

// 对话框数据
	enum { IDD = IDD_DLG_CALCU_INFO };

public:
	void SetCalcuData(CalcuData* pData) {pCalcuData=pData;}
	BOOL RefreshData(void);
private:
	CalcuData *pCalcuData;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl mDataInfoListCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
