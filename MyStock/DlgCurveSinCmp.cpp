// DlgCurveSinCmp.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgCurveSinCmp.h"
#include "afxdialogex.h"


// CDlgCurveSinCmp 对话框

IMPLEMENT_DYNAMIC(CDlgCurveSinCmp, CDlgCmpMethod)

CDlgCurveSinCmp::CDlgCurveSinCmp(CWnd* pParent /*=NULL*/)
	: CDlgCmpMethod(CDlgCurveSinCmp::IDD, pParent)
{

}

CDlgCurveSinCmp::~CDlgCurveSinCmp()
{
}

void CDlgCurveSinCmp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_X_SCALE, mEditXScale);
	DDX_Control(pDX, IDC_SLIDER_GATE_PERCENT, mSliderGatePercent);
	DDX_Control(pDX, IDC_SLIDER_EQUNUMS, mSliderEquGateNums);
	DDX_Control(pDX, IDC_MFCMENUBUTTON_XSCALE, mMenuBtnXScale);
}


BEGIN_MESSAGE_MAP(CDlgCurveSinCmp, CDlgCmpMethod)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &CDlgCurveSinCmp::OnBnClickedOk)
	ON_BN_CLICKED(IDC_MFCMENUBUTTON_XSCALE, &CDlgCurveSinCmp::OnBnClickedMfcmenubuttonXscale)
END_MESSAGE_MAP()


// CDlgCurveSinCmp 消息处理程序


BOOL CDlgCurveSinCmp::OnInitDialog()
{
	CDlgCmpMethod::OnInitDialog();

	if(pStockDayTable==NULL)
		return FALSE;
	if(strBeginDayDate=="" || strEndDayDate=="")
		return FALSE;

	mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDayDate);
	mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDayDate);

	if(mBeginPos==-1 || mEndPos==-1 )
		return FALSE;

	if(mBeginPos>mEndPos)
		return FALSE;

	ParseCmpMethodParas();

	CString strVal;

	strVal.Format("%f",f_x_scale);
	mEditXScale.SetWindowText(strVal);

	//mSliderGatePercent.SetRangeMin(10);
	//mSliderGatePercent.SetRangeMax(100);
	mSliderGatePercent.SetRange(10,100,TRUE);
	mSliderGatePercent.SetPos((int)f_gate_percent);
	
	CString strTemp;
	strTemp.Format("百分之 %d",(int)f_gate_percent);
	GetDlgItem(IDC_STATIC_GATE_PERCENT)->SetWindowText(strTemp);

	int mNums=(mEndPos-mBeginPos);
	int mMin=mNums/2;
	mSliderEquGateNums.SetRange(mMin,mNums,TRUE);
	mSliderEquGateNums.SetPos(mEquGateNums);
	strTemp.Format("%d",mEquGateNums);
	GetDlgItem(IDC_STATIC_EQUNUMS)->SetWindowText(strTemp);

	CMenu* pMenu = new CMenu;
	pMenu->LoadMenu(IDR_MENU_XSCALE);
	
	mMenuBtnXScale.m_hMenu=pMenu->GetSubMenu(0)->GetSafeHmenu();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



BOOL CDlgCurveSinCmp::ParseCmpMethodParas(void)
{
	CString strXScale=mapCmpMethodParas["XScale"];
	if(strXScale!="")
		f_x_scale=atof((LPCSTR)strXScale);
	else
	{
		CStockDayData *pStockDayData=NULL;
		pStockDayData=pStockDayTable->GetStockDayDataByIndex(mEndPos);
		if(pStockDayData)
		{
			float f_end_val=pStockDayData->GetEndPrice();
			if(f_end_val>=1000.0)
				f_x_scale=100.0f;
			else if(f_end_val>=100.0)
				f_x_scale=10.0f;
			else if(f_end_val>=10.0)
				f_x_scale=1.0f;
			else if(f_end_val>=1.0)
				f_x_scale=0.1f;
			else
				f_x_scale=0.1f;
		}
		else
			f_x_scale=100.0f;
	}
	CString strGatePercent=mapCmpMethodParas["GatePercent"];
	if(strGatePercent!="")
		f_gate_percent=atof((LPCSTR)strGatePercent);
	else
		f_gate_percent=50.0f;

	CString strEquGateNums=mapCmpMethodParas["EquGateNums"];
	if(strEquGateNums!="")
		mEquGateNums=atoi((LPCSTR)strEquGateNums);
	else
		mEquGateNums=(mEndPos-mBeginPos)*3/4;


	return TRUE;
}

void CDlgCurveSinCmp::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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


