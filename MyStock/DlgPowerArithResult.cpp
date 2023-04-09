// DlgPowerArithResult.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgPowerArithResult.h"
#include "afxdialogex.h"
#include "StockDataMgr.h"
#include "zbTypeDef.h"
#include "CommonMacro.h"
#include "Convert.h"
#include <algorithm>  
#include "DlgCalcPower.h"
#include "DlgStockNatureAnalysis.h"
#include "DlgCalcRiskLevel.h"
#include "DlgSimilarResult.h"
#include "StockProfitLossArithmetic.h"
#include "Util.h"
#include "DlgStockPriceDestribute.h"

// CDlgPowerArithResult 对话框

IMPLEMENT_DYNAMIC(CDlgPowerArithResult, CDialogEx)

CDlgPowerArithResult::CDlgPowerArithResult(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPowerArithResult::IDD, pParent),pExpStockDayTable(NULL)
{
	mLastDayNums=120;
	strBeginDate="";
	strEndDate="";
}

CDlgPowerArithResult::~CDlgPowerArithResult()
{
}

void CDlgPowerArithResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_POWER_RESULT, mResultListCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN, mBeginDateCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, mEndDateCtrl);
	DDX_Control(pDX, IDC_COMBO_SORT, mCmbSort);
	DDX_Control(pDX, IDC_SCRIPTCONTROL1, mScriptControl);
	DDX_Control(pDX, IDC_MENUBTN_RANGE, mMenuBtnRange);
}


BEGIN_MESSAGE_MAP(CDlgPowerArithResult, CDialogEx)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_MENU_DFCF_WEB_OPEN, &CDlgPowerArithResult::OnUpdateMenuDfcfWebOpen)
	ON_COMMAND(ID_MENU_DFCF_WEB_OPEN, &CDlgPowerArithResult::OnMenuDfcfWebOpen)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_POWER_RESULT, &CDlgPowerArithResult::OnRclickListPowerResult)
	ON_BN_CLICKED(IDC_BTN_RECALC, &CDlgPowerArithResult::OnBnClickedBtnRecalc)
	ON_BN_CLICKED(IDC_BTN_RECALC_SORT, &CDlgPowerArithResult::OnBnClickedBtnRecalcSort)
	ON_UPDATE_COMMAND_UI(ID_MENU_CALC_POWER, &CDlgPowerArithResult::OnUpdateMenuCalcPower)
	ON_COMMAND(ID_MENU_CALC_POWER, &CDlgPowerArithResult::OnMenuCalcPower)
	ON_COMMAND(ID_MENU_STOCK_ANALYSIS, &CDlgPowerArithResult::OnMenuStockAnalysis)
	ON_UPDATE_COMMAND_UI(ID_MENU_STOCK_ANALYSIS, &CDlgPowerArithResult::OnUpdateMenuStockAnalysis)
	ON_UPDATE_COMMAND_UI(ID_MENU_DANGER_CALC, &CDlgPowerArithResult::OnUpdateMenuDangerCalc)
	ON_COMMAND(ID_MENU_DANGER_CALC, &CDlgPowerArithResult::OnMenuDangerCalc)
	ON_UPDATE_COMMAND_UI(ID_MENU_FIND_SIMILAR, &CDlgPowerArithResult::OnUpdateMenuFindSimilar)
	ON_COMMAND(ID_MENU_FIND_SIMILAR, &CDlgPowerArithResult::OnMenuFindSimilar)
	ON_BN_CLICKED(IDC_BTN_FILTER, &CDlgPowerArithResult::OnBnClickedBtnFilter)
	ON_BN_CLICKED(IDC_MENUBTN_RANGE, &CDlgPowerArithResult::OnBnClickedMenubtnRange)
	ON_UPDATE_COMMAND_UI(ID_MENU_STOCK_PRICE_DESTRIBUTE, &CDlgPowerArithResult::OnUpdateMenuStockPriceDestribute)
	ON_COMMAND(ID_MENU_STOCK_PRICE_DESTRIBUTE, &CDlgPowerArithResult::OnMenuStockPriceDestribute)
	ON_BN_CLICKED(IDC_BTN_CALC_NO_CHANGE, &CDlgPowerArithResult::OnBnClickedBtnCalcNoChange)
END_MESSAGE_MAP()


// CDlgPowerArithResult 消息处理程序


