// DlgDropOffRsi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgDropOffRsi.h"
#include "afxdialogex.h"


// CDlgDropOffRsi �Ի���

IMPLEMENT_DYNAMIC(CDlgDropOffRsi, CDialogEx)

CDlgDropOffRsi::CDlgDropOffRsi(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDropOffRsi::IDD, pParent)
{

}

CDlgDropOffRsi::~CDlgDropOffRsi()
{
}

void CDlgDropOffRsi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDropOffRsi, CDialogEx)
END_MESSAGE_MAP()


// CDlgDropOffRsi ��Ϣ�������


BOOL CDlgDropOffRsi::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
