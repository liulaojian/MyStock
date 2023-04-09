// DlgStockMonitorKDJ.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgStockMonitorKDJ.h"
#include "afxdialogex.h"
#include "StockDataMgr.h"
#include "CommonMacro.h"
// CDlgStockMonitorKDJ �Ի���

IMPLEMENT_DYNAMIC(CDlgStockMonitorKDJ, CDlgMonitorCallBack)

CDlgStockMonitorKDJ::CDlgStockMonitorKDJ(CWnd* pParent /*=NULL*/)
	: CDlgMonitorCallBack(CDlgStockMonitorKDJ::IDD, pParent)
{

}

CDlgStockMonitorKDJ::~CDlgStockMonitorKDJ()
{
}

void CDlgStockMonitorKDJ::DoDataExchange(CDataExchange* pDX)
{
	CDlgMonitorCallBack::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INFO, mListInfo);
	DDX_Control(pDX, IDC_LIST_RESULT, mListResult);
	DDX_Control(pDX, IDC_COMBO_SNIPER, mCmbSniperType);
}


BEGIN_MESSAGE_MAP(CDlgStockMonitorKDJ, CDlgMonitorCallBack)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_BEGIN, &CDlgStockMonitorKDJ::OnBnClickedBtnBegin)
END_MESSAGE_MAP()


// CDlgStockMonitorKDJ ��Ϣ�������


BOOL CDlgStockMonitorKDJ::OnInitDialog()
{
	CDlgMonitorCallBack::OnInitDialog();

	

	mCmbSniperType.ResetContent();
	int ret=mCmbSniperType.AddString("60����K�� KDJ��10�� CCI���-120");
	mCmbSniperType.SetItemData(ret,STOCK_SNIPER_K60MIN_KDJ_ZERO_CCI_ZERO);

	ret=mCmbSniperType.AddString("60����K�� �ϴ�CCI-100");
	mCmbSniperType.SetItemData(ret,STOCK_SNIPER_K60MIN_CCI_MINUS_50);

	ret=mCmbSniperType.AddString("60����K�� SAR");
	mCmbSniperType.SetItemData(ret,STOCK_SNIPER_K60MIN_SAR);

	mCmbSniperType.SetCurSel(0);

	
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
			pKDJStockMonitor->SetLoopBackMode(FALSE);
			pKDJStockMonitor->Init();
			vecKDJStockMonitor.push_back(pKDJStockMonitor);
		}

	}

	/*
	Vec_CString vecStockCodeList=StockDataMgr()->GetStockCodeStringList();
	pKDJStockMonitor=new CKDJStockMonitor(vecStockCodeList);
	pKDJStockMonitor->SetDlgMonitorCallBack(this);
	pKDJStockMonitor->SetLoopBackMode(FALSE);
	pKDJStockMonitor->Init();*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgStockMonitorKDJ::OnTimer(UINT_PTR nIDEvent)
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

			for(int i=0;i<30;i++)
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


void CDlgStockMonitorKDJ::OnBnClickedBtnBegin()
{

	int iItem = mCmbSniperType.GetCurSel();
	if(iItem<0) return ;
	int mSniperType=mCmbSniperType.GetItemData(iItem);

	

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
				SetTimer(KDJMONITOR_TIMER_EVENT_REFRESH,200,0);
				GetDlgItem(IDC_BTN_BEGIN)->SetWindowText("ֹͣ");
			}
			else
			{
				GetDlgItem(IDC_BTN_BEGIN)->SetWindowText("��ʼ");
				pKDJStockMonitor->SetMonitorRun(FALSE);
			//	KillTimer(KDJMONITOR_TIMER_EVENT_REFRESH);
			}
		}

		
	}
	

	/*
	pKDJStockMonitor->SetStockSniperType(mSniperType);

	if(!pKDJStockMonitor->GetMonitorRun())
	{
		pKDJStockMonitor->beginMonitor();
		SetTimer(KDJMONITOR_TIMER_EVENT_REFRESH,200,0);
		GetDlgItem(IDC_BTN_BEGIN)->SetWindowText("ֹͣ");
	}
	else
	{
		GetDlgItem(IDC_BTN_BEGIN)->SetWindowText("��ʼ");
		pKDJStockMonitor->SetMonitorRun(FALSE);
	//	KillTimer(KDJMONITOR_TIMER_EVENT_REFRESH);

	}*/
	
}

