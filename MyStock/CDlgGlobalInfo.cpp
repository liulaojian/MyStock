// CDlgGlobalInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "CDlgGlobalInfo.h"
#include "afxdialogex.h"

#include "TanAngleAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include "resource.h"
#include "Convert.h"
#include "CommonMacro.h"
#include "Global.h"
#include "StockKDJArithmetic.h"
// CDlgGlobalInfo 对话框

IMPLEMENT_DYNAMIC(CDlgGlobalInfo, CDialogEx)

static int BACK_NUMS = 10;	//40


CDlgGlobalInfo::CDlgGlobalInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_GLOBAL_INFO, pParent)
{

}

CDlgGlobalInfo::~CDlgGlobalInfo()
{
}

void CDlgGlobalInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NOW, mEditNow);
	DDX_Control(pDX, IDC_EDIT_PRE5, mEditPre5);
	DDX_Control(pDX, IDC_EDIT_PRE25, mEditPre25);
	DDX_Control(pDX, IDC_EDIT_PRE20, mEditPre20);
	DDX_Control(pDX, IDC_EDIT_PRE15, mEditPre15);
	DDX_Control(pDX, IDC_EDIT_PRE10, mEditPre10);
	DDX_Control(pDX, IDC_EDIT_PRE30, mEditPre30);
	DDX_Control(pDX, IDC_EDIT_PRE35, mEditPre35);
	DDX_Control(pDX, IDC_EDIT_PRE40, mEditPre40);
	DDX_Control(pDX, IDC_LIST_GLOBAL_INFO_DAY, mListGlobalInfoDay);
	DDX_Control(pDX, IDC_COMBO_GLOBAL_INFO, mCmbGlobalInfo);
}


BEGIN_MESSAGE_MAP(CDlgGlobalInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_BEGIN, &CDlgGlobalInfo::OnBnClickedBtnBegin)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_BEGIN_DAY, &CDlgGlobalInfo::OnBnClickedBtnBeginDay)
	ON_BN_CLICKED(IDC_BTN_OK, &CDlgGlobalInfo::OnBnClickedBtnOk)
END_MESSAGE_MAP()


// CDlgGlobalInfo 消息处理程序