BOOL CDlgPowerArithResult::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	


	mCmbSort.ResetContent();
	int ret=mCmbSort.AddString("按定制日期排序");
	mCmbSort.SetItemData(ret,SORT_BY_CUSTOM_DATE);

	ret=mCmbSort.AddString("按Power10排序");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_10);

	ret=mCmbSort.AddString("按Power20排序");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_20);

	ret=mCmbSort.AddString("按Power40排序");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_40);

	ret=mCmbSort.AddString("按Power60排序");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_60);

	ret=mCmbSort.AddString("按Power120排序");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_120);

	ret=mCmbSort.AddString("按Power240排序");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_240);

	ret=mCmbSort.AddString("按Power10和Power20排序");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_10_AND_20);

	ret=mCmbSort.AddString("按Power10 20 40 排序");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_10_AND_20_AND_40);

	ret=mCmbSort.AddString("按Power10 20 40 60");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_10_AND_20_40_60);

	
	ret=mCmbSort.AddString("按Power 20 40 ");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_20_AND_40);

	ret=mCmbSort.AddString("按Power 20 40 60 120 240");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_20_AND_40_60_120_240);
	

	ret=mCmbSort.AddString("按Power40 60 排序");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_40_AND_60);

	ret=mCmbSort.AddString("按Power40 60 120排序");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_40_AND_60_120);

	ret=mCmbSort.AddString("按Power60 120 排序");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_60_AND_120);
	
	ret=mCmbSort.AddString("按Power60 120 240 排序");
	mCmbSort.SetItemData(ret,SORT_BY_POWER_60_AND_120_240);
	
	mCmbSort.SetCurSel(0);

	


	mResultListCtrl.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT ); //设置报表风格



	mResultListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 

	mResultListCtrl.InsertColumn( POWER_COLUMN_ID, "顺序ID号", LVCFMT_LEFT, 80 );
	mResultListCtrl.InsertColumn( POWER_COLUMN_STOCK_CODE, "股票代码", LVCFMT_LEFT, 100 );
	mResultListCtrl.InsertColumn( POWER_COLUMN_STOCK_NAME, "股票名称", LVCFMT_LEFT, 100 );
	mResultListCtrl.InsertColumn( POWER_COLUMN_STOCK_BEGIN_DATE, "开始日期", LVCFMT_LEFT, 100 );
	mResultListCtrl.InsertColumn( POWER_COLUMN_STOCK_END_DATE, "结束日期", LVCFMT_LEFT, 100 );
	mResultListCtrl.InsertColumn( POWER_COLUMN_STOCK_POWER_5_PERCENT, "5日能量值", LVCFMT_LEFT, 100 );
	mResultListCtrl.InsertColumn( POWER_COLUMN_STOCK_POWER_10_PERCENT, "10日能量值", LVCFMT_LEFT, 100 );
	mResultListCtrl.InsertColumn( POWER_COLUMN_STOCK_POWER_20_PERCENT, "20日能量值", LVCFMT_LEFT, 100 );
	mResultListCtrl.InsertColumn( POWER_COLUMN_STOCK_POWER_40_PERCENT, "40日能量值", LVCFMT_LEFT, 100 );
	mResultListCtrl.InsertColumn( POWER_COLUMN_STOCK_POWER_60_PERCENT, "60日能量值", LVCFMT_LEFT, 100 );
	mResultListCtrl.InsertColumn( POWER_COLUMN_STOCK_POWER_120_PERCENT, "120日能量值", LVCFMT_LEFT, 100 );
	mResultListCtrl.InsertColumn( POWER_COLUMN_STOCK_POWER_240_PERCENT, "240日能量值", LVCFMT_LEFT, 100 );
	mResultListCtrl.InsertColumn( POWER_COLUMN_STOCK_POWER_DATE_PERCENT, "日期间能量值", LVCFMT_LEFT, 100 );
	

	CMenu* pMenu = new CMenu;
	pMenu->LoadMenu(IDR_MENU_STOCK_RANGE);

	mMenuBtnRange.m_hMenu=pMenu->GetSubMenu(0)->GetSafeHmenu();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CDlgPowerArithResult::Init(void)
{
	CalcPowerArithmeticInfo(mLastDayNums);
	SetTimer(POWER_EVENT_REFRESH_DATA,200,0);

	return TRUE; 
}


static int mStaticSortType=SORT_BY_CUSTOM_DATE;

