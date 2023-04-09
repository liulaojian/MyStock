// DlgStockDateSel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgStockDateSel.h"
#include "afxdialogex.h"


// CDlgStockDateSel �Ի���

IMPLEMENT_DYNAMIC(CDlgStockDateSel, CDialogEx)

CDlgStockDateSel::CDlgStockDateSel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgStockDateSel::IDD, pParent)
{

}

CDlgStockDateSel::~CDlgStockDateSel()
{
}

void CDlgStockDateSel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN, mDateTimeBegin);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, mDateTimeEnd);
}


BEGIN_MESSAGE_MAP(CDlgStockDateSel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgStockDateSel::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgStockDateSel ��Ϣ�������


BOOL CDlgStockDateSel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mDateTimeBegin.SetTime(&mBeginTime);
	mDateTimeEnd.SetTime(&mEndTime);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgStockDateSel::OnBnClickedOk()
{
	mDateTimeBegin.GetTime(mBeginTime);
	mDateTimeEnd.GetTime(mEndTime);

	CTimeSpan span=mEndTime-mBeginTime;

	int iDay=span.GetDays();
	if(iDay<=0)
	{
		AfxMessageBox("��ʼʱ����ڵ��ڽ���ʱ��");
		return;
	}


	CDialogEx::OnOK();
}
