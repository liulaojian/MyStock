// DlgFilterIncrease.cpp: 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgFilterIncrease.h"
#include "afxdialogex.h"


// CDlgFilterIncrease 对话框

IMPLEMENT_DYNAMIC(CDlgFilterIncrease, CDialogEx)

CDlgFilterIncrease::CDlgFilterIncrease(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FILTER_INCREASE, pParent)
{

}

CDlgFilterIncrease::~CDlgFilterIncrease()
{
}

void CDlgFilterIncrease::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INCREASE, mEditIncrease);
	DDX_Control(pDX, IDC_SPIN_INCREASE, mSpinIncrease);
}


BEGIN_MESSAGE_MAP(CDlgFilterIncrease, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OK, &CDlgFilterIncrease::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CDlgFilterIncrease::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CDlgFilterIncrease 消息处理程序


BOOL CDlgFilterIncrease::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mSpinIncrease.SetBuddy(&mEditIncrease);
	mSpinIncrease.SetRange(5, 50);
	mSpinIncrease.SetPos(10);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgFilterIncrease::OnBnClickedBtnOk()
{
	CString strVal;
	int temp;
	mEditIncrease.GetWindowText(strVal);
	temp = atoi(strVal);
	fIncrease = temp;
	CDialogEx::OnOK();
}


void CDlgFilterIncrease::OnBnClickedBtnCancel()
{
	CDialogEx::OnCancel();
}