bool CmpStockPowerArithmeticInfo(const StockPowerPeriodInfo * pInfo1, const StockPowerPeriodInfo * pInfo2)  
{  
	if(SORT_BY_CUSTOM_DATE==mStaticSortType)
	{
		if(pInfo1->f_date_power<pInfo2->f_date_power)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_10)
	{
		if(pInfo1->f_10_power<pInfo2->f_10_power)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_20)
	{
		if(pInfo1->f_20_power<pInfo2->f_20_power)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_40)
	{
		if(pInfo1->f_40_power<pInfo2->f_40_power)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_60)
	{
		if(pInfo1->f_60_power<pInfo2->f_60_power)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_120)
	{
		if(pInfo1->f_120_power<pInfo2->f_120_power)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_240)
	{
		if(pInfo1->f_240_power<pInfo2->f_240_power)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_10_AND_20)
	{
		double f_1_power_10_20=pInfo1->f_10_power+pInfo1->f_20_power;
		double f_2_power_10_20=pInfo2->f_10_power+pInfo2->f_20_power;
		if(f_1_power_10_20<f_2_power_10_20)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_10_AND_20_AND_40)
	{
		double f_1_power_total=pInfo1->f_10_power+pInfo1->f_20_power+pInfo1->f_40_power;
		double f_2_power_total=pInfo2->f_10_power+pInfo2->f_20_power+pInfo2->f_40_power;
		if(f_1_power_total<f_2_power_total)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_10_AND_20_40_60)
	{
		double f_1_power_total=pInfo1->f_10_power+pInfo1->f_20_power+pInfo1->f_40_power+pInfo1->f_60_power;
		double f_2_power_total=pInfo2->f_10_power+pInfo2->f_20_power+pInfo2->f_40_power+pInfo2->f_60_power;
		if(f_1_power_total<f_2_power_total)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_20_AND_40)
	{
		double f_1_power_total=pInfo1->f_20_power+pInfo1->f_40_power;
		double f_2_power_total=pInfo2->f_20_power+pInfo2->f_40_power;
		if(f_1_power_total<f_2_power_total)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_20_AND_40_60_120_240)
	{
		double f_1_power_total=pInfo1->f_20_power+pInfo1->f_40_power+pInfo1->f_60_power+pInfo1->f_120_power+pInfo1->f_240_power;
		double f_2_power_total=pInfo2->f_20_power+pInfo2->f_40_power+pInfo2->f_60_power+pInfo2->f_120_power+pInfo2->f_240_power;
		if(f_1_power_total<f_2_power_total)
			return true;
	}
	
	else if(mStaticSortType==SORT_BY_POWER_40_AND_60)
	{
		double f_1_power_total=pInfo1->f_40_power+pInfo1->f_60_power;
		double f_2_power_total=pInfo2->f_40_power+pInfo2->f_60_power;
		if(f_1_power_total<f_2_power_total)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_40_AND_60_120)
	{
		double f_1_power_total=pInfo1->f_40_power+pInfo1->f_60_power+pInfo1->f_120_power;
		double f_2_power_total=pInfo2->f_40_power+pInfo2->f_60_power+pInfo2->f_120_power;
		if(f_1_power_total<f_2_power_total)
			return true;
	}
	
	else if(mStaticSortType==SORT_BY_POWER_60_AND_120)
	{
		double f_1_power_total=pInfo1->f_60_power+pInfo1->f_120_power;
		double f_2_power_total=pInfo2->f_60_power+pInfo2->f_120_power;
		if(f_1_power_total<f_2_power_total)
			return true;
	}
	else if(mStaticSortType==SORT_BY_POWER_60_AND_120_240)
	{
		double f_1_power_total=pInfo1->f_60_power+pInfo1->f_120_power+pInfo1->f_240_power;
		double f_2_power_total=pInfo2->f_60_power+pInfo2->f_120_power+pInfo2->f_240_power;
		if(f_1_power_total<f_2_power_total)
			return true;
	}
	
	

	return false;
}  

BOOL CDlgPowerArithResult::CalcPowerArithmeticInfo(int mNums)
{

	pExpStockDayTable=StockDataMgr()->GetStockDayTable("SH000001");

	strEndDate=pExpStockDayTable->GetStockDayDateReverseIndex(0);
	strBeginDate=pExpStockDayTable->GetStockDayDateReverseIndex(mLastDayNums);
	CTime mBeginDate=ConverStringToCTime(strBeginDate);
	CTime mEndDate=ConverStringToCTime(strEndDate);
	mBeginDateCtrl.SetTime(&mBeginDate);
	mEndDateCtrl.SetTime(&mEndDate);

	for(int i=0;i<vecStockPowerPeriodInfo.size();i++)
	{
		if(vecStockPowerPeriodInfo[i])
			SAFE_DELETE(vecStockPowerPeriodInfo[i]);
	}
	if(vecStockPowerPeriodInfo.size()>0)
		vecStockPowerPeriodInfo.clear();

	Vec_CString vecStockCodeList;
	vecStockCodeList=StockDataMgr()->GetStockCodeStringList();
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		CStockPowerArithmetic mStockPowerArithmetic(vecStockCodeList[i]);
		StockPowerPeriodInfo * pStockPowerPeriodInfo=NULL;
		if(mStockPowerArithmetic.Init())
		{
			pStockPowerPeriodInfo=mStockPowerArithmetic.NewCalcStockPeriodInfo(mNums);
			if(pStockPowerPeriodInfo!=NULL)
			{
				vecStockPowerPeriodInfo.push_back(pStockPowerPeriodInfo);
			}
		}

	}
	return TRUE;
}

