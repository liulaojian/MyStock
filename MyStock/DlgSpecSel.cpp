// DlgSpecSel.cpp: 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgSpecSel.h"
#include "afxdialogex.h"


// CDlgSpecSel 对话框

IMPLEMENT_DYNAMIC(CDlgSpecSel, CDialogEx)

CDlgSpecSel::CDlgSpecSel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_SPEC_SEL, pParent)
{

}

CDlgSpecSel::~CDlgSpecSel()
{
}

void CDlgSpecSel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SF_SEL, mCmbSfSel);
}


BEGIN_MESSAGE_MAP(CDlgSpecSel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSpecSel::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgSpecSel::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgSpecSel 消息处理程序


BOOL CDlgSpecSel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mSFSel = 0;
	mCmbSfSel.ResetContent();
	int ret;


	ret = mCmbSfSel.AddString("均线上穿");
	mCmbSfSel.SetItemData(ret, 0);


	ret = mCmbSfSel.AddString("DMI上穿");
	mCmbSfSel.SetItemData(ret, 1);


	ret = mCmbSfSel.AddString("PSY Low");
	mCmbSfSel.SetItemData(ret, 2);

	mCmbSfSel.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgSpecSel::OnBnClickedOk()
{
	int	iItem = mCmbSfSel.GetCurSel();
	if (iItem < 0) return;

	mSFSel = mCmbSfSel.GetItemData(iItem);
	CDialogEx::OnOK();
}


void CDlgSpecSel::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
