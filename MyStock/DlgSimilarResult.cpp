// DlgSimilarResult.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgSimilarResult.h"
#include "afxdialogex.h"
#include "StockDataMgr.h"
#include "Convert.h"
#include "Log.h"
#include "StockPowerArithmetic.h"
// CDlgSimilarResult 对话框

IMPLEMENT_DYNAMIC(CDlgSimilarResult, CDialogEx)

CDlgSimilarResult::CDlgSimilarResult(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSimilarResult::IDD, pParent)
{
	strStockCode="";
	strSimilarResult="";
	strEndDate="";
}

CDlgSimilarResult::~CDlgSimilarResult()
{
}

void CDlgSimilarResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SIMILAR, mEditSimilar);
}


BEGIN_MESSAGE_MAP(CDlgSimilarResult, CDialogEx)
END_MESSAGE_MAP()


// CDlgSimilarResult 消息处理程序


BOOL CDlgSimilarResult::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if(strStockCode=="")
		return FALSE;
	CString strStockName=StockDataMgr()->GetStockName(strStockCode);

	CString strInfo;

	CString strExpInfo=CalcExpPowerValue(strEndDate);

	strInfo.Format("%s  %s    指数 %s  能量值 %s",strStockCode,strStockName,strEndDate,strExpInfo);
	GetDlgItem(IDC_STATIC_STOCK)->SetWindowText(strInfo);

	CStringArray arryList;
	StringSplit(strSimilarResult,arryList,'#');

	CString strTotal="";
	for(int i=0;i<arryList.GetCount();i++)
	{
		CString strResult=arryList.GetAt(i);
		CStringArray arryInfo;

		//PrintfDebug("%s",strResult);
		StringSplit(strResult,arryInfo,'|');

		if(arryInfo.GetCount()==2)
		{
			CString strResultStockCode=arryInfo.GetAt(0);

			CString strResultStockName=StockDataMgr()->GetStockName(strResultStockCode);

			CString strResultDate=arryInfo.GetAt(1);

			CString strRange=CalcNext3DayRange(strResultStockCode,strResultDate);
			CString strExpRange=CalcExpPowerValue(strResultDate);
			CString strTemp;
			strTemp.Format("%s  %s  %s   %s             %s\r\n",strResultStockCode,strResultStockName,strResultDate,strRange,strExpRange);
			strTotal+=strTemp;
		}
	}

	mEditSimilar.SetWindowText(strTotal);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


CString CDlgSimilarResult::CalcNext3DayRange(CString strResultStockCode,CString strResultDate)
{
	CStockDayTable *pStockDayTable;

	pStockDayTable=StockDataMgr()->GetStockDayTable(strResultStockCode);

	if(pStockDayTable==NULL)
		return "";

	

	int mPos=pStockDayTable->GetStockDayIndex(strResultDate);
	if(mPos<0)
		return "";

	Vec_StockDayData vecStockDayData;
	pStockDayTable->LockData();
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	pStockDayTable->UnlockData();

	if((mPos+3)>=vecStockDayData.size())
		return "";
	
	CStockDayData *pStockDayData=NULL;

	pStockDayData=vecStockDayData[mPos];

	double f_now_close=pStockDayData->GetEndPrice();

	pStockDayData=vecStockDayData[mPos+1];

	double f_next_1_close=pStockDayData->GetEndPrice();

	pStockDayData=vecStockDayData[mPos+2];

	double f_next_2_close=pStockDayData->GetEndPrice();

	pStockDayData=vecStockDayData[mPos+3];

	double f_next_3_close=pStockDayData->GetEndPrice();

	double f_1_range=(f_next_1_close-f_now_close)*100.0/f_now_close;
	double f_2_range=(f_next_2_close-f_next_1_close)*100.0/f_next_1_close;

	double f_3_range=(f_next_3_close-f_next_2_close)*100.0/f_next_2_close;


	CString strInfo;


	strInfo.Format("第1天涨幅 %.2f  第2天涨幅 %.2f   第3天涨幅 %.2f",f_1_range,f_2_range,f_3_range);


	return strInfo;
}


CString CDlgSimilarResult::CalcExpPowerValue(CString strResultDate)
{
	CString strExpStockCode="SH000001";

	CStockDayTable *pStockDayTable;

	pStockDayTable=StockDataMgr()->GetStockDayTable(strExpStockCode);

	if(pStockDayTable==NULL)
		return "";

	int mPos=pStockDayTable->GetStockDayIndex(strResultDate);
	if(mPos<0)
		return "";
	Vec_StockDayData vecStockDayData;
	pStockDayTable->LockData();
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	pStockDayTable->UnlockData();

	CString strBeginDate=vecStockDayData[mPos-20]->GetDate();

	CString strInfo="";

	CStockPowerArithmetic mStockPowerArithmetic(strExpStockCode);
	StockPowerPeriodInfo * pStockPowerPeriodInfo=NULL;
	if(mStockPowerArithmetic.Init())
	{
		pStockPowerPeriodInfo=mStockPowerArithmetic.NewCalcStockPeriodInfo(strBeginDate,strResultDate);
		if(pStockPowerPeriodInfo!=NULL)
		{
			double f_10_power=pStockPowerPeriodInfo->f_10_power;
			double f_20_power=pStockPowerPeriodInfo->f_20_power;
			double f_40_power=pStockPowerPeriodInfo->f_40_power;
			double f_60_power=pStockPowerPeriodInfo->f_60_power;
			double f_120_power=pStockPowerPeriodInfo->f_120_power;
			double f_240_power=pStockPowerPeriodInfo->f_240_power;

			strInfo.Format("指数10日 %.2f  20日 %.2f  40日 %.2f  60日 %2.f  120日 %2.f  240日 %2.f",
				f_10_power,f_20_power,f_40_power,f_60_power,f_120_power,f_240_power);
		}
	}

	return strInfo;
}