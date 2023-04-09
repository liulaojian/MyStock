// DlgIndustrySel.cpp: 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgIndustrySel.h"
#include "afxdialogex.h"


// CDlgIndustrySel 对话框

IMPLEMENT_DYNAMIC(CDlgIndustrySel, CDialogEx)

CDlgIndustrySel::CDlgIndustrySel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_INDUSTRY_SEL, pParent)
{

}

CDlgIndustrySel::~CDlgIndustrySel()
{
}

void CDlgIndustrySel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_INDUSTRY, mCmbIndusry);
	DDX_Control(pDX, IDC_CHECK_SEL_REVERSE, mCheckReverse);
}


BEGIN_MESSAGE_MAP(CDlgIndustrySel, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OK, &CDlgIndustrySel::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CDlgIndustrySel::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CDlgIndustrySel 消息处理程序


BOOL CDlgIndustrySel::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	mCmbIndusry.ResetContent();
	int ret;
	Vec_IndustryDataList vecIndustryDataList = IndustryDataMgr()->GetIndustryDataList();
	IndustryData* pIndustryData = NULL;
	for (int i = 0; i < vecIndustryDataList.size(); i++)
	{
		pIndustryData = vecIndustryDataList[i];
		ret = mCmbIndusry.AddString(pIndustryData->strIndustryName.c_str());
		mCmbIndusry.SetItemData(ret, reinterpret_cast<DWORD_PTR>(pIndustryData));
	}
	
	mCmbIndusry.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgIndustrySel::OnBnClickedBtnOk()
{
	int	iItem = mCmbIndusry.GetCurSel();
	if (iItem < 0) return;
	IndustryData* pIndustryData = reinterpret_cast<IndustryData*>(mCmbIndusry.GetItemData(iItem));

	pSelIndustryData = pIndustryData;

	if (mCheckReverse.GetCheck() == BST_CHECKED)
		bReVerseSel = TRUE;

	CDialogEx::OnOK();
}


void CDlgIndustrySel::OnBnClickedBtnCancel()
{
	CDialogEx::OnCancel();
}
