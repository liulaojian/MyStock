// DlgLoopBackSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgLoopBackSetting.h"
#include "afxdialogex.h"
#include "Convert.h"
#include "Util.h"

// CDlgLoopBackSetting 对话框

IMPLEMENT_DYNAMIC(CDlgLoopBackSetting, CDialogEx)

CDlgLoopBackSetting::CDlgLoopBackSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLoopBackSetting::IDD, pParent),pStockDayTable(NULL)
{

}

CDlgLoopBackSetting::~CDlgLoopBackSetting()
{
}

void CDlgLoopBackSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_LOOPBACK_BEGIN, mDateTimeBegin);
	DDX_Control(pDX, IDC_DATETIMEPICKER_LOOPBACK_END, mDateTimeEnd);
	DDX_Control(pDX, IDC_COMBO_CMPMETHOD, mCmbCmpMethod);
	DDX_Control(pDX, IDC_COMBO_CMPMETHOD_NUMS, mCmbMethodNums);
	DDX_Control(pDX, IDC_COMBO_TOTAL_FUND, mCmbToatlFund);
	DDX_Control(pDX, IDC_COMBO_STAMP_TAX, mCmbStampTax);
	DDX_Control(pDX, IDC_COMBO_SERVICE_CHARGE, mCmbServiceCharge);
	DDX_Control(pDX, IDC_COMBO_SERVICE_CHARGE_MIN, mCmbMinServiceCharge);
	DDX_Control(pDX, IDC_COMBO_STOCK_EXP, mCmbStockExp);
}


