// DlgVPSFSel.cpp: 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgVPSFSel.h"
#include "afxdialogex.h"


// CDlgVPSFSel 对话框

IMPLEMENT_DYNAMIC(CDlgVPSFSel, CDialogEx)

CDlgVPSFSel::CDlgVPSFSel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_VPSF_SEL, pParent)
{

}

CDlgVPSFSel::~CDlgVPSFSel()
{
}

void CDlgVPSFSel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SF_SEL, mCmbSFSel);
}


BEGIN_MESSAGE_MAP(CDlgVPSFSel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgVPSFSel::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgVPSFSel::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgVPSFSel 消息处理程序


BOOL CDlgVPSFSel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mSFSel = 0;
	mCmbSFSel.ResetContent();
	int ret;


	ret = mCmbSFSel.AddString("MFI RSI相等");
	mCmbSFSel.SetItemData(ret, 0);

	ret = mCmbSFSel.AddString("极限下降");
	mCmbSFSel.SetItemData(ret, 1);


	ret = mCmbSFSel.AddString("MFI相等");
	mCmbSFSel.SetItemData(ret, 2);

	//ret = mCmbSFSel.AddString("MFI低值设置");
	//mCmbSFSel.SetItemData(ret, 3);

	ret = mCmbSFSel.AddString("CR 相等");
	mCmbSFSel.SetItemData(ret, 4);


	ret = mCmbSFSel.AddString("VR 相等");
	mCmbSFSel.SetItemData(ret, 5);


	ret = mCmbSFSel.AddString("RSI PTY过滤");
	mCmbSFSel.SetItemData(ret, 6);


	//ret = mCmbSFSel.AddString("卡Ma5上");
	//mCmbSFSel.SetItemData(ret, 7);

	ret = mCmbSFSel.AddString("Sar Ma5过滤");
	mCmbSFSel.SetItemData(ret, 8);

	

	mCmbSFSel.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgVPSFSel::OnBnClickedOk()
{
	int	iItem = mCmbSFSel.GetCurSel();
	if (iItem < 0) return;

	mSFSel = mCmbSFSel.GetItemData(iItem);

	CDialogEx::OnOK();
}


void CDlgVPSFSel::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
