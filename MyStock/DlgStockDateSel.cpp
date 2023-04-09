// DlgStockDateSel.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgStockDateSel.h"
#include "afxdialogex.h"


// CDlgStockDateSel 对话框

IMPLEMENT_DYNAMIC(CDlgStockDateSel, CDialogEx)

CDlgStockDateSel::CDlgStockDateSel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgStockDateSel::IDD, pParent)
{

}

CDlgStockDateSel::~CDlgStockDateSel()
{
}

void CDlgStockDateSel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN, mDateTimeBegin);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, mDateTimeEnd);
}


BEGIN_MESSAGE_MAP(CDlgStockDateSel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgStockDateSel::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgStockDateSel 消息处理程序


BOOL CDlgStockDateSel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mDateTimeBegin.SetTime(&mBeginTime);
	mDateTimeEnd.SetTime(&mEndTime);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgStockDateSel::OnBnClickedOk()
{
	mDateTimeBegin.GetTime(mBeginTime);
	mDateTimeEnd.GetTime(mEndTime);

	CTimeSpan span=mEndTime-mBeginTime;

	int iDay=span.GetDays();
	if(iDay<=0)
	{
		AfxMessageBox("开始时间大于等于结束时间");
		return;
	}


	CDialogEx::OnOK();
}
