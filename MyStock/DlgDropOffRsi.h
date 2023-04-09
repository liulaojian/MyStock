#pragma once

#include "StockDataMgr.h"
#include "StockRSIArithmetic.h"
// CDlgDropOffRsi 对话框


enum
{
	DROPOFFRSI_COLUMN_ID=0,				//ID
	DROPOFFRSI_COLUMN_STOCK_CODE,			
	DROPOFFRSI_COLUMN_STOCK_NAME,
};

enum
{
	DROPOFFRSI_EVENT_REFRESH_DATA=0x2000
};

typedef struct
{
	CString strStockCode;
	CString strStockName;
	CStockRSIData *pStockRSIData;
} DropOffRsiData;
typedef std::vector<DropOffRsiData *> Vec_DropOffRsiData;


class CDlgDropOffRsi : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDropOffRsi)

public:
	CDlgDropOffRsi(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDropOffRsi();

// 对话框数据
	enum { IDD = IDD_DLG_DROPOFF_RSI };

public:


private:
	Vec_DropOffRsiData vecDropOffRsiData;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