void CDlgCurveSinCmp::OnBnClickedOk()
{
	CString strTemp;
	mEditXScale.GetWindowText(strTemp);
	f_x_scale=atof((LPCSTR)strTemp);
	if(f_x_scale<0.08)
		return;
	strTemp.Format("%f",f_x_scale);
	mapCmpMethodParas["XScale"]=strTemp;

	strTemp.Format("%f",f_gate_percent);
	mapCmpMethodParas["GatePercent"]=strTemp;

	strTemp.Format("%d",mEquGateNums);
	mapCmpMethodParas["EquGateNums"]=strTemp;
	CDlgCmpMethod::OnOK();
}


void CDlgCurveSinCmp::OnBnClickedMfcmenubuttonXscale()
{
	if(mMenuBtnXScale.m_nMenuResult == ID_MENU_XSCALE_AVE_1_20)
	{
		CStockDayData *pBeginStockDayData=NULL;
		pBeginStockDayData=pStockDayTable->GetStockDayDataByIndex(mBeginPos);
		CStockDayData *pEndStockDayData=NULL;
		pEndStockDayData=pStockDayTable->GetStockDayDataByIndex(mEndPos);

		if(pBeginStockDayData!=NULL && pEndStockDayData!=NULL)
		{
			float f_begin_val,f_end_val;
			f_begin_val=pBeginStockDayData->GetEndPrice();
			f_end_val=pEndStockDayData->GetEndPrice();
			float f_val=(f_begin_val+f_end_val)/2;
			f_val=f_val/20.0;

			if(f_val>=100.0)
			{
				int mVal=f_val;
				int n=mVal/100;
				mVal=n*100;
				f_val=mVal;
			}
			else if(f_val>=10.0)
			{
				int mVal=f_val;
				int n=mVal/10;
				mVal=n*10;
				f_val=mVal;
			}
			else if(f_val>=1.0)
			{
				int mVal=f_val;
				f_val=mVal;
			}
			else
			{
				int n=f_val/0.1;
				f_val=n*0.1;
			}

			CString strTemp;
			strTemp.Format("%f",f_val);
			mEditXScale.SetWindowText(strTemp);

		}

	}
	else if(mMenuBtnXScale.m_nMenuResult == ID_MENU_XSCALE_AVE_1_30)
	{
		CStockDayData *pBeginStockDayData=NULL;
		pBeginStockDayData=pStockDayTable->GetStockDayDataByIndex(mBeginPos);
		CStockDayData *pEndStockDayData=NULL;
		pEndStockDayData=pStockDayTable->GetStockDayDataByIndex(mEndPos);

		if(pBeginStockDayData!=NULL && pEndStockDayData!=NULL)
		{
			float f_begin_val,f_end_val;
			f_begin_val=pBeginStockDayData->GetEndPrice();
			f_end_val=pEndStockDayData->GetEndPrice();
			float f_val=(f_begin_val+f_end_val)/2;
			f_val=f_val/30.0;

			if(f_val>=100.0)
			{
				int mVal=f_val;
				int n=mVal/100;
				mVal=n*100;
				f_val=mVal;
			}
			else if(f_val>=10.0)
			{
				int mVal=f_val;
				int n=mVal/10;
				mVal=n*10;
				f_val=mVal;
			}
			else if(f_val>=1.0)
			{
				int mVal=f_val;
				f_val=mVal;
			}
			else
			{
				int n=f_val/0.1;
				f_val=n*0.1;
			}

			CString strTemp;
			strTemp.Format("%f",f_val);
			mEditXScale.SetWindowText(strTemp);

		}

	}
	else if(mMenuBtnXScale.m_nMenuResult == ID_MENU_XSCALE_AVE_1_40)
	{
		CStockDayData *pBeginStockDayData=NULL;
		pBeginStockDayData=pStockDayTable->GetStockDayDataByIndex(mBeginPos);
		CStockDayData *pEndStockDayData=NULL;
		pEndStockDayData=pStockDayTable->GetStockDayDataByIndex(mEndPos);

		if(pBeginStockDayData!=NULL && pEndStockDayData!=NULL)
		{
			float f_begin_val,f_end_val;
			f_begin_val=pBeginStockDayData->GetEndPrice();
			f_end_val=pEndStockDayData->GetEndPrice();
			float f_val=(f_begin_val+f_end_val)/2;
			f_val=f_val/40.0;

			if(f_val>=100.0)
			{
				int mVal=f_val;
				int n=mVal/100;
				mVal=n*100;
				f_val=mVal;
			}
			else if(f_val>=10.0)
			{
				int mVal=f_val;
				int n=mVal/10;
				mVal=n*10;
				f_val=mVal;
			}
			else if(f_val>=1.0)
			{
				int mVal=f_val;
				f_val=mVal;
			}
			else
			{
				int n=f_val/0.1;
				f_val=n*0.1;
			}

			CString strTemp;
			strTemp.Format("%f",f_val);
			mEditXScale.SetWindowText(strTemp);

		}

	}
}
