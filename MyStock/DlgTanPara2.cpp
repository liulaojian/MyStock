// DlgTanPara2.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgTanPara2.h"
#include "afxdialogex.h"


// CDlgTanPara2 对话框

IMPLEMENT_DYNAMIC(CDlgTanPara2, CDialogEx)

CDlgTanPara2::CDlgTanPara2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTanPara2::IDD, pParent)
{

}

CDlgTanPara2::~CDlgTanPara2()
{
}

void CDlgTanPara2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_AVE_VOL_MUL_MIN, mEditAveVolMulMin);
	DDX_Control(pDX, IDC_SPIN_AVE_VOL_MUL_MIN, mSpinAveVolMulMin);
	DDX_Control(pDX, IDC_EDIT_AVE_VOL_MUL_MAX, mEditAveVolMulMax);
	DDX_Control(pDX, IDC_SPIN_AVE_VOL_MUL_MAX, mSpinAveVolMulMax);
	DDX_Control(pDX, IDC_CHECK_IGNOR_M5ANGLE, mCheckIgnorM5Angle);
	DDX_Control(pDX, IDC_CHECK_USE_CONTI_UP, mCheckUseContiUp);
}


BEGIN_MESSAGE_MAP(CDlgTanPara2, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTanPara2::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgTanPara2 消息处理程序


BOOL CDlgTanPara2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	mAveVolMulMin=5;
	mSpinAveVolMulMin.SetBuddy(&mEditAveVolMulMin);
	mSpinAveVolMulMin.SetRange(0, 100);
	mSpinAveVolMulMin.SetPos(mAveVolMulMin);

	mAveVolMulMax=20;
	mSpinAveVolMulMax.SetBuddy(&mEditAveVolMulMax);
	mSpinAveVolMulMax.SetRange(0, 100);
	mSpinAveVolMulMax.SetPos(mAveVolMulMax);
	bIgnorM5Angle=FALSE;	
	bUseContiUpNums=FALSE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgTanPara2::OnBnClickedOk()
{
	CString strVal;
	int temp;
	mEditAveVolMulMin.GetWindowText(strVal);
	temp=atoi(strVal);
	mAveVolMulMin=temp;

	mEditAveVolMulMax.GetWindowText(strVal);
	temp=atoi(strVal);
	mAveVolMulMax=temp;

	if(mAveVolMulMax<=mAveVolMulMin)
	{
		AfxMessageBox("Ave Vol max <=min");
		return;
	}

	f_AveVolMulMin=(double)mAveVolMulMin/10.0;

	f_AveVolMulMax=(double)mAveVolMulMax/10.0;

	bIgnorM5Angle=mCheckIgnorM5Angle.GetCheck();
	bUseContiUpNums=mCheckUseContiUp.GetCheck();

	CDialogEx::OnOK();
}
