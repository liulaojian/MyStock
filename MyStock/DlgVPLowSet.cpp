// DlgVPLowSet.cpp: 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgVPLowSet.h"
#include "afxdialogex.h"


// CDlgVPLowSet 对话框

IMPLEMENT_DYNAMIC(CDlgVPLowSet, CDialogEx)

CDlgVPLowSet::CDlgVPLowSet(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_VP_LOWSET, pParent)
{

}

CDlgVPLowSet::~CDlgVPLowSet()
{
}

void CDlgVPLowSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MIN_MFI, mEditMinMfi);
	DDX_Control(pDX, IDC_SPIN_MIN_MFI, mSpinMinMfi);
	DDX_Control(pDX, IDC_EDIT_MIN_MFI_DAY, mEditMinMfiDay);
	DDX_Control(pDX, IDC_SPIN_MIN_MFI_DAY, mSpinMinMfiDay);
	DDX_Control(pDX, IDC_CHECK_EQU, mCheckEqu);
	DDX_Control(pDX, IDC_EDIT_DIF_CUR_MAX, mEditDifCurMax);
	DDX_Control(pDX, IDC_SPIN_DIF_CUR_MAX, mSpinDifCurMax);
}


BEGIN_MESSAGE_MAP(CDlgVPLowSet, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OK, &CDlgVPLowSet::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CDlgVPLowSet::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CDlgVPLowSet 消息处理程序


BOOL CDlgVPLowSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mSpinMinMfi.SetBuddy(&mEditMinMfi);
	mSpinMinMfi.SetRange(1, 30);
	mSpinMinMfi.SetPos(13);


	mSpinMinMfiDay.SetBuddy(&mEditMinMfiDay);
	mSpinMinMfiDay.SetRange(1, 20);
	mSpinMinMfiDay.SetPos(15);


	mSpinDifCurMax.SetBuddy(&mEditDifCurMax);
	mSpinDifCurMax.SetRange(0, 20);
	mSpinDifCurMax.SetPos(1);

	mCheckEqu.SetCheck(BST_CHECKED);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgVPLowSet::OnBnClickedBtnOk()
{
	CString strVal;
	int temp;
	mEditMinMfi.GetWindowText(strVal);
	temp = atoi(strVal);
	mMinMfiValue = temp;

	mEditMinMfiDay.GetWindowText(strVal);
	temp = atoi(strVal);
	mMinMfiDay = temp;


	mEditDifCurMax.GetWindowText(strVal);
	temp = atoi(strVal);
	mMfiDifCurMax = temp;

	if (mCheckEqu.GetCheck() == BST_CHECKED)
		bIsMfiCurMaxEqu = true;
	else
		bIsMfiCurMaxEqu = false;

	CDialogEx::OnOK();
}


void CDlgVPLowSet::OnBnClickedBtnCancel()
{
	CDialogEx::OnCancel();
}
