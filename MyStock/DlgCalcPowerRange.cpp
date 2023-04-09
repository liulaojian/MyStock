// DlgCalcPowerRange.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgCalcPowerRange.h"
#include "afxdialogex.h"


// CDlgCalcPowerRange �Ի���

IMPLEMENT_DYNAMIC(CDlgCalcPowerRange, CDialogEx)

CDlgCalcPowerRange::CDlgCalcPowerRange(CString strCode,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCalcPowerRange::IDD, pParent)
{
	strStockCode=strCode;
	pStockDayTable=NULL;
}

CDlgCalcPowerRange::~CDlgCalcPowerRange()
{
}

void CDlgCalcPowerRange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_HIGH, mHighDateCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER_LOW, mLowDateCtrl);
}


BEGIN_MESSAGE_MAP(CDlgCalcPowerRange, CDialogEx)
END_MESSAGE_MAP()


// CDlgCalcPowerRange ��Ϣ�������


BOOL CDlgCalcPowerRange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
