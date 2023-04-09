// DlgStockPriceFilter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgStockPriceFilter.h"
#include "afxdialogex.h"


// CDlgStockPriceFilter �Ի���

IMPLEMENT_DYNAMIC(CDlgStockPriceFilter, CDialogEx)

CDlgStockPriceFilter::CDlgStockPriceFilter(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgStockPriceFilter::IDD, pParent)
{

}

CDlgStockPriceFilter::~CDlgStockPriceFilter()
{
}

void CDlgStockPriceFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DAYNUMS, mCmbDayNums);
	DDX_Control(pDX, IDC_COMBO_UP_PERCENT, mCmbUpPercent);
	DDX_Control(pDX, IDC_COMBO_DOWN_PERCENT, mCmbDownPercent);
}


BEGIN_MESSAGE_MAP(CDlgStockPriceFilter, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CDlgStockPriceFilter::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgStockPriceFilter ��Ϣ�������


BOOL CDlgStockPriceFilter::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mCmbDayNums.ResetContent();
	int ret=mCmbDayNums.AddString("ǰ30��������");
	mCmbDayNums.SetItemData(ret,30);

	ret=mCmbDayNums.AddString("ǰ45��������");
	mCmbDayNums.SetItemData(ret,45);

	ret=mCmbDayNums.AddString("ǰ60��������");
	mCmbDayNums.SetItemData(ret,60);

	ret=mCmbDayNums.AddString("ǰ75��������");
	mCmbDayNums.SetItemData(ret,75);

	ret=mCmbDayNums.AddString("ǰ90��������");
	mCmbDayNums.SetItemData(ret,90);

	ret=mCmbDayNums.AddString("ǰ105��������");
	mCmbDayNums.SetItemData(ret,105);

	ret=mCmbDayNums.AddString("ǰ120��������");
	mCmbDayNums.SetItemData(ret,120);
	mCmbDayNums.SetCurSel(2);

	mCmbUpPercent.ResetContent();
	

	ret=mCmbUpPercent.AddString("0%");
	mCmbUpPercent.SetItemData(ret,0);

	ret=mCmbUpPercent.AddString("-1%");
	mCmbUpPercent.SetItemData(ret,-1);

	ret=mCmbUpPercent.AddString("-2%");
	mCmbUpPercent.SetItemData(ret,-2);

	ret=mCmbUpPercent.AddString("-3%");
	mCmbUpPercent.SetItemData(ret,-3);


	mCmbUpPercent.SetCurSel(1);


//--------------------------------------------
	mCmbDownPercent.ResetContent();
	
	ret=mCmbDownPercent.AddString("-2%");
	mCmbDownPercent.SetItemData(ret,-2);

	ret=mCmbDownPercent.AddString("-3%");
	mCmbDownPercent.SetItemData(ret,-3);

	ret=mCmbDownPercent.AddString("-4%");
	mCmbDownPercent.SetItemData(ret,-4);

	ret=mCmbDownPercent.AddString("-5%");
	mCmbDownPercent.SetItemData(ret,-5);

	ret=mCmbDownPercent.AddString("-6%");
	mCmbDownPercent.SetItemData(ret,-6);


	mCmbDownPercent.SetCurSel(2);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgStockPriceFilter::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnTimer(nIDEvent);
}


void CDlgStockPriceFilter::OnBnClickedOk()
{
	int iItem = mCmbDayNums.GetCurSel();
	if(iItem<0) return ;
	mDayNums=mCmbDayNums.GetItemData(iItem);

	iItem = mCmbUpPercent.GetCurSel();
	if(iItem<0) return ;
	int t=mCmbUpPercent.GetItemData(iItem);
	f_up_percent=(float)t;

	iItem = mCmbDownPercent.GetCurSel();
	if(iItem<0) return ;
	t=mCmbDownPercent.GetItemData(iItem);
	f_down_percent=(float)t;
	if(f_up_percent<=f_down_percent)
	{
		AfxMessageBox("���䲻��");
		return;
	}

	CDialogEx::OnOK();
}