BOOL CDlgGlobalInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mListGlobalInfoDay.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT); //设置报表风格


	mListGlobalInfoDay.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	mListGlobalInfoDay.InsertColumn(GLOBALINFO_COLUMN_ID, "ID号", LVCFMT_LEFT, 80);
	mListGlobalInfoDay.InsertColumn(GLOBALINFO_COLUMN_DATE, "日期", LVCFMT_LEFT, 100);
	mListGlobalInfoDay.InsertColumn(GLOBALINFO_COLUMN_TAN_5, "TAN 5", LVCFMT_LEFT, 100);
	mListGlobalInfoDay.InsertColumn(GLOBALINFO_COLUMN_TAN_8, "TAN 8", LVCFMT_LEFT, 100);

	int ret;
	
	ret = mCmbGlobalInfo.AddString("回溯10日");
	mCmbGlobalInfo.SetItemData(ret, 10);

	ret = mCmbGlobalInfo.AddString("回溯15日");
	mCmbGlobalInfo.SetItemData(ret, 15);

	ret = mCmbGlobalInfo.AddString("回溯20日");
	mCmbGlobalInfo.SetItemData(ret, 20);

	ret = mCmbGlobalInfo.AddString("回溯25日");
	mCmbGlobalInfo.SetItemData(ret, 25);

	ret = mCmbGlobalInfo.AddString("回溯30日");
	mCmbGlobalInfo.SetItemData(ret, 30);


	ret = mCmbGlobalInfo.AddString("回溯35日");
	mCmbGlobalInfo.SetItemData(ret, 35);


	ret = mCmbGlobalInfo.AddString("回溯40日");
	mCmbGlobalInfo.SetItemData(ret, 40);


	ret = mCmbGlobalInfo.AddString("回溯45日");
	mCmbGlobalInfo.SetItemData(ret, 45);

	ret = mCmbGlobalInfo.AddString("回溯50日");
	mCmbGlobalInfo.SetItemData(ret, 50);


	ret = mCmbGlobalInfo.AddString("回溯60日");
	mCmbGlobalInfo.SetItemData(ret, 60);

	ret = mCmbGlobalInfo.AddString("回溯70日");
	mCmbGlobalInfo.SetItemData(ret, 70);

	ret = mCmbGlobalInfo.AddString("回溯75日");
	mCmbGlobalInfo.SetItemData(ret, 75);

	mCmbGlobalInfo.SetCurSel(1);


	CString strExpStockCode = "SH000001";
	CStockDayTable* pExpStockDayTable = NULL;
	pExpStockDayTable = StockDataMgr()->GetStockDayTable(strExpStockCode);
	strNowDate = pExpStockDayTable->GetNearestStockDayDate(mStockDateTime);

	GetDlgItem(IDC_STATIC_NOW)->SetWindowText(strNowDate);

	int mNowIndex = pExpStockDayTable->GetStockDayIndex(strNowDate);

	int mPre5Index = mNowIndex - 5;
	strPre5Date = pExpStockDayTable->GetStockDayDateByIndex(mPre5Index);
	GetDlgItem(IDC_STATIC_PRE5)->SetWindowText(strPre5Date);

	int mPre10Index= mNowIndex - 10;
	strPre10Date = pExpStockDayTable->GetStockDayDateByIndex(mPre10Index);
	GetDlgItem(IDC_STATIC_PRE10)->SetWindowText(strPre10Date);


	int mPre15Index = mNowIndex - 15;
	strPre15Date = pExpStockDayTable->GetStockDayDateByIndex(mPre15Index);
	GetDlgItem(IDC_STATIC_PRE15)->SetWindowText(strPre15Date);

	int mPre20Index = mNowIndex - 20;
	strPre20Date = pExpStockDayTable->GetStockDayDateByIndex(mPre20Index);
	GetDlgItem(IDC_STATIC_PRE20)->SetWindowText(strPre20Date);


	int mPre25Index = mNowIndex - 25;
	strPre25Date = pExpStockDayTable->GetStockDayDateByIndex(mPre25Index);
	GetDlgItem(IDC_STATIC_PRE25)->SetWindowText(strPre25Date);

	int mPre30Index = mNowIndex - 30;
	strPre30Date = pExpStockDayTable->GetStockDayDateByIndex(mPre30Index);
	GetDlgItem(IDC_STATIC_PRE30)->SetWindowText(strPre30Date);


	int mPre35Index = mNowIndex - 35;
	strPre35Date = pExpStockDayTable->GetStockDayDateByIndex(mPre35Index);
	GetDlgItem(IDC_STATIC_PRE35)->SetWindowText(strPre35Date);

	int mPre40Index = mNowIndex - 40;
	strPre40Date = pExpStockDayTable->GetStockDayDateByIndex(mPre40Index);
	GetDlgItem(IDC_STATIC_PRE40)->SetWindowText(strPre40Date);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


static UINT  doRunGlobalInfoProc(LPVOID pParam)
{

	CDlgGlobalInfo* pDlgGlobalInfo = (CDlgGlobalInfo*)pParam;

	
	pDlgGlobalInfo->doRunInfo();
	

	
	return 0;
}

