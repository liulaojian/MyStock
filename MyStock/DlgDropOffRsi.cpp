// DlgDropOffRsi.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgDropOffRsi.h"
#include "afxdialogex.h"


// CDlgDropOffRsi 对话框

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


// CDlgDropOffRsi 消息处理程序


BOOL CDlgDropOffRsi::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
