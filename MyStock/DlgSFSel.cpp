// DlgSFSel.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgSFSel.h"
#include "afxdialogex.h"


// CDlgSFSel 对话框

IMPLEMENT_DYNAMIC(CDlgSFSel, CDialogEx)

CDlgSFSel::CDlgSFSel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSFSel::IDD, pParent)
{

}

CDlgSFSel::~CDlgSFSel()
{
}

void CDlgSFSel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SF_SEL, mCmbSFSel);
}


BEGIN_MESSAGE_MAP(CDlgSFSel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSFSel::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSFSel 消息处理程序


BOOL CDlgSFSel::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	mSFSel=0;
	mCmbSFSel.ResetContent();
	int ret;
	

	ret=mCmbSFSel.AddString("K线分析-1");
	mCmbSFSel.SetItemData(ret,0);
	
	//ret=mCmbSFSel.AddString("掉量不掉价");
	//mCmbSFSel.SetItemData(ret,1);

	ret=mCmbSFSel.AddString("均线TAN角度");
	mCmbSFSel.SetItemData(ret,2);


	ret=mCmbSFSel.AddString("TAN配套(发展均衡)");
	mCmbSFSel.SetItemData(ret,3);
	

	//ret=mCmbSFSel.AddString("多日均线TAN");
	//mCmbSFSel.SetItemData(ret,4);

	//ret=mCmbSFSel.AddString("TAN配套2(冲击均衡)");
	//mCmbSFSel.SetItemData(ret,5);

	//ret=mCmbSFSel.AddString("RSI过滤");
	//mCmbSFSel.SetItemData(ret,6);


	//ret=mCmbSFSel.AddString("单日均线TAN");
	//mCmbSFSel.SetItemData(ret,7);


	//ret=mCmbSFSel.AddString("长量均增长");
	//mCmbSFSel.SetItemData(ret,8);


	ret=mCmbSFSel.AddString("TAN配套3(走势M20中间)");
	mCmbSFSel.SetItemData(ret,9);

	ret=mCmbSFSel.AddString("TAN配套4(启动均衡)");
	mCmbSFSel.SetItemData(ret,10);

	ret=mCmbSFSel.AddString("TAN配套5(<10)"); //TAN配套5  //(角度均衡)
	mCmbSFSel.SetItemData(ret,11);

	ret=mCmbSFSel.AddString("TAN配套6(选步长5)");
	mCmbSFSel.SetItemData(ret,12);

	//ret=mCmbSFSel.AddString("K线分析-配套");
	//mCmbSFSel.SetItemData(ret,13);

	ret=mCmbSFSel.AddString("TAN配套7(增长相同)");
	mCmbSFSel.SetItemData(ret,13);

	//ret=mCmbSFSel.AddString("TAN配套8");
	//mCmbSFSel.SetItemData(ret,14);

	ret = mCmbSFSel.AddString("TAN配套9(长间隔)");
	mCmbSFSel.SetItemData(ret, 15);

	ret = mCmbSFSel.AddString("TAN配套10(行业选择)");
	mCmbSFSel.SetItemData(ret, 16);

#if 0
	ret=mCmbSFSel.AddString("ThreeLow");
	mCmbSFSel.SetItemData(ret,15);

	ret=mCmbSFSel.AddString("一条线");
	mCmbSFSel.SetItemData(ret,16);
#endif	


	mCmbSFSel.SetCurSel(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgSFSel::OnBnClickedOk()
{
	
	int	iItem = mCmbSFSel.GetCurSel();
	if(iItem<0) return ;
	
	mSFSel=mCmbSFSel.GetItemData(iItem);
	
	CDialogEx::OnOK();
}
