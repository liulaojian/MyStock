// DlgIndustryFilter.cpp: 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgIndustryFilter.h"
#include "afxdialogex.h"
#include "DlgTanAngle.h"
#include "Algorithm.h"
#include "TanAngleAlg.h"
#include "Convert.h"
// CDlgIndustryFilter 对话框

IMPLEMENT_DYNAMIC(CDlgIndustryFilter, CDialogEx)

CDlgIndustryFilter::CDlgIndustryFilter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_INDUSTRY_FILTER, pParent)
{

}

CDlgIndustryFilter::~CDlgIndustryFilter()
{
}

void CDlgIndustryFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_FIRST_POS, mCmbFirstPos);
	DDX_Control(pDX, IDC_CMB_FSECOND_POS, mCmbSecondPos);
	DDX_Control(pDX, IDC_LIST1, mList1);
}


BEGIN_MESSAGE_MAP(CDlgIndustryFilter, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_FILTER, &CDlgIndustryFilter::OnBnClickedBtnFilter)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_OK, &CDlgIndustryFilter::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CDlgIndustryFilter::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CDlgIndustryFilter 消息处理程序


BOOL CDlgIndustryFilter::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mList1.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT);
	mList1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	mList1.InsertColumn(INDUSTRYFILTER_COLUMN_ID, "ID号", LVCFMT_LEFT, 80);
	mList1.InsertColumn(INDUSTRYFILTER_COLUMN_CODE, "代码", LVCFMT_LEFT, 100);
	mList1.InsertColumn(INDUSTRYFILTER_COLUMN_NAME, "名称", LVCFMT_LEFT, 100);

	int ret;

	ret = mCmbFirstPos.AddString("5交易日");
	mCmbFirstPos.SetItemData(ret, 5);

	ret = mCmbFirstPos.AddString("10交易日");
	mCmbFirstPos.SetItemData(ret, 10);

	ret = mCmbFirstPos.AddString("15交易日");
	mCmbFirstPos.SetItemData(ret, 15);

	ret = mCmbFirstPos.AddString("20交易日");
	mCmbFirstPos.SetItemData(ret, 20);

	ret = mCmbFirstPos.AddString("25交易日");
	mCmbFirstPos.SetItemData(ret, 25);


	ret = mCmbFirstPos.AddString("30交易日");
	mCmbFirstPos.SetItemData(ret, 30);

	ret = mCmbFirstPos.AddString("35交易日");
	mCmbFirstPos.SetItemData(ret, 35);


	mCmbFirstPos.SetCurSel(2);

	
	ret = mCmbSecondPos.AddString("10交易日");
	mCmbSecondPos.SetItemData(ret, 10);

	ret = mCmbSecondPos.AddString("15交易日");
	mCmbSecondPos.SetItemData(ret, 15);

	ret = mCmbSecondPos.AddString("20交易日");
	mCmbSecondPos.SetItemData(ret, 20);

	ret = mCmbSecondPos.AddString("25交易日");
	mCmbSecondPos.SetItemData(ret, 25);

	ret = mCmbSecondPos.AddString("30交易日");
	mCmbSecondPos.SetItemData(ret, 30);

	ret = mCmbSecondPos.AddString("35交易日");
	mCmbSecondPos.SetItemData(ret, 35);

	ret = mCmbSecondPos.AddString("40交易日");
	mCmbSecondPos.SetItemData(ret, 40);
	mCmbSecondPos.SetCurSel(4);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//处理
