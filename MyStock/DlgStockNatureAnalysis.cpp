// DlgStockNatureAnalysis.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgStockNatureAnalysis.h"
#include "afxdialogex.h"
#include "StockDataMgr.h"
#include "Convert.h"
#include "CommonMacro.h"
#include "T_FreeVector.h"
#include "StockNatureAnalysisArithmetic.h"
// CDlgStockNatureAnalysis 对话框

IMPLEMENT_DYNAMIC(CDlgStockNatureAnalysis, CDialogEx)

CDlgStockNatureAnalysis::CDlgStockNatureAnalysis(CString strCode,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgStockNatureAnalysis::IDD, pParent)
{
	strStockCode=strCode;
	strExpStockCode="SH000001";
	pExpStockDayTable=NULL;
	pStockDayTable=NULL;
	strBeginDate="";
	strEndDate="";
	
}

CDlgStockNatureAnalysis::~CDlgStockNatureAnalysis()
{
}

void CDlgStockNatureAnalysis::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN, mDateTimeBegin);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, mDateTimeEnd);
	DDX_Control(pDX, IDC_LIST_STOCK, mStockListCtrl);
	DDX_Control(pDX, IDC_COMBO_EXP_INCREASE, mCmbExpInCrease);
	DDX_Control(pDX, IDC_LIST_GATHER_INFO, mListBoxGatherInfo);
}


BEGIN_MESSAGE_MAP(CDlgStockNatureAnalysis, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_ANALYSIS, &CDlgStockNatureAnalysis::OnBnClickedBtnAnalysis)
END_MESSAGE_MAP()


// CDlgStockNatureAnalysis 消息处理程序


