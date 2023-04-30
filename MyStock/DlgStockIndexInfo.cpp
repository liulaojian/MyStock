// DlgStockIndexInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgStockIndexInfo.h"
#include "afxdialogex.h"

#include  "StockCCIArithmetic.h"
#include "StockRSIArithmetic.h"
#include "StockSARArithmetic.h"
#include "StockKDJArithmetic.h"
#include "StockCRAtithmetic.h"
#include "StockMFIArithmetic.h"
#include "StockPSYArithmetic.h"
#include "StockVRArithmetic.h"

// CDlgStockIndexInfo 对话框

IMPLEMENT_DYNAMIC(CDlgStockIndexInfo, CDialogEx)

CDlgStockIndexInfo::CDlgStockIndexInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_STOCK_INDEX_INFO, pParent)
{

}

CDlgStockIndexInfo::~CDlgStockIndexInfo()
{
}

void CDlgStockIndexInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgStockIndexInfo, CDialogEx)
END_MESSAGE_MAP()


// CDlgStockIndexInfo 消息处理程序


BOOL CDlgStockIndexInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