void CDlgIndustryFilter::OnBnClickedBtnFilter()
{
	int	iItem = mCmbFirstPos.GetCurSel();
	if (iItem < 0) return;

	int mFirstPos = mCmbFirstPos.GetItemData(iItem);
	

	iItem = mCmbSecondPos.GetCurSel();
	if (iItem < 0) return;

	int mSecondPos = mCmbSecondPos.GetItemData(iItem);

	if (mSecondPos < mFirstPos)
	{
		AfxMessageBox("第二位置不能少于第一位置");
		return;
	}

	Vec_IndustryFilterInfo vecNowFilterInfo;
	Vec_IndustryFilterInfo vecFirstFilterInfo;
	Vec_IndustryFilterInfo vecSecondFilterInfo;
	int mBackDays;
	int mMaxAngle;
	double f_max_volume_multiple;
	bool bIgnoreM5;
	bool bUseM120;
	bool bUseAllUp;
	int mMaxInsBack;
	double f_max_ins_thes;
	int mKLineType = 0;
	Vec_TanAngleData vecTanAngleData;
	CDlgTanAngle dlg;
	if (dlg.DoModal() != IDOK)
		return;
	
	mBackDays = dlg.GetBackDays();
	mMaxAngle = dlg.GetMaxAngle();
	f_max_volume_multiple = dlg.GetMaxVolumeMultiple();
	bIgnoreM5 = dlg.IsIgnoreM5();
	bUseM120 = dlg.IsIgnoreM60();
	bUseAllUp = dlg.IsUseAllUp();
	mMaxInsBack = dlg.GetMaxInsBack();
	f_max_ins_thes = dlg.GetMaxInsThes();
	mKLineType = dlg.GetKLineType();
	CTanAngleAlg mTanAngleAlg;
	mTanAngleAlg.SetKLineType(mKLineType);
	vecTanAngleData = mTanAngleAlg.doFilter(mStockDateTime, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);

	IndustryFilterInfo* pIndustryFilterInfo = NULL;
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		pIndustryFilterInfo = new IndustryFilterInfo();
		pIndustryFilterInfo->strStockCode = vecTanAngleData[i]->strStockCode;
		pIndustryFilterInfo->strStockName = vecTanAngleData[i]->strStockName;
		vecNowFilterInfo.push_back(pIndustryFilterInfo);
	}

	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		delete vecTanAngleData[i];
		vecTanAngleData[i] = NULL;
	}
	vecTanAngleData.clear();

	CTanAngleAlg mTanAngleAlg2;
	mTanAngleAlg2.SetKLineType(mKLineType);
	CString strExpStockCode = "SH000001";
	CStockDayTable* pExpStockDayTable = NULL;
	pExpStockDayTable = StockDataMgr()->GetStockDayTable(strExpStockCode);
	CString strNowDate = pExpStockDayTable->GetNearestStockDayDate(mStockDateTime);

	int mNowIndex = pExpStockDayTable->GetStockDayIndex(strNowDate);

	int mFirstIndex = mNowIndex - mFirstPos;
	CString strFirstDate = pExpStockDayTable->GetStockDayDateByIndex(mFirstIndex);
	CTime mFirstDate = ConverStringToCTime(strFirstDate);

	vecTanAngleData = mTanAngleAlg2.doFilter(mFirstDate, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		pIndustryFilterInfo = new IndustryFilterInfo();
		pIndustryFilterInfo->strStockCode = vecTanAngleData[i]->strStockCode;
		pIndustryFilterInfo->strStockName = vecTanAngleData[i]->strStockName;
		vecFirstFilterInfo.push_back(pIndustryFilterInfo);
	}
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		delete vecTanAngleData[i];
		vecTanAngleData[i] = NULL;
	}
	vecTanAngleData.clear();


	CTanAngleAlg mTanAngleAlg3;
	mTanAngleAlg3.SetKLineType(mKLineType);
	int mSecondIndex = mNowIndex - mSecondPos;
	CString strSecondDate = pExpStockDayTable->GetStockDayDateByIndex(mSecondIndex);
	CTime mSecondDate = ConverStringToCTime(strSecondDate);

	vecTanAngleData = mTanAngleAlg3.doFilter(mSecondDate, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		pIndustryFilterInfo = new IndustryFilterInfo();
		pIndustryFilterInfo->strStockCode = vecTanAngleData[i]->strStockCode;
		pIndustryFilterInfo->strStockName = vecTanAngleData[i]->strStockName;
		vecSecondFilterInfo.push_back(pIndustryFilterInfo);
	}
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		delete vecTanAngleData[i];
		vecTanAngleData[i] = NULL;
	}
	vecTanAngleData.clear();

	//First没有  Now 有的
	Vec_IndustryFilterInfo vecFirstDiffNowFilterInfo;

	for (int i = 0; i < vecNowFilterInfo.size(); i++)
	{
		bool bFound = false;
		for (int j = 0; j < vecFirstFilterInfo.size(); j++)
		{
			if (vecFirstFilterInfo[j]->strStockCode == vecNowFilterInfo[i]->strStockCode)
			{
				bFound = true;
				break;
			}

		}

		if (!bFound)
		{
			vecFirstDiffNowFilterInfo.push_back(vecNowFilterInfo[i]);
		}
	}


	//Second 没有 Now 有的
	Vec_IndustryFilterInfo vecSecondDiffNowFilterInfo;
	for (int i = 0; i < vecNowFilterInfo.size(); i++)
	{
		bool bFound = false;
		for (int j = 0; j < vecSecondFilterInfo.size(); j++)
		{
			if (vecSecondFilterInfo[j]->strStockCode == vecNowFilterInfo[i]->strStockCode)
			{
				bFound = true;
				break;
			}

		}

		if (!bFound)
		{
			vecSecondDiffNowFilterInfo.push_back(vecNowFilterInfo[i]);
		}
	}