BOOL CDlgStockNatureAnalysis::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if(strBeginDate==""||strEndDate=="")
	{
		return FALSE;
	}
	
	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);
	pExpStockDayTable=StockDataMgr()->GetStockDayTable(strExpStockCode);

	mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDate);
	mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1||mEndPos==-1)
		return FALSE;

	mExpBeginPos=pExpStockDayTable->GetNearestStockDayIndex(strBeginDate);
	mExpEndPos=pExpStockDayTable->GetNearestStockDayIndex(strEndDate);
	if(mExpBeginPos==-1||mExpEndPos==-1)
		return FALSE;
	mStockListCtrl.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT ); //设置报表风格
	mStockListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 


	mStockListCtrl.InsertColumn( ANALY_COLUMN_STOCK_DATE, "顺序ID号", LVCFMT_LEFT, 70 );
	mStockListCtrl.InsertColumn( ANALY_COLUMN_STOCK_DATE, "日期", LVCFMT_LEFT, 85 );
	mStockListCtrl.InsertColumn( ANALY_COLUMN_STOCK_END_PRICE, "股票结束价格", LVCFMT_LEFT, 85 );
	mStockListCtrl.InsertColumn( ANALY_COLUMN_STOCK_INCREASE, "股票涨幅", LVCFMT_LEFT, 75 );
	mStockListCtrl.InsertColumn( ANALY_COLUMN_STOCK_PREAVE3DAY_INCREASE, "前3日平均涨幅", LVCFMT_LEFT, 100 );
	mStockListCtrl.InsertColumn( ANALY_COLUMN_STOCK_PREAVE3DAY_VOLUME_INCREASE, "Pre3DayVIC", LVCFMT_LEFT, 100 );
	mStockListCtrl.InsertColumn( ANALY_COLUMN_STOCK_VOLUME_INCREASE, "成交额涨幅", LVCFMT_LEFT, 85 );
	mStockListCtrl.InsertColumn( ANALY_COLUMN_STOCK_EXP_END_PRICE, "指数结束点数", LVCFMT_LEFT, 95 );
	mStockListCtrl.InsertColumn( ANALY_COLUMN_STOCK_EXP_INCREASE, "指数涨幅", LVCFMT_LEFT, 85 );
	mStockListCtrl.InsertColumn( ANALY_COLUMN_STOCK_EXP_PREAVE3DAY_INCREASE, "指数前3日平均涨幅", LVCFMT_LEFT, 115 );
	mStockListCtrl.InsertColumn( ANALY_COLUMN_STOCK_EXP_VOLUME_INCREASE, "指数成交额涨幅", LVCFMT_LEFT, 105 );
	mStockListCtrl.InsertColumn( ANALY_COLUMN_STOCK_EXP_PREAVE3DAY_VOLUME_INCREASE, "ExpPre3DayVIC", LVCFMT_LEFT, 105 );

	
	CTime mBeginDate=ConverStringToCTime(strBeginDate);
	CTime mEndDate=ConverStringToCTime(strEndDate);
	mDateTimeBegin.SetTime(&mBeginDate);
	mDateTimeEnd.SetTime(&mEndDate);

	CString strTitle;
	strTitle.Format("股票 %s %s 指数  %s  %s ",strStockCode,StockDataMgr()->GetStockName(strStockCode),strExpStockCode,StockDataMgr()->GetStockName(strExpStockCode));

	GetDlgItem(IDC_STATIC_STOCK)->SetWindowText(strTitle);


	mCmbExpInCrease.ResetContent();
	int ret=mCmbExpInCrease.AddString("全部");
	mCmbExpInCrease.SetItemData(ret,EXP_FILTER_ALL);
	ret=mCmbExpInCrease.AddString("指数大涨");
	mCmbExpInCrease.SetItemData(ret,EXP_FILTER_BIG_RISE);
	ret=mCmbExpInCrease.AddString("指数中涨");
	mCmbExpInCrease.SetItemData(ret,EXP_FILTER_MIDDLE_RISE);
	ret=mCmbExpInCrease.AddString("指数小涨");
	mCmbExpInCrease.SetItemData(ret,EXP_FILTER_SMALL_RISE);
	ret=mCmbExpInCrease.AddString("指数毫涨");
	mCmbExpInCrease.SetItemData(ret,EXP_FILTER_MILL_RISE);
	ret=mCmbExpInCrease.AddString("指数微涨或微跌");
	mCmbExpInCrease.SetItemData(ret,EXP_FILTER_MIRO_RISE_FALL);
	ret=mCmbExpInCrease.AddString("指数毫跌");
	mCmbExpInCrease.SetItemData(ret,EXP_FILTER_MILL_FALL);
	ret=mCmbExpInCrease.AddString("指数小跌");
	mCmbExpInCrease.SetItemData(ret,EXP_FILTER_SMALL_FALL);
	ret=mCmbExpInCrease.AddString("指数中跌");
	mCmbExpInCrease.SetItemData(ret,EXP_FILTER_MIDDLE_FALL);
	ret=mCmbExpInCrease.AddString("指数大跌");
	mCmbExpInCrease.SetItemData(ret,EXP_FILTER_BIG_FALL);
	mCmbExpInCrease.SetCurSel(0);


	CalcStockAnalysisInfoList();

	CStockNatureAnalysisArthmetic  mCStockNatureAnalysisArthmetic(strStockCode);
	mCStockNatureAnalysisArthmetic.SetBeginDate(strBeginDate);
	mCStockNatureAnalysisArthmetic.SetEndDate(strEndDate);
	if(mCStockNatureAnalysisArthmetic.Init())
	{
		Vec_CString vecResult=mCStockNatureAnalysisArthmetic.BuildAnalysisResultListString();
		mListBoxGatherInfo.ResetContent();

		for(int i=0;i<vecResult.size();i++)
		{
			mListBoxGatherInfo.AddString(vecResult[i]);
		}
	}

	SetTimer(ANALY_EVENT_REFRESH_DATA,200,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

bool CDlgStockNatureAnalysis::RefreshData(void)
{
	CString strConv,strTemp;
	int nRow;
	StockAnalysisInfo *pStockAnalysisInfo=NULL;
	int i=0;
	mStockListCtrl.DeleteAllItems();
	for(i=0;i<vecStockAnalysisInfo.size();i++)
	{
		pStockAnalysisInfo=vecStockAnalysisInfo[i];
		if(!pStockAnalysisInfo)
			continue;
	
		strConv.Format("%4d",i+1);
		nRow=i;
		if(nRow>=mStockListCtrl.GetItemCount())
			mStockListCtrl.InsertItem(i,strConv);
		else
			mStockListCtrl.SetItemText(nRow, ANALY_COLUMN_ID,strConv);

		
		mStockListCtrl.SetItemText(nRow, ANALY_COLUMN_STOCK_DATE,pStockAnalysisInfo->strStockDate);
		
		CString strTemp;
		strTemp.Format("%.2f",pStockAnalysisInfo->f_stock_end_price);
		mStockListCtrl.SetItemText(nRow, ANALY_COLUMN_STOCK_END_PRICE,strTemp);

		strTemp.Format("%.2f",pStockAnalysisInfo->f_stock_increase);
		mStockListCtrl.SetItemText(nRow, ANALY_COLUMN_STOCK_INCREASE,strTemp);

		strTemp.Format("%.2f",pStockAnalysisInfo->f_stock_pre3ave_increase);
		mStockListCtrl.SetItemText(nRow, ANALY_COLUMN_STOCK_PREAVE3DAY_INCREASE,strTemp);

		strTemp.Format("%.2f",pStockAnalysisInfo->f_stock_volume_increase);
		mStockListCtrl.SetItemText(nRow, ANALY_COLUMN_STOCK_VOLUME_INCREASE,strTemp);

		strTemp.Format("%.2f",pStockAnalysisInfo->f_stock_pre3ave_volume_increase);
		mStockListCtrl.SetItemText(nRow, ANALY_COLUMN_STOCK_PREAVE3DAY_VOLUME_INCREASE,strTemp);


		strTemp.Format("%.2f",pStockAnalysisInfo->f_exp_end_price);
		mStockListCtrl.SetItemText(nRow, ANALY_COLUMN_STOCK_EXP_END_PRICE,strTemp);

		strTemp.Format("%.2f",pStockAnalysisInfo->f_exp_increase);
		mStockListCtrl.SetItemText(nRow, ANALY_COLUMN_STOCK_EXP_INCREASE,strTemp);

		strTemp.Format("%.2f",pStockAnalysisInfo->f_exp_pre3ave_increase);
		mStockListCtrl.SetItemText(nRow, ANALY_COLUMN_STOCK_EXP_PREAVE3DAY_INCREASE,strTemp);


		strTemp.Format("%.2f",pStockAnalysisInfo->f_exp_volume_increase);
		mStockListCtrl.SetItemText(nRow, ANALY_COLUMN_STOCK_EXP_VOLUME_INCREASE,strTemp);

		strTemp.Format("%.2f",pStockAnalysisInfo->f_exp_pre3ave_volume_increase);
		mStockListCtrl.SetItemText(nRow, ANALY_COLUMN_STOCK_EXP_PREAVE3DAY_VOLUME_INCREASE,strTemp);


		mStockListCtrl.SetItemData(nRow,reinterpret_cast<DWORD>(pStockAnalysisInfo));

	}
	
	if(i<mStockListCtrl.GetItemCount())
	{
		for(int j=i;j<mStockListCtrl.GetItemCount();j++)
			mStockListCtrl.DeleteItem(j);
	}

	return true;
}

BOOL CDlgStockNatureAnalysis::CalcStockAnalysisInfoList(void)
{

	/*for(int i=0;i<vecStockAnalysisInfo.size();i++)
	{
		SAFE_DELETE(vecStockAnalysisInfo[i]);
	}
	vecStockAnalysisInfo.clear();*/

	CFreeVector<Vec_StockAnalysisInfo>::freeVector(vecStockAnalysisInfo);
	
	vecStockAnalysisInfo.clear();


	CStockDayData * pStockDayData=NULL;
	CStockDayData * pExpStockDayData=NULL;




	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=pStockDayTable->GetStockDayDataByIndex(i);
		pExpStockDayData=pExpStockDayTable->GetStockDayDataByIndex(i-mBeginPos+mExpBeginPos);

		if(!pStockDayData || !pExpStockDayData)
			continue;

		float f_end_price_increase=pStockDayTable->GetStockEndPriceIncrease(pStockDayData->GetDate());

		if(f_end_price_increase==INVALID_INCREASE)
			continue;

		float f_exp_end_price_increase=pExpStockDayTable->GetStockEndPriceIncrease(pStockDayData->GetDate());

		if(f_exp_end_price_increase==INVALID_INCREASE)
			continue;

		if(JudgeExpIncrease(f_exp_end_price_increase))
		{
			StockAnalysisInfo *pStockAnalysisInfo=new StockAnalysisInfo();

			pStockAnalysisInfo->strStockCode=strStockCode;
			pStockAnalysisInfo->strStockDate=pStockDayData->GetDate();
			pStockAnalysisInfo->f_exp_end_price=pExpStockDayData->GetEndPrice();
			pStockAnalysisInfo->f_exp_increase=f_exp_end_price_increase;
			pStockAnalysisInfo->f_exp_pre3ave_increase=pExpStockDayTable->GetStockEndPricePreAveIncrease(pStockDayData->GetDate(),3);
			pStockAnalysisInfo->f_exp_volume_increase=pExpStockDayTable->GetStockVolumeIncrease(pStockDayData->GetDate());
			pStockAnalysisInfo->f_exp_pre3ave_volume_increase=pExpStockDayTable->GetStockVolumePreAveIncrease(pStockDayData->GetDate(),3);
			pStockAnalysisInfo->f_stock_end_price=pStockDayData->GetEndPrice();
			pStockAnalysisInfo->f_stock_increase=f_end_price_increase;
			pStockAnalysisInfo->f_stock_pre3ave_increase=pStockDayTable->GetStockEndPricePreAveIncrease(pStockDayData->GetDate(),3);
			pStockAnalysisInfo->f_stock_volume_increase=pStockDayTable->GetStockVolumeIncrease(pStockDayData->GetDate());
			pStockAnalysisInfo->f_stock_pre3ave_volume_increase=pStockDayTable->GetStockVolumePreAveIncrease(pStockDayData->GetDate(),3);
			vecStockAnalysisInfo.push_back(pStockAnalysisInfo);
		}
		
	}

	


	return TRUE;
}

