// DlgTanAngle.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgTanAngle.h"
#include "afxdialogex.h"


// CDlgTanAngle 对话框

IMPLEMENT_DYNAMIC(CDlgTanAngle, CDialogEx)

CDlgTanAngle::CDlgTanAngle(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTanAngle::IDD, pParent)
{

}

CDlgTanAngle::~CDlgTanAngle()
{
}

void CDlgTanAngle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DAYS, mEditDays);
	DDX_Control(pDX, IDC_SPIN_DAYS, mSpinDays);
	DDX_Control(pDX, IDC_EDIT_MAX_ANGLE, mEditMaxAngle);
	DDX_Control(pDX, IDC_SPIN_MAX_ANGLE, mSpinMaxAngle);
	DDX_Control(pDX, IDC_EDIT_MAX_VOL, mEditMaxVol);
	DDX_Control(pDX, IDC_SPIN_MAX_VOL, mSpinMaxVol);
	DDX_Control(pDX, IDC_CHECK_IGNORE_M5, mCheckIgnoreM5);
	DDX_Control(pDX, IDC_CHECK_USE_ALLUP, mCheckUseAllUp);
	DDX_Control(pDX, IDC_EDIT_MAX_INS_BACK, mEditMaxInsBack);
	DDX_Control(pDX, IDC_SPIN_MAX_INS_BACK, mSpinMaxInsBack);
	DDX_Control(pDX, IDC_CHECK_IGNORE_M60, mCheckIgnoreM60);
	DDX_Control(pDX, IDC_EDIT_MAX_INS_THES, mEditMaxInsThes);
	DDX_Control(pDX, IDC_SPIN_MAX_INS_THES, mSpinMaxInsThes);
	DDX_Control(pDX, IDC_COMBO_KLINE_TYPE, mKLineType);
}


BEGIN_MESSAGE_MAP(CDlgTanAngle, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTanAngle::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgTanAngle 消息处理程序


BOOL CDlgTanAngle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mBackDays=8;
	mSpinDays.SetBuddy(&mEditDays);
	mSpinDays.SetRange(3, 15);
	mSpinDays.SetPos(mBackDays);

	mMaxAngle=90;
	mSpinMaxAngle.SetBuddy(&mEditMaxAngle);
	mSpinMaxAngle.SetRange(50, 90);
	mSpinMaxAngle.SetPos(mMaxAngle);

	mMaxVolMul=100;
	mSpinMaxVol.SetBuddy(&mEditMaxVol);
	mSpinMaxVol.SetRange(3, 100);
	mSpinMaxVol.SetPos(mMaxVolMul);

	mMaxInsBack=8;
	mSpinMaxInsBack.SetBuddy(&mEditMaxInsBack);
	mSpinMaxInsBack.SetRange(6, 16);
	mSpinMaxInsBack.SetPos(mMaxInsBack);

	mMaxInsThes = 6;
	mSpinMaxInsThes.SetBuddy(&mEditMaxInsThes);
	mSpinMaxInsThes.SetRange(3, 10);
	mSpinMaxInsThes.SetPos(mMaxInsThes);


	mCheckIgnoreM5.SetCheck(FALSE);
	mCheckUseAllUp.SetCheck(FALSE);
	mCheckIgnoreM60.SetCheck(FALSE);


	int ret;
	ret = mKLineType.AddString("K线日线");
	mKLineType.SetItemData(ret, 0);

	ret = mKLineType.AddString("K线小时线");
	mKLineType.SetItemData(ret, 1);

	mKLineType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgTanAngle::OnBnClickedOk()
{
	CString strVal;
	int temp;
	mEditDays.GetWindowText(strVal);
	temp=atoi(strVal);
	mBackDays=temp;

	mEditMaxAngle.GetWindowText(strVal);
	temp=atoi(strVal);
	mMaxAngle=temp;


	mEditMaxVol.GetWindowText(strVal);
	temp=atoi(strVal);
	mMaxVolMul=temp;
	f_max_volume_multiple=(double)mMaxVolMul/10.0;


	mEditMaxInsBack.GetWindowText(strVal);
	temp=atoi(strVal);
	mMaxInsBack=temp;

	mEditMaxInsThes.GetWindowText(strVal);
	temp=atoi(strVal);
	mMaxInsThes=temp;
	f_max_ins_thes=mMaxInsThes;

	bIgnoreM5=mCheckIgnoreM5.GetCheck();
	bUseAllUp=mCheckUseAllUp.GetCheck();
	bIgnoreM60=mCheckIgnoreM60.GetCheck();

	int	iItem = mKLineType.GetCurSel();
	if (iItem < 0) return;

	mKType = mKLineType.GetItemData(iItem);


	CDialogEx::OnOK();
}