BEGIN_MESSAGE_MAP(CDlgLoopBackSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgLoopBackSetting::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgLoopBackSetting 消息处理程序


BOOL CDlgLoopBackSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if(pStockDayTable==NULL)
		return FALSE;

	CTime mBeginDateTime,mEndDateTime;

	mBeginDateTime=ConverStringToCTime(pStockDayTable->GetStockDayDateReverseIndex(98));
	mEndDateTime=ConverStringToCTime(pStockDayTable->GetStockDayDateReverseIndex(8));

	mDateTimeBegin.SetTime(&mBeginDateTime);
	mDateTimeEnd.SetTime(&mEndDateTime);

	mCmbToatlFund.ResetContent();
	int ret=mCmbToatlFund.AddString("2万");
	float *pVal=new float;
	(*pVal)=20000.0;
	mCmbToatlFund.SetItemData(ret,(DWORD_PTR)pVal);

	ret=mCmbToatlFund.AddString("5万");
	pVal=new float;
	(*pVal)=50000.0;
	mCmbToatlFund.SetItemData(ret,(DWORD_PTR)pVal);

	ret=mCmbToatlFund.AddString("10万");
	pVal=new float;
	(*pVal)=100000.0;
	mCmbToatlFund.SetItemData(ret,(DWORD_PTR)pVal);
	mCmbToatlFund.SetCurSel(0);


	mCmbStampTax.ResetContent();
	ret=mCmbStampTax.AddString("千分之1");
	pVal=new float;
	(*pVal)=0.001;
	mCmbStampTax.SetItemData(ret,(DWORD_PTR)pVal);
	ret=mCmbStampTax.AddString("千分之1.5");
	pVal=new float;
	(*pVal)=0.0015;
	mCmbStampTax.SetItemData(ret,(DWORD_PTR)pVal);
	ret=mCmbStampTax.AddString("千分之2");
	pVal=new float;
	(*pVal)=0.002;
	mCmbStampTax.SetItemData(ret,(DWORD_PTR)pVal);
	mCmbStampTax.SetCurSel(0);

	mCmbServiceCharge.ResetContent();
	ret=mCmbServiceCharge.AddString("万分之2.5");
	pVal=new float;
	(*pVal)=0.00025;
	mCmbServiceCharge.SetItemData(ret,(DWORD_PTR)pVal);
	ret=mCmbServiceCharge.AddString("万分之3");
	pVal=new float;
	(*pVal)=0.0003;
	mCmbServiceCharge.SetItemData(ret,(DWORD_PTR)pVal);
	ret=mCmbServiceCharge.AddString("万分之2");
	pVal=new float;
	(*pVal)=0.0002;
	mCmbServiceCharge.SetItemData(ret,(DWORD_PTR)pVal);
	ret=mCmbServiceCharge.AddString("万分之1");
	pVal=new float;
	(*pVal)=0.0001;
	mCmbServiceCharge.SetItemData(ret,(DWORD_PTR)pVal);
	mCmbServiceCharge.SetCurSel(0);

	mCmbMinServiceCharge.ResetContent();
	ret=mCmbMinServiceCharge.AddString("5元");
	pVal=new float;
	(*pVal)=5.0;
	mCmbMinServiceCharge.SetItemData(ret,(DWORD_PTR)pVal);
	ret=mCmbMinServiceCharge.AddString("2元");
	pVal=new float;
	(*pVal)=2.0;
	mCmbMinServiceCharge.SetItemData(ret,(DWORD_PTR)pVal);
	ret=mCmbMinServiceCharge.AddString("10元");
	pVal=new float;
	(*pVal)=10.0;
	mCmbMinServiceCharge.SetItemData(ret,(DWORD_PTR)pVal);
	mCmbMinServiceCharge.SetCurSel(0);

	mCmbMethodNums.ResetContent();
	ret=mCmbMethodNums.AddString("15");
	mCmbMethodNums.SetItemData(ret,15);
	ret=mCmbMethodNums.AddString("16");
	mCmbMethodNums.SetItemData(ret,16);
	ret=mCmbMethodNums.AddString("17");
	mCmbMethodNums.SetItemData(ret,17);
	ret=mCmbMethodNums.AddString("18");
	mCmbMethodNums.SetItemData(ret,18);
	ret=mCmbMethodNums.AddString("19");
	mCmbMethodNums.SetItemData(ret,19);
	ret=mCmbMethodNums.AddString("20");
	mCmbMethodNums.SetItemData(ret,20);
	mCmbMethodNums.SetCurSel(0);


	mCmbCmpMethod.ResetContent();
	ret=mCmbCmpMethod.AddString("历史比较法");
	mCmbCmpMethod.SetCurSel(0);

	mCmbStockExp.ResetContent();
	ret=mCmbStockExp.AddString("上证指数");
	ret=mCmbStockExp.AddString("上证50");
	ret=mCmbStockExp.AddString("沪深300");
	mCmbStockExp.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgLoopBackSetting::OnBnClickedOk()
{
	int	iItem = mCmbToatlFund.GetCurSel();
	if(iItem<0) return ;
	float  *p_val;
	p_val=(float*)mCmbToatlFund.GetItemData(iItem);
	f_total_fund=(*p_val);

	iItem = mCmbStampTax.GetCurSel();
	if(iItem<0) return ;
	p_val=(float*)mCmbStampTax.GetItemData(iItem);
	f_stamp_tax=(*p_val);

	iItem = mCmbServiceCharge.GetCurSel();
	if(iItem<0) return ;
	p_val=(float*)mCmbServiceCharge.GetItemData(iItem);
	f_service_charge=(*p_val);

	
	iItem = mCmbMinServiceCharge.GetCurSel();
	if(iItem<0) return ;
	p_val=(float*)mCmbMinServiceCharge.GetItemData(iItem);
	f_min_service_charge=(*p_val);

	mCmbCmpMethod.GetWindowText(strCmpMethodDes);
	iItem = mCmbMethodNums.GetCurSel();
	if(iItem<0) return ;
	mCmpMethodNums=mCmbMethodNums.GetItemData(iItem);

	CTime mBeginTime,mEndTime;

	mDateTimeBegin.GetTime(mBeginTime);
	mDateTimeEnd.GetTime(mEndTime);

	strBeginDate=pStockDayTable->GetNearestStockDayDate(mBeginTime);
	strEndDate=pStockDayTable->GetNearestStockDayDate(mEndTime);


	mCmbStockExp.GetWindowText(strStockExpName);

	CDialogEx::OnOK();
}