BOOL CDlgStockNatureAnalysis::JudgeExpIncrease(float f_exp_increase)
{
	int iItem = mCmbExpInCrease.GetCurSel();
	if(iItem<0) return FALSE;
	int mExpInCreaseMode=mCmbExpInCrease.GetItemData(iItem);

	BOOL bOk=FALSE;

	switch(mExpInCreaseMode)
	{
	case EXP_FILTER_ALL:
		bOk=TRUE;
		break;

	case EXP_FILTER_BIG_RISE:
		if(f_exp_increase>=3.0)
			bOk=TRUE;
		break;
	case EXP_FILTER_MIDDLE_RISE:
		if(f_exp_increase<3.0 && f_exp_increase>=1.5)
			bOk=TRUE;
		break;

	case EXP_FILTER_SMALL_RISE:
		if(f_exp_increase<1.5 && f_exp_increase>=0.5)
			bOk=TRUE;
		break;

	case EXP_FILTER_MILL_RISE:
		if(f_exp_increase<0.5 && f_exp_increase>=0.2)
			bOk=TRUE;
		break;
	case EXP_FILTER_MIRO_RISE_FALL:

		if(f_exp_increase<0.2 && f_exp_increase>-0.2)
			bOk=TRUE;

		break;
	case EXP_FILTER_MILL_FALL:

		if(f_exp_increase<=-0.2 && f_exp_increase>-0.5)
			bOk=TRUE;


		break;
	case EXP_FILTER_SMALL_FALL:
		if(f_exp_increase<=-0.5 && f_exp_increase>-1.5)
			bOk=TRUE;
		break;
	case EXP_FILTER_MIDDLE_FALL:
		if(f_exp_increase<=-1.5 && f_exp_increase>-3.0)
			bOk=TRUE;
		break;
	case EXP_FILTER_BIG_FALL:
		if(f_exp_increase<=-3.0)
			bOk=TRUE;
		break;


	}

	return bOk;
}

