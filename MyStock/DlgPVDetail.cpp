// DlgPVDetail.cpp: 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgPVDetail.h"
#include "afxdialogex.h"


// CDlgPVDetail 对话框

IMPLEMENT_DYNAMIC(CDlgPVDetail, CDialogEx)

CDlgPVDetail::CDlgPVDetail(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIG_PV_DETARL, pParent)
{

}

CDlgPVDetail::~CDlgPVDetail()
{
}

void CDlgPVDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mListDetail);
}


BEGIN_MESSAGE_MAP(CDlgPVDetail, CDialogEx)
END_MESSAGE_MAP()


// CDlgPVDetail 消息处理程序


BOOL CDlgPVDetail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strTitle = "量价详细 ";

	strTitle += mRSIData.strStockCode;
	strTitle += "  ";
	strTitle += mRSIData.strStockName;
	SetWindowText(strTitle);

	CString strInfo;
	float cr = mRSIData.cr;
	strInfo.Format("当前CR值 %.2f", cr);
	mListDetail.AddString(strInfo);

	float f_min_cr = mRSIData.f_min_cr;
	strInfo.Format("最小CR值 %.2f", f_min_cr);
	mListDetail.AddString(strInfo);

	strInfo.Format("最小CR值距今 %d 日", mRSIData.m_min_cr_day);
	mListDetail.AddString(strInfo);

	strInfo.Format("最大CR值 %.2f", mRSIData.f_max_cr);
	mListDetail.AddString(strInfo);

	strInfo.Format("最大CR值距今 %d 日", mRSIData.m_max_cr_day);
	mListDetail.AddString(strInfo);


	mListDetail.AddString("    ");
	mListDetail.AddString("    ");


	strInfo.Format("当前MFI值 %.2f", mRSIData.mfi);
	mListDetail.AddString(strInfo);


	strInfo.Format("最小MFI值 %.2f", mRSIData.f_min_mfi);
	mListDetail.AddString(strInfo);
	strInfo.Format("最小MFI值距今 %d 日", mRSIData.m_min_mfi_day);
	mListDetail.AddString(strInfo);


	strInfo.Format("最大MFI值 %.2f", mRSIData.f_max_mfi);
	mListDetail.AddString(strInfo);

	strInfo.Format("最大MFI值距今 %d 日", mRSIData.m_max_mfi_day);
	mListDetail.AddString(strInfo);



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
