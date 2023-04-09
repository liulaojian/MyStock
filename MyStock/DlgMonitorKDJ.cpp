// DlgMonitorKDJ.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgMonitorKDJ.h"
#include "afxdialogex.h"


// CDlgMonitorKDJ 对话框

IMPLEMENT_DYNAMIC(CDlgMonitorKDJ, CDialogEx)

CDlgMonitorKDJ::CDlgMonitorKDJ(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMonitorKDJ::IDD, pParent)
{

}

CDlgMonitorKDJ::~CDlgMonitorKDJ()
{
}

void CDlgMonitorKDJ::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMonitorKDJ, CDialogEx)
END_MESSAGE_MAP()


// CDlgMonitorKDJ 消息处理程序