void CDlgStockNatureAnalysis::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==ANALY_EVENT_REFRESH_DATA)
	{
		RefreshData();

		KillTimer(ANALY_EVENT_REFRESH_DATA);
	}

	CDialogEx::OnTimer(nIDEvent);
}

//分析
void CDlgStockNatureAnalysis::OnBnClickedBtnAnalysis()
{

	CTime mBeginTime,mEndTime;
	mDateTimeBegin.GetTime(mBeginTime);
	mDateTimeEnd.GetTime(mEndTime);



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
	int mTempBeginPos=pExpStockDayTable->GetNearestStockDayIndex(strTempBeginDate);
	int mTempEndPos=pExpStockDayTable->GetNearestStockDayIndex(strTempEndDate);

	if((mTempEndPos-mTempBeginPos)<30)
	{
		AfxMessageBox("不支持小于30个交易日");
		return;
	}

	strBeginDate=strTempBeginDate;
	strEndDate=strTempEndDate;


	mDateTimeBegin.SetTime(&mBeginTime);
	mDateTimeEnd.SetTime(&mEndTime);

	mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDate);
	mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1||mEndPos==-1)
	{
		AfxMessageBox("日期错误");
		return ;
	}
	mExpBeginPos=pExpStockDayTable->GetNearestStockDayIndex(strBeginDate);
	mExpEndPos=pExpStockDayTable->GetNearestStockDayIndex(strEndDate);
	if(mExpBeginPos==-1||mExpEndPos==-1)
	{
		AfxMessageBox("日期错误");
		return ;
	}

	CalcStockAnalysisInfoList();

	CStockNatureAnalysisArthmetic  mCStockNatureAnalysisArthmetic(strStockCode);
	mCStockNatureAnalysisArthmetic.SetBeginDate(strBeginDate);
	mCStockNatureAnalysisArthmetic.SetEndDate(strEndDate);
	if(mCStockNatureAnalysisArthmetic.Init())
	{
		Vec_CString vecResult=mCStockNatureAnalysisArthmetic.BuildAnalysisResultListString();
		mListBoxGatherInfo.ResetContent();

		for(int i=0;i<vecResult.size();i++)
		{
			mListBoxGatherInfo.AddString(vecResult[i]);
		}
	}


	SetTimer(ANALY_EVENT_REFRESH_DATA,200,0);
}
