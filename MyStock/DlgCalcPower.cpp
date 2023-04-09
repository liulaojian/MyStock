// DlgCalcPower.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgCalcPower.h"
#include "afxdialogex.h"
#include "StockDataMgr.h"
#include "Convert.h"
// CDlgCalcPower 对话框

IMPLEMENT_DYNAMIC(CDlgCalcPower, CDialogEx)

CDlgCalcPower::CDlgCalcPower(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCalcPower::IDD, pParent)
{
	strStockCode="SH000001";
	pStockDayTable=NULL;
	strBeginDate="";
	strEndDate="";
}

CDlgCalcPower::~CDlgCalcPower()
{
}

void CDlgCalcPower::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN, mBeginDateCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, mEndDateCtrl);
	DDX_Control(pDX, IDC_EDIT_RESULT, mResultEdit);
	DDX_Control(pDX, IDC_EDIT_STOCK_DAYS, mEditStockDays);
}


BEGIN_MESSAGE_MAP(CDlgCalcPower, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CALC, &CDlgCalcPower::OnBnClickedBtnCalc)
END_MESSAGE_MAP()


// CDlgCalcPower 消息处理程序


BOOL CDlgCalcPower::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);

	CString strStockInfo;
	CString strStockName;
	strStockName=StockDataMgr()->GetStockName(strStockCode);
	strStockInfo.Format("%s  %s ",strStockCode,strStockName);
	GetDlgItem(IDC_STATIC_STOCK)->SetWindowText(strStockInfo);

	if(strBeginDate!="" && strEndDate!="")
	{
		CTime mBeginDate=ConverStringToCTime(strBeginDate);
		CTime mEndDate=ConverStringToCTime(strEndDate);
		mBeginDateCtrl.SetTime(&mBeginDate);
		mEndDateCtrl.SetTime(&mEndDate);
	}
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgCalcPower::OnBnClickedBtnCalc()
{
	CTime mBeginTime,mEndTime;
	mBeginDateCtrl.GetTime(mBeginTime);
	mEndDateCtrl.GetTime(mEndTime);



	CString strTempBeginDate=pStockDayTable->GetNearestStockDayDate(mBeginTime);
	CString strTempEndDate=pStockDayTable->GetNearestStockDayDate(mEndTime);


	mBeginTime=ConverStringToCTime(strTempBeginDate);
	mEndTime=ConverStringToCTime(strTempEndDate);

	CTimeSpan span=mEndTime-mBeginTime;

	int iDay=span.GetDays();
	if(iDay<=0)
	{
		AfxMessageBox("开始时间大于等于结束时间");
		return;
	}
	int mBeginPos=pStockDayTable->GetNearestStockDayIndex(strTempBeginDate);
	int mEndPos=pStockDayTable->GetNearestStockDayIndex(strTempEndDate);

	if((mEndPos-mBeginPos)<2)
	{
		AfxMessageBox("算法不支持小于2个交易日");
		return;
	}

	strBeginDate=strTempBeginDate;
	strEndDate=strTempEndDate;

	mBeginDateCtrl.SetTime(&mBeginTime);
	mEndDateCtrl.SetTime(&mEndTime);

	Vec_StockDayData vecStockDayData;

	vecStockDayData=pStockDayTable->GetStockDayDataListBwIndex(mBeginPos,mEndPos);

	if(vecStockDayData.size()==0)
		return;
	float f_power;
	float f_total_power=0.0;
	CStockDayData * pStockDayData=NULL;
	for(int i=1;i<vecStockDayData.size();i++)
	{
		pStockDayData=vecStockDayData[i];

		float f_percent=(pStockDayData->GetEndPrice()-vecStockDayData[i-1]->GetEndPrice())/vecStockDayData[i-1]->GetEndPrice();
		f_percent=f_percent/2.0;
		f_power=f_percent*pStockDayData->GetTotalPrice();
		f_total_power+=f_power;
	}

	CString strTotalPower;
	strTotalPower.Format("%.2f",f_total_power);
	mResultEdit.SetWindowText(strTotalPower);
	
	CString strTemp;
	strTemp.Format("%d",vecStockDayData.size());
	mEditStockDays.SetWindowText(strTemp);
}


