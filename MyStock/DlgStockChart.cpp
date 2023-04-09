// DlgStockChart.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgStockChart.h"
#include "afxdialogex.h"


// CDlgStockChart �Ի���

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


// CDlgStockChart ��Ϣ�������


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
	// �쳣: OCX ����ҳӦ���� FALSE
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DestroyWindow();//���ڵ�����
	CDialogEx::OnClose();
}


void CDlgStockChart::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::PostNcDestroy();
}


void CDlgStockChart::OnRButtonDown(UINT nFlags, CPoint point)
{
	
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CDlgStockChart::OnMenuSaveBmp()
{
	
}