void  CDlgGlobalInfo::doRunInfo(void)
{
	Vec_TanAngleData vecTanAngleData;
	CTime mNowDate = ConverStringToCTime(strNowDate);
	CTanAngleAlg* pNowTanAngleAlg = new CTanAngleAlg();

	int mBackDays = 5;
	int mMaxAngle = 90;
	double f_max_volume_multiple = 10.0;
	bool bIgnoreM5 = false;
	bool bUseM120 = false;
	bool bUseAllUp = false;
	int mMaxInsBack = 8;
	double f_max_ins_thes = 6.0;

	vecTanAngleData = pNowTanAngleAlg->doFilter(mNowDate, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	int mStockCodeSize = StockDataMgr()->GetStockCodeListSize();
	double f_Tan_Per_5 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_5=%f\n", f_Tan_Per_5);

	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 8;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mNowDate, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	double f_Tan_Per_8 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_8=%f\n", f_Tan_Per_8);

	CString strInfo;

	CString strTemp;

	strTemp.Format("回溯为5的右侧比例为百分之 %f    回溯为8的右侧比例为百分之 %f ", f_Tan_Per_5, f_Tan_Per_8);
	strInfo += strTemp;
	printf("%s\n", (LPCSTR)strInfo);
	strNowInfo = strInfo;
	
	//------------------------------------------
	strInfo = "";
	CTime mPre5Date = ConverStringToCTime(strPre5Date);
	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 5;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre5Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_5 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_5=%f\n", f_Tan_Per_5);

	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 8;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre5Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_8 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_8=%f\n", f_Tan_Per_8);
	strTemp.Format("回溯为5的右侧比例为百分之 %f    回溯为8的右侧比例为百分之 %f ", f_Tan_Per_5, f_Tan_Per_8);
	strInfo += strTemp;
	printf("%s\n", (LPCSTR)strInfo);
	strPre5Info = strInfo;
	
	//------------------------------------------

	CTime mPre10Date = ConverStringToCTime(strPre10Date);
	strInfo = "";
	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 5;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre10Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_5 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_5=%f\n", f_Tan_Per_5);

	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 8;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre10Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_8 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_8=%f\n", f_Tan_Per_8);
	strTemp.Format("回溯为5的右侧比例为百分之 %f    回溯为8的右侧比例为百分之 %f ", f_Tan_Per_5, f_Tan_Per_8);
	strInfo += strTemp;
	printf("%s\n", (LPCSTR)strInfo);
	strPre10Info = strInfo;

	//------------------------------------------
	CTime mPre15Date = ConverStringToCTime(strPre15Date);
	strInfo = "";
	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 5;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre15Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_5 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_5=%f\n", f_Tan_Per_5);

	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 8;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre15Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_8 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_8=%f\n", f_Tan_Per_8);
	strTemp.Format("回溯为5的右侧比例为百分之 %f    回溯为8的右侧比例为百分之 %f ", f_Tan_Per_5, f_Tan_Per_8);
	strInfo += strTemp;
	printf("%s\n", (LPCSTR)strInfo);
	strPre15Info = strInfo;

	//------------------------------------------

	CTime mPre20Date = ConverStringToCTime(strPre20Date);
	strInfo = "";
	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 5;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre20Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_5 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_5=%f\n", f_Tan_Per_5);

	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 8;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre20Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_8 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_8=%f\n", f_Tan_Per_8);
	strTemp.Format("回溯为5的右侧比例为百分之 %f    回溯为8的右侧比例为百分之 %f ", f_Tan_Per_5, f_Tan_Per_8);
	strInfo += strTemp;
	printf("%s\n", (LPCSTR)strInfo);
	strPre20Info = strInfo;

	//------------------------------------------

	CTime mPre25Date = ConverStringToCTime(strPre25Date);
	strInfo = "";
	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 5;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre25Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_5 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_5=%f\n", f_Tan_Per_5);

	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 8;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre25Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_8 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_8=%f\n", f_Tan_Per_8);
	strTemp.Format("回溯为5的右侧比例为百分之 %f    回溯为8的右侧比例为百分之 %f ", f_Tan_Per_5, f_Tan_Per_8);
	strInfo += strTemp;
	printf("%s\n", (LPCSTR)strInfo);
	strPre25Info = strInfo;

	//---------------------------------------------------------

	CTime mPre30Date = ConverStringToCTime(strPre30Date);
	strInfo = "";
	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 5;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre30Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_5 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_5=%f\n", f_Tan_Per_5);

	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 8;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre30Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_8 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_8=%f\n", f_Tan_Per_8);
	strTemp.Format("回溯为5的右侧比例为百分之 %f    回溯为8的右侧比例为百分之 %f ", f_Tan_Per_5, f_Tan_Per_8);
	strInfo += strTemp;
	printf("%s\n", (LPCSTR)strInfo);
	strPre30Info = strInfo;


	//------------------------------------------------------------
	CTime mPre35Date = ConverStringToCTime(strPre35Date);
	strInfo = "";
	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 5;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre35Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_5 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_5=%f\n", f_Tan_Per_5);

	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 8;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre35Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_8 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_8=%f\n", f_Tan_Per_8);
	strTemp.Format("回溯为5的右侧比例为百分之 %f    回溯为8的右侧比例为百分之 %f ", f_Tan_Per_5, f_Tan_Per_8);
	strInfo += strTemp;
	printf("%s\n", (LPCSTR)strInfo);
	strPre35Info = strInfo;

	//------------------------------------------------------------

	CTime mPre40Date = ConverStringToCTime(strPre40Date);
	strInfo = "";
	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 5;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre40Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_5 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_5=%f\n", f_Tan_Per_5);

	for (int j = 0; j < vecTanAngleData.size(); j++)
		SAFE_DELETE(vecTanAngleData[j]);
	vecTanAngleData.clear();
	pNowTanAngleAlg = new CTanAngleAlg();
	mBackDays = 8;
	vecTanAngleData = pNowTanAngleAlg->doFilter(mPre40Date, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	f_Tan_Per_8 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	printf("f_Tan_Per_8=%f\n", f_Tan_Per_8);
	strTemp.Format("回溯为5的右侧比例为百分之 %f    回溯为8的右侧比例为百分之 %f ", f_Tan_Per_5, f_Tan_Per_8);
	strInfo += strTemp;
	printf("%s\n", (LPCSTR)strInfo);
	strPre40Info = strInfo;

	SetTimer(GLOBAL_REFRESH_DATA, 300, 0);

}
void CDlgGlobalInfo::OnBnClickedBtnBegin()
{

	if (pThread)
		return;

	pThread = AfxBeginThread(doRunGlobalInfoProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);

	

}


void CDlgGlobalInfo::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (GLOBAL_REFRESH_DATA == nIDEvent)
	{
		KillTimer(GLOBAL_REFRESH_DATA);
		//printf("%s   ", (LPCSTR)strNowInfo); 
		//printf("%s\n", (LPCSTR)strPre5Info);
		
		mEditNow.SetWindowText(strNowInfo);
		mEditPre5.SetWindowText(strPre5Info);
		mEditPre10.SetWindowText(strPre10Info);
		mEditPre15.SetWindowText(strPre15Info);
		mEditPre20.SetWindowText(strPre20Info);
		mEditPre25.SetWindowText(strPre25Info);
		mEditPre30.SetWindowText(strPre30Info);
		mEditPre35.SetWindowText(strPre35Info);
		mEditPre40.SetWindowText(strPre40Info);
	}
	else if (GLOBAL_REFRESH_DATA_DAY == nIDEvent)
	{
		KillTimer(GLOBAL_REFRESH_DATA_DAY);
		RefreshData();
	}
	CDialogEx::OnTimer(nIDEvent);
}

BOOL CDlgGlobalInfo::RefreshData(void)
{
	CString strConv, strTemp;
	int nRow;
	mListGlobalInfoDay.DeleteAllItems();
	int i = 0;
	StockGlobalInfo* pStockGlobalInfo;
	for (i = 0; i < vecStockGlobalInfoM5List.size(); i++)
	{
		pStockGlobalInfo = vecStockGlobalInfoM5List[i];
		if (!pStockGlobalInfo)
			continue;
		strConv.Format("%4d", i + 1);
		nRow = i;
		if (nRow >= mListGlobalInfoDay.GetItemCount())
			mListGlobalInfoDay.InsertItem(i, strConv);
		else
			mListGlobalInfoDay.SetItemText(nRow, GLOBALINFO_COLUMN_ID, strConv);

		mListGlobalInfoDay.SetItemText(nRow, GLOBALINFO_COLUMN_DATE, pStockGlobalInfo->strStockDate);

		CString strTemp;

		double f_tan_5 = pStockGlobalInfo->f_Tan_Per_5;

		strTemp.Format("%.2f", f_tan_5);
		mListGlobalInfoDay.SetItemText(nRow, GLOBALINFO_COLUMN_TAN_5, strTemp);

		double f_tan_8 = pStockGlobalInfo->f_Tan_Per_8;

		strTemp.Format("%.2f", f_tan_8);
		mListGlobalInfoDay.SetItemText(nRow, GLOBALINFO_COLUMN_TAN_8, strTemp);

		mListGlobalInfoDay.SetItemData(nRow, reinterpret_cast<DWORD_PTR>(pStockGlobalInfo));
	}

	if (i < mListGlobalInfoDay.GetItemCount())
	{
		for (int j = i; j < mListGlobalInfoDay.GetItemCount(); j++)
			mListGlobalInfoDay.DeleteItem(j);
	}

	return TRUE;
}

static UINT  doRunGlobalInfoDayProc(LPVOID pParam)
{

	CDlgGlobalInfo* pDlgGlobalInfo = (CDlgGlobalInfo*)pParam;


	pDlgGlobalInfo->doRunDayInfo();



	return 0;
}



void  CDlgGlobalInfo::doRunDayInfo(void)
{
	CString strExpStockCode = "SH000001";
	CStockDayTable* pExpStockDayTable = NULL;
	pExpStockDayTable = StockDataMgr()->GetStockDayTable(strExpStockCode);
	
	int mPreIndex = 0;
	int mNowIndex = 0;
	StockGlobalInfo* pStockGlobalInfo = new StockGlobalInfo();


	pStockGlobalInfo->strStockDate= pExpStockDayTable->GetNearestStockDayDate(mStockDateTime);
	mNowIndex = pExpStockDayTable->GetStockDayIndex(pStockGlobalInfo->strStockDate);
	mPreIndex = mNowIndex - 1;
	vecStockGlobalInfoDayList.push_back(pStockGlobalInfo);

	int nums = 1;
	
	while (nums <= BACK_NUMS)
	{
		pStockGlobalInfo = new StockGlobalInfo();
		pStockGlobalInfo->strStockDate = pExpStockDayTable->GetStockDayDateByIndex(mPreIndex);
		mPreIndex--;
		vecStockGlobalInfoDayList.push_back(pStockGlobalInfo);
		nums++;
	}

	Vec_TanAngleData vecTanAngleData;

	int mBackDays = 8;
	int mMaxAngle = 90;
	double f_max_volume_multiple = 10.0;
	bool bIgnoreM5 = false;
	bool bUseM120 = false;
	bool bUseAllUp = false;
	int mMaxInsBack = 8;
	double f_max_ins_thes = 6.0;
	CTime mDate;
	CTanAngleAlg* pTanAngleAlg;
	int mStockCodeSize = StockDataMgr()->GetStockCodeListSize();

	for (int i = 0; i < vecStockGlobalInfoDayList.size(); i++)
	{
		pStockGlobalInfo = vecStockGlobalInfoDayList[i];
		mDate = ConverStringToCTime(pStockGlobalInfo->strStockDate);

		for (int j = 0; j < vecTanAngleData.size(); j++)
			SAFE_DELETE(vecTanAngleData[j]);	
		vecTanAngleData.clear();
		pTanAngleAlg = new CTanAngleAlg();
		mBackDays = 8;
		vecTanAngleData = pTanAngleAlg->doFilter(mDate, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
		pStockGlobalInfo->f_Tan_Per_8 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;


		for (int j = 0; j < vecTanAngleData.size(); j++)
			SAFE_DELETE(vecTanAngleData[j]);
		vecTanAngleData.clear();
		pTanAngleAlg = new CTanAngleAlg();
		mBackDays = 5;

		vecTanAngleData = pTanAngleAlg->doFilter(mDate, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
		pStockGlobalInfo->f_Tan_Per_5 = (vecTanAngleData.size() * 100.0) / mStockCodeSize;

	}

	for (int i = 0; i < vecStockGlobalInfoDayList.size(); i++)
	{
		pStockGlobalInfo = vecStockGlobalInfoDayList[i];
		printf(" %s   %.2f  %.2f \n", (LPCSTR)pStockGlobalInfo->strStockDate, pStockGlobalInfo->f_Tan_Per_5,pStockGlobalInfo->f_Tan_Per_8);
	}


	std::vector<double> vec_global_info_8;
	std::vector<double> vec_global_info_5;
	std::vector<CString > vec_global_info_date;
	for (int i = vecStockGlobalInfoDayList.size()-1; i>=0; i--)
	{
		vec_global_info_8.push_back(vecStockGlobalInfoDayList[i]->f_Tan_Per_8);
		vec_global_info_5.push_back(vecStockGlobalInfoDayList[i]->f_Tan_Per_5);
		vec_global_info_date.push_back(vecStockGlobalInfoDayList[i]->strStockDate);
	}

	std::vector<double> vec_global_info_8_m5;
	std::vector<double> vec_global_info_5_m5;

	vec_global_info_8_m5= CStockKDJArithmetic::CalcMA(5, vec_global_info_8);
	vec_global_info_5_m5 = CStockKDJArithmetic::CalcMA(5, vec_global_info_5);

	vecStockGlobalInfoM5List.clear();
	for (int i = vecStockGlobalInfoDayList.size() - 1; i >= 0; i--)
	{
		pStockGlobalInfo = new StockGlobalInfo();
		pStockGlobalInfo->strStockDate = vec_global_info_date[i];
		pStockGlobalInfo->f_Tan_Per_5 = vec_global_info_5_m5[i];
		pStockGlobalInfo->f_Tan_Per_8 = vec_global_info_8_m5[i];
		vecStockGlobalInfoM5List.push_back(pStockGlobalInfo);

	}

	SetTimer(GLOBAL_REFRESH_DATA_DAY, 300, 0);
}

void CDlgGlobalInfo::OnBnClickedBtnBeginDay()
{
	int	iItem = mCmbGlobalInfo.GetCurSel();
	if (iItem < 0) return;

	int mNums = mCmbGlobalInfo.GetItemData(iItem);
	BACK_NUMS = mNums;

	vecStockGlobalInfoDayList.clear();

	if (pThreadAll)
		return;

	pThreadAll = AfxBeginThread(doRunGlobalInfoDayProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);



}


void CDlgGlobalInfo::OnBnClickedBtnOk()
{
	int	iItem = mCmbGlobalInfo.GetCurSel();
	if (iItem < 0) return;

	int mGlobalInfo = mCmbGlobalInfo.GetItemData(iItem);
	BACK_NUMS = mGlobalInfo;
}
