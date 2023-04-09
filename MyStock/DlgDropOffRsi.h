#pragma once

#include "StockDataMgr.h"
#include "StockRSIArithmetic.h"
// CDlgDropOffRsi �Ի���


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
	CDlgDropOffRsi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDropOffRsi();

// �Ի�������
	enum { IDD = IDD_DLG_DROPOFF_RSI };

public:


private:
	Vec_DropOffRsiData vecDropOffRsiData;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
