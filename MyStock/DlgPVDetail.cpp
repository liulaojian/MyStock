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

	strInfo.Format("当前RSI1值 %.2f", mRSIData.rsi_1);
	mListDetail.AddString(strInfo);
	strInfo.Format("当前RSI2值 %.2f", mRSIData.rsi_2);
	mListDetail.AddString(strInfo);
	strInfo.Format("当前RSI3值 %.2f", mRSIData.rsi_3);
	mListDetail.AddString(strInfo);

	mListDetail.AddString("    ");
	mListDetail.AddString("    ");
	strInfo.Format("最小RSI1值 %.2f", mRSIData.f_min_rsi1);
	mListDetail.AddString(strInfo);
	strInfo.Format("最小RSI2值 %.2f", mRSIData.f_min_rsi2);
	mListDetail.AddString(strInfo);
	strInfo.Format("最小RSI3值 %.2f", mRSIData.f_min_rsi3);
	mListDetail.AddString(strInfo);
	strInfo.Format("最小RSI1距今 %d日", mRSIData.m_min_rsi_day);
	mListDetail.AddString(strInfo);

	mListDetail.AddString("    ");
	mListDetail.AddString("    ");
	strInfo.Format("最大RSI1值 %.2f", mRSIData.f_max_rsi1);
	mListDetail.AddString(strInfo);
	strInfo.Format("最大RSI2值 %.2f", mRSIData.f_max_rsi2);
	mListDetail.AddString(strInfo);
	strInfo.Format("最大RSI3值 %.2f", mRSIData.f_max_rsi3);
	mListDetail.AddString(strInfo);
	strInfo.Format("最大RSI1距今 %d日", mRSIData.m_max_rsi_day);
	mListDetail.AddString(strInfo);


	mListDetail.AddString("    ");
	mListDetail.AddString("    ");
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


	mListDetail.AddString("    ");
	mListDetail.AddString("    ");

	strInfo.Format("当前VR值 %.2f", mRSIData.vr);
	mListDetail.AddString(strInfo);


	strInfo.Format("最小VR值 %.2f", mRSIData.f_min_vr);
	mListDetail.AddString(strInfo);
	strInfo.Format("最小VR值距今 %d 日", mRSIData.m_min_vr_day);
	mListDetail.AddString(strInfo);


	strInfo.Format("最大VR值 %.2f", mRSIData.f_max_vr);
	mListDetail.AddString(strInfo);

	strInfo.Format("最大VR值距今 %d 日", mRSIData.m_max_vr_day);
	mListDetail.AddString(strInfo);

	//if (mRSIData.b_vr_upcross)
	//	mListDetail.AddString("VR上穿");

	//mListDetail.AddString("    ");
	//strInfo.Format("相对BOLLUp线 %.2f  %.2f  %.2f  %.2f  %.2f", mRSIData.f_boll_up_per[0], mRSIData.f_boll_up_per[1], mRSIData.f_boll_up_per[2],
	//	mRSIData.f_boll_up_per[3], mRSIData.f_boll_up_per[4]);
	//mListDetail.AddString(strInfo);

	
	mListDetail.AddString("    ");

	strInfo.Format("最近三日PSY (%.2f  %.2f)  (%.2f  %.2f)  (%.2f  %.2f)", mRSIData.f_psy[0], mRSIData.f_mpsy[1], 
		mRSIData.f_psy[1],mRSIData.f_mpsy[1], mRSIData.f_psy[2], mRSIData.f_mpsy[2]);
	mListDetail.AddString(strInfo);

	mListDetail.AddString("    ");
	strInfo.Format("上影线比率      %.2f  %.2f  %.2f  %.2f  %.2f", mRSIData.f_up_shadow_line_per[0], mRSIData.f_up_shadow_line_per[1], mRSIData.f_up_shadow_line_per[2],
		mRSIData.f_up_shadow_line_per[3], mRSIData.f_up_shadow_line_per[4]);
	mListDetail.AddString(strInfo);
	strInfo.Format("下影线比率      %.2f  %.2f  %.2f  %.2f  %.2f", mRSIData.f_down_shadow_line_per[0], mRSIData.f_down_shadow_line_per[1], mRSIData.f_down_shadow_line_per[2],
		mRSIData.f_down_shadow_line_per[3], mRSIData.f_down_shadow_line_per[4]);
	mListDetail.AddString(strInfo);
	strInfo.Format("全振幅百分比   %.2f  %.2f  %.2f  %.2f  %.2f", mRSIData.f_amplitude_per[0], mRSIData.f_amplitude_per[1], mRSIData.f_amplitude_per[2],
		mRSIData.f_amplitude_per[3], mRSIData.f_amplitude_per[4]);
	mListDetail.AddString(strInfo);
	strInfo.Format("5日涨幅百分比  %.2f  %.2f  %.2f  %.2f  %.2f", mRSIData.f_close_increase_per[0], mRSIData.f_close_increase_per[1], mRSIData.f_close_increase_per[2],
		mRSIData.f_close_increase_per[3], mRSIData.f_close_increase_per[4]);
	mListDetail.AddString(strInfo);
	strInfo.Format("Ma5线比率      %.2f  %.2f  %.2f  %.2f  %.2f", mRSIData.f_ma5_per[0], mRSIData.f_ma5_per[1], mRSIData.f_ma5_per[2],
		mRSIData.f_ma5_per[3], mRSIData.f_ma5_per[4]);
	mListDetail.AddString(strInfo);

	strInfo.Format("Sar比率        %.3f  %.3f  %.3f  %.3f  %.3f", mRSIData.f_sar_per[0], mRSIData.f_sar_per[1], mRSIData.f_sar_per[2],
		mRSIData.f_sar_per[3], mRSIData.f_sar_per[4]);
	mListDetail.AddString(strInfo);

	mListDetail.AddString("    ");


	for(int i=0;i< mRSIData.m_ccivr_data.vecInfo.size();i++)
		mListDetail.AddString(mRSIData.m_ccivr_data.vecInfo[i]);

	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
