// DlgStockMonitor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgStockMonitor.h"
#include "afxdialogex.h"
#include "StockDataMgr.h"
#include "StockPowerArithmetic.h"
// DlgStockMonitor �Ի���

IMPLEMENT_DYNAMIC(DlgStockMonitor, CDlgMonitorCallBack)

DlgStockMonitor::DlgStockMonitor(CWnd* pParent /*=NULL*/)
	: CDlgMonitorCallBack(DlgStockMonitor::IDD, pParent)
{

}

DlgStockMonitor::~DlgStockMonitor()
{
}

void DlgStockMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDlgMonitorCallBack::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STOCK, mStockListCtrl);
}


BEGIN_MESSAGE_MAP(DlgStockMonitor, CDlgMonitorCallBack)
	ON_WM_TIMER()
	ON_NOTIFY(NM_RCLICK, IDC_LIST_STOCK, &DlgStockMonitor::OnRclickListStock)
	ON_UPDATE_COMMAND_UI(ID_MENU_STOCK_CHART, &DlgStockMonitor::OnUpdateMenuStockChart)
	ON_COMMAND(ID_MENU_DFCF_WEB_OPEN, &DlgStockMonitor::OnMenuDfcfWebOpen)
END_MESSAGE_MAP()


// DlgStockMonitor ��Ϣ�������


BOOL DlgStockMonitor::OnInitDialog()
{
	CDlgMonitorCallBack::OnInitDialog();

	mStockListCtrl.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT ); //���ñ�����

	mStockListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES); 

	mStockListCtrl.InsertColumn( MONITOR_COLUMN_ID, "˳��ID��", LVCFMT_LEFT, 80 );

	mStockListCtrl.InsertColumn( MONITOR_COLUMN_STOCK_CODE, "��Ʊ����", LVCFMT_LEFT, 115 );

	mStockListCtrl.InsertColumn( MONITOR_COLUMN_STOCK_NAME, "��Ʊ����", LVCFMT_LEFT, 115 );

	mStockListCtrl.InsertColumn( MONITOR_COLUMN_STOCK_MIN5_ENDPRICE, "5�������۸�", LVCFMT_LEFT, 140 );
	mStockListCtrl.InsertColumn( MONITOR_COLUMN_STOCK_MIN5_LASTTIME, "5�������ʱ��", LVCFMT_LEFT, 140 );

	mStockListCtrl.InsertColumn( MONITOR_COLUMN_MONITOR_LASTTIMER, "������ִ��ʱ��", LVCFMT_LEFT, 140);
	mStockListCtrl.InsertColumn( MONITOR_COLUMN_MONITOR_CAPTURED, "��ز���", LVCFMT_LEFT, 140 );
	mStockListCtrl.InsertColumn( MONITOR_COLUMN_MONITOR_INFO, "�����Ϣ", LVCFMT_LEFT, 140 );

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL DlgStockMonitor::Init(void)
{
	vecMonitorResultInfo.clear();

	MonitorResultInfo *pMonitorResultInfo=NULL;

	for(int i=0;i<vecStockCodeList.size();i++)
	{
		pMonitorResultInfo=new MonitorResultInfo();
		pMonitorResultInfo->strStockCode=vecStockCodeList[i];
		pMonitorResultInfo->strLastStockMin5EndPrice="";
		pMonitorResultInfo->strLastStockMin5DateTime="";
		pMonitorResultInfo->strLastMonitorTime="";
		pMonitorResultInfo->strCaptureInfo="";
		pMonitorResultInfo->strMonitorInfo="���δ����";
		vecMonitorResultInfo.push_back(pMonitorResultInfo);
	}
	SetTimer(MONITOR_TIMER_EVENT_REFRESH,200,0);
	CString strTitle;
	strTitle.Format("��Ʊ���  ���۸������%d������������ͼ۸� %.2f   --   %.2f �� ",mDayNums,f_down_percent,f_up_percent);
	SetWindowText(strTitle);
	return TRUE;
}

