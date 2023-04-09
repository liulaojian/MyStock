// DlgHistoryCmpResult.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgHistoryCmpResult.h"
#include "afxdialogex.h"
#include "StockDataMgr.h"
#include "DlgStockChart.h"

// CDlgHistoryCmpResult 对话框

IMPLEMENT_DYNAMIC(CDlgHistoryCmpResult, CDialogEx)

CDlgHistoryCmpResult::CDlgHistoryCmpResult(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgHistoryCmpResult::IDD, pParent),pStockDayTable(NULL),strTitle("")
{

}

CDlgHistoryCmpResult::~CDlgHistoryCmpResult()
{
}

void CDlgHistoryCmpResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RESULT, mResultListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgHistoryCmpResult, CDialogEx)
	ON_WM_TIMER()
	ON_NOTIFY(NM_RCLICK, IDC_LIST_RESULT, &CDlgHistoryCmpResult::OnRclickListResult)
	ON_UPDATE_COMMAND_UI(ID_MENU_STOCK_CHART, &CDlgHistoryCmpResult::OnUpdateMenuStockChart)
	ON_COMMAND(ID_MENU_STOCK_CHART, &CDlgHistoryCmpResult::OnMenuStockChart)
END_MESSAGE_MAP()


// CDlgHistoryCmpResult 消息处理程序


BOOL CDlgHistoryCmpResult::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mResultListCtrl.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT ); //设置报表风格


	mResultListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 
	mResultListCtrl.InsertColumn( RESULT_COLUMN_ID, "顺序ID号", LVCFMT_LEFT, 80 );
	mResultListCtrl.InsertColumn( RESULT_COLUMN_STOCK_CODE, "股票代码", LVCFMT_LEFT, 115 );

	mResultListCtrl.InsertColumn( RESULT_COLUMN_STOCK_NAME, "股票名称", LVCFMT_LEFT, 115 );
	mResultListCtrl.InsertColumn( RESULT_COLUMN_STOCK_DAY_BEGIN, "日数据开始", LVCFMT_LEFT, 140 );
	mResultListCtrl.InsertColumn( RESULT_COLUMN_STOCK_DAY_END, "日数据结束", LVCFMT_LEFT, 140 );

	
	SetTimer(RESULT_TIMER_EVENT_REFRESH,200,0);

	if(strTitle!="")
	{
		SetWindowText(strTitle);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgHistoryCmpResult::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==RESULT_TIMER_EVENT_REFRESH)
	{
		RefreshData();
		KillTimer(RESULT_TIMER_EVENT_REFRESH);
	}
	CDialogEx::OnTimer(nIDEvent);
}



bool CDlgHistoryCmpResult::RefreshData(void)
{
	CString strConv,strTemp;
	int nRow;
	int i=0;
	for(i=0;i<vecHistoryResultList.size();i++)
	{
		strConv.Format("%4d",i+1);
		nRow=i;
		if(nRow>=mResultListCtrl.GetItemCount())
			mResultListCtrl.InsertItem(i,strConv);
		else
			mResultListCtrl.SetItemText(nRow, RESULT_COLUMN_ID,strConv);
		mResultListCtrl.SetItemText(nRow, RESULT_COLUMN_STOCK_CODE,pStockDayTable->GetStockCode());
		mResultListCtrl.SetItemText(nRow, RESULT_COLUMN_STOCK_NAME,StockDataMgr()->GetStockName(pStockDayTable->GetStockCode()));

		mResultListCtrl.SetItemText(nRow, RESULT_COLUMN_STOCK_DAY_BEGIN,vecHistoryResultList[i]->strBeginDate);
		mResultListCtrl.SetItemText(nRow, RESULT_COLUMN_STOCK_DAY_END,vecHistoryResultList[i]->strEndDate);

		mResultListCtrl.SetItemData(nRow,reinterpret_cast<DWORD_PTR>(vecHistoryResultList[i]));
	}
	
	return true;
}

void CDlgHistoryCmpResult::OnRclickListResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if(pNMItemActivate->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU_CHART ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );

	}

	*pResult = 0;
}

//在股票图列表中打开
void CDlgHistoryCmpResult::OnUpdateMenuStockChart(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}




void CDlgHistoryCmpResult::OnMenuStockChart()
{
	HistoryResult  *pHistoryResult=NULL;
	for(int  i=0; i<mResultListCtrl.GetItemCount(); i++)
	{
		if( mResultListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			pHistoryResult=reinterpret_cast<HistoryResult *>(mResultListCtrl.GetItemData(i));

			break;
		}
	}

	if(pHistoryResult==NULL)
		return;
	CDlgStockChart *pDlgStockChart;
	pDlgStockChart=new CDlgStockChart(this);
	pDlgStockChart->Create(IDD_DLG_STOCK_CHART);
	pDlgStockChart->SetStockDayTable(pStockDayTable);
	pDlgStockChart->SetBeginDate(pHistoryResult->strBeginDate);
	pDlgStockChart->SetEndDate(pHistoryResult->strEndDate);
	pDlgStockChart->Init();
	pDlgStockChart->ShowWindow(SW_SHOWNORMAL);
	pDlgStockChart->CenterWindow(this);
	

}
