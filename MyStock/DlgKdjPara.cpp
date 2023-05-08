// DlgKdjPara.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgKdjPara.h"
#include "afxdialogex.h"


// CDlgKdjPara 对话框

IMPLEMENT_DYNAMIC(CDlgKdjPara, CDialogEx)

CDlgKdjPara::CDlgKdjPara(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgKdjPara::IDD, pParent)
{

}

CDlgKdjPara::~CDlgKdjPara()
{
}

void CDlgKdjPara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KDJ_NUMS, mEditKdjNums);
	DDX_Control(pDX, IDC_SPIN_KDJ_NUMS, mSpinKdjNums);
	DDX_Control(pDX, IDC_EDIT_KDJ_MULS, mEditKdjMuls);
	DDX_Control(pDX, IDC_SPIN_KDJ_MULS, mSpinKdjMuls);
	DDX_Control(pDX, IDC_EDIT_RSI_PRENUMS, mEditRsiPreNums);
	DDX_Control(pDX, IDC_SPIN_RSI_PRENUMS, mSpinRsiPreNums);
}


BEGIN_MESSAGE_MAP(CDlgKdjPara, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgKdjPara::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgKdjPara 消息处理程序


BOOL CDlgKdjPara::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mKdjNums=10;
	mSpinKdjNums.SetBuddy(&mEditKdjNums);
	mSpinKdjNums.SetRange(3, 30);
	mSpinKdjNums.SetPos(10);


	mKdjMuls=3;
	mSpinKdjMuls.SetBuddy(&mEditKdjMuls);
	mSpinKdjMuls.SetRange(1, 5);
	mSpinKdjMuls.SetPos(3);

	mRsiPreNums=22;
	mSpinRsiPreNums.SetBuddy(&mEditRsiPreNums);
	mSpinRsiPreNums.SetRange(12, 55);
	mSpinRsiPreNums.SetPos(mRsiPreNums);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgKdjPara::OnBnClickedOk()
{
	CString strVal;
	int temp;
	mEditKdjNums.GetWindowText(strVal);
	temp=atoi(strVal);
	mKdjNums=temp;

	mEditKdjMuls.GetWindowText(strVal);
	temp=atoi(strVal);
	mKdjMuls=temp;

	mEditRsiPreNums.GetWindowText(strVal);
	temp=atoi(strVal);
	mRsiPreNums=temp;

	CDialogEx::OnOK();
}