bool CDlgPowerArithResult::RefreshData(void)
{
	CString strConv,strTemp;
	int nRow;
	mResultListCtrl.DeleteAllItems();
	int i=0;
	StockPowerPeriodInfo* pStockPowerPeriodInfo=NULL;
	for(i=0;i<vecStockPowerPeriodInfo.size();i++)
	{
		pStockPowerPeriodInfo=vecStockPowerPeriodInfo[i];
		if(!pStockPowerPeriodInfo)
			continue;
		strConv.Format("%4d",i+1);
		nRow=i;
		if(nRow>=mResultListCtrl.GetItemCount())
			mResultListCtrl.InsertItem(i,strConv);
		else
			mResultListCtrl.SetItemText(nRow, POWER_COLUMN_ID,strConv);

		CString strStockName=StockDataMgr()->GetStockName(pStockPowerPeriodInfo->strStockCode);

		mResultListCtrl.SetItemText(nRow, POWER_COLUMN_STOCK_CODE,pStockPowerPeriodInfo->strStockCode);
		mResultListCtrl.SetItemText(nRow, POWER_COLUMN_STOCK_NAME,strStockName);
		mResultListCtrl.SetItemText(nRow, POWER_COLUMN_STOCK_BEGIN_DATE,pStockPowerPeriodInfo->strBeginDate);
		mResultListCtrl.SetItemText(nRow, POWER_COLUMN_STOCK_END_DATE,pStockPowerPeriodInfo->strEndDate);

		CString strTemp;

		strTemp.Format("%.2f",pStockPowerPeriodInfo->f_5_power);
		mResultListCtrl.SetItemText(nRow, POWER_COLUMN_STOCK_POWER_5_PERCENT,strTemp);

		strTemp.Format("%.2f",pStockPowerPeriodInfo->f_10_power);
		mResultListCtrl.SetItemText(nRow, POWER_COLUMN_STOCK_POWER_10_PERCENT,strTemp);

		strTemp.Format("%.2f",pStockPowerPeriodInfo->f_20_power);
		mResultListCtrl.SetItemText(nRow, POWER_COLUMN_STOCK_POWER_20_PERCENT,strTemp);

		strTemp.Format("%.2f",pStockPowerPeriodInfo->f_40_power);
		mResultListCtrl.SetItemText(nRow, POWER_COLUMN_STOCK_POWER_40_PERCENT,strTemp);

		strTemp.Format("%.2f",pStockPowerPeriodInfo->f_60_power);
		mResultListCtrl.SetItemText(nRow, POWER_COLUMN_STOCK_POWER_60_PERCENT,strTemp);

		strTemp.Format("%.2f",pStockPowerPeriodInfo->f_120_power);
		mResultListCtrl.SetItemText(nRow, POWER_COLUMN_STOCK_POWER_120_PERCENT,strTemp);

		strTemp.Format("%.2f",pStockPowerPeriodInfo->f_240_power);
		mResultListCtrl.SetItemText(nRow, POWER_COLUMN_STOCK_POWER_240_PERCENT,strTemp);

		strTemp.Format("%.2f",pStockPowerPeriodInfo->f_date_power);
		mResultListCtrl.SetItemText(nRow, POWER_COLUMN_STOCK_POWER_DATE_PERCENT,strTemp);
		

		mResultListCtrl.SetItemData(nRow,reinterpret_cast<DWORD_PTR>(pStockPowerPeriodInfo));

		
	}

	if(i<mResultListCtrl.GetItemCount())
	{
		for(int j=i;j<mResultListCtrl.GetItemCount();j++)
			mResultListCtrl.DeleteItem(j);
	}
	return true;
}

void CDlgPowerArithResult::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==POWER_EVENT_REFRESH_DATA)
	{
		RefreshData();
		KillTimer(POWER_EVENT_REFRESH_DATA);
	}

	CDialogEx::OnTimer(nIDEvent);
}

//打开网页
void CDlgPowerArithResult::OnUpdateMenuDfcfWebOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}




void CDlgPowerArithResult::OnMenuDfcfWebOpen()
{
	StockPowerPeriodInfo *  pStockPowerPeriodInfo=NULL;
	for(int  i=0; i<mResultListCtrl.GetItemCount(); i++)
	{
		if( mResultListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			pStockPowerPeriodInfo=reinterpret_cast<StockPowerPeriodInfo *>(mResultListCtrl.GetItemData(i));

			break;
		}
	}

	if(pStockPowerPeriodInfo==NULL)
		return;

	CString strStockCode=pStockPowerPeriodInfo->strStockCode;

	CString strWebUrl;
	strWebUrl.Format("http://quote.eastmoney.com/%s.html",strStockCode);
	ShellExecute(NULL,"open",strWebUrl,NULL,NULL,SW_SHOWNORMAL);
}


void CDlgPowerArithResult::OnRclickListPowerResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if(pNMItemActivate->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU_MONITOR ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );

	}
	*pResult = 0;
}

//重新计算
void CDlgPowerArithResult::OnBnClickedBtnRecalc()
{
	CTime mBeginTime,mEndTime;
	mBeginDateCtrl.GetTime(mBeginTime);
	mEndDateCtrl.GetTime(mEndTime);



	CString strTempBeginDate=pExpStockDayTable->GetNearestStockDayDate(mBeginTime);
	CString strTempEndDate=pExpStockDayTable->GetNearestStockDayDate(mEndTime);


	mBeginTime=ConverStringToCTime(strTempBeginDate);
	mEndTime=ConverStringToCTime(strTempEndDate);

	CTimeSpan span=mEndTime-mBeginTime;

	int iDay=span.GetDays();
	if(iDay<=0)
	{
		AfxMessageBox("开始时间大于等于结束时间");
		return;
	}
	int mBeginPos=pExpStockDayTable->GetNearestStockDayIndex(strTempBeginDate);
	int mEndPos=pExpStockDayTable->GetNearestStockDayIndex(strTempEndDate);

	if((mEndPos-mBeginPos)<5)
	{
		AfxMessageBox("算法不支持小于5个交易日");
		return;
	}

	strBeginDate=strTempBeginDate;
	strEndDate=strTempEndDate;

	mBeginDateCtrl.SetTime(&mBeginTime);
	mEndDateCtrl.SetTime(&mEndTime);


	for(int i=0;i<vecStockPowerPeriodInfo.size();i++)
	{
		if(vecStockPowerPeriodInfo[i])
			SAFE_DELETE(vecStockPowerPeriodInfo[i]);
	}
	if(vecStockPowerPeriodInfo.size()>0)
		vecStockPowerPeriodInfo.clear();

	Vec_CString vecStockCodeList;
	vecStockCodeList=StockDataMgr()->GetStockCodeStringList();
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		CStockPowerArithmetic mStockPowerArithmetic(vecStockCodeList[i]);
		StockPowerPeriodInfo* pStockPowerPeriodInfo=NULL;
		if(mStockPowerArithmetic.Init())
		{
			pStockPowerPeriodInfo=mStockPowerArithmetic.NewCalcStockPeriodInfo(strBeginDate,strEndDate);
			if(pStockPowerPeriodInfo!=NULL)
			{
				vecStockPowerPeriodInfo.push_back(pStockPowerPeriodInfo);
			}
		}

	}
	
	SetTimer(POWER_EVENT_REFRESH_DATA,200,0);


}

