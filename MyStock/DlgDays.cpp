// DlgDays.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgDays.h"
#include "afxdialogex.h"


// CDlgDays 对话框

IMPLEMENT_DYNAMIC(CDlgDays, CDialogEx)

CDlgDays::CDlgDays(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDays::IDD, pParent)
{

}

CDlgDays::~CDlgDays()
{
}

void CDlgDays::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DAYS, mEditDays);
	DDX_Control(pDX, IDC_SPIN_DAYS, mSpinDays);
}


BEGIN_MESSAGE_MAP(CDlgDays, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgDays::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgDays 消息处理程序


BOOL CDlgDays::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mDayNums=8;
	mSpinDays.SetBuddy(&mEditDays);
	mSpinDays.SetRange(3, 40);
	mSpinDays.SetPos(mDayNums);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgDays::OnBnClickedOk()
{
	CString strVal;
	int temp;
	mEditDays.GetWindowText(strVal);
	temp=atoi(strVal);
	mDayNums=temp;

	CDialogEx::OnOK();
}
