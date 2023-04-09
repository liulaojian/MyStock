// DlgSniperLoopBack.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgSniperLoopBack.h"
#include "afxdialogex.h"
#include "CommonMacro.h"
#include "Convert.h"
#include "StockLoopBackDataMgr.h"
// CDlgSniperLoopBack 对话框

IMPLEMENT_DYNAMIC(CDlgSniperLoopBack, CDlgMonitorCallBack)

CDlgSniperLoopBack::CDlgSniperLoopBack(CWnd* pParent /*=NULL*/)
	: CDlgMonitorCallBack(CDlgSniperLoopBack::IDD, pParent)
{

}

CDlgSniperLoopBack::~CDlgSniperLoopBack()
{
}

void CDlgSniperLoopBack::DoDataExchange(CDataExchange* pDX)
{
	CDlgMonitorCallBack::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SNIPER_TYPE, mCmbSniperType);
	DDX_Control(pDX, IDC_DATETIMEPICKER_LOOPBACK, mLoopBackDateTimeCtrl);
	DDX_Control(pDX, IDC_LIST_INFO, mListInfo);
	DDX_Control(pDX, IDC_LIST_RESULT, mListResult);
}


BEGIN_MESSAGE_MAP(CDlgSniperLoopBack, CDlgMonitorCallBack)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_BEGIN, &CDlgSniperLoopBack::OnBnClickedBtnBegin)
END_MESSAGE_MAP()


// CDlgSniperLoopBack 消息处理程序