//
void CDlgPowerArithResult::OnBnClickedBtnRecalcSort()
{
	int iItem = mCmbSort.GetCurSel();
	if(iItem<0) return ;
	int mSortType=mCmbSort.GetItemData(iItem);
	mStaticSortType=mSortType;
	std::sort(vecStockPowerPeriodInfo.begin(),vecStockPowerPeriodInfo.end(),CmpStockPowerArithmeticInfo);  
	SetTimer(POWER_EVENT_REFRESH_DATA,200,0);
}

//计算能量值
void CDlgPowerArithResult::OnUpdateMenuCalcPower(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CDlgPowerArithResult::OnMenuCalcPower()
{
	StockPowerPeriodInfo *  pStockPowerPeriodInfo=NULL;
	for(int  i=0; i<mResultListCtrl.GetItemCount(); i++)
	{
		if( mResultListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			pStockPowerPeriodInfo=reinterpret_cast<StockPowerPeriodInfo *>(mResultListCtrl.GetItemData(i));

			break;
		}
	}

	if(pStockPowerPeriodInfo==NULL)
		return;

	CString strStockCode=pStockPowerPeriodInfo->strStockCode;

	CDlgCalcPower dlg;
	dlg.SetStockCode(strStockCode);
	dlg.SetBeginDate(strBeginDate);
	dlg.SetEndDate(strEndDate);
	dlg.DoModal();

}

//股性分析
void CDlgPowerArithResult::OnMenuStockAnalysis()
{
	StockPowerPeriodInfo *  pStockPowerPeriodInfo=NULL;
	for(int  i=0; i<mResultListCtrl.GetItemCount(); i++)
	{
		if( mResultListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			pStockPowerPeriodInfo=reinterpret_cast<StockPowerPeriodInfo *>(mResultListCtrl.GetItemData(i));

			break;
		}
	}

	if(pStockPowerPeriodInfo==NULL)
		return;

	CString strStockCode=pStockPowerPeriodInfo->strStockCode;
	CDlgStockNatureAnalysis dlg(strStockCode);
	dlg.SetBeginDate(strBeginDate);
	dlg.SetEndDate(strEndDate);
	dlg.DoModal();


}


void CDlgPowerArithResult::OnUpdateMenuStockAnalysis(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

//危险度计算
void CDlgPowerArithResult::OnUpdateMenuDangerCalc(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CDlgPowerArithResult::OnMenuDangerCalc()
{
	StockPowerPeriodInfo *  pStockPowerPeriodInfo=NULL;
	for(int  i=0; i<mResultListCtrl.GetItemCount(); i++)
	{
		if( mResultListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			pStockPowerPeriodInfo=reinterpret_cast<StockPowerPeriodInfo *>(mResultListCtrl.GetItemData(i));

			break;
		}
	}

	if(pStockPowerPeriodInfo==NULL)
		return;

	CString strStockCode=pStockPowerPeriodInfo->strStockCode;

	CDlgCalcRiskLevel dlg(strStockCode);

	dlg.DoModal();




}

//查找相似能量点
void CDlgPowerArithResult::OnUpdateMenuFindSimilar(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CDlgPowerArithResult::OnMenuFindSimilar()
{
	StockPowerPeriodInfo *  pStockPowerPeriodInfo=NULL;
	for(int  i=0; i<mResultListCtrl.GetItemCount(); i++)
	{
		if( mResultListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			pStockPowerPeriodInfo=reinterpret_cast<StockPowerPeriodInfo *>(mResultListCtrl.GetItemData(i));

			break;
		}
	}

	if(pStockPowerPeriodInfo==NULL)
		return;

	
	CString strStockCode=pStockPowerPeriodInfo->strStockCode;

	//"SH000001" "SH000016" "SH000300""SZ399001""SZ399005" "SZ399006" 

	CStockPowerArithmetic *pStockPowerArithmetic=NULL;
	Vec_CString vecStockCode=StockDataMgr()->GetStockCodeStringList();

	Vec_CString vecTotalResult;
	for(int i=0;i<vecStockCode.size();i++)
	{
		pStockPowerArithmetic=new CStockPowerArithmetic(vecStockCode[i]);
		if(pStockPowerArithmetic->Init())
		{
			Vec_CString vecResult;
			vecResult=pStockPowerArithmetic->FindSimilarStockPowerPeriodInfo(pStockPowerPeriodInfo);

			for(int j=0;j<vecResult.size();j++)
			{
				vecTotalResult.push_back(vecResult[j]);
				//if(vecTotalResult.size()>2)
				//	break;
			}
		}
		SAFE_DELETE(pStockPowerArithmetic);
	}

	if(vecTotalResult.size()>0)
	{
		CString strInfo="";
		for(int j=0;j<vecTotalResult.size();j++)
		{
			strInfo+=vecTotalResult[j];
			if(j<vecTotalResult.size()-1)
				strInfo+="#";
		}
		//AfxMessageBox(strInfo);
		CDlgSimilarResult dlg;
		dlg.SetStockCode(strStockCode);
		dlg.SetSimilarResult(strInfo);
		dlg.SetEndDate(pStockPowerPeriodInfo->strEndDate);
		dlg.DoModal();

	}
	else
		AfxMessageBox("无");

}

CString CDlgPowerArithResult::LoadScript(CString strScriptFile)
{
	CStdioFile scriptFile;
	CString strTotal="";
	CString strLine;
	scriptFile.Open(strScriptFile,CFile::modeRead);
	while(scriptFile.ReadString(strLine))
	{
		strTotal+=strLine;
	}
	scriptFile.Close();
	return strTotal;
}

BOOL  CDlgPowerArithResult::CheckPowerPeriod(StockPowerPeriodInfo *pStockPowerPeriodInfo,CString strScriptFilePath)
{
	if(pStockPowerPeriodInfo==NULL)
		return FALSE;
	double f_5_power,f_10_power,f_20_power,f_40_power,f_60_power,f_120_power,f_240_power;
	f_5_power=pStockPowerPeriodInfo->f_5_power;
	f_10_power=pStockPowerPeriodInfo->f_10_power;
	f_20_power=pStockPowerPeriodInfo->f_20_power;
	f_40_power=pStockPowerPeriodInfo->f_40_power;
	f_60_power=pStockPowerPeriodInfo->f_60_power;
	f_120_power=pStockPowerPeriodInfo->f_120_power;
	f_240_power=pStockPowerPeriodInfo->f_240_power;

	
	/*CString strPath;
	strPath=GetReturnPath();
	strPath+="\\";
	strPath+=POWER_SCRIPT_FILE_NAME;*/

	CString strScript=LoadScript(strScriptFilePath);
	if(strScript=="")
	{
		if(f_10_power>f_20_power  && f_10_power<60.0)	//
		{
			if(f_20_power>f_40_power)
			{
				if(f_40_power>f_60_power)
				{
					if(f_60_power>f_120_power)
					{
						if(f_120_power>f_240_power)
						{
							return TRUE;
						}
					}
				}
			}
		}

		return FALSE;
	}
	DEBUG_TRY
	mScriptControl.AddCode((LPCSTR)strScript);
	CString strCode;
	strCode.Format("checkpower(%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f)",f_5_power,f_10_power,f_20_power,f_40_power,f_60_power,f_120_power,f_240_power);

	VARIANT A = mScriptControl.Eval((LPCSTR)strCode);

	int mResult=A.intVal;

	mScriptControl.Reset();

	//PrintfDebug("%s %d\n",pStockPowerPeriodInfo->strStockCode,mResult);

	if(mResult>0)
		return TRUE;
	else
		return FALSE;
	DEBUG_CATCH2("%s", __FUNCTION__);
	return FALSE;
}

void CDlgPowerArithResult::OnBnClickedBtnFilter()
{

	
	//TCHAR script[MAX_PATH] = L"function output(){return 2;}";
	
	/*CString strScript="function output(a,b){  if(a>b) return 1; else return 0;}";
	mScriptControl.AddCode((LPCSTR)strScript);//
	CString strCode="output(4.0,3.0)";
	VARIANT A = mScriptControl.Eval((LPCSTR)strCode);		//"output()"
	CString strOut;
	strOut.Format("%d",A.intVal);
	AfxMessageBox(strOut);
	*/

	CFileDialog dlg(TRUE,".js",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"js(*.js)|*.js||");
	CString strJsFilePath="";
	char bufJsFilePath[1024]={0};
	if(dlg.DoModal()==IDOK)   
	{
		
		CString strJsFilePath=dlg.GetPathName();
		strcpy(bufJsFilePath,(LPCSTR)strJsFilePath);
	}
	else
		return;

	
	Vec_StockPowerPeriodInfo vecNewStockPowerPeriodInfo;
	StockPowerPeriodInfo *pStockPowerPeriodInfo=NULL;
	for(int i=0;i<vecStockPowerPeriodInfo.size();i++)
	{
		pStockPowerPeriodInfo=vecStockPowerPeriodInfo[i];
		if(!pStockPowerPeriodInfo)
			continue;


		if(CheckPowerPeriod(pStockPowerPeriodInfo,bufJsFilePath))
		{
			vecNewStockPowerPeriodInfo.push_back(pStockPowerPeriodInfo);
		}

		/*
		double f_10_power,f_20_power,f_40_power,f_60_power,f_120_power,f_240_power;
		f_10_power=pStockPowerPeriodInfo->f_10_power;
		f_20_power=pStockPowerPeriodInfo->f_20_power;
		f_40_power=pStockPowerPeriodInfo->f_40_power;
		f_60_power=pStockPowerPeriodInfo->f_60_power;
		f_120_power=pStockPowerPeriodInfo->f_120_power;
		f_240_power=pStockPowerPeriodInfo->f_240_power;
		if(f_10_power>f_20_power  && f_10_power<60.0)	//
		{
			if(f_20_power>f_40_power)
			{
				if(f_40_power>f_60_power)
				{
					if(f_60_power>f_120_power)
					{
						if(f_120_power>f_240_power)
						//if(f_240_power>0.0 && f_120_power>0.0 )
						{
							vecNewStockPowerPeriodInfo.push_back(pStockPowerPeriodInfo);
						}
					}
				}
			}
		}*/

		/*if(f_20_power<-50.0 && f_40_power<-50.0 && f_60_power<-50.0)
		{
			if(f_10_power>-5.0)
			{
				vecNewStockPowerPeriodInfo.push_back(pStockPowerPeriodInfo);
			}
		}*/
	}
	
	if(vecNewStockPowerPeriodInfo.size()>0)
	{
		vecStockPowerPeriodInfo.clear();
		vecStockPowerPeriodInfo.assign(vecNewStockPowerPeriodInfo.begin(),vecNewStockPowerPeriodInfo.end());
		SetTimer(POWER_EVENT_REFRESH_DATA,200,0);
	}
	else
	{
		vecStockPowerPeriodInfo.clear();
		SetTimer(POWER_EVENT_REFRESH_DATA,200,0);
	}

}

BOOL CDlgPowerArithResult::CheckStockRange(StockPowerPeriodInfo *pStockPowerPeriodInfo,int mId)
{
	CStockDayTable *pStockDayTable=NULL;
	CString strStockCode=pStockPowerPeriodInfo->strStockCode;
	CString strDate=pStockPowerPeriodInfo->strEndDate;

	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);

	if(!pStockDayTable)
		return FALSE;

	int mPos=pStockDayTable->GetStockDayIndex(strDate);

	if(mPos==-1)
		return FALSE;

	Vec_StockDayData vecStockDayData;
	pStockDayTable->LockData();
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	pStockDayTable->UnlockData();

	if(mId==ID_MENU_N_RANGE_4)
	{
		if(mPos>=(vecStockDayData.size()-1))
			return FALSE;
	}
	else if(mId==ID_MENU_NN_RANGE_6)
	{
		if(mPos>=(vecStockDayData.size()-2))
			return FALSE;
	}

	CStockDayData *pNowStockDayData=vecStockDayData[mPos];



	


	if(mId==ID_MENU_N_RANGE_4||mId==ID_MENU_N_RANGE_1)
	{
		CStockDayData *pNextStockDayData=vecStockDayData[mPos+1];

		double f_now_close=pNowStockDayData->GetEndPrice();
		double f_next_close=pNextStockDayData->GetEndPrice();

		double f_range=(f_next_close-f_now_close)*100.0/f_now_close;
		if(mId==ID_MENU_N_RANGE_4)
		{
			if(f_range>4.0)
				return TRUE;
		}
		else
		{
			if(f_range>1.0)
				return TRUE;
		}
	}
	else if(mId==ID_MENU_NN_RANGE_6||mId==ID_MENU_NN_RANGE_1)
	{
		CStockDayData *pNextStockDayData=vecStockDayData[mPos+1];
		CStockDayData *pNNStockDayData=vecStockDayData[mPos+2];
		double f_now_close=pNowStockDayData->GetEndPrice();
		double f_next_close=pNextStockDayData->GetEndPrice();
		double f_nn_close=pNNStockDayData->GetEndPrice();
		double f_range=(f_next_close-f_now_close)*100.0/f_now_close;
		double f_n_range=(f_nn_close-f_next_close)*100.0/f_next_close;

		if(mId==ID_MENU_NN_RANGE_6)
		{
			if((f_range+f_n_range)>6.0)
				return TRUE;
		}
		else
		{
			if((f_range+f_n_range)>1.0)
				return TRUE;
		}
		

	}
	else if(mId==ID_MENU_PPP_RANGE_SUB_20)
	{
		CStockDayData *pStockPDayData=vecStockDayData[mPos-1];
		CStockDayData *pStockPPDayData=vecStockDayData[mPos-2];
		CStockDayData *pStockPPPDayData=vecStockDayData[mPos-3];
		double f_now_close=pNowStockDayData->GetEndPrice();
		double f_p_close=pStockPDayData->GetEndPrice();
		double f_pp_close=pStockPPDayData->GetEndPrice();
		double f_ppp_close=pStockPPPDayData->GetEndPrice();

		double f_p_range=(f_now_close-f_p_close)*100.0/f_p_close;
		double f_pp_range=(f_p_close-f_pp_close)*100.0/f_pp_close;
		double f_ppp_range=(f_pp_close-f_ppp_close)*100.0/f_ppp_close;

		double f_range=f_p_range+f_pp_range+f_ppp_range;

		if(f_range<-20.0)
			return TRUE;

	}
	else if(mId==ID_MENU_P20_RANGE_SUB_35)
	{
		
		double f_total_range=0.0;
		CStockDayData *pStockP11DayData=vecStockDayData[mPos-21];
		double f_p_close=pStockP11DayData->GetEndPrice();
		for(int i=20;i>0;i--)
		{
			CStockDayData *pStockP10DayData=vecStockDayData[mPos-i];

			double f_now_close=pStockP10DayData->GetEndPrice();

			double f_range=(f_now_close-f_p_close)*100.0/f_p_close;

			f_total_range+=f_range;

			f_p_close=f_now_close;

		}
		if(f_total_range<-35.0)
			return TRUE;

	}
	
	return FALSE;
}

void CDlgPowerArithResult::OnBnClickedMenubtnRange()
{
	/*if(mMenuBtnRange.m_nMenuResult == ID_MENU_N_RANGE_4)
	{
		

	}
	else if(mMenuBtnRange.m_nMenuResult == ID_MENU_NN_RANGE_6)
	{

	}*/

	Vec_StockPowerPeriodInfo vecNewStockPowerPeriodInfo;
	StockPowerPeriodInfo *pStockPowerPeriodInfo=NULL;
	for(int i=0;i<vecStockPowerPeriodInfo.size();i++)
	{
		pStockPowerPeriodInfo=vecStockPowerPeriodInfo[i];
		if(!pStockPowerPeriodInfo)
			continue;
		if(CheckStockRange(pStockPowerPeriodInfo,mMenuBtnRange.m_nMenuResult))
		{
			vecNewStockPowerPeriodInfo.push_back(pStockPowerPeriodInfo);
		}

	}

	if(vecNewStockPowerPeriodInfo.size()>0)
	{
		vecStockPowerPeriodInfo.clear();
		vecStockPowerPeriodInfo.assign(vecNewStockPowerPeriodInfo.begin(),vecNewStockPowerPeriodInfo.end());
		SetTimer(POWER_EVENT_REFRESH_DATA,200,0);
	}
	else
	{
		vecStockPowerPeriodInfo.clear();
		SetTimer(POWER_EVENT_REFRESH_DATA,200,0);
	}
}

//查看股价分布图
void CDlgPowerArithResult::OnUpdateMenuStockPriceDestribute(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}




void CDlgPowerArithResult::OnMenuStockPriceDestribute()
{

	StockPowerPeriodInfo *  pStockPowerPeriodInfo=NULL;
	for(int  i=0; i<mResultListCtrl.GetItemCount(); i++)
	{
		if( mResultListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			pStockPowerPeriodInfo=reinterpret_cast<StockPowerPeriodInfo *>(mResultListCtrl.GetItemData(i));

			break;
		}
	}

	if(pStockPowerPeriodInfo==NULL)
		return;

	CString strStockCode=pStockPowerPeriodInfo->strStockCode;


	CTime mEndTime;
	mEndDateCtrl.GetTime(mEndTime);
	CString strEndDate=ConverCTimeToString(mEndTime);
	CStockProfitLossData* pStockProfitLossData=NULL;
	pStockProfitLossData=CStockProfitLossArithmetic::CalcProfitLossData(strStockCode,strEndDate,240,50);

	CDlgStockPriceDestribute dlg;
	dlg.SetStockProfitLossData(pStockProfitLossData);
	dlg.DoModal();
}

//不变计算
void CDlgPowerArithResult::OnBnClickedBtnCalcNoChange()
{
	CTime mBeginTime,mEndTime;
	mBeginDateCtrl.GetTime(mBeginTime);
	mEndDateCtrl.GetTime(mEndTime);



	CString strTempBeginDate=pExpStockDayTable->GetNearestStockDayDate(mBeginTime);
	CString strTempEndDate=pExpStockDayTable->GetNearestStockDayDate(mEndTime);


	mBeginTime=ConverStringToCTime(strTempBeginDate);
	mEndTime=ConverStringToCTime(strTempEndDate);

	CTimeSpan span=mEndTime-mBeginTime;

	int iDay=span.GetDays();
	if(iDay<=0)
	{
		AfxMessageBox("开始时间大于等于结束时间");
		return;
	}
	int mBeginPos=pExpStockDayTable->GetNearestStockDayIndex(strTempBeginDate);
	int mEndPos=pExpStockDayTable->GetNearestStockDayIndex(strTempEndDate);

	if((mEndPos-mBeginPos)<5)
	{
		AfxMessageBox("算法不支持小于5个交易日");
		return;
	}

	strBeginDate=strTempBeginDate;
	strEndDate=strTempEndDate;

	mBeginDateCtrl.SetTime(&mBeginTime);
	mEndDateCtrl.SetTime(&mEndTime);

	Vec_CString vecStockCodeList;
	for(int i=0;i<vecStockPowerPeriodInfo.size();i++)
	{
		if(vecStockPowerPeriodInfo[i])
			vecStockCodeList.push_back(vecStockPowerPeriodInfo[i]->strStockCode);
	}
	
	CFreeVector<Vec_StockPowerPeriodInfo>::freeVector(vecStockPowerPeriodInfo);
	
	
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		CStockPowerArithmetic mStockPowerArithmetic(vecStockCodeList[i]);
		StockPowerPeriodInfo* pStockPowerPeriodInfo=NULL;
		if(mStockPowerArithmetic.Init())
		{
			pStockPowerPeriodInfo=mStockPowerArithmetic.NewCalcStockPeriodInfo(strBeginDate,strEndDate);
			if(pStockPowerPeriodInfo!=NULL)
			{
				vecStockPowerPeriodInfo.push_back(pStockPowerPeriodInfo);
			}
		}

	}

	SetTimer(POWER_EVENT_REFRESH_DATA,200,0);

}
