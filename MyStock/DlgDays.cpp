// DlgDays.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgDays.h"
#include "afxdialogex.h"


// CDlgDays �Ի���

IMPLEMENT_DYNAMIC(CDlgDays, CDialogEx)

CDlgDays::CDlgDays(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDays::IDD, pParent)
{

}

CDlgDays::~CDlgDays()
{
}

void CDlgDays::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DAYS, mEditDays);
	DDX_Control(pDX, IDC_SPIN_DAYS, mSpinDays);
}


BEGIN_MESSAGE_MAP(CDlgDays, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgDays::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgDays ��Ϣ�������


BOOL CDlgDays::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mDayNums=8;
	mSpinDays.SetBuddy(&mEditDays);
	mSpinDays.SetRange(3, 40);
	mSpinDays.SetPos(mDayNums);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgDays::OnBnClickedOk()
{
	CString strVal;
	int temp;
	mEditDays.GetWindowText(strVal);
	temp=atoi(strVal);
	mDayNums=temp;

	CDialogEx::OnOK();
}
