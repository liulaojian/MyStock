// DlgSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgSetting.h"
#include "afxdialogex.h"
#include "SystemMgr.h"
#include "Util.h"

// CDlgSetting 对话框

IMPLEMENT_DYNAMIC(CDlgSetting, CDialogEx)

CDlgSetting::CDlgSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSetting::IDD, pParent)
{

}

CDlgSetting::~CDlgSetting()
{
}

void CDlgSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STOCKXML_FILE, mEditXmlFile);
	DDX_Control(pDX, IDC_EDIT_TDX_DIR, mEditTdxDir);
}


BEGIN_MESSAGE_MAP(CDlgSetting, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CDlgSetting::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDOK, &CDlgSetting::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_OPEN_TDX, &CDlgSetting::OnBnClickedBtnOpenTdx)
END_MESSAGE_MAP()


// CDlgSetting 消息处理程序



BOOL CDlgSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strXmlFile=SystemMgr()->GetMyStockXmlFile();
	mEditXmlFile.SetWindowText(strXmlFile);

	CString strTdxDir = SystemMgr()->GetTDXDir();
	mEditTdxDir.SetWindowText(strTdxDir);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



//open
void CDlgSetting::OnBnClickedBtnOpen()
{
	CFileDialog dlg(TRUE,".xml",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"xml(*.xml)|*.xml||");

	if(dlg.DoModal()==IDOK)   
	{
		CString strXmlFilePath=dlg.GetPathName();

		SystemMgr()->SetMyStockXmlFile(strXmlFilePath);
		mEditXmlFile.SetWindowText(strXmlFilePath);
	}
}


void CDlgSetting::OnBnClickedBtnOpenTdx()
{
	CString strPath;
	if (BrowseDir(strPath, GetSafeHwnd(), "请选择通达信安装目录"))
	{
		SystemMgr()->SetTDXDir(strPath);
		mEditTdxDir.SetWindowText(strPath);
	}
}



void CDlgSetting::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


