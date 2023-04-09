// DlgTanAnglePara.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgTanAnglePara.h"
#include "afxdialogex.h"


// CDlgTanAnglePara 对话框

IMPLEMENT_DYNAMIC(CDlgTanAnglePara, CDialogEx)

CDlgTanAnglePara::CDlgTanAnglePara(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTanAnglePara::IDD, pParent)
{

}

CDlgTanAnglePara::~CDlgTanAnglePara()
{
}

void CDlgTanAnglePara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TAN60_ANGLE_MIN, mEditTanAngleMin);
	DDX_Control(pDX, IDC_SPIN_TAN60_ANGLE_MIN, mSpinTanAngleMin);
	DDX_Control(pDX, IDC_EDIT_TAN60_ANGLE_MAX, mEditTanAngleMax);
	DDX_Control(pDX, IDC_SPIN_TAN60_ANGLE_MAX, mSpinTanAngleMax);
	DDX_Control(pDX, IDC_EDIT_AVE_VOL_MUL_MIN, mEditAveVolMulMin);
	DDX_Control(pDX, IDC_SPIN_AVE_VOL_MUL_MIN, mSpinAveVolMulMin);
	DDX_Control(pDX, IDC_EDIT_AVE_VOL_MUL_MAX, mEditAveVolMulMax);
	DDX_Control(pDX, IDC_SPIN_AVE_VOL_MUL_MAX, mSpinAveVolMulMax);
	DDX_Control(pDX, IDC_CHECK_TAN_ORDER_UP, mCheckTanOrderUp);
	DDX_Control(pDX, IDC_CHECK_M60_LESS_m20, mCheckM60UpNumsLessM20);
	DDX_Control(pDX, IDC_CHECK_M60_ALL_UP, mCheckM60AllUp);
	DDX_Control(pDX, IDC_EDIT_MAX_VOL_MUL_MIN, mEditMaxVolMulMin);
	DDX_Control(pDX, IDC_SPIN_MAX_VOL_MUL_MIN, mSpinMaxVolMulMin);
	DDX_Control(pDX, IDC_EDIT_MAX_VOL_MUL_MAX, mEditMaxVolMulMax);
	DDX_Control(pDX, IDC_SPIN_MAX_VOL_MUL_MAX, mSpinMaxVolMulMax);
	DDX_Control(pDX, IDC_EDIT_MAX_ANGLE_VALUE, mEditMaxTan);
	DDX_Control(pDX, IDC_SPIN_MAX_ANGLE_VALUE, mSpinMaxTan);
	DDX_Control(pDX, IDC_EDIT_PRICE_INCREASE, mEditPriceIncrease);
	DDX_Control(pDX, IDC_SPIN_PRICE_INCREASE, mSpinPriceIncrease);
	DDX_Control(pDX, IDC_EDIT_MIN_MAX_ANGLE_VALUE, mEditMinMaxTan);
	DDX_Control(pDX, IDC_SPIN_MIN_MAX_ANGLE_VALUE, mSpinMinMaxTan);
}


BEGIN_MESSAGE_MAP(CDlgTanAnglePara, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTanAnglePara::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_TAN_MODE, &CDlgTanAnglePara::OnBnClickedBtnTanMode)
END_MESSAGE_MAP()


// CDlgTanAnglePara 消息处理程序


