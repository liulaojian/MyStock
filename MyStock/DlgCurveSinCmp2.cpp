// DlgCurveSinCmp2.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgCurveSinCmp2.h"
#include "afxdialogex.h"


// CDlgCurveSinCmp2 对话框

IMPLEMENT_DYNAMIC(CDlgCurveSinCmp2, CDlgCmpMethod)

CDlgCurveSinCmp2::CDlgCurveSinCmp2(CWnd* pParent /*=NULL*/)
	: CDlgCmpMethod(CDlgCurveSinCmp2::IDD, pParent)
{
	mCmpMethodNums=15;
}

CDlgCurveSinCmp2::~CDlgCurveSinCmp2()
{
}

void CDlgCurveSinCmp2::DoDataExchange(CDataExchange* pDX)
{
	CDlgCmpMethod::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_X_BASE_METHOD, mCmbXScale);
	DDX_Control(pDX, IDC_SLIDER_GATE_PERCENT, mSliderGatePercent);
	DDX_Control(pDX, IDC_SLIDER_EQUNUMS, mSliderEquGateNums);
}


BEGIN_MESSAGE_MAP(CDlgCurveSinCmp2, CDlgCmpMethod)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &CDlgCurveSinCmp2::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCurveSinCmp2 消息处理程序


BOOL CDlgCurveSinCmp2::OnInitDialog()
{
	CDlgCmpMethod::OnInitDialog();

	if(pStockDayTable==NULL)
		return FALSE;

	mCmbXScale.ResetContent();
	int ret=mCmbXScale.AddString("按平均值的1/20取整");
	mCmbXScale.SetItemData(ret,XSCALE_AVE_1_20);
	ret=mCmbXScale.AddString("按平均值的1/30取整");
	mCmbXScale.SetItemData(ret,XSCALE_AVE_1_30);
	ret=mCmbXScale.AddString("按平均值的1/40取整");
	mCmbXScale.SetItemData(ret,XSCALE_AVE_1_40);
	mCmbXScale.SetCurSel(0);

	ParseCmpMethodParas();

	mSliderGatePercent.SetRange(10,100,TRUE);
	mSliderGatePercent.SetPos((int)f_gate_percent);

	CString strTemp;
	strTemp.Format("百分之 %d",(int)f_gate_percent);
	GetDlgItem(IDC_STATIC_GATE_PERCENT)->SetWindowText(strTemp);

	int mNums=mCmpMethodNums;
	int mMin=mNums/2;
	mSliderEquGateNums.SetRange(mMin,mNums,TRUE);
	mSliderEquGateNums.SetPos(mEquGateNums);
	strTemp.Format("%d",mEquGateNums);
	GetDlgItem(IDC_STATIC_EQUNUMS)->SetWindowText(strTemp);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CDlgCurveSinCmp2::ParseCmpMethodParas(void)
{
	CString strGatePercent=mapCmpMethodParas["GatePercent"];
	if(strGatePercent!="")
		f_gate_percent=atof((LPCSTR)strGatePercent);
	else
		f_gate_percent=50.0f;

	CString strEquGateNums=mapCmpMethodParas["EquGateNums"];
	if(strEquGateNums!="")
		mEquGateNums=atoi((LPCSTR)strEquGateNums);
	else
		mEquGateNums=mCmpMethodNums*3/4;

	return TRUE;
}

void CDlgCurveSinCmp2::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	switch(pScrollBar->GetDlgCtrlID())
	{
	case IDC_SLIDER_GATE_PERCENT:
		{
			CString strTemp;
			int mPos=mSliderGatePercent.GetPos();
			f_gate_percent=(double)mPos;
			strTemp.Format("百分之 %d",(int)f_gate_percent);
			GetDlgItem(IDC_STATIC_GATE_PERCENT)->SetWindowText(strTemp);
		}
		break;

	case IDC_SLIDER_EQUNUMS:
		{
			CString strTemp;
			int mPos=mSliderEquGateNums.GetPos();
			mEquGateNums=mPos;

			strTemp.Format("%d",mEquGateNums);
			GetDlgItem(IDC_STATIC_EQUNUMS)->SetWindowText(strTemp);
		}
		break;
	}

	CDlgCmpMethod::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDlgCurveSinCmp2::OnBnClickedOk()
{
	int iItem = mCmbXScale.GetCurSel();
	if(iItem<0) return ;
	mXScaleMode=mCmbXScale.GetItemData(iItem);

	CString strTemp;
	strTemp.Format("%d",mXScaleMode);
	mapCmpMethodParas["XScaleMode"]=strTemp;

	strTemp.Format("%f",f_gate_percent);
	mapCmpMethodParas["GatePercent"]=strTemp;

	strTemp.Format("%d",mEquGateNums);
	mapCmpMethodParas["EquGateNums"]=strTemp;

	CDlgCmpMethod::OnOK();

}