#if 0
	//vecSecondDiffNowFilterInfo 没有 vecFirstDiffNowFilterInfo 有的

	Vec_IndustryFilterInfo vecSecondDiffFirstFilterInfo;
	for (int i = 0; i < vecFirstDiffNowFilterInfo.size(); i++)
	{
		bool bFound = false;
		for (int j = 0; j < vecSecondDiffNowFilterInfo.size(); j++)
		{
			if (vecSecondDiffNowFilterInfo[j]->strStockCode == vecFirstDiffNowFilterInfo[i]->strStockCode)
			{
				bFound = true;
				break;
			}

		}

		if (!bFound)
		{
			vecSecondDiffFirstFilterInfo.push_back(vecFirstDiffNowFilterInfo[i]);
		}
	}
#else

	Vec_IndustryFilterInfo vecSecondDiffFirstFilterInfo;
	for (int i = 0; i < vecFirstDiffNowFilterInfo.size(); i++)
	{
		bool bFound = false;
		for (int j = 0; j < vecSecondDiffNowFilterInfo.size(); j++)
		{
			if (vecSecondDiffNowFilterInfo[j]->strStockCode == vecFirstDiffNowFilterInfo[i]->strStockCode)
			{
				bFound = true;
				break;
			}

		}

		if (bFound)
		{
			vecSecondDiffFirstFilterInfo.push_back(vecFirstDiffNowFilterInfo[i]);
		}
	}


#endif

	for (int i = 0; i < vecResultFilterInfo.size(); i++)
	{
		delete vecResultFilterInfo[i];
		vecResultFilterInfo[i] = NULL;
	}
	vecResultFilterInfo.clear();

	
	for (int i = 0; i < vecSecondDiffFirstFilterInfo.size(); i++)
	{
		pIndustryFilterInfo = new IndustryFilterInfo();
		pIndustryFilterInfo->strStockCode = vecSecondDiffFirstFilterInfo[i]->strStockCode;
		pIndustryFilterInfo->strStockName = vecSecondDiffFirstFilterInfo[i]->strStockName;
		vecResultFilterInfo.push_back(pIndustryFilterInfo);
	}

	vecFirstDiffNowFilterInfo.clear();
	vecSecondDiffNowFilterInfo.clear();
	vecSecondDiffFirstFilterInfo.clear();


	for (int i = 0; i < vecNowFilterInfo.size(); i++)
	{
		delete vecNowFilterInfo[i];
		vecNowFilterInfo[i] = NULL;
	}
	vecNowFilterInfo.clear();

	for (int i = 0; i < vecFirstFilterInfo.size(); i++)
	{
		delete vecFirstFilterInfo[i];
		vecFirstFilterInfo[i] = NULL;
	}
	vecFirstFilterInfo.clear();


	for (int i = 0; i < vecSecondFilterInfo.size(); i++)
	{
		delete vecSecondFilterInfo[i];
		vecSecondFilterInfo[i] = NULL;
	}
	vecSecondFilterInfo.clear();


	SetTimer(INDUSTRYFILTER_REFRESH_DATA, 300, 0);
}


void CDlgIndustryFilter::OnTimer(UINT_PTR nIDEvent)
{
	if (INDUSTRYFILTER_REFRESH_DATA == nIDEvent)
	{
		KillTimer(INDUSTRYFILTER_REFRESH_DATA);
		RefreshData();

	}
	CDialogEx::OnTimer(nIDEvent);
}



BOOL CDlgIndustryFilter::RefreshData(void)
{
	CString strConv, strTemp;
	int nRow;
	mList1.DeleteAllItems();
	int i = 0;
	IndustryFilterInfo* pIndustryFilterInfo;
	for (i = 0; i < vecResultFilterInfo.size(); i++)
	{
		pIndustryFilterInfo = vecResultFilterInfo[i];
		if (!pIndustryFilterInfo)
			continue;
		strConv.Format("%4d", i + 1);
		nRow = i;
		if (nRow >= mList1.GetItemCount())
			mList1.InsertItem(i, strConv);
		else
			mList1.SetItemText(nRow, INDUSTRYFILTER_COLUMN_ID, strConv);

		mList1.SetItemText(nRow, INDUSTRYFILTER_COLUMN_CODE, pIndustryFilterInfo->strStockCode);

		
		mList1.SetItemText(nRow, INDUSTRYFILTER_COLUMN_NAME, pIndustryFilterInfo->strStockName);

		mList1.SetItemData(nRow, reinterpret_cast<DWORD_PTR>(pIndustryFilterInfo));
	}

	if (i < mList1.GetItemCount())
	{
		for (int j = i; j < mList1.GetItemCount(); j++)
			mList1.DeleteItem(j);
	}

	return TRUE;
}

void CDlgIndustryFilter::OnBnClickedBtnOk()
{
	CDialogEx::OnOK();
}


void CDlgIndustryFilter::OnBnClickedBtnCancel()
{
	CDialogEx::OnCancel();
}