bool DlgStockMonitor::RefreshData(void)
{
	CString strConv,strTemp;
	int nRow;
	int i=0;
	
	for(i=0;i<vecMonitorResultInfo.size();i++)
	{
		strConv.Format("%4d",i+1);
		nRow=i;
		if(nRow>=mStockListCtrl.GetItemCount())
			mStockListCtrl.InsertItem(i,strConv);
		else
			mStockListCtrl.SetItemText(nRow, MONITOR_COLUMN_ID,strConv);

		mStockListCtrl.SetItemText(nRow, MONITOR_COLUMN_STOCK_CODE,vecMonitorResultInfo[i]->strStockCode);

		CString strStockName=StockDataMgr()->GetStockName(vecMonitorResultInfo[i]->strStockCode);

		mStockListCtrl.SetItemText(nRow, MONITOR_COLUMN_STOCK_NAME,strStockName);

		mStockListCtrl.SetItemText(nRow, MONITOR_COLUMN_STOCK_MIN5_ENDPRICE,vecMonitorResultInfo[i]->strLastStockMin5EndPrice);

		mStockListCtrl.SetItemText(nRow, MONITOR_COLUMN_STOCK_MIN5_LASTTIME,vecMonitorResultInfo[i]->strLastStockMin5DateTime);

		mStockListCtrl.SetItemText(nRow, MONITOR_COLUMN_MONITOR_LASTTIMER,vecMonitorResultInfo[i]->strLastMonitorTime);

		mStockListCtrl.SetItemText(nRow, MONITOR_COLUMN_MONITOR_CAPTURED,vecMonitorResultInfo[i]->strCaptureInfo);

		mStockListCtrl.SetItemText(nRow, MONITOR_COLUMN_MONITOR_INFO,vecMonitorResultInfo[i]->strMonitorInfo);

		mStockListCtrl.SetItemData(nRow,reinterpret_cast<DWORD>(vecMonitorResultInfo[i]));
	}

	if(i<mStockListCtrl.GetItemCount())
	{
		for(int j=i;j<mStockListCtrl.GetItemCount();j++)
			mStockListCtrl.DeleteItem(j);
	}

	return true;
}

void DlgStockMonitor::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(MONITOR_TIMER_EVENT_REFRESH==nIDEvent)
	{
		RefreshData();
		KillTimer(MONITOR_TIMER_EVENT_REFRESH);
	}
	CDlgMonitorCallBack::OnTimer(nIDEvent);
}


void DlgStockMonitor::OnRclickListStock(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if(pNMItemActivate->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU_MONITOR ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );

	}
	*pResult = 0;
}

//�����Ƹ���ҳ��
void DlgStockMonitor::OnUpdateMenuStockChart(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void DlgStockMonitor::OnMenuDfcfWebOpen()
{
	MonitorResultInfo *pMonitorResultInfo=NULL;
	for(int  i=0; i<mStockListCtrl.GetItemCount(); i++)
	{
		if( mStockListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			pMonitorResultInfo=reinterpret_cast<MonitorResultInfo *>(mStockListCtrl.GetItemData(i));

			break;
		}
	}

	if(pMonitorResultInfo==NULL)
		return;

	CString strStockCode=pMonitorResultInfo->strStockCode;
	/*CStockPowerArithmetic mStockPowerArithmetic(strStockCode);
	StockPowerArithmeticInfo* pStockPowerArithmeticInfo=NULL;
	if(mStockPowerArithmetic.Init())
	{
		pStockPowerArithmeticInfo=mStockPowerArithmetic.CalcLastStockPowerArithmeticInfo(120);
	}*/
	
	CString strWebUrl;
	strWebUrl.Format("http://quote.eastmoney.com/%s.html",strStockCode);
	ShellExecute(NULL,"open",strWebUrl,NULL,NULL,SW_SHOWNORMAL);
	
}
