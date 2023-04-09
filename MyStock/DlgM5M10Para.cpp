// DlgM5M10Para.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgM5M10Para.h"
#include "afxdialogex.h"


// CDlgM5M10Para 对话框

IMPLEMENT_DYNAMIC(CDlgM5M10Para, CDialogEx)

CDlgM5M10Para::CDlgM5M10Para(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgM5M10Para::IDD, pParent)
{

}

CDlgM5M10Para::~CDlgM5M10Para()
{
}

void CDlgM5M10Para::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PERIOD, mEditPeriod);
	DDX_Control(pDX, IDC_SPIN_PERIOD, mSpinPeriod);
	DDX_Control(pDX, IDC_EDIT_M5_M10_COND_20_25, mEditM5M10_20_25);
	DDX_Control(pDX, IDC_SPIN_M5_M10_COND_20_25, mSpinM5M10_20_25);
	DDX_Control(pDX, IDC_EDIT_M5_M10_COND_BIG_25, mEditM5M10_Big25);
	DDX_Control(pDX, IDC_SPIN_M5_M10_COND_BIG_25, mSpinM5M10_Big25);
	DDX_Control(pDX, IDC_EDIT_CLOSE_M10_COND_10_20, mEditCloseM10_10_20);
	DDX_Control(pDX, IDC_SPIN_CLOSE_M10_COND_10_20, mSpinCloseM10_10_20);
	DDX_Control(pDX, IDC_SPIN_CLOSE_M10_COND_20_25, mSpinCloseM10_20_25);
	DDX_Control(pDX, IDC_SPIN_CLOSE_M10_COND_BIG25, mSpinCloseM10_Big25);
	DDX_Control(pDX, IDC_EDIT_CLOSE_M10_COND_20_25, mEditCloseM10_20_25);
	DDX_Control(pDX, IDC_EDIT_CLOSE_M10_COND_BIG25, mEditCloseM10_Big25);
}


BEGIN_MESSAGE_MAP(CDlgM5M10Para, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgM5M10Para::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgM5M10Para 消息处理程序


BOOL CDlgM5M10Para::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_m5_m10_period=12;
	mSpinPeriod.SetBuddy(&mEditPeriod);
	mSpinPeriod.SetRange(10, 40);
	mSpinPeriod.SetPos(m_m5_m10_period);

	m_m5_m10_20_25_nums=2;
	mSpinM5M10_20_25.SetBuddy(&mEditM5M10_20_25);
	mSpinM5M10_20_25.SetRange(1, 20);
	mSpinM5M10_20_25.SetPos(m_m5_m10_20_25_nums);


	m_m5_m10_big25_nums=0;
	mSpinM5M10_Big25.SetBuddy(&mEditM5M10_Big25);
	mSpinM5M10_Big25.SetRange(0, 10);
	mSpinM5M10_Big25.SetPos(m_m5_m10_big25_nums);


	m_close_m10_10_20_nums=5;
	mSpinCloseM10_10_20.SetBuddy(&mEditCloseM10_10_20);
	mSpinCloseM10_10_20.SetRange(1, 20);
	mSpinCloseM10_10_20.SetPos(m_close_m10_10_20_nums);

	m_close_m10_20_25_nums=2;
	mSpinCloseM10_20_25.SetBuddy(&mEditCloseM10_20_25);
	mSpinCloseM10_20_25.SetRange(1, 20);
	mSpinCloseM10_20_25.SetPos(m_close_m10_20_25_nums);

	m_close_m10_big25_nums=0;
	mSpinCloseM10_Big25.SetBuddy(&mEditCloseM10_Big25);
	mSpinCloseM10_Big25.SetRange(0, 10);
	mSpinCloseM10_Big25.SetPos(m_close_m10_big25_nums);



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgM5M10Para::OnBnClickedOk()
{
	CString strVal;
	int temp;
	mEditPeriod.GetWindowText(strVal);
	temp=atoi(strVal);
	m_m5_m10_period=temp;


	mEditM5M10_20_25.GetWindowText(strVal);
	temp=atoi(strVal);
	m_m5_m10_20_25_nums=temp;


	mEditM5M10_Big25.GetWindowText(strVal);
	temp=atoi(strVal);
	m_m5_m10_big25_nums=temp;


	mEditCloseM10_10_20.GetWindowText(strVal);
	temp=atoi(strVal);
	m_close_m10_10_20_nums=temp;

	mEditCloseM10_20_25.GetWindowText(strVal);
	temp=atoi(strVal);
	m_close_m10_20_25_nums=temp;

	mEditCloseM10_Big25.GetWindowText(strVal);
	temp=atoi(strVal);
	m_close_m10_big25_nums=temp;


	CDialogEx::OnOK();
}
