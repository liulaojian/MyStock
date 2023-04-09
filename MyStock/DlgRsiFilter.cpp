// DlgRsiFilter.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgRsiFilter.h"
#include "afxdialogex.h"


// CDlgRsiFilter 对话框

IMPLEMENT_DYNAMIC(CDlgRsiFilter, CDialogEx)

CDlgRsiFilter::CDlgRsiFilter(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRsiFilter::IDD, pParent)
{

}

CDlgRsiFilter::~CDlgRsiFilter()
{
}

void CDlgRsiFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RSI1_LOW, mEditRsi1Low);
	DDX_Control(pDX, IDC_SPIN_RSI1_LOW, mSpinRsi1Low);
	DDX_Control(pDX, IDC_EDIT_RSI1_HIGH, mEditRsi1High);
	DDX_Control(pDX, IDC_SPIN_RSI1_HIGH, mSpinRsi1High);
	DDX_Control(pDX, IDC_EDIT_RSI2_LOW, mEditRsi2Low);
	DDX_Control(pDX, IDC_EDIT_RSI2_HIGH, mEditRsi2High);
	DDX_Control(pDX, IDC_EDIT_RSI3_LOW, mEditRsi3Low);
	DDX_Control(pDX, IDC_SPIN_RSI2_LOW, mSpinRsi2Low);
	DDX_Control(pDX, IDC_SPIN_RSI2_HIGH, mSpinRsi2High);
	DDX_Control(pDX, IDC_SPIN_RSI3_LOW, mSpinRsi3Low);
	DDX_Control(pDX, IDC_EDIT_RSI3_HIGH, mEditRsi3High);
	DDX_Control(pDX, IDC_SPIN_RSI3_HIGH, mSpinRsi3High);
	DDX_Control(pDX, IDC_EDIT_RSI_DIST, mEditRsiDist);
	DDX_Control(pDX, IDC_SPIN_RSI_DIST, mSpinRsiDist);
}


BEGIN_MESSAGE_MAP(CDlgRsiFilter, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgRsiFilter::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgRsiFilter 消息处理程序


BOOL CDlgRsiFilter::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	f_rsi1_low=0;
	mSpinRsi1Low.SetBuddy(&mEditRsi1Low);
	mSpinRsi1Low.SetRange(0, 100);
	mSpinRsi1Low.SetPos(0);


	f_rsi1_high=12;
	mSpinRsi1High.SetBuddy(&mEditRsi1High);
	mSpinRsi1High.SetRange(0, 100);
	mSpinRsi1High.SetPos(12);


	f_rsi2_low=0;
	mSpinRsi2Low.SetBuddy(&mEditRsi2Low);
	mSpinRsi2Low.SetRange(0, 100);
	mSpinRsi2Low.SetPos(0);


	f_rsi2_high=20;
	mSpinRsi2High.SetBuddy(&mEditRsi2High);
	mSpinRsi2High.SetRange(0, 100);
	mSpinRsi2High.SetPos(20);


	f_rsi3_low=0;
	mSpinRsi3Low.SetBuddy(&mEditRsi3Low);
	mSpinRsi3Low.SetRange(0, 100);
	mSpinRsi3Low.SetPos(0);


	f_rsi3_high=30;
	mSpinRsi3High.SetBuddy(&mEditRsi3High);
	mSpinRsi3High.SetRange(0, 100);
	mSpinRsi3High.SetPos(30);


	m_risi_dist=3;
	mSpinRsiDist.SetBuddy(&mEditRsiDist);
	mSpinRsiDist.SetRange(1, 40);
	mSpinRsiDist.SetPos(3);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgRsiFilter::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strVal;
	mEditRsi1Low.GetWindowText(strVal);
	int temp=atoi(strVal);
	f_rsi1_low=temp;

	mEditRsi1High.GetWindowText(strVal);
	temp=atoi(strVal);
	f_rsi1_high=temp;

	mEditRsi2Low.GetWindowText(strVal);
	temp=atoi(strVal);
	f_rsi2_low=temp;

	mEditRsi2High.GetWindowText(strVal);
	temp=atoi(strVal);
	f_rsi2_high=temp;


	mEditRsi3Low.GetWindowText(strVal);
	temp=atoi(strVal);
	f_rsi3_low=temp;

	mEditRsi3High.GetWindowText(strVal);
	temp=atoi(strVal);
	f_rsi3_high=temp;

	mEditRsiDist.GetWindowText(strVal);
	temp=atoi(strVal);
	m_risi_dist=temp;

	CDialogEx::OnOK();
}