BOOL CDlgTanAnglePara::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	mTan60AngleMin=9;
	mSpinTanAngleMin.SetBuddy(&mEditTanAngleMin);
	mSpinTanAngleMin.SetRange(0, 60);
	mSpinTanAngleMin.SetPos(mTan60AngleMin);


	mTan60AngleMax=30;
	mSpinTanAngleMax.SetBuddy(&mEditTanAngleMax);
	mSpinTanAngleMax.SetRange(0, 90);
	mSpinTanAngleMax.SetPos(mTan60AngleMax);

	mAveVolMulMin=5;
	mSpinAveVolMulMin.SetBuddy(&mEditAveVolMulMin);
	mSpinAveVolMulMin.SetRange(0, 100);
	mSpinAveVolMulMin.SetPos(mAveVolMulMin);

	mAveVolMulMax=20;
	mSpinAveVolMulMax.SetBuddy(&mEditAveVolMulMax);
	mSpinAveVolMulMax.SetRange(0, 100);
	mSpinAveVolMulMax.SetPos(mAveVolMulMax);


	//int mMaxVolMulMin;
	//double f_MaxVolMulMin;
	mMaxVolMulMin=5;
	mSpinMaxVolMulMin.SetBuddy(&mEditMaxVolMulMin);
	mSpinMaxVolMulMin.SetRange(0, 100);
	mSpinMaxVolMulMin.SetPos(mMaxVolMulMin);


	mMaxVolMulMax=18;
	mSpinMaxVolMulMax.SetBuddy(&mEditMaxVolMulMax);
	mSpinMaxVolMulMax.SetRange(0, 100);
	mSpinMaxVolMulMax.SetPos(mMaxVolMulMax);

	mMaxTanAngle=65;
	mSpinMaxTan.SetBuddy(&mEditMaxTan);
	mSpinMaxTan.SetRange(0, 90);
	mSpinMaxTan.SetPos(mMaxTanAngle);

	mMinMaxTanAngle=15;
	mSpinMinMaxTan.SetBuddy(&mEditMinMaxTan);
	mSpinMinMaxTan.SetRange(0, 90);
	mSpinMinMaxTan.SetPos(mMinMaxTanAngle);

	//int mMaxVolMulMax;
	//double f_MaxVolMulMax;


	mPriceIncrease=80;
	mSpinPriceIncrease.SetBuddy(&mEditPriceIncrease);
	mSpinPriceIncrease.SetRange(0, 500);
	mSpinPriceIncrease.SetPos(mPriceIncrease);


	bNormalMode=TRUE;

	
	
	SetTanMode();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgTanAnglePara::SetTanMode(void)
{
	if(bNormalMode)		
	{

		mTan60AngleMin=3;
		mSpinTanAngleMin.SetPos(mTan60AngleMin);

		mTan60AngleMax=32;
		mSpinTanAngleMax.SetPos(mTan60AngleMax);

		mAveVolMulMin=5;
		mSpinAveVolMulMin.SetPos(mAveVolMulMin);

		mAveVolMulMax=22;
		mSpinAveVolMulMax.SetPos(mAveVolMulMax);

		mMaxVolMulMin=5;
		mSpinMaxVolMulMin.SetPos(mMaxVolMulMin);


		mMaxVolMulMax=20;
		mSpinMaxVolMulMax.SetPos(mMaxVolMulMax);

		mMaxTanAngle=65;
		mSpinMaxTan.SetPos(mMaxTanAngle);

		mMinMaxTanAngle=0;
		mSpinMinMaxTan.SetPos(mMinMaxTanAngle);

		mPriceIncrease=80;
		mSpinPriceIncrease.SetPos(mPriceIncrease);

		GetDlgItem(IDC_BTN_TAN_MODE)->SetWindowText("普通模式");
	}
	else
	{
		mTan60AngleMin=5;
		mSpinTanAngleMin.SetPos(mTan60AngleMin);

		mTan60AngleMax=30;
		mSpinTanAngleMax.SetPos(mTan60AngleMax);

		mAveVolMulMin=19;
		mSpinAveVolMulMin.SetPos(mAveVolMulMin);

		mAveVolMulMax=30;
		mSpinAveVolMulMax.SetPos(mAveVolMulMax);

		mMaxVolMulMin=15;
		mSpinMaxVolMulMin.SetPos(mMaxVolMulMin);


		mMaxVolMulMax=20;
		mSpinMaxVolMulMax.SetPos(mMaxVolMulMax);

		mMaxTanAngle=70;
		mSpinMaxTan.SetPos(mMaxTanAngle);

		mMinMaxTanAngle=32;
		mSpinMinMaxTan.SetPos(mMinMaxTanAngle);

		mPriceIncrease=500;
		mSpinPriceIncrease.SetPos(mPriceIncrease);
		GetDlgItem(IDC_BTN_TAN_MODE)->SetWindowText("激进模式");
	}

}

void CDlgTanAnglePara::OnBnClickedOk()
{
	CString strVal;
	int temp;
	mEditTanAngleMin.GetWindowText(strVal);
	temp=atoi(strVal);
	mTan60AngleMin=temp;

	mEditTanAngleMax.GetWindowText(strVal);
	temp=atoi(strVal);
	mTan60AngleMax=temp;
	if(mTan60AngleMax<=mTan60AngleMin)
	{
		AfxMessageBox("Tan Angle max <=min");
		return;
	}

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


	mEditMaxVolMulMin.GetWindowText(strVal);
	temp=atoi(strVal);
	mMaxVolMulMin=temp;
	f_MaxVolMulMin=(double)mMaxVolMulMin/10.0;

	mEditMaxVolMulMax.GetWindowText(strVal);
	temp=atoi(strVal);
	mMaxVolMulMax=temp;
	f_MaxVolMulMax=(double)mMaxVolMulMax/10.0;


	mEditMaxTan.GetWindowText(strVal);
	temp=atoi(strVal);
	mMaxTanAngle=temp;

	mEditMinMaxTan.GetWindowText(strVal);
	temp=atoi(strVal);
	mMinMaxTanAngle=temp;


	mEditPriceIncrease.GetWindowText(strVal);
	temp=atoi(strVal);
	mPriceIncrease=temp;
	fPriceIncrease=mPriceIncrease;


	bTanAngleOrderUp=mCheckTanOrderUp.GetCheck();

	bTanAngleM60UpLessM20=mCheckM60UpNumsLessM20.GetCheck();

	bTanAngleM60AllUp=mCheckM60AllUp.GetCheck();

	if(bTanAngleM60AllUp&&bTanAngleM60UpLessM20)
	{
		AfxMessageBox("M60一直上升和M60上升小于M20不兼容");
		return;
	}

	CDialogEx::OnOK();
}


void CDlgTanAnglePara::OnBnClickedBtnTanMode()
{
	if(bNormalMode)
		bNormalMode=FALSE;
	else
		bNormalMode=TRUE;
	SetTanMode();
}
