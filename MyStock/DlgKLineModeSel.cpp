// DlgKLineModeSel.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgKLineModeSel.h"
#include "afxdialogex.h"


// CDlgKLineModeSel 对话框

IMPLEMENT_DYNAMIC(CDlgKLineModeSel, CDialogEx)

CDlgKLineModeSel::CDlgKLineModeSel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgKLineModeSel::IDD, pParent)
{

}

CDlgKLineModeSel::~CDlgKLineModeSel()
{
}

void CDlgKLineModeSel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODE, mCmbKLineMode);
}


BEGIN_MESSAGE_MAP(CDlgKLineModeSel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgKLineModeSel::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgKLineModeSel 消息处理程序


BOOL CDlgKLineModeSel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mKLineMode=0;
	mCmbKLineMode.ResetContent();
	int ret=mCmbKLineMode.AddString("光头强突模式");
	mCmbKLineMode.SetItemData(ret,0);
	ret=mCmbKLineMode.AddString("量价均衡模式");
	mCmbKLineMode.SetItemData(ret,1);
	ret=mCmbKLineMode.AddString("三连阳");
	mCmbKLineMode.SetItemData(ret,2);
	ret=mCmbKLineMode.AddString("中阳线");
	mCmbKLineMode.SetItemData(ret,3);

	ret=mCmbKLineMode.AddString("阴阳阳");
	mCmbKLineMode.SetItemData(ret,4);

	mCmbKLineMode.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgKLineModeSel::OnBnClickedOk()
{
	int	iItem = mCmbKLineMode.GetCurSel();
	if(iItem<0) return ;

	mKLineMode=mCmbKLineMode.GetItemData(iItem);
	CDialogEx::OnOK();
}
