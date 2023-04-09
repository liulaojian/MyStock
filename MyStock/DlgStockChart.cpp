// DlgStockChart.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgStockChart.h"
#include "afxdialogex.h"


// CDlgStockChart 对话框

IMPLEMENT_DYNAMIC(CDlgStockChart, CDialogEx)

CDlgStockChart::CDlgStockChart(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgStockChart::IDD, pParent),pStockChartStatic(NULL)
{

}

CDlgStockChart::~CDlgStockChart()
{
}

void CDlgStockChart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgStockChart, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_SAVE_BMP, &CDlgStockChart::OnMenuSaveBmp)
END_MESSAGE_MAP()


// CDlgStockChart 消息处理程序


BOOL CDlgStockChart::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rcWnd;  
	//GetWindowRect(&rcWnd);  
	//ScreenToClient(&rcWnd);  
	GetClientRect (&rcWnd);
	int l,t,r,b;
	l=0;
	t=0;
	//r=((rcWnd.right-rcWnd.left)*7)/8;
	//b=((rcWnd.bottom-rcWnd.top)*4)/5;
	r=(rcWnd.right-rcWnd.left);
	b=(rcWnd.bottom-rcWnd.top);

	pStockChartStatic=new CStockChartStatic();
	
	pStockChartStatic->Create("CSTATIC",WS_CHILD|WS_VISIBLE|SS_GRAYFRAME|SS_CENTER|SS_NOTIFY,CRect(l,t,r,b),this,IDC_STATIC_STOCK_CHART);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CDlgStockChart::Init(void)
{
	if(pStockChartStatic)
		pStockChartStatic->Init();
	return TRUE;
}

CStockDayTable * CDlgStockChart::GetStockDayTable(void)
{
	if(pStockChartStatic==NULL)
		return NULL;

	return pStockChartStatic->GetStockDayTable();
}

void CDlgStockChart::SetStockDayTable(CStockDayTable *pTable)
{
	if(pStockChartStatic==NULL)
		return ;
	pStockChartStatic->SetStockDayTable(pTable);
}

void CDlgStockChart::SetBeginDate(CString strVal)
{
	if(pStockChartStatic==NULL)
		return ;
	pStockChartStatic->SetBeginDate(strVal);
}


void CDlgStockChart::SetEndDate(CString strVal)
{
	if(pStockChartStatic==NULL)
		return ;
	pStockChartStatic->SetEndDate(strVal);
}

void CDlgStockChart::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DestroyWindow();//窗口的销毁
	CDialogEx::OnClose();
}


void CDlgStockChart::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::PostNcDestroy();
}


void CDlgStockChart::OnRButtonDown(UINT nFlags, CPoint point)
{
	
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CDlgStockChart::OnMenuSaveBmp()
{
	
}