BOOL CDlgSniperLoopBack::OnInitDialog()
{
	CDlgMonitorCallBack::OnInitDialog();

	mCmbSniperType.ResetContent();
	int ret=mCmbSniperType.AddString("60分钟K线 KDJ过10线 CCI最大-120");
	mCmbSniperType.SetItemData(ret,STOCK_SNIPER_K60MIN_KDJ_ZERO_CCI_ZERO);

	ret=mCmbSniperType.AddString("60分钟K线 上穿CCI-100");
	mCmbSniperType.SetItemData(ret,STOCK_SNIPER_K60MIN_CCI_MINUS_50);

	ret=mCmbSniperType.AddString("60分钟K线 SAR");
	mCmbSniperType.SetItemData(ret,STOCK_SNIPER_K60MIN_SAR);
	

	mCmbSniperType.SetCurSel(0);


	CString strLoopBackDate=StockDataMgr()->GetExpLastDayDate();

	CTime mLoopBackDate=ConverStringToCTime(strLoopBackDate);
	mLoopBackDateTimeCtrl.SetTime(&mLoopBackDate);
	
	

	/*Vec_CString vecStockCodeList=StockDataMgr()->GetStockCodeStringList();
	pKDJStockMonitor=new CKDJStockMonitor(vecStockCodeList);
	pKDJStockMonitor->SetDlgMonitorCallBack(this);
	pKDJStockMonitor->SetLoopBackMode(TRUE);
	pKDJStockMonitor->Init();*/
	
	
	
	CKDJStockMonitor *pKDJStockMonitor;

	Vec_CString vecStockCodeList=StockDataMgr()->GetStockCodeStringList();

	Vec_CString vecSubStockCodeList;

	int mThreadNums=vecStockCodeList.size()/150+1;

	for(int n=0;n<mThreadNums;n++)
	{
		vecSubStockCodeList.clear();
		int mBegin=n*150;
		int mEnd=(n+1)*150-1;
		if(mEnd>(vecStockCodeList.size()-1))
			mEnd=vecStockCodeList.size()-1;
		for(int i=mBegin;i<=mEnd;i++)
		{
			vecSubStockCodeList.push_back(vecStockCodeList[i]);
		}


		if(vecSubStockCodeList.size()>0)
		{
			pKDJStockMonitor=new CKDJStockMonitor(vecSubStockCodeList);
			pKDJStockMonitor->SetDlgMonitorCallBack(this);
			pKDJStockMonitor->SetLoopBackMode(TRUE);
			pKDJStockMonitor->Init();
			vecKDJStockMonitor.push_back(pKDJStockMonitor);
		}

	}
	
	



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgSniperLoopBack::OnTimer(UINT_PTR nIDEvent)
{
	
	if(KDJMONITOR_TIMER_EVENT_REFRESH==nIDEvent)
	{
		MonitorLogInfo *pMonitorLogInfo=NULL;
		pMonitorLogInfo=PopMonitorLogInfo();
		if(pMonitorLogInfo)
		{
			mListInfo.AddString(pMonitorLogInfo->strLogInfo);

			SAFE_DELETE(pMonitorLogInfo);
			//mListInfo.SendMessage(WM_VSCROLL, SB_BOTTOM, NULL);

			for(int i=0;i<500;i++)
			{
				pMonitorLogInfo=PopMonitorLogInfo();
				if(!pMonitorLogInfo)
					break;
				mListInfo.AddString(pMonitorLogInfo->strLogInfo);
				SAFE_DELETE(pMonitorLogInfo);
			}
			mListInfo.SendMessage(WM_VSCROLL, SB_BOTTOM, NULL);

		}

		MonitorResultInfo *pMonitorResultInfo=NULL;
		pMonitorResultInfo=PopMonitorResultInfo();
		if(pMonitorResultInfo)
		{
			mListResult.AddString(pMonitorResultInfo->strCaptureInfo);
			SAFE_DELETE(pMonitorResultInfo);
			mListResult.SendMessage(WM_VSCROLL, SB_BOTTOM, NULL);
		}
	}

	CDlgMonitorCallBack::OnTimer(nIDEvent);
}

//开始
void CDlgSniperLoopBack::OnBnClickedBtnBegin()
{

	int iItem = mCmbSniperType.GetCurSel();
	if(iItem<0) return ;
	int mSniperType=mCmbSniperType.GetItemData(iItem);


	CTime mLoopBackTime;
	mLoopBackDateTimeCtrl.GetTime(mLoopBackTime);
	CString strLoopBackDate=ConverCTimeToString(mLoopBackTime);

	CString strLoopBackDateTime;

	strLoopBackDateTime=strLoopBackDate;
	strLoopBackDateTime+=" 0935";
	StockLoopBackDataMgr()->SetLoopBackDayDate(strLoopBackDate);
	StockLoopBackDataMgr()->SetLoopBackMin5DateTime(strLoopBackDateTime);
	StockLoopBackDataMgr()->BuildtLoopBackDayData();
	StockLoopBackDataMgr()->BuildtLoopBackMin5Data();

	/*
	pKDJStockMonitor->SetStockSniperType(mSniperType);

	if(!pKDJStockMonitor->GetMonitorRun())
	{
		pKDJStockMonitor->beginMonitor();
		SetTimer(KDJMONITOR_TIMER_EVENT_REFRESH,10,0);
		GetDlgItem(IDC_BTN_BEGIN)->SetWindowText("停止");
	}
	else
	{
		GetDlgItem(IDC_BTN_BEGIN)->SetWindowText("开始");
		pKDJStockMonitor->SetMonitorRun(FALSE);
		KillTimer(KDJMONITOR_TIMER_EVENT_REFRESH);

	}
	*/
	
	
	CKDJStockMonitor *pKDJStockMonitor;
	for(int i=0;i<vecKDJStockMonitor.size();i++)
	{
		pKDJStockMonitor=vecKDJStockMonitor[i];

		if(pKDJStockMonitor)
		{
			pKDJStockMonitor->SetStockSniperType(mSniperType);
			if(!pKDJStockMonitor->GetMonitorRun())
			{
				pKDJStockMonitor->beginMonitor();
				SetTimer(KDJMONITOR_TIMER_EVENT_REFRESH,10,0);
				GetDlgItem(IDC_BTN_BEGIN)->SetWindowText("停止");
			}
			else
			{
				GetDlgItem(IDC_BTN_BEGIN)->SetWindowText("开始");
				pKDJStockMonitor->SetMonitorRun(FALSE);
				//KillTimer(KDJMONITOR_TIMER_EVENT_REFRESH);
			}
		}


	}

	
}
