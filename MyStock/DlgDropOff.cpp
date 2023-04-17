// DlgDropOff.cpp : 实现文件
//

#include "stdafx.h"
#include <map>
#include <vector>
#include "MyStock.h"
#include "DlgDropOff.h"
#include "afxdialogex.h"
#include "Convert.h"
#include "SystemMgr.h"
#include "StockRSIArithmetic.h"
#include "DlgStockChip.h"
#include "DlgRsiFilter.h"
#include "StockKDJArithmetic.h"

#include "DlgKdjPara.h"
#include "DlgM5M10Para.h"
#include "DlgSFSel.h"
#include <algorithm>
//#include "TanAngleAlg.h"
#include "TriAngleAlg.h"

#include "DlgTanAngle.h"
#include "DlgTanAnglePara.h"
#include "DlgDays.h"
#include "MulTanAngleAlg.h"
#include "MulTanAngleAss.h"
#include "RsiReverseAlg.h"
#include "SingleTanAngleAlg.h"
#include "DlgCalcu.h"
#include "LongAveGroupAlg.h"
#include "StepStepAlg.h"
#include "LimitUpAlg.h"
#include "ThreeLowFilterAlg.h"
#include "DlgTanPara2.h"
#include "KLineFilterAlg.h"
#include "CommonMacro.h"
#include "DlgKLineModeSel.h"
#include "BollFilterAlg.h"
#include "GeneralAnalyze.h"
#include "TimePriceMapAlg.h"

#include "CDlgGlobalInfo.h"
#include "DlgStockChart.h"

#include "DlgIndustrySel.h"
#include "DlgIndustryInfo.h"

#include "IndustryDataMgr.h"
#include "ConceptDataMgr.h"

#include "DlgBackFlow.h"

#include "DlgAngleDetail.h"

#include "StockCRAtithmetic.h"
#include "StockMFIArithmetic.h"
// CDlgDropOff 对话框

IMPLEMENT_DYNAMIC(CDlgDropOff, CDialogEx)

CDlgDropOff::CDlgDropOff(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDropOff::IDD, pParent)
{
	
}

CDlgDropOff::~CDlgDropOff()
{
}

void CDlgDropOff::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ITEM, mListCtrlItem);
	DDX_Control(pDX, IDC_EDIT_FMUL, mEditFMul);
	DDX_Control(pDX, IDC_SPIN1, mSpin);
	DDX_Control(pDX, IDC_EDIT_MIN_NUMS, mEditMinNums);
	DDX_Control(pDX, IDC_SPIN_MIN_NUMS, mSpinMinNums);
	DDX_Control(pDX, IDC_EDIT_DAYNUMS, mEditDayNums);
	DDX_Control(pDX, IDC_SPIN_DAY_NUMS, mSpinDayNums);
	DDX_Control(pDX, IDC_EDIT_AVE_FMUL, mEditAveMul);
	DDX_Control(pDX, IDC_SPIN_AVE, mSpinAve);
	DDX_Control(pDX, IDC_CHECK_AVE, mCheckAve);
	DDX_Control(pDX, IDC_CHECK_MAX, mCheckMax);
	DDX_Control(pDX, IDC_CHECK_AVE_10_DAY, mCheckAve10Day);
	DDX_Control(pDX, IDC_CHECK_DATE, mCheckDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, mDataTimeDropOff);
	DDX_Control(pDX, IDC_CHECK_AVE_5_DAY, mCheckAve5Day);
	DDX_Control(pDX, IDC_EDIT_MAX_DAYS, mEditMaxDays);
	DDX_Control(pDX, IDC_SPIN_MAX_DAYS, mSpinMaxDays);
	DDX_Control(pDX, IDC_CHECK_RESERVE_FILTER, mCheckReserveFilter);
	DDX_Control(pDX, IDCMENU_BTN_DROP_OFF, mFunButtonMenu);
	DDX_Control(pDX, IDC_CHECK_MERGE_FILTER, mCheckMergeFilter);
	DDX_Control(pDX, IDC_LIST_SECOND, mSecondListCtrlItem);
}


BEGIN_MESSAGE_MAP(CDlgDropOff, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_BEGIN, &CDlgDropOff::OnBnClickedBtnBegin)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_DATE, &CDlgDropOff::OnClickedCheckDate)
	ON_BN_CLICKED(IDC_BTN_EXPER_FILTER, &CDlgDropOff::OnBnClickedBtnExperFilter)
	ON_BN_CLICKED(IDC_BTN_EXPER_FILTER2, &CDlgDropOff::OnBnClickedBtnExperFilter2)
	ON_BN_CLICKED(IDC_BTN_EXPER_FILTER3, &CDlgDropOff::OnBnClickedBtnExperFilter3)
	ON_BN_CLICKED(IDC_BTN_EXPER_FILTER4, &CDlgDropOff::OnBnClickedBtnExperFilter4)
	ON_BN_CLICKED(IDC_BTN_EXPER_FILTER5, &CDlgDropOff::OnBnClickedBtnExperFilter5)
	ON_BN_CLICKED(IDCMENU_BTN_DROP_OFF, &CDlgDropOff::OnBnClickedBtnDropOff)
	ON_BN_CLICKED(IDC_BTN_CLEAR_LEFT, &CDlgDropOff::OnBnClickedBtnClearLeft)
	ON_BN_CLICKED(IDC_BTN_CLEAR_RIGHT, &CDlgDropOff::OnBnClickedBtnClearRight)
	ON_BN_CLICKED(IDC_BTN_ADD_TO_RIGHT, &CDlgDropOff::OnBnClickedBtnAddToRight)
	ON_BN_CLICKED(IDC_BTN_ADD_TO_LEFT, &CDlgDropOff::OnBnClickedBtnAddToLeft)
	ON_BN_CLICKED(IDC_BTN_SHOW_HIDE, &CDlgDropOff::OnBnClickedBtnShowHide)
	ON_BN_CLICKED(IDC_BTN_KDJ_FILTER, &CDlgDropOff::OnBnClickedBtnKdjFilter)
	ON_BN_CLICKED(IDC_BTN_3M_UP, &CDlgDropOff::OnBnClickedBtn3mUp)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ITEM, &CDlgDropOff::OnRclickListItem)
	ON_COMMAND(IDR_MENU_TO_RIGHT, &CDlgDropOff::OnMenuToRight)
	ON_BN_CLICKED(IDC_BTN_NEXT_GROUP, &CDlgDropOff::OnBnClickedBtnNextGroup)
	//ON_BN_CLICKED(IDC_BTN_ADD_CALCU, &CDlgDropOff::OnBnClickedBtnAddCalcu)
	//ON_BN_CLICKED(IDC_BTN_CALCU, &CDlgDropOff::OnBnClickedBtnCalcu)
	ON_BN_CLICKED(IDC_BTN_ADD_TO_LEFTXOR, &CDlgDropOff::OnBnClickedBtnAddToLeftxor)
	ON_COMMAND(IDR_MENU_ANGLE_DETAIL, &CDlgDropOff::OnMenuAngleDetail)
	ON_BN_CLICKED(IDC_BTN_ADD_TO_LEFTXOR2, &CDlgDropOff::OnBnClickedBtnAddToLeftxor2)
	ON_BN_CLICKED(IDC_BTN_ADD_TO_LEFTXOR3, &CDlgDropOff::OnBnClickedBtnAddToLeftxor3)
	ON_COMMAND(IDR_MENU_NEXT_GROWP, &CDlgDropOff::OnMenuNextGrowp)
	ON_COMMAND(IDR_MENU_NEXT_GROWP_3, &CDlgDropOff::OnMenuNextGrowp3)
	ON_COMMAND(IDR_MENU_NEXT_GROWP_8, &CDlgDropOff::OnMenuNextGrowp8)
	ON_COMMAND(IDR_MENU_SHELL_WEB, &CDlgDropOff::OnMenuShellWeb)
	ON_COMMAND(IDR_MENU_K_LINE_ANALYZE, &CDlgDropOff::OnMenuKLineAnalyze)
	ON_BN_CLICKED(IDC_BTN_BACK_FLOW, &CDlgDropOff::OnBnClickedBtnBackFlow)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgDropOff 消息处理程序

static volatile bool bDropOffStockProc=false;
BOOL CDlgDropOff::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mListCtrlItem.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT ); //设置报表风格


	mListCtrlItem.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 
	mListCtrlItem.InsertColumn( DROPOFF_COLUMN_ID, "顺序ID号", LVCFMT_LEFT, 80 );
	mListCtrlItem.InsertColumn( DROPOFF_COLUMN_STOCK_CODE, "股票代码", LVCFMT_LEFT, 90 );

	mListCtrlItem.InsertColumn( DROPOFF_COLUMN_STOCK_NAME, "股票名称", LVCFMT_LEFT, 90 );
	mListCtrlItem.InsertColumn( DROPOFF_COLUMN_MAX_MULTIPLE, "20日Tan/5日低量数", LVCFMT_LEFT, 130 ); //最大倍数/5日低量数
	mListCtrlItem.InsertColumn( DROPOFF_COLUMN_AVE_MULTIPLE, "10日Tan/量价值", LVCFMT_LEFT, 110 );		//平均倍数/量价值
	mListCtrlItem.InsertColumn( DROPOFF_COLUMN_MAX_DATE, "5日Tan/当前rsi", LVCFMT_LEFT, 70 );
	mListCtrlItem.InsertColumn( DROPOFF_COLUMN_MIN_DATE, "Tan量价/最小rsi", LVCFMT_LEFT, 70 );
	mListCtrlItem.InsertColumn( DROPOFF_COLUMN_MAX_PASS_DAY, "60日Tan/触发系数", LVCFMT_LEFT, 130 );
	mListCtrlItem.InsertColumn( DROPOFF_COLUMN_FILTERNUMS, "10>20/过滤", LVCFMT_LEFT, 45 );
	mListCtrlItem.InsertColumn( DROPOFF_COLUMN_SPECNUMS, "60>20/指定", LVCFMT_LEFT, 40 );
	mListCtrlItem.InsertColumn( DROPOFF_COLUMN_INFO, "杂项", LVCFMT_LEFT, 40 );

	mSecondListCtrlItem.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 
	mSecondListCtrlItem.InsertColumn( DROPOFF2_COLUMN_ID, "顺序ID号", LVCFMT_LEFT, 80 );
	mSecondListCtrlItem.InsertColumn( DROPOFF2_COLUMN_STOCK_CODE, "股票代码", LVCFMT_LEFT, 95 );
	mSecondListCtrlItem.InsertColumn( DROPOFF2_COLUMN_STOCK_NAME, "股票名称", LVCFMT_LEFT, 95 );
	mSecondListCtrlItem.InsertColumn( DROPOFF2_COLUMN_SPECNUMS, "指定次数", LVCFMT_LEFT, 95 );
	

	bDropOffStockProc=false;

	fDivMulti=20.0;
	mSpin.SetBuddy(&mEditFMul);
	mSpin.SetRange(8, 30);
	mSpin.SetPos(20);

	fAveDivMulti=3.0;
	mSpinAve.SetBuddy(&mEditAveMul);
	mSpinAve.SetRange(20, 150);
	mSpinAve.SetPos(30);

	mMinNums=3;
	mSpinMinNums.SetBuddy(&mEditMinNums);
	mSpinMinNums.SetRange(2, 15);
	mSpinMinNums.SetPos(3);

	mDayNums=100;
	mSpinDayNums.SetBuddy(&mEditDayNums);
	mSpinDayNums.SetRange(40, 150);
	mSpinDayNums.SetPos(100);

	mMaxDayNums=30;
	mSpinMaxDays.SetBuddy(&mEditMaxDays);
	mSpinMaxDays.SetRange(20, 70);
	mSpinMaxDays.SetPos(30);

	bUseAve=false;
	bUseMax=true;
	bUseAve10Day=false;
	bUseAve5Day=false;
	mCheckAve.SetCheck(0);
	mCheckMax.SetCheck(1);
	mCheckAve10Day.SetCheck(0);
	mCheckAve5Day.SetCheck(0);

	bReserveFilter=false;
	mCheckReserveFilter.SetCheck(0);

	bMergeFilter=false;
	mCheckMergeFilter.SetCheck(0);

	bUsePreDate=false;
	mCheckDate.SetCheck(0);
	mDataTimeDropOff.ShowWindow(FALSE);
	vecStockCodeList=StockDataMgr()->GetStockCodeList();

	bExperFilter4=FALSE;
	mMaxParaMode=MAX_PARA_MODE_STRICT;

	CStockDayTable *pExpStockDayTable=StockDataMgr()->GetStockDayTable("SH000001");
	CStockDayData *pStockDayData=pExpStockDayTable->GetLastStockDayData();

	CTime mDate=ConverStringToCTime(pStockDayData->GetDate());
	mDataTimeDropOff.SetTime(&mDate);

	
	RECT mRect;		
	GetWindowRect(&mRect);
	int x=mRect.left;
	int y=mRect.top;
	int width=mRect.right-x;
	int height=mRect.bottom-y;
	MoveWindow(x,y,width-395,height);
	bExtWinHide=TRUE;
	GetDlgItem(IDC_BTN_SHOW_HIDE)->SetWindowText("展开");


	pFunMenu=new CMenu;
	pFunMenu->LoadMenu(IDR_MENU_DROP_OFF);
	mFunButtonMenu.m_hMenu = pFunMenu->GetSubMenu(0)->GetSafeHmenu();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL  CDlgDropOff::CalcDropOffStockDayData(CStockDayTable*pStockDayTable,CString  strStockCode,CString  strStockName,Vec_StockDayData vecStockDayData )
{

	try
	{
		int mSize=vecStockDayData.size();

		float  fMaxTotalPrice=0.0;		//最大成交金额
		float  fMinTotalPrice=99999999999956.00;		//最小成交金额
		int    mMaxTotalPriceIndex=-1;
		int    mMinTotalPriceIndex=-1;
		CStockDayData *pStockDayData=NULL;
		CStockDayData *pMaxTotalPriceStockDayData=NULL;		//最大成交金额
		CStockDayData *pMinTotalPriceStockDayData=NULL;		//最小成交金额

		
		float  fMinPrice=999999999999.0;		//最小价格
		int    mMinPriceIndex=-1;	//最小价格Index
		for(int i=0;i<mSize;i++)
		{
			pStockDayData=vecStockDayData[i];
			if(pStockDayData->GetMinPrice()<fMinPrice)
			{
				fMinPrice=pStockDayData->GetMinPrice();
				mMinPriceIndex=i;
			}
		}



		float  fAveTotalPrice=0.0;
		float fTempTotal=0.0;
		for(int i=0;i<mSize;i++)
		{
			pStockDayData=vecStockDayData[i];
			fTempTotal+=pStockDayData->GetTotalPrice();
		}
		fAveTotalPrice=fTempTotal/mSize;


		for(int i=0;i<mSize;i++)
		{
			pStockDayData=vecStockDayData[i];
			if(pStockDayData->GetTotalPrice()>fMaxTotalPrice)
			{
				fMaxTotalPrice=pStockDayData->GetTotalPrice();
				pMaxTotalPriceStockDayData=pStockDayData;
				mMaxTotalPriceIndex=i;
			}

		}
		
		BOOL bPreAve5=FALSE;		//最大值前面有连续5个值成交量小于最大值fDivMulti倍
		int mCalcNums=0;
		int mTotalCalcNums=0;
		for(int i=0;i<mMaxTotalPriceIndex;i++)
		{
			pStockDayData=vecStockDayData[i];
			float f_pre_div=pMaxTotalPriceStockDayData->GetTotalPrice()/pStockDayData->GetTotalPrice();
			
			if(f_pre_div>fDivMulti)
			{
				mCalcNums++;
			}
			else
			{
				if(mCalcNums>=3)
					mTotalCalcNums++;
				mCalcNums=0;
			}
		}

		if(mTotalCalcNums>=3)
		{
			bPreAve5=TRUE;
			
		}


		int mMaxDifDayNums=mSize-mMaxTotalPriceIndex;
		bool bDo=false;
		if(bUseMax)
		{
			if(mMaxDifDayNums<=mMaxDayNums) // 30
				bDo=true;
		}
		else if(bUseAve||bUseAve10Day||bUseAve5Day)
		{
			bDo=true;

		}
		if(bDo)
		{
			if(bUseAve10Day||bUseAve5Day)
			{
				if(bUseAve10Day)
				{
					float f_10_total=0.0;
					for(int i=mSize-10;i<mSize;i++)
					{
						pStockDayData=vecStockDayData[i];
						f_10_total+=pStockDayData->GetTotalPrice();
					}
					fMinTotalPrice=f_10_total/10.0;
					pMinTotalPriceStockDayData=vecStockDayData[mSize-1];
					mMinTotalPriceIndex=mSize-1;

				}
				else
				{
					float f_5_max=0.0;
					for(int i=mSize-5;i<mSize;i++)
					{
						pStockDayData=vecStockDayData[i];
						if(f_5_max<pStockDayData->GetTotalPrice())
							f_5_max=pStockDayData->GetTotalPrice();
					}
					
					fMinTotalPrice=f_5_max;
					pMinTotalPriceStockDayData=vecStockDayData[mSize-1];
					mMinTotalPriceIndex=mSize-1;

				}
				

			}
			else
			{
				for(int i=mMaxTotalPriceIndex;i<mSize;i++)
				{
					pStockDayData=vecStockDayData[i];
					if(pStockDayData->GetTotalPrice()<fMinTotalPrice)
					{
						fMinTotalPrice=pStockDayData->GetTotalPrice();
						pMinTotalPriceStockDayData=pStockDayData;
						mMinTotalPriceIndex=i;
					}

				}
			}
			

			if(fMinTotalPrice>10.0)
			{
				float fmaxdiv=0.0;
				float favediv=0.0;
				favediv=fAveTotalPrice/fMinTotalPrice;
				fmaxdiv=fMaxTotalPrice/fMinTotalPrice;
				bool bOk=false;
				if(bUseAve&&!bUseMax)
				{
					if(favediv>=fAveDivMulti) 
						bOk=true;
				}
				else if(!bUseAve&&bUseMax)
				{
					if(fmaxdiv>=fDivMulti) 
					{
						//float  fMinPrice=999999999999.0;		//最小价格
						//int    mMinPriceIndex=-1;	//最小价格Index
						//mMaxTotalPriceIndex=i;
						if(mMaxParaMode==MAX_PARA_MODE_LOOSE)
						{

							float fSecondMinPrice=999999999999.0;	//最大成交量到现在过程中的最小价格
							int    mSecondMinPriceIndex=-1;			//最大成交量到现在过程中的最小价格Index
							for(int i=mMaxTotalPriceIndex;i<mSize;i++)
							{
								pStockDayData=vecStockDayData[i];
								if(pStockDayData->GetMinPrice()<fSecondMinPrice)
								{
									fSecondMinPrice=pStockDayData->GetMinPrice();
									mSecondMinPriceIndex=i;
								}
							}

							float f_min_secondmin_pert=fMinPrice/fSecondMinPrice;		//最小价格/最大成交量到现在过程中的最小价格
							if(f_min_secondmin_pert>0.99 && bPreAve5 &&(favediv>2.2))
							{
									bOk=true;
									printf("%s  mTotalCalcNums=%d\n",strStockCode,mTotalCalcNums);
							}
						}
						else
						{

							bOk=true;
						}

							
					}
				}
				else
				{
					bool bTemoOk1=false;
					bool bTemoOk2=false;
					
					if(favediv>=fAveDivMulti) 
						bTemoOk1=true;
					if(fmaxdiv>=fDivMulti) 
						bTemoOk2=true;
					if(bTemoOk2&&bTemoOk1)
						bOk=true;
				}
					
				if(bOk) 
				{
					//printf("fdiv=%f stockcode=%s  maxday=%s  minday=%s\n",fdiv,strStockCode,pMaxTotalPriceStockDayData->GetDate(),\
					//	pMinTotalPriceStockDayData->GetDate());
					int mNums=mSize-mMinTotalPriceIndex;
					if(mNums<mMinNums)
					{
						DropOffData *pDropOffData=new DropOffData();
						pDropOffData->strStockCode=strStockCode;
						pDropOffData->strStockName=strStockName;
						pDropOffData->fMaxMultiple=fmaxdiv;
						pDropOffData->fAveMultiple=favediv;
						pDropOffData->strMaxDate=pMaxTotalPriceStockDayData->GetDate();
						pDropOffData->strMinDate=pMinTotalPriceStockDayData->GetDate();
						pDropOffData->mMaxValuePassDay=mMaxDifDayNums;
						pDropOffData->fDownTotalRang=-1.0;
						pDropOffData->mFilterNums=0;
						pDropOffData->mSpecNums=0;
						pDropOffData->strInfo="";
						vecDropOffData.push_back(pDropOffData);
					}
					

				}
			}


		}

	}
	catch (...)
	{
		printf("catch %s\n",strStockCode);
	}
	
	

	return true;
}


BOOL CDlgDropOff:: CalcDropOffStock(void)
{
	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		try
		{
			pStockCode=vecStockCodeList[i];
			pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
			int size=pStockDayTable->GetStockDayDataListSize();
			Vec_StockDayData vecStockDayData;
			if(bUsePreDate)
			{
				CTime mDropOffTime;
				mDataTimeDropOff.GetTime(mDropOffTime);
				CString strDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
				int mDateIndex=pStockDayTable->GetNearestStockDayIndex(strDate);
				if(mDateIndex>mDayNums)
				{
					vecStockDayData=pStockDayTable->GetStockDayDataListBwIndex(mDateIndex-mDayNums,mDateIndex);
					CalcDropOffStockDayData(pStockDayTable,pStockCode->strStockCode,pStockCode->strStockName,vecStockDayData);
				}	
			}
			else
			{
				vecStockDayData=pStockDayTable->GetStockDayDataListBwIndex(size-1-mDayNums,size-1);
				CalcDropOffStockDayData(pStockDayTable,pStockCode->strStockCode,pStockCode->strStockName,vecStockDayData);
			}

		}
		catch(...)
		{

			printf("catch--%s i=%d\n",pStockCode->strStockCode,i);
		}
		
		
	}

	


	return true;
}

BOOL  CDlgDropOff::FakeFilter(void)
{
	if(!SystemMgr()->IsFakeMode())
	{
		return FALSE;
	}
#ifdef CHECK_USER
	try
	{
		Vec_DropOffData  vecDropOffDataBk;
		vecDropOffDataBk=vecDropOffData;

		vecDropOffData.clear();

		int mStockSize=vecStockCodeList.size();

		DropOffData *pDropOffData=NULL;
		CString strStockCode;
		CString strStockName;
		int mSecond=0;
		for(int i=0;i<vecDropOffDataBk.size();i++)
		{
			strStockCode=vecDropOffDataBk[i]->strStockCode;

			int index=StockDataMgr()->GetStockDayTableIndex(strStockCode);
			//printf("index=%d code=%s\n",index,strStockCode);
			if(index>=(mStockSize-18))
				index--;
			else
				index+=17;
			strStockCode=vecStockCodeList[index]->strStockCode;
			strStockName=vecStockCodeList[index]->strStockName;

			pDropOffData=vecDropOffDataBk[i];
			pDropOffData->strStockCode=strStockCode;
			pDropOffData->strStockName=strStockName;
			vecDropOffData.push_back(pDropOffData);

		}
	}
	catch(...)
	{
		printf("catch--7\n");

	}
#endif
	


	return TRUE;
}

BOOL CDlgDropOff:: FilterByReserve(void)
{
	if(!bReserveFilter)
		return FALSE;

	Vec_DropOffData  vecDropOffDataBk;
	vecDropOffDataBk=vecDropOffData;

	vecDropOffData.clear();

	DropOffData *pDropOffData=NULL;
	DropOffData *pDropOffData_Reserve=NULL;
	for(int i=0;i<vecDropOffDataBk.size();i++)
	{
		pDropOffData=vecDropOffDataBk[i];
		for(int j=0;j<vecDropOffData_Reserve.size();j++)
		{
			pDropOffData_Reserve=vecDropOffData_Reserve[j];
			if(pDropOffData_Reserve->strStockCode==pDropOffData->strStockCode)
			{
				pDropOffData_Reserve->mFilterNums++;
				pDropOffData->mFilterNums=pDropOffData_Reserve->mFilterNums;
				vecDropOffData.push_back(pDropOffData);
				break;
			}
		}


	}

	return TRUE;
}

BOOL  CDlgDropOff::FilterByMerge(void)
{
	if(!bMergeFilter)
		return FALSE;

	

	DropOffData *pDropOffData_Merge=NULL;
	DropOffData *pDropOffData=NULL;
	

	for(int i=0;i<vecDropOffData_Merge.size();i++)
	{
		pDropOffData_Merge=vecDropOffData_Merge[i];

		BOOL bFound=FALSE;
		for(int j=0;j<vecDropOffData.size();j++)
		{
			pDropOffData=vecDropOffData[j];
			if(pDropOffData_Merge->strStockCode==pDropOffData->strStockCode)
			{
				bFound=TRUE;
				pDropOffData_Merge->mFilterNums++;
				pDropOffData->mFilterNums=pDropOffData_Merge->mFilterNums;
				break;
			}
		}
		if(!bFound)
			vecDropOffData.push_back(pDropOffData_Merge);
	}


	return TRUE;

}

static UINT  CalcDropOffStockProc(LPVOID pParam)
{

	CDlgDropOff *pDlgDropOff=(CDlgDropOff *)pParam;
	bDropOffStockProc=true;
	try
	{
		pDlgDropOff->CalcDropOffStock();
		pDlgDropOff->FakeFilter();
		pDlgDropOff->FilterByReserve();
		pDlgDropOff->FilterByMerge();
	}
	catch(...)
	{

		printf("CalcDropOffStockProc catch--0\n");
	}
	bDropOffStockProc=false;

	
	
	pDlgDropOff->SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return 0;
}
void CDlgDropOff::OnBnClickedBtnBegin()
{
	if(bDropOffStockProc)
	{
		AfxMessageBox("上次还在运行中");
		return;
	}
	CString strVal;
	mEditFMul.GetWindowText(strVal);
	int temp=atoi(strVal);
	fDivMulti=temp;

	mEditAveMul.GetWindowText(strVal);
	temp=atoi(strVal);
	fAveDivMulti=temp/10.0;
		

	mEditMinNums.GetWindowText(strVal);
	temp=atoi(strVal);
	mMinNums=temp;

	mEditDayNums.GetWindowText(strVal);
	temp=atoi(strVal);
	mDayNums=temp;

	mEditMaxDays.GetWindowText(strVal);
	temp=atoi(strVal);
	mMaxDayNums=temp;


	bUseAve=mCheckAve.GetCheck();
	bUseMax=mCheckMax.GetCheck();
	bUseAve10Day=mCheckAve10Day.GetCheck();
	bUseAve5Day=mCheckAve5Day.GetCheck();
	if(!bUseAve&&!bUseMax)
	{
		AfxMessageBox("平均和最大必须选择一个");
		return;
	}

	if(bUseAve10Day&&bUseAve5Day)
	{

		AfxMessageBox("5日平均和10日平均不能同时选");
		return;
	}

	bReserveFilter=mCheckReserveFilter.GetCheck();

	bMergeFilter=mCheckMergeFilter.GetCheck();

	if(bReserveFilter&&bMergeFilter)
	{

		AfxMessageBox("合并和保留两种不能同时选");
		return;
	}

	if(bReserveFilter)
	{
		vecDropOffData_Reserve.clear();
		vecDropOffData_Reserve=vecDropOffData;
	}

	if(bMergeFilter)
	{
		vecDropOffData_Merge.clear();
		vecDropOffData_Merge=vecDropOffData;
	}
	

	vecDropOffData.clear();
	//pThread=AfxBeginThread(CalcDropOffStockProc,(LPVOID)this, THREAD_PRIORITY_TIME_CRITICAL,0,0,NULL);
	
	CalcDropOffStockProc(this);
}

BOOL CDlgDropOff::RefreshData(void)
{
	CString strConv,strTemp;
	int nRow;
	mListCtrlItem.DeleteAllItems();
	int i=0;

	DropOffData *pDropOffData=NULL;
	for(i=0;i<vecDropOffData.size();i++)
	{
		pDropOffData=vecDropOffData[i];
		if(!pDropOffData)
			continue;
		strConv.Format("%4d",i+1);
		nRow=i;
		if(nRow>=mListCtrlItem.GetItemCount())
			mListCtrlItem.InsertItem(i,strConv);
		else
			mListCtrlItem.SetItemText(nRow, DROPOFF_COLUMN_ID,strConv);

		mListCtrlItem.SetItemText(nRow, DROPOFF_COLUMN_STOCK_CODE,pDropOffData->strStockCode);
		mListCtrlItem.SetItemText(nRow, DROPOFF_COLUMN_STOCK_NAME,pDropOffData->strStockName);

		CString strTemp;

		double f_div=pDropOffData->fMaxMultiple;
		
		strTemp.Format("%.2f",f_div);
		mListCtrlItem.SetItemText(nRow, DROPOFF_COLUMN_MAX_MULTIPLE,strTemp);

		f_div=pDropOffData->fAveMultiple;

		strTemp.Format("%.2f",f_div);
		mListCtrlItem.SetItemText(nRow, DROPOFF_COLUMN_AVE_MULTIPLE,strTemp);

		mListCtrlItem.SetItemText(nRow, DROPOFF_COLUMN_MAX_DATE,pDropOffData->strMaxDate);
		mListCtrlItem.SetItemText(nRow, DROPOFF_COLUMN_MIN_DATE,pDropOffData->strMinDate);

		strTemp.Format("%d",pDropOffData->mMaxValuePassDay);
		mListCtrlItem.SetItemText(nRow, DROPOFF_COLUMN_MAX_PASS_DAY,strTemp);
		
		
		strTemp.Format("%d",pDropOffData->mFilterNums);
		mListCtrlItem.SetItemText(nRow, DROPOFF_COLUMN_FILTERNUMS,strTemp);

		strTemp.Format("%d",pDropOffData->mSpecNums);
		mListCtrlItem.SetItemText(nRow, DROPOFF_COLUMN_SPECNUMS,strTemp);
		
		mListCtrlItem.SetItemText(nRow, DROPOFF_COLUMN_INFO,pDropOffData->strInfo);

		mListCtrlItem.SetItemData(nRow,reinterpret_cast<DWORD_PTR>(pDropOffData));
	}

	if(i<mListCtrlItem.GetItemCount())
	{
		for(int j=i;j<mListCtrlItem.GetItemCount();j++)
			mListCtrlItem.DeleteItem(j);
	}

	return true;
}


void CDlgDropOff::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(DROPOFF_EVENT_REFRESH_DATA==nIDEvent)
	{
		KillTimer(DROPOFF_EVENT_REFRESH_DATA);
		RefreshData();
	}
	else if(DROPOFF_EVENT_REFRESH_DATA_SECOND==nIDEvent)
	{

		KillTimer(DROPOFF_EVENT_REFRESH_DATA_SECOND);
		RefreshData_Second();
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CDlgDropOff::OnClickedCheckDate()
{
	if(mCheckDate.GetCheck())
	{
		mDataTimeDropOff.ShowWindow(TRUE);
		bUsePreDate=true;
	}
	else
	{
		mDataTimeDropOff.ShowWindow(FALSE);
		bUsePreDate=false;
	}
}

//经验过滤
void CDlgDropOff::OnBnClickedBtnExperFilter()
{

#if 0
	bUseAve=mCheckAve.GetCheck();
	bUseAve5Day=mCheckAve5Day.GetCheck();
	if((!bUseAve)||(!bUseAve5Day))
	{
		AfxMessageBox("经验过滤只适用于5日平均和使用平均");
		return;
	}
	if(mDayNums>55||mDayNums<45)
	{

		AfxMessageBox("经验过滤只适用于最近天数在45-55间");
		return;
	}
	Vec_DropOffData  vecDropOffData2;
	vecDropOffData2=vecDropOffData;
	vecDropOffData.clear();
	DropOffData *pDropOffData=NULL;
	for(int i=0;i<vecDropOffData2.size();i++)
	{
		pDropOffData=vecDropOffData2[i];
		if(pDropOffData)
		{

			if(pDropOffData->fMaxMultiple>10.0&&pDropOffData->fMaxMultiple<15.0)
			{
				if(pDropOffData->fAveMultiple>3.0&&pDropOffData->fAveMultiple<4.0)
				{
					if(pDropOffData->mMaxValuePassDay>=28&&pDropOffData->mMaxValuePassDay<=43)
					{
						vecDropOffData.push_back(pDropOffData);

					}
					
				}

			}
		}

	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
#endif

	if(mMaxParaMode==MAX_PARA_MODE_LOOSE)
		mMaxParaMode=MAX_PARA_MODE_STRICT;
	else
		mMaxParaMode=MAX_PARA_MODE_LOOSE;

	if(mMaxParaMode==MAX_PARA_MODE_LOOSE)
	{
		fDivMulti=10.0;
		mSpin.SetPos(10);

		mMaxDayNums=45;
		mSpinMaxDays.SetPos(45);
		this->SetWindowText("缩量查找法 最大法宽松模式");
	}
	else
	{
		fDivMulti=20.0;
		mSpin.SetPos(20);

		mMaxDayNums=30;
		mSpinMaxDays.SetPos(30);
		this->SetWindowText("缩量查找法 最大法严格模式");

	}




}


static UINT  CalcRsiStockProc(LPVOID pParam)
{

	CDlgDropOff *pDlgDropOff=(CDlgDropOff *)pParam;
	
	try
	{
		pDlgDropOff->CalcRsiStock();
		pDlgDropOff->FilterByReserve();
		pDlgDropOff->FilterByMerge();
	}
	catch(...)
	{

		printf("CalcRsiStockProc catch--0\n");
	}
	
	pDlgDropOff->SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return 0;
}


void CDlgDropOff::OnBnClickedBtnExperFilter2()
{

#if 0
	if((bUseAve)||(!bUseMax))
	{
		AfxMessageBox("经验过滤2只适用于使用最大值");
		return;
	}

	if(mDayNums>110||mDayNums<90)
	{

		AfxMessageBox("经验过滤2只适用于最近天数在90-110间");
		return;
	}
	Vec_DropOffData  vecDropOffData2;
	vecDropOffData2=vecDropOffData;
	vecDropOffData.clear();
	DropOffData *pDropOffData=NULL;
	for(int i=0;i<vecDropOffData2.size();i++)
	{
		pDropOffData=vecDropOffData2[i];
		if(pDropOffData)
		{

			if(pDropOffData->fMaxMultiple>30.0&&pDropOffData->fMaxMultiple<40.0)
			{
				if(pDropOffData->fAveMultiple>3.5&&pDropOffData->fAveMultiple<4.5)
				{
					if(pDropOffData->mMaxValuePassDay>=24&&pDropOffData->mMaxValuePassDay<=35)
					{
						vecDropOffData.push_back(pDropOffData);

					}

				}

			}
		}

	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
#endif
	CDlgRsiFilter dlg;
	if(dlg.DoModal()==IDOK)
	{
		f_rsi1_low=dlg.GetRsi1Low();
		f_rsi1_high=dlg.GetRsi1High();
		f_rsi2_low=dlg.GetRsi2Low();
		f_rsi2_high=dlg.GetRsi2High();
		f_rsi3_low=dlg.GetRsi3Low();
		f_rsi3_high=dlg.GetRsi3High();
		m_risi_dist=dlg.GetRsiDist();

		bReserveFilter=mCheckReserveFilter.GetCheck();
		bMergeFilter=mCheckMergeFilter.GetCheck();

		if(bReserveFilter&&bMergeFilter)
		{
			AfxMessageBox("不能同时两种过滤");
			return;
		}

		if(bReserveFilter)
		{
			vecDropOffData_Reserve.clear();
			vecDropOffData_Reserve=vecDropOffData;
		}

		if(bMergeFilter)
		{

			vecDropOffData_Merge.clear();
			vecDropOffData_Merge=vecDropOffData;
		}

		vecDropOffData.clear();
		//pThread=AfxBeginThread(CalcRsiStockProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
		CalcRsiStockProc(this);
	}
	
}


BOOL CDlgDropOff::CalcRsiStock(void)
{
	

	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		try
		{
			pStockCode=vecStockCodeList[i];
			pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);

			if(bUsePreDate)
			{
				CTime mDropOffTime;
				mDataTimeDropOff.GetTime(mDropOffTime);
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}
			else
			{
				CTime mDropOffTime=CTime::GetCurrentTime();
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}
			printf("check %s\n",pStockCode->strStockCode);
			
			CStockRSIData* pStockRSIData=NULL;
			pStockRSIData=CStockRSIArithmetic::CalcRSIData(pStockCode->strStockCode,strNowDate,125,K_LINE_DAY,6,12,24); 
			int size=pStockRSIData->vec_rsi_1_value.size();
			double sel_rsi_1=0.0;
			double sel_rsi_2=0.0;
			double sel_rsi_3=0.0;
			if(size>m_risi_dist)
			{
				int mMeetNums=0;
				int mFirstMeetIndex=0;
				for(int j=size-m_risi_dist;j<size;j++)
				{
					double rsi_1=pStockRSIData->vec_rsi_1_value[j];
					double rsi_2=pStockRSIData->vec_rsi_2_value[j];
					double rsi_3=pStockRSIData->vec_rsi_3_value[j];
					
					if(rsi_1<=f_rsi1_high&&rsi_1>=f_rsi1_low)
					{
						printf(" %s rsi1 ok\n",pStockCode->strStockCode);
						if(rsi_2>=f_rsi2_low&&rsi_2<=f_rsi2_high) //
						{
							printf(" %s rsi2 ok\n",pStockCode->strStockCode);
							if(rsi_3>=f_rsi3_low&&rsi_3<=f_rsi3_high)
							{
								printf(" %s rsi3 ok\n",pStockCode->strStockCode);
								if(!mMeetNums)
									mFirstMeetIndex=j;
								mMeetNums++;
								sel_rsi_1=rsi_1;
								sel_rsi_2=rsi_2;
								sel_rsi_3=sel_rsi_3;
							}

						}
						
					}

				}


				if(mMeetNums>0)
				{
					DropOffData *pDropOffData=new DropOffData();
					pDropOffData->strStockCode=pStockCode->strStockCode;
					pDropOffData->strStockName=pStockCode->strStockName;
					pDropOffData->fMaxMultiple=sel_rsi_1;
					pDropOffData->fAveMultiple=sel_rsi_2;
					pDropOffData->strMaxDate=strNowDate;
					pDropOffData->strMinDate=strNowDate;
					pDropOffData->mMaxValuePassDay=size-mFirstMeetIndex;
					pDropOffData->fDownTotalRang=sel_rsi_3;
					vecDropOffData.push_back(pDropOffData);

				}
			}
			


		}
		catch(...)
		{

		}
	}
	return TRUE;
}


static UINT  CalcChipStockProc(LPVOID pParam)
{
	CDlgDropOff *pDlgDropOff;
	pDlgDropOff=(CDlgDropOff *)pParam;

	pDlgDropOff->DoCalcStockChip();
	pDlgDropOff->FilterByReserve();
	pDlgDropOff->FilterByMerge();
	return 0;
}



void CDlgDropOff::OnBnClickedBtnExperFilter3()
{
#if 0
	bool bOk=false;
	if((bUseAve)&&(!bUseMax)&&bUseAve10Day)
	{
		bOk=true;
	}

	if(!bOk)
	{
		AfxMessageBox("经验过滤3只适用于使用10日平均值");
		return;
	}
	if(mDayNums>110||mDayNums<90)
	{

		AfxMessageBox("经验过滤3只适用于最近天数在90-110间");
		return;
	}

	Vec_DropOffData  vecDropOffData2;
	vecDropOffData2=vecDropOffData;
	vecDropOffData.clear();
	DropOffData *pDropOffData=NULL;
	for(int i=0;i<vecDropOffData2.size();i++)
	{
		pDropOffData=vecDropOffData2[i];
		if(pDropOffData)
		{

			if(pDropOffData->fMaxMultiple>13.5&&pDropOffData->fMaxMultiple<18.5)
			{
				if(pDropOffData->fAveMultiple>3.0&&pDropOffData->fAveMultiple<4.6)
				{
					vecDropOffData.push_back(pDropOffData);
				}

			}
		}

	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
#endif
	CDlgStockChip dlg;
	
	if(dlg.DoModal()==IDOK)
	{
		fStockChipLow=dlg.GetStockChipLow();
		fStockChipHigh=dlg.GetStockChipHight();
		mStockChipConti=dlg.GetStockChipConti();
		bReserveFilter=mCheckReserveFilter.GetCheck();
		bMergeFilter=mCheckMergeFilter.GetCheck();
		if(bReserveFilter&&bMergeFilter)
		{
			AfxMessageBox("不能同时两种过滤");
			return;
		}

		if(bReserveFilter)
		{
			vecDropOffData_Reserve.clear();
			vecDropOffData_Reserve=vecDropOffData;
		}

		if(bMergeFilter)
		{

			vecDropOffData_Merge.clear();
			vecDropOffData_Merge=vecDropOffData;
		}

		

		vecDropOffData.clear();
		//pThread=AfxBeginThread(CalcChipStockProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
		CalcChipStockProc(this);
	}


	
}

BOOL CDlgDropOff::DoCalcStockChip(void)
{
	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		try
		{
			pStockCode=vecStockCodeList[i];
			pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
			
			if(bUsePreDate)
			{
				CTime mDropOffTime;
				mDataTimeDropOff.GetTime(mDropOffTime);
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}
			else
			{
				CTime mDropOffTime=CTime::GetCurrentTime();
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}
			CString strDate=strNowDate;
			int mNums=0;
			for(int j=0;j<mStockChipConti;j++)
			{
				if(j>0)
					strDate=pStockDayTable->GetStockDayDatePreOfIndex(strNowDate,j);
				CStockProfitLossData* pStockProfitLossData=NULL;
				pStockProfitLossData=CStockProfitLossArithmetic::CalcProfitLossData(pStockCode->strStockCode,strDate,120,75); //50//120 240
				if(pStockProfitLossData)
				{
					pStockProfitLossData->CalcVolumeSectionRange();
					double f_down_total_rang=AnalysisStockProfitLossData(pStockProfitLossData);

					if(f_down_total_rang<fStockChipHigh&&f_down_total_rang>=fStockChipLow)
					{
						mNums++;
					}


				}

			}
			printf("%s  %d\n",pStockCode->strStockCode,mNums);
			if(mNums>=mStockChipConti)
			{

				DropOffData *pDropOffData=new DropOffData();
				pDropOffData->strStockCode=pStockCode->strStockCode;
				pDropOffData->strStockName=pStockCode->strStockName;
				pDropOffData->fMaxMultiple=mNums;
				pDropOffData->fAveMultiple=mNums;
				pDropOffData->strMaxDate=strNowDate;
				pDropOffData->strMinDate=strNowDate;
				pDropOffData->mMaxValuePassDay=mNums;
				pDropOffData->fDownTotalRang=-1.0;
				vecDropOffData.push_back(pDropOffData);
			}
			

		}
		catch(...)
		{
			printf("catch %s \n",pStockCode->strStockCode);
		}
	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
}


static UINT  RunFilter4Proc(LPVOID pParam)
{
	CDlgDropOff *pDlgDropOff;
	pDlgDropOff=(CDlgDropOff *)pParam;

	pDlgDropOff->DoFilter4();

	return 0;
}

double CDlgDropOff::AnalysisStockProfitLossData(CStockProfitLossData* pStockProfitLossData)
{
	CString strNowDate=pStockProfitLossData->strEndDate;
	CString strStockCode=pStockProfitLossData->strStockCode;
	CStockDayTable *pStockDayTable=NULL;

	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);


	if(!pStockDayTable)
		return 100.0;

	int mPos=pStockDayTable->GetStockDayIndex(strNowDate);

	if(mPos<0)
		return 100.0;

	Vec_StockDayData vecStockDayData;
	pStockDayTable->LockData();
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	pStockDayTable->UnlockData();


	CStockDayData *pStockDayData=NULL;

	pStockDayData=vecStockDayData[mPos];

	double f_now_price=pStockDayData->GetEndPrice();

	double f_min_price=99999999.0;

	double f_max_price=-99999999.0;

	for(int i=0;i<pStockProfitLossData->vec_profitloss.size();i++)
	{
		if(f_min_price>pStockProfitLossData->vec_profitloss[i]->fMinPrice)
			f_min_price=pStockProfitLossData->vec_profitloss[i]->fMinPrice;

		if(f_max_price<pStockProfitLossData->vec_profitloss[i]->fMaxPrice)
			f_max_price=pStockProfitLossData->vec_profitloss[i]->fMaxPrice;

	}

	double f_up_range=f_max_price-f_now_price;
	double f_down_rang=f_now_price-f_min_price;


	double f_up_per_range=f_up_range/50.0;

	double f_down_per_range=f_down_rang/50.0;

	//up
	CString strUpTotalInfo="";
	long long mUpTotalVolume=0;
	for(int i=0;i<50;i++)
	{

		double f_low_price,f_high_price;
		f_low_price=f_now_price+(i*f_up_per_range);
		f_high_price=f_now_price+((i+1)*f_up_per_range);

		long long mVolume=pStockProfitLossData->GetStockVolumeBwPrice(f_low_price,f_high_price);
		mUpTotalVolume+=mVolume;
		double f_volume_range=((double)mVolume*100.0)/(double)pStockProfitLossData->mTotalStockVolume;
		CString strTemp;
		strTemp.Format("%.2f",f_volume_range);
		CString strInfo;
		strInfo.Format("目前股价上方%d--%d 价格 %.2f --%.2f 间 有 %ld 股 占 总股本 ",i,i+1,f_low_price,f_high_price,mVolume);

		strUpTotalInfo+=strInfo;
		strUpTotalInfo+=strTemp;
		strUpTotalInfo+="\r\n";
		
	}
	

	CString strDownTotalInfo="";
	long long mDownTotalVolume=0;
	for(int i=0;i<50;i++)
	{
		double f_low_price,f_high_price;
		f_high_price=f_now_price-(i*f_down_per_range);
		f_low_price=f_now_price-((i+1)*f_down_per_range);

		long long mVolume=pStockProfitLossData->GetStockVolumeBwPrice(f_low_price,f_high_price);
		mDownTotalVolume+=mVolume;
		double f_volume_range=((double)mVolume*100.0)/(double)pStockProfitLossData->mTotalStockVolume;
		CString strTemp;
		strTemp.Format("%.2f",f_volume_range);
		CString strInfo;
		strInfo.Format("目前股价下方%d--%d 价格 %.2f --%.2f 间 有 %ld 股 占 总股本 ",i,i+1,f_low_price,f_high_price,mVolume);

		strDownTotalInfo+=strInfo;
		strDownTotalInfo+=strTemp;
		strDownTotalInfo+="\r\n";

	}

	

	CString strStockInfo;
	CString strStockName=StockDataMgr()->GetStockName(strStockCode);

	double f_up_total_rang=((double)mUpTotalVolume*100.0)/(double)(mUpTotalVolume+mDownTotalVolume);

	double f_down_total_rang=((double)mDownTotalVolume*100.0)/(double)(mUpTotalVolume+mDownTotalVolume);

	//strStockInfo.Format("%s   %s  总股本 %I64d  现股价  %.2f  高于占 %.2f  低于占 %.2f ",strStockCode,strStockName,pStockProfitLossData->mTotalStockVolume,f_now_price,f_up_total_rang,f_down_total_rang);

	//printf("%s\n",strStockInfo);
	return f_down_total_rang;
}

BOOL CDlgDropOff:: DoFilter4(void)
{
	bExperFilter4=TRUE;
	DropOffData *pDropOffData=NULL;
	CString strNowDate;
	CStockDayTable*pStockDayTable=NULL;
	
	Vec_DropOffData  vecDropOffData_Bk;
	

	for(int i=0;i<vecDropOffData.size();i++)
	{
		pDropOffData=vecDropOffData[i];

		for (int j = 0; j < vecRSIData.size(); j++)
		{
			if (pDropOffData->strStockCode == vecRSIData[j].strStockCode)
			{
				float f_rsi3_dif = vecRSIData[j].rsi_3 - vecRSIData[j].f_min_rsi3;
				float f_rsi2_dif = vecRSIData[j].rsi_2 - vecRSIData[j].f_min_rsi2;
				float f_rsi1_dif = vecRSIData[j].rsi_1 - vecRSIData[j].f_min_rsi1;
#if 0
				if ((f_rsi1_dif > 0) && (f_rsi2_dif > 0) && (f_rsi3_dif > 0))
				{
					if (f_rsi1_dif > f_rsi2_dif)
					{
						if (f_rsi2_dif > f_rsi3_dif)
						{
							float f_min_rsi3_rsi1_dif= vecRSIData[j].f_min_rsi3 - vecRSIData[j].rsi_1;
							if (f_min_rsi3_rsi1_dif < 3.0)
							{
								if (vecRSIData[j].f_total_value < 0)
								{
									if (vecRSIData[j].rsi_1 > vecRSIData[j].rsi_3)
									{
										vecDropOffData_Bk.push_back(pDropOffData);
										break;
									}
								}
								else
								{
									vecDropOffData_Bk.push_back(pDropOffData);
									break;
								}

							}
							
							
						}
					}

				} //if
#else
				
				if (vecRSIData[j].f_min_rsi3 < 40.0)
				{
					
					vecDropOffData_Bk.push_back(pDropOffData);
					break;
				}
#endif
				
			}
		}

		/*pStockDayTable = StockDataMgr()->GetStockDayTable(pDropOffData->strStockCode);
		if(bUsePreDate)
		{
			CTime mDropOffTime;
			mDataTimeDropOff.GetTime(mDropOffTime);
			strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		}
		else
		{
			CTime mDropOffTime=CTime::GetCurrentTime();
			strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		}

		CStockProfitLossData* pStockProfitLossData=NULL;
		pStockProfitLossData=CStockProfitLossArithmetic::CalcProfitLossData(pDropOffData->strStockCode,strNowDate,120,50); //240
		if(pStockProfitLossData)
		{
			pStockProfitLossData->CalcVolumeSectionRange();
			double f_down_total_rang=AnalysisStockProfitLossData(pStockProfitLossData);
			//f_down_total_rang+=1.0;
			if(f_down_total_rang<3.0)
			{
				pDropOffData->fDownTotalRang=f_down_total_rang;
				vecDropOffData_Bk.push_back(pDropOffData);
				printf("%s  %f\n",pDropOffData->strStockCode,f_down_total_rang);
			}
			
			
		}*/


	}

	vecDropOffData.clear();
	vecDropOffData=vecDropOffData_Bk;
	FilterByReserve();
	FilterByMerge();
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	bExperFilter4=FALSE;
	return TRUE;
}

//经验过滤4
void CDlgDropOff::OnBnClickedBtnExperFilter4()
{
	if(bExperFilter4)
	{
		AfxMessageBox("还在处理");
		return;
	}

	bReserveFilter=mCheckReserveFilter.GetCheck();
	bMergeFilter=mCheckMergeFilter.GetCheck();
	if(bReserveFilter&&bMergeFilter)
	{
		AfxMessageBox("不能同时两种过滤");
		return;
	}

	if(bReserveFilter)
	{
		vecDropOffData_Reserve.clear();
		vecDropOffData_Reserve=vecDropOffData;
	}

	if(bMergeFilter)
	{

		vecDropOffData_Merge.clear();
		vecDropOffData_Merge=vecDropOffData;
	}

	

	//AfxBeginThread(RunFilter4Proc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
	RunFilter4Proc(this);
}

#if 0
static UINT  CalcMultiHeadProc(LPVOID pParam)
{
	CDlgDropOff *pDlgDropOff;
	pDlgDropOff=(CDlgDropOff *)pParam;

	pDlgDropOff->DoCalcMultiHead();

	return 0;
}


//清空并多头排列
void CDlgDropOff::OnBnClickedBtnExperFilter5()
{
	vecDropOffData.clear();
	pThread=AfxBeginThread(CalcMultiHeadProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
}

BOOL CDlgDropOff::DoCalcMultiHead(void)
{
	
	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		try
		{
			pStockCode=vecStockCodeList[i];
			pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);

			if(bUsePreDate)
			{
				CTime mDropOffTime;
				mDataTimeDropOff.GetTime(mDropOffTime);
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}
			else
			{
				CTime mDropOffTime=CTime::GetCurrentTime();
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}

			CStockKDJData *pStockKDJData=NULL;
			CString strEndDate=strNowDate;
			pStockKDJData=CStockKDJArithmetic::CalcKDJData(pStockCode->strStockCode,strEndDate,125,K_LINE_DAY,9,3,3);

			if(pStockKDJData==NULL)
				continue;


			int mLength=pStockKDJData->m_length;

			std::vector<double> vec_ma5,vec_ma10,vec_ma20,vec_ma60;
			vec_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
			vec_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
			vec_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
			vec_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);

			

#if 0
			int mCalcNums=10;
			BOOL bMa10_Up_Ma20=FALSE;
			int  mMa10_Up_Ma20_Index=-1;
			for(int i=vec_ma5.size()-1;i>=vec_ma5.size()-2;i--)
			{
				
				double f_ma10=vec_ma10[i];
				double f_ma10_pre=vec_ma10[i-1];

				double f_ma20=vec_ma20[i];
				double f_ma20_pre=vec_ma20[i-1];

				if(f_ma10>f_ma20 && f_ma10_pre<f_ma20_pre)	//10 上穿 20
				{
					bMa10_Up_Ma20=TRUE;
					mMa10_Up_Ma20_Index=i;
					break;
				}
			}
			if(!bMa10_Up_Ma20)
				continue;

			

			double f_ma10_3=vec_ma10[mMa10_Up_Ma20_Index];
			double f_ma10_2=vec_ma10[mMa10_Up_Ma20_Index-1];
			double f_ma10_1=vec_ma10[mMa10_Up_Ma20_Index-2];

			double f_ma60=vec_ma60[mMa10_Up_Ma20_Index];

			if(f_ma60>f_ma10_3)		//60日线下行，不要
				continue;

			bool b_ma10_ok=false;
			if(f_ma10_3>f_ma10_2 && f_ma10_2>f_ma10_1)
				b_ma10_ok=true;
			if(!b_ma10_ok)
				continue;


			printf("%s Ma10_Up_Ma20 ok\n",pStockCode->strStockCode);
			BOOL bMa5_Up_Ma20=FALSE;
			int  mMa5_Up_Ma20_Index=-1;
			for(int i=mMa10_Up_Ma20_Index-1;i>=mMa10_Up_Ma20_Index-7;i--)
			{
				double f_ma5=vec_ma5[i];
				double f_ma5_pre=vec_ma5[i-1];
				double f_ma20=vec_ma20[i];
				double f_ma20_pre=vec_ma20[i-1];

				if(f_ma5>f_ma20 && f_ma5_pre<f_ma20_pre)
				{
					bMa5_Up_Ma20=TRUE;

					mMa5_Up_Ma20_Index=i;
				}
			}

			if(!bMa5_Up_Ma20)
				continue;
			double f_ma5_3=vec_ma5[mMa5_Up_Ma20_Index];
			double f_ma5_2=vec_ma5[mMa5_Up_Ma20_Index-1];
			double f_ma5_1=vec_ma5[mMa5_Up_Ma20_Index-2];

			bool b_ma5_ok=false;
			if(f_ma5_3>f_ma5_2 && f_ma5_2>f_ma5_1)
				b_ma5_ok=true;
			if(!b_ma5_ok)
				continue;


			printf("%s Ma5_Up_Ma20 ok\n",pStockCode->strStockCode);
			BOOL bMa5_Up_Ma10=FALSE;
			int  mMa5_Up_Ma10_Index=-1;
			for(int i=mMa5_Up_Ma20_Index-1;i>=mMa5_Up_Ma20_Index-7;i--)
			{
				double f_ma5=vec_ma5[i];
				double f_ma5_pre=vec_ma5[i-1];
				double f_ma10=vec_ma10[i];
				double f_ma10_pre=vec_ma10[i-1];
				if(f_ma5>f_ma10 && f_ma5_pre<f_ma10_pre)
				{
					bMa5_Up_Ma10=TRUE;

					mMa5_Up_Ma10_Index=i;
				}
			}

			if(!bMa5_Up_Ma10)
				continue;


			printf("%s Ma5_Up_Ma10 ok\n",pStockCode->strStockCode);

			DropOffData *pDropOffData=new DropOffData();
			pDropOffData->strStockCode=pStockCode->strStockCode;
			pDropOffData->strStockName=pStockCode->strStockName;
			pDropOffData->fMaxMultiple=0;
			pDropOffData->fAveMultiple=0;
			pDropOffData->strMaxDate=strNowDate;
			pDropOffData->strMinDate=strNowDate;
			pDropOffData->mMaxValuePassDay=0;
			pDropOffData->fDownTotalRang=-1.0;
			vecDropOffData.push_back(pDropOffData);
#else
			int mCalcNums=10;
			bool bma5ok=true;
			for(int i=vec_ma5.size()-mCalcNums;i<vec_ma5.size()-1;i++)
			{
				double f_pre_value=vec_ma5[i];
				double f_now_value=vec_ma5[i+1];
				if(f_now_value<=f_pre_value)
				{
					bma5ok=false;
					break;
				}
			}
			
			bool bma10ok=true;
			for(int i=vec_ma10.size()-mCalcNums;i<vec_ma10.size()-1;i++)
			{
				double f_pre_value=vec_ma10[i];
				double f_now_value=vec_ma10[i+1];
				if(f_now_value<=f_pre_value)
				{
					bma10ok=false;
					break;
				}
			}

			bool bma20ok=true;
			for(int i=vec_ma20.size()-mCalcNums;i<vec_ma20.size()-1;i++)
			{
				double f_pre_value=vec_ma20[i];
				double f_now_value=vec_ma20[i+1];
				if(f_now_value<=f_pre_value)
				{
					bma20ok=false;
					break;
				}
			}

			bool bma60ok=true;
			for(int i=vec_ma60.size()-mCalcNums;i<vec_ma60.size()-1;i++)
			{
				double f_pre_value=vec_ma60[i];
				double f_now_value=vec_ma60[i+1];
				if(f_now_value<=f_pre_value)
				{
					bma60ok=false;
					break;
				}
			}

			if(bma60ok&&bma20ok&&bma10ok&&bma5ok) //
			{
				printf("%s ok\n",pStockCode->strStockCode);

				DropOffData *pDropOffData=new DropOffData();
				pDropOffData->strStockCode=pStockCode->strStockCode;
				pDropOffData->strStockName=pStockCode->strStockName;
				pDropOffData->fMaxMultiple=0;
				pDropOffData->fAveMultiple=0;
				pDropOffData->strMaxDate=strNowDate;
				pDropOffData->strMinDate=strNowDate;
				pDropOffData->mMaxValuePassDay=0;
				pDropOffData->fDownTotalRang=-1.0;
				vecDropOffData.push_back(pDropOffData);

			}
			else
			{
				printf("%s not pass\n",pStockCode->strStockCode);

			}
#endif
		}
		catch(...)
		{


		}
	}
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
}
#endif

static UINT  CalcDownShadowLineProc(LPVOID pParam)
{
	CDlgDropOff *pDlgDropOff;
	pDlgDropOff=(CDlgDropOff *)pParam;

	pDlgDropOff->DoCalcDownShadowLine();
	pDlgDropOff->FilterByReserve();
	pDlgDropOff->FilterByMerge();
	return 0;
}


//超长下影线
void CDlgDropOff::OnBnClickedBtnExperFilter5()
{
	bReserveFilter=mCheckReserveFilter.GetCheck();
	bMergeFilter=mCheckMergeFilter.GetCheck();
	if(bReserveFilter&&bMergeFilter)
	{
		AfxMessageBox("不能同时两种过滤");
		return;
	}

	if(bReserveFilter)
	{
		vecDropOffData_Reserve.clear();
		vecDropOffData_Reserve=vecDropOffData;
	}

	if(bMergeFilter)
	{

		vecDropOffData_Merge.clear();
		vecDropOffData_Merge=vecDropOffData;
	}

	vecDropOffData.clear();
	//pThread=AfxBeginThread(CalcDownShadowLineProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
	CalcDownShadowLineProc(this);
}


BOOL CDlgDropOff::DoCalcDownShadowLine(void)
{

	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		try
		{
			pStockCode=vecStockCodeList[i];
			pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);

			if(bUsePreDate)
			{
				CTime mDropOffTime;
				mDataTimeDropOff.GetTime(mDropOffTime);
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}
			else
			{
				CTime mDropOffTime=CTime::GetCurrentTime();
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}

			Vec_StockDayData vecStockDayData;
			int mDateIndex=pStockDayTable->GetNearestStockDayIndex(strNowDate);
			if(mDateIndex>3)
			{
				vecStockDayData=pStockDayTable->GetStockDayDataListBwIndex(mDateIndex-3,mDateIndex);

			}
			if(vecStockDayData.size()==0)
				continue;
#if 0
			bool bOk=false;
			double f_pre_100=0.0;
			CStockDayData *pStockDayData=NULL;
			
			for(int i=0;i<vecStockDayData.size();i++)
			{
				pStockDayData=vecStockDayData[i];
				double f_close_price=pStockDayData->GetEndPrice();
				double f_min_price=pStockDayData->GetMinPrice();
				double f_begin_price=pStockDayData->GetBeginPrice();
				
				//if((f_begin_price>f_close_price)&&(f_min_price<f_close_price)) //
				if(f_begin_price>f_close_price)		//low
				{
					if(f_min_price<f_close_price)
					{
						double f_dif=f_close_price-f_min_price;
						f_pre_100=(f_dif*100.0)/f_min_price;
						if(f_pre_100>4.0)
						{

							printf("%s ok\n",pStockCode->strStockCode);

							DropOffData *pDropOffData=new DropOffData();
							pDropOffData->strStockCode=pStockCode->strStockCode;
							pDropOffData->strStockName=pStockCode->strStockName;
							pDropOffData->fMaxMultiple=f_pre_100;
							pDropOffData->fAveMultiple=f_pre_100;
							pDropOffData->strMaxDate=pStockDayData->GetDate();
							pDropOffData->strMinDate=pStockDayData->GetDate();
							pDropOffData->mMaxValuePassDay=0;
							pDropOffData->fDownTotalRang=f_pre_100;
							vecDropOffData.push_back(pDropOffData);
							bOk=true;
							break;

						}

					}
				}
				else if(f_begin_price<=f_close_price)	
				{
					if(f_min_price<f_begin_price)
					{
						double f_dif=f_begin_price-f_min_price;
						f_pre_100=(f_dif*100.0)/f_min_price;
						if(f_pre_100>4.0)
						{

							printf("%s ok\n",pStockCode->strStockCode);

							DropOffData *pDropOffData=new DropOffData();
							pDropOffData->strStockCode=pStockCode->strStockCode;
							pDropOffData->strStockName=pStockCode->strStockName;
							pDropOffData->fMaxMultiple=f_pre_100;
							pDropOffData->fAveMultiple=f_pre_100;
							pDropOffData->strMaxDate=pStockDayData->GetDate();
							pDropOffData->strMinDate=pStockDayData->GetDate();
							pDropOffData->mMaxValuePassDay=0;
							pDropOffData->fDownTotalRang=f_pre_100;
							vecDropOffData.push_back(pDropOffData);
							bOk=true;
							break;

						}
					}

				}


			}

			if(!bOk)
			{

				printf("%s %f nopass\n",pStockCode->strStockCode,f_pre_100);
			}
			
#endif
			CStockDayData *pStockDayData=NULL;
			pStockDayData=vecStockDayData[vecStockDayData.size()-1];
			CStockDayData *pStockDayDataPre=NULL;
			pStockDayDataPre=vecStockDayData[vecStockDayData.size()-2];

			float f_end_price=pStockDayData->GetEndPrice();
			float f_pre_end_price=pStockDayDataPre->GetEndPrice();

			float f_high_price=pStockDayData->GetMaxPrice();
			float f_low_price=pStockDayData->GetMinPrice();
			BOOL bOneBoard=FALSE;

			float f_temp=fabs(f_high_price-f_low_price)*100.0/f_low_price;

			

			if(f_temp<0.2)
				bOneBoard=TRUE;
			if(f_end_price>f_pre_end_price)
			{
				double f_pert=(f_end_price-f_pre_end_price)*100.0/f_pre_end_price;
				if(f_pert>9.5)
				{
					//printf("%s  %f\n",pStockCode->strStockCode,f_temp);

					DropOffData *pDropOffData=new DropOffData();
					pDropOffData->strStockCode=pStockCode->strStockCode;
					pDropOffData->strStockName=pStockCode->strStockName;
					pDropOffData->fMaxMultiple=f_pert;
					if(bOneBoard)
						pDropOffData->fAveMultiple=1.0;
					else
						pDropOffData->fAveMultiple=0.0;
					pDropOffData->strMaxDate=pStockDayData->GetDate();
					pDropOffData->strMinDate=pStockDayData->GetDate();
					pDropOffData->mMaxValuePassDay=0;
					pDropOffData->fDownTotalRang=f_pert;
					vecDropOffData.push_back(pDropOffData);
				}

			}
			

		}
		catch(...)
		{

		}
	}
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
}


static UINT  CalcMenuPriceVolumeM5M10Proc(LPVOID pParam)
{
	CDlgDropOff *pDlgDropOff;
	pDlgDropOff=(CDlgDropOff *)pParam;

	pDlgDropOff->DoCalcMenuPriceVolumeM5M10();
	pDlgDropOff->FilterByReserve();
	pDlgDropOff->FilterByMerge();
	return 0;
}

void CDlgDropOff::OnBnClickedBtnDropOff()
{
	if(mFunButtonMenu.m_nMenuResult == IDR_MENU_PRICE_VOLUME_M5_M10)
	{
		CDlgM5M10Para dlg;
		if(dlg.DoModal()==IDOK)
		{
			m_m5_m10_period=dlg.GetM5M10Period();
			m_m5_m10_20_25_nums=dlg.GetM5M10_20_25_Nums();
			m_m5_m10_big25_nums=dlg.GetM5M10_Big25_Nums();
			m_close_m10_10_20_nums=dlg.GetCloseM10_10_20_Nums();
			m_close_m10_20_25_nums=dlg.GetCloseM10_20_25_Nums();
			m_close_m10_big25_nums=dlg.GetCloseM10_Big25_Nums();

			bReserveFilter=mCheckReserveFilter.GetCheck();
			bMergeFilter=mCheckMergeFilter.GetCheck();
			if(bReserveFilter&&bMergeFilter)
			{
				AfxMessageBox("不能同时两种过滤");
				return;
			}

			if(bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve=vecDropOffData;
			}

			if(bMergeFilter)
			{

				vecDropOffData_Merge.clear();
				vecDropOffData_Merge=vecDropOffData;
			}
			vecDropOffData.clear();
			//pThread=AfxBeginThread(CalcMenuPriceVolumeM5M10Proc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
			CalcMenuPriceVolumeM5M10Proc(this);
		}
		
	}
	else if(mFunButtonMenu.m_nMenuResult == IDR_MENU_LIMIT_UP_FILTER)
	{
		bReserveFilter=mCheckReserveFilter.GetCheck();

		if(bReserveFilter)
		{
			vecDropOffData_Reserve.clear();
			vecDropOffData_Reserve=vecDropOffData;
		}

		vecDropOffData.clear();
		DoFilterLimitUpMatch();

	}
	else if(mFunButtonMenu.m_nMenuResult == IDR_MENU_SMOOTH_FILTER)
	{
		bReserveFilter=mCheckReserveFilter.GetCheck();

		if(bReserveFilter)
		{
			vecDropOffData_Reserve.clear();
			vecDropOffData_Reserve=vecDropOffData;
		}

		vecDropOffData.clear();
		DoFilterTimePriceMapMatch();
	}
	else if (mFunButtonMenu.m_nMenuResult == IDR_MENU_KLINE_FILTER) //k线算法
	{
		bReserveFilter = mCheckReserveFilter.GetCheck();

		if (bReserveFilter)
		{
			vecDropOffData_Reserve.clear();
			vecDropOffData_Reserve = vecDropOffData;
		}
		DoFilterKLineMapMatch();

	}
	else if (mFunButtonMenu.m_nMenuResult == IDR_MENU_KLINE_BAD_FILTER) //k线算法走势变坏
	{
		DoFilterKLineBadFilter();
	}
	else if (mFunButtonMenu.m_nMenuResult == IDR_MENU_KLINE_NINE_TURN)
	{
		DoFilterKLineNineTurn();

	}
	else if (mFunButtonMenu.m_nMenuResult == IDR_MENU_GROUP_INFO)
	{
		CTime mDropOffTime;
		if (bUsePreDate)
		{
			mDataTimeDropOff.GetTime(mDropOffTime);
		}
		else
		{
			mDropOffTime = CTime::GetCurrentTime();
		}

		CDlgGlobalInfo dlg;
		dlg.SetStockDateTime(mDropOffTime);
		dlg.DoModal();

	}
	else if (mFunButtonMenu.m_nMenuResult == IDR_MENU_INDUSTRY_INFO)
	{
		DoIndustyInfoStat();
	}
}


BOOL CDlgDropOff::DoFilterTimePriceMapMatch(void)
{
	Vec_TimePriceMapData vecTimePriceMapData;
	CTimePriceMapAlg mTimePriceMapAlg;
	vecTimePriceMapData.clear();
	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}
	vecTimePriceMapData=mTimePriceMapAlg.doFilter(mDropOffTime);

	for(int i=0;i<vecTimePriceMapData.size();i++)
	{
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecTimePriceMapData[i]->strStockCode;
		pDropOffData->strStockName=vecTimePriceMapData[i]->strStockName;
		pDropOffData->fMaxMultiple=0;
		pDropOffData->fAveMultiple=0;
		pDropOffData->strMaxDate="";
		pDropOffData->strMinDate="";
		pDropOffData->mMaxValuePassDay=0;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=0;
		pDropOffData->mSpecNums=0;
		pDropOffData->strInfo="";
		vecDropOffData.push_back(pDropOffData);
	}
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
}



//K线算法
BOOL CDlgDropOff::DoFilterKLineMapMatch(void)
{
	CTime mDropOffTime;
	if (bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime = CTime::GetCurrentTime();
	}
	Vec_DropOffData  vecDropOffData2;
	for (int i = 0; i < vecDropOffData.size(); i++)
	{
		CString strStockCode = vecDropOffData[i]->strStockCode;
		CString strStockName = vecDropOffData[i]->strStockName;

		CKLineFilterAlg  mKLineFilterAlg;

		Vec_KLineFilterData2 vecKLineFilterData2= mKLineFilterAlg.doFilter2(strStockCode, strStockName, mDropOffTime);
		KLineContinusMNData mKLineContinusMNData= mKLineFilterAlg.doCalcMNPriceContiUp(strStockCode, strStockName, mDropOffTime);
		//if (CKLineFilterAlg::IsKLineFourDownFilter(vecKLineFilterData2))
		if (CKLineFilterAlg::IsCrossStartRevertFilter(vecKLineFilterData2, mKLineContinusMNData))
		{
			vecDropOffData2.push_back(vecDropOffData[i]);
		}
		CKLineFilterAlg::FreeVecKLineFilterData2(vecKLineFilterData2);
	}
	vecDropOffData.clear();

	if(vecDropOffData2.size()>0)
		vecDropOffData.assign(vecDropOffData2.begin(), vecDropOffData2.end());


	SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);
	
	return TRUE;
}

//k线算法走势变坏检查
BOOL  CDlgDropOff::DoFilterKLineBadFilter(void)
{

	CTime mDropOffTime;
	if (bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime = CTime::GetCurrentTime();
	}
	Vec_DropOffData  vecDropOffData2;
	for (int i = 0; i < vecDropOffData.size(); i++)
	{
		CString strStockCode = vecDropOffData[i]->strStockCode;
		CString strStockName = vecDropOffData[i]->strStockName;

		CKLineFilterAlg  mKLineFilterAlg;

		Vec_KLineFilterData2 vecKLineFilterData2 = mKLineFilterAlg.doFilter2(strStockCode, strStockName, mDropOffTime);
	
		if (!CKLineFilterAlg::IsKLineBadTrend(vecKLineFilterData2))
		{
			vecDropOffData2.push_back(vecDropOffData[i]);
		}
		CKLineFilterAlg::FreeVecKLineFilterData2(vecKLineFilterData2);
	}
	
	vecDropOffData.clear();

	if (vecDropOffData2.size() > 0)
		vecDropOffData.assign(vecDropOffData2.begin(), vecDropOffData2.end());

	SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);


	return TRUE;
}

//k线算法9转
BOOL CDlgDropOff::DoFilterKLineNineTurn(void)
{

	CTime mDropOffTime;
	if (bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime = CTime::GetCurrentTime();
	}
	Vec_DropOffData  vecDropOffData2;
	for (int i = 0; i < vecDropOffData.size(); i++)
	{
		CString strStockCode = vecDropOffData[i]->strStockCode;
		CString strStockName = vecDropOffData[i]->strStockName;

		CKLineFilterAlg  mKLineFilterAlg;

		Vec_KLineFilterData2 vecKLineFilterData2 = mKLineFilterAlg.doFilter2(strStockCode, strStockName, mDropOffTime);

		if (CKLineFilterAlg::IsKLineNineTurn(vecKLineFilterData2))
		{
			vecDropOffData2.push_back(vecDropOffData[i]);
		}
		CKLineFilterAlg::FreeVecKLineFilterData2(vecKLineFilterData2);
	}

	vecDropOffData.clear();

	if (vecDropOffData2.size() > 0)
		vecDropOffData.assign(vecDropOffData2.begin(), vecDropOffData2.end());

	SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);
	return TRUE;
}
//k线算法行业
BOOL CDlgDropOff::DoFilterKLineIndustry(void)
{

	CTime mDropOffTime;
	if (bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime = CTime::GetCurrentTime();
	}
	Vec_DropOffData  vecDropOffData2;
	for (int i = 0; i < vecDropOffData.size(); i++)
	{
		CString strStockCode = vecDropOffData[i]->strStockCode;
		CString strStockName = vecDropOffData[i]->strStockName;

		CKLineFilterAlg  mKLineFilterAlg;

		Vec_KLineFilterData2 vecKLineFilterData2 = mKLineFilterAlg.doFilter2(strStockCode, strStockName, mDropOffTime);

		if (CKLineFilterAlg::IsKLineIndustry(vecKLineFilterData2))
		{
			vecDropOffData2.push_back(vecDropOffData[i]);
		}
		CKLineFilterAlg::FreeVecKLineFilterData2(vecKLineFilterData2);
	}

	vecDropOffData.clear();

	if (vecDropOffData2.size() > 0)
		vecDropOffData.assign(vecDropOffData2.begin(), vecDropOffData2.end());

	SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);

	return TRUE;
}

BOOL CDlgDropOff::DoCalcMenuPriceVolumeM5M10(void)
{

	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		try
		{
			pStockCode=vecStockCodeList[i];
			pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
			
			
			if(bUsePreDate)
			{
				CTime mDropOffTime;
				mDataTimeDropOff.GetTime(mDropOffTime);
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}
			else
			{
				CTime mDropOffTime=CTime::GetCurrentTime();
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}

			CStockKDJData *pStockKDJData=NULL;

			if(pStockCode->strStockCode=="SH600618")
			{
				int a=0;
				a++;
			}

			pStockKDJData=CStockKDJArithmetic::CalcKDJData(pStockCode->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
			if(pStockKDJData==NULL)
				continue;

			std::vector<double> vec_ma5,vec_ma10;
			vec_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_volume_price);
			vec_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_volume_price);
			int size=vec_ma5.size();

			bool bOk=true;
			int m_per_10_nums=0;
			int m_per_20_nums=0;
			int m_per_25_nums=0;
			int m_per_big_25_nums=0;

			for(int j=size-m_m5_m10_period;j<size;j++)		//12//连续12周期 10日平均线和5日平均线 差值 小于10%
			{
				double _m10=vec_ma10[j];
				double _m5=vec_ma5[j];
				double f_per=fabs((_m5-_m10)*100.0/_m10);
				if(f_per<=10.0)
				{
					m_per_10_nums++;
				}
				else if(f_per>10.0&&f_per<=20.0)
				{
					m_per_20_nums++;
				}
				else if(f_per>20.0&&f_per<=25.0)
				{
					m_per_25_nums++;
				}
				else
				{
					m_per_big_25_nums++;
				}
			}

			if(m_per_big_25_nums>m_m5_m10_big25_nums)  //0
			{
				bOk=false;
			}
			else if(m_per_25_nums>=m_m5_m10_20_25_nums)  //2
			{
				bOk=false;
			}

			if(bOk)
			{

				printf("%s m5 m10 per_10_nums=%d per_20_nums=%d per_25_nums=%d per_big_25_nums=%d\n",pStockCode->strStockCode
					,m_per_10_nums,m_per_20_nums,m_per_25_nums,m_per_big_25_nums);
				m_per_10_nums=0;
				m_per_20_nums=0;
				m_per_25_nums=0;
				m_per_big_25_nums=0;
				bool bOk2=true;
				for(int j=size-12;j<size;j++)
				{
					double _m10=vec_ma10[j];
					double _closeval=pStockKDJData->vec_volume_price[j];
					double f_per=(_closeval-_m10)*100.0/_m10;
					if(f_per<=10.0)
					{
						m_per_10_nums++;
					}
					else if(f_per>10.0&&f_per<=20.0)
					{
						m_per_20_nums++;
					}
					else if(f_per>20.0&&f_per<=25.0)
					{
						m_per_25_nums++;
					}
					else
					{
						m_per_big_25_nums++;
					}
				}

				if(m_per_big_25_nums>m_close_m10_big25_nums)		//0
				{
					bOk=false;
				}
				else if(m_per_25_nums>=m_close_m10_20_25_nums)		//2
				{
					bOk=false;
				}
				else if(m_per_20_nums>=m_close_m10_10_20_nums)		//5
				{

					bOk=false;
				}
				if(bOk2)
				{
					printf("%s vol m10 per_10_nums=%d per_20_nums=%d per_25_nums=%d per_big_25_nums=%d\n",pStockCode->strStockCode
						,m_per_10_nums,m_per_20_nums,m_per_25_nums,m_per_big_25_nums);
					DropOffData *pDropOffData=new DropOffData();
					pDropOffData->strStockCode=pStockCode->strStockCode;
					pDropOffData->strStockName=pStockCode->strStockName;
					pDropOffData->fMaxMultiple=0.0;
					pDropOffData->fAveMultiple=0.0;
					pDropOffData->strMaxDate=strNowDate;
					pDropOffData->strMinDate=strNowDate;
					pDropOffData->mMaxValuePassDay=0;
					pDropOffData->fDownTotalRang=0.0;
					vecDropOffData.push_back(pDropOffData);

				}

			}

			
			
		}
		catch(...)
		{

		}
	}


	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;



	return TRUE;
}


BOOL CDlgDropOff::RefreshData_Second(void)
{

	CString strConv,strTemp;
	int nRow;
	mSecondListCtrlItem.DeleteAllItems();
	int i=0;

	DropOffData *pDropOffData=NULL;
	for(i=0;i<vecDropOffData_Second.size();i++)
	{
		pDropOffData=vecDropOffData_Second[i];
		if(!pDropOffData)
			continue;
		strConv.Format("%4d",i+1);
		nRow=i;
		if(nRow>=mSecondListCtrlItem.GetItemCount())
			mSecondListCtrlItem.InsertItem(i,strConv);
		else
			mSecondListCtrlItem.SetItemText(nRow, DROPOFF2_COLUMN_ID,strConv);

		mSecondListCtrlItem.SetItemText(nRow, DROPOFF2_COLUMN_STOCK_CODE,pDropOffData->strStockCode);
		mSecondListCtrlItem.SetItemText(nRow, DROPOFF2_COLUMN_STOCK_NAME,pDropOffData->strStockName);
		strTemp.Format("%d",pDropOffData->mSpecNums);
		mSecondListCtrlItem.SetItemText(nRow, DROPOFF2_COLUMN_SPECNUMS,strTemp);
		
		mSecondListCtrlItem.SetItemData(nRow,reinterpret_cast<DWORD_PTR>(pDropOffData));
	}

	if(i<mSecondListCtrlItem.GetItemCount())
	{
		for(int j=i;j<mSecondListCtrlItem.GetItemCount();j++)
			mSecondListCtrlItem.DeleteItem(j);
	}

	return true;
}

//清空LEFT
void CDlgDropOff::OnBnClickedBtnClearLeft()
{
	vecDropOffData.clear();
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
}

//清空RIGHT
void CDlgDropOff::OnBnClickedBtnClearRight()
{
	vecDropOffData_Second.clear();
	SetTimer(DROPOFF_EVENT_REFRESH_DATA_SECOND,300,0);

}

//添加到Right
void CDlgDropOff::OnBnClickedBtnAddToRight()
{
	DropOffData *pDropOffData=NULL;
	DropOffData *pDropOffData_Right=NULL;

	for(int i=0;i<vecDropOffData.size();i++)
	{
		pDropOffData=vecDropOffData[i];
		bool bFound=false;

		for(int j=0;j<vecDropOffData_Second.size();j++)
		{
			pDropOffData_Right=vecDropOffData_Second[j];
			if(pDropOffData->strStockCode==pDropOffData_Right->strStockCode)
			{
				pDropOffData_Right->mSpecNums++;
				bFound=true;
				break;
			}

		}

		if(!bFound)
		{
			vecDropOffData_Second.push_back(pDropOffData);
		}


	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA_SECOND,300,0);
}

//添加到Left
void CDlgDropOff::OnBnClickedBtnAddToLeft()
{
	DropOffData *pDropOffData=NULL;
	DropOffData *pDropOffData_Right=NULL;
	for(int i=0;i<vecDropOffData_Second.size();i++)
	{
		pDropOffData_Right=vecDropOffData_Second[i];
		bool bFound=false;

		for(int j=0;j<vecDropOffData.size();j++)
		{
			pDropOffData=vecDropOffData[j];
			if(pDropOffData->strStockCode==pDropOffData_Right->strStockCode)
			{
				bFound=true;
				break;
			}

		}

		if(!bFound)
		{
			vecDropOffData.push_back(pDropOffData_Right);
		}
	
	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
}

//添加到Left xor
void CDlgDropOff::OnBnClickedBtnAddToLeftxor()
{
	/*
	DropOffData *pDropOffData=NULL;
	DropOffData *pDropOffData_Right=NULL;
	Vec_DropOffData  vecDropOffData2;
	for(int i=0;i<vecDropOffData_Second.size();i++)
	{
		pDropOffData_Right=vecDropOffData_Second[i];
		bool bFound=false;

		for(int j=0;j<vecDropOffData.size();j++)
		{
			pDropOffData=vecDropOffData[j];
			if(pDropOffData->strStockCode==pDropOffData_Right->strStockCode)
			{
				bFound=true;
				break;
			}

		}

		if(bFound)
		{
			vecDropOffData2.push_back(pDropOffData_Right);
		}

		



	}
	vecDropOffData.clear();
	vecDropOffData=vecDropOffData2;

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	*/

	vecDropOffData.clear();
	TanAngleData *pTanAngleData=NULL;
	DropOffData *pDropOffData_Right=NULL;
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];
		BOOL bFound=FALSE;
		for(int j=0;j<vecDropOffData_Second.size();j++)
		{
			pDropOffData_Right=vecDropOffData_Second[j];
			if(pDropOffData_Right->strStockCode==pTanAngleData->strStockCode)
			{
				bFound=TRUE;
				break;
			}
		}

		if(!bFound)
			continue;

		double f_ma5_angle=pTanAngleData->fPara0;
		double f_ma10_angle=pTanAngleData->fPara1;
		double f_ma20_angle=pTanAngleData->fPara2;
		double f_ma60_angle=pTanAngleData->fPara3;
		double f_max_volume_per=pTanAngleData->fPara4;
		double f_ave_volume_per=pTanAngleData->fPara5;
		double f_60_20_cross_price_increase=pTanAngleData->fPara6;
		double f_20_10_cross_price_increase=pTanAngleData->fPara7;
		double f_60_day_increase=pTanAngleData->fPara8;
		int m_10_big_20_nums=pTanAngleData->mPara6;
		int m_60_big_20_nums=pTanAngleData->mPara7;
		int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
		int m_max_volume_distance=pTanAngleData->mMaxDis;
		int mContiDownNums=pTanAngleData->mContiDownNums;
		int mContiVolDownNums=pTanAngleData->mContiVolDownNums;

		int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;
		int mNextGrow=pTanAngleData->mNextGrow;
		int mBigIncreaseNums=pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums=pTanAngleData->mRsi1BigNums;
		double fNextGrow=pTanAngleData->fNextGrow;
		double f_volume_per=pTanAngleData->fVolumePer;
		double f_cur_rsi_1=pTanAngleData->fRsi1;

		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=pTanAngleData->strStockCode;
		pDropOffData->strStockName=pTanAngleData->strStockName;
		pDropOffData->fMaxMultiple=pTanAngleData->fPara2;
		pDropOffData->fAveMultiple=pTanAngleData->fPara1;
		CString strInfo;
		strInfo.Format("%.2f,up%.2f",pTanAngleData->fPara0,pTanAngleData->fPara7);
		pDropOffData->strMaxDate=strInfo;
		strInfo.Format("%.2f,%d ave:%.2f  %.2f",pTanAngleData->fPara4,pTanAngleData->mMaxDis,pTanAngleData->fPara5,pTanAngleData->fPara6);
		pDropOffData->strMinDate=strInfo;
		pDropOffData->mMaxValuePassDay=pTanAngleData->fPara3;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=pTanAngleData->mPara6;
		pDropOffData->mSpecNums=pTanAngleData->mPara7;
		strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#cr%.2f#rb%d#%.2f",pTanAngleData->fPara8,pTanAngleData->mPara8,pTanAngleData->mPara9,pTanAngleData->mPara10,pTanAngleData->mContiDownNums,pTanAngleData->mContiVolDownNums,pTanAngleData->mStepIndex,pTanAngleData->mNowIsMaxPriceNums,
			pTanAngleData->mBigIncreaseNums,f_cur_rsi_1,pTanAngleData->mRsi1BigNums,f_volume_per);
		pDropOffData->strInfo=strInfo;
		vecDropOffData.push_back(pDropOffData);
	}
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
}


void CDlgDropOff::OnBnClickedBtnAddToLeftxor2()
{
	DropOffData *pDropOffData=NULL;
	DropOffData *pDropOffData_Right=NULL;
	Vec_DropOffData  vecDropOffData2;
	for(int i=0;i<vecDropOffData_Second.size();i++)
	{
		pDropOffData_Right=vecDropOffData_Second[i];
		bool bFound=false;

		for(int j=0;j<vecDropOffData.size();j++)
		{
			pDropOffData=vecDropOffData[j];
			if(pDropOffData->strStockCode==pDropOffData_Right->strStockCode)
			{
				bFound=true;
				break;
			}

		}

		if(bFound)
		{
			vecDropOffData2.push_back(pDropOffData);
		}





	}
	vecDropOffData.clear();
	vecDropOffData=vecDropOffData2;

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
}

void CDlgDropOff::OnBnClickedBtnAddToLeftxor3()
{
	DropOffData *pDropOffData=NULL;
	DropOffData *pDropOffData_Right=NULL;
	Vec_DropOffData  vecDropOffData2;
	
	for(int i=0;i<vecDropOffData.size();i++)
	{
		pDropOffData=vecDropOffData[i];
		bool bFound=false;

		for(int j=0;j<vecDropOffData_Second.size();j++)
		{
			pDropOffData_Right=vecDropOffData_Second[j];
			if(pDropOffData->strStockCode==pDropOffData_Right->strStockCode)
			{
				bFound=true;
				break;
			}

		}

		if(!bFound)
		{
			vecDropOffData2.push_back(pDropOffData);
		}
	}
	vecDropOffData.clear();
	vecDropOffData=vecDropOffData2;

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
}



void CDlgDropOff::OnBnClickedBtnShowHide()
{

	if(!bExtWinHide)
	{
		RECT mRect;		
		GetWindowRect(&mRect);
		int x=mRect.left;
		int y=mRect.top;
		int width=mRect.right-x;
		int height=mRect.bottom-y;
		MoveWindow(x,y,width-395,height);
		bExtWinHide=TRUE;
		GetDlgItem(IDC_BTN_SHOW_HIDE)->SetWindowText("展开");
	}
	else
	{
		RECT mRect;		
		GetWindowRect(&mRect);
		int x=mRect.left;
		int y=mRect.top;
		int width=mRect.right-x;
		int height=mRect.bottom-y;
		MoveWindow(x,y,width+395,height);
		bExtWinHide=FALSE;
		GetDlgItem(IDC_BTN_SHOW_HIDE)->SetWindowText("隐藏");
	}
}


static UINT  RunFilterKdjProc(LPVOID pParam)
{
	CDlgDropOff *pDlgDropOff;
	pDlgDropOff=(CDlgDropOff *)pParam;

	pDlgDropOff->DoFilterKDJ();
	pDlgDropOff->SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return 0;
}


bool sortFun(const DropOffData *pData1, const DropOffData *pData2)
{
	return pData1->fAveMultiple > pData2->fAveMultiple;//降序排列  
}


BOOL CDlgDropOff::DoFilterKDJ(void)
{

	
	DropOffData *pDropOffData=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	vecRSIData.clear();
	for(int i=0;i<vecDropOffData.size();i++)
	{
		try
		{

			pDropOffData=vecDropOffData[i];
			pStockDayTable=StockDataMgr()->GetStockDayTable(pDropOffData->strStockCode);

			if(bUsePreDate)
			{
				CTime mDropOffTime;
				mDataTimeDropOff.GetTime(mDropOffTime);
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}
			else
			{
				CTime mDropOffTime=CTime::GetCurrentTime();
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}

			if(pDropOffData->strStockCode=="SH600618")
			{
				int a=0;
				a++;

			}

			CStockMFIData* pStockMFIData = CStockMFIArithmetic::CalcMFIData(pDropOffData->strStockCode, strNowDate, 125, K_LINE_DAY, 14);
			int mfi_size = pStockMFIData->vec_mfi.size();
			float mfi_now_value = pStockMFIData->vec_mfi[mfi_size - 1];
			float f_mfi_min_value = 999999.0;
			int m_mfi_min_value_index = -1;

			for (int j = mfi_size - mRsiPreNums; j < mfi_size; j++)
			{
				float f_mfi = pStockMFIData->vec_mfi[j];
				if (f_mfi < f_mfi_min_value)
				{
					f_mfi_min_value = f_mfi;
					m_mfi_min_value_index = j;
				}
			}

			float f_mfi_max_value = -999999.0;
			int m_mfi_max_value_index = -1;
			for (int j = mfi_size - mRsiPreNums; j < mfi_size; j++)
			{
				float f_mfi = pStockMFIData->vec_mfi[j];
				if (f_mfi > f_mfi_max_value)
				{
					f_mfi_max_value = f_mfi;
					m_mfi_max_value_index = j;
				}

			}



			CStockCRData*  pStockCRData=CStockCRArithmetic::CalcCRData(pDropOffData->strStockCode, strNowDate, 125, K_LINE_DAY, 26);
			int cr_size = pStockCRData->vec_cr.size();

			float cr_now_value = pStockCRData->vec_cr[cr_size - 1];

			float f_cr_min_value = 999999.0;
			int m_cr_min_value_index = -1;

			for (int j = cr_size - mRsiPreNums; j < cr_size; j++) 
			{
				float f_cr = pStockCRData->vec_cr[j];
				if (f_cr < f_cr_min_value)
				{
					f_cr_min_value = f_cr;
					m_cr_min_value_index = j;
				}
			}

			float f_cr_max_value = -999999.0;
			int m_cr_max_value_index = -1;
			for (int j = cr_size - mRsiPreNums; j < cr_size; j++)
			{
				float f_cr = pStockCRData->vec_cr[j];
				if (f_cr > f_cr_max_value)
				{
					f_cr_max_value = f_cr;
					m_cr_max_value_index = j;
				}

			}


			CStockRSIData* pStockRSIData=NULL;
			pStockRSIData=CStockRSIArithmetic::CalcRSIData(pDropOffData->strStockCode,strNowDate,125,K_LINE_DAY,6,12,24); 
			int rsi_size=pStockRSIData->vec_rsi_1_value.size();

			double rsi_1=pStockRSIData->vec_rsi_1_value[rsi_size-1];
			double rsi_2=pStockRSIData->vec_rsi_2_value[rsi_size-1];
			double rsi_3=pStockRSIData->vec_rsi_3_value[rsi_size-1];

			double f_min_rsi1=999999.0;
			int m_min_rsi1_index=-1;

			for(int j=rsi_size-mRsiPreNums;j<rsi_size;j++) //42 18
			{
				double f_rsi1=pStockRSIData->vec_rsi_1_value[j];
				if(f_rsi1<f_min_rsi1)
				{
					f_min_rsi1=f_rsi1;
					m_min_rsi1_index=j;
				}
			}

			double f_min_rsi2=pStockRSIData->vec_rsi_2_value[m_min_rsi1_index];
			double f_min_rsi3=pStockRSIData->vec_rsi_3_value[m_min_rsi1_index];



			int mUpCoeff_Price_1=0;
			
			std::vector<double> vec_closema5,vec_closema10,vec_closema20;
			vec_closema5=CStockKDJArithmetic::CalcMA(5,pStockRSIData->vec_close_price);
			vec_closema10=CStockKDJArithmetic::CalcMA(10,pStockRSIData->vec_close_price);
			vec_closema20=CStockKDJArithmetic::CalcMA(20,pStockRSIData->vec_close_price);
			mUpCoeff_Price_1=CalcUpCoeff_Price_1(pStockRSIData->vec_close_price,vec_closema5,vec_closema20);
			
		
	
			int mUpCoeff_Vol_1=0;
		
			std::vector<double> vec_ma5,vec_ma10;
			vec_ma5=CStockKDJArithmetic::CalcMA(5,pStockRSIData->vec_volume_price);
			vec_ma10=CStockKDJArithmetic::CalcMA(10,pStockRSIData->vec_volume_price);
			int size=vec_ma5.size();
			mUpCoeff_Vol_1=CalcUpCoeff_Vol_1(pStockRSIData->vec_volume_price,vec_ma5,vec_ma10,pStockRSIData->vec_close_price);

			int mUpCoeff_Vol_2=CalcUpCoeff_Vol_2(pStockRSIData->vec_volume_price,vec_ma5,vec_ma10,pStockRSIData->vec_close_price);

			if(mUpCoeff_Vol_2>mUpCoeff_Vol_1)
				mUpCoeff_Vol_1=mUpCoeff_Vol_2;

			int mUpCoeff_Vol_3=CalcUpCoeff_Vol_3(pStockRSIData->vec_volume_price,vec_ma5,vec_ma10,pStockRSIData->vec_close_price);
			if(mUpCoeff_Vol_3>mUpCoeff_Vol_1)
				mUpCoeff_Vol_1=mUpCoeff_Vol_3;

			int mUpCoeff_Vol_4=CalcUpCoeff_Vol_4(pStockRSIData->vec_volume_price,vec_ma5,vec_ma10,pStockRSIData->vec_close_price);
			if(mUpCoeff_Vol_4>mUpCoeff_Vol_1)
				mUpCoeff_Vol_1=mUpCoeff_Vol_4;

			int mUpCoeff_Vol_Addition_1=CalcUpCoeff_Vol_Addition_1(pStockRSIData->vec_volume_price,pStockRSIData->vec_close_price,rsi_1);

			mUpCoeff_Vol_1+=mUpCoeff_Vol_Addition_1;

			double f_total_value=0.0;
			double f_pre_value=0.0;
			int m_low_ave_5_nums=0;
			int m_low_sub_mark_nums=0;
			bool bCrash=true;
			for(int j=size-mKdjNums;j<size;j++)
			{
				double begin=pStockRSIData->vec_open_price[j];
				double end=pStockRSIData->vec_close_price[j];
				double f=-((end-begin)*100.0/begin);
			
				double vol=pStockRSIData->vec_volume_price[j];
				double vol_m10=vec_ma10[j];
				double vol_m5=vec_ma5[j];
				if(vol<=0.01)
				{
					f_total_value+=f_pre_value;
					continue;
				}


				double g;

				if(f>=0.0)
					g=vol_m10/vol;
				else
					g=vol/vol_m10;

				double f_muls=g;
				if(vol<vol_m5)
				{
					for(int n=1;n<mKdjMuls;n++)
					{
						f_muls=f_muls*g;
					}

				}
			
				double f_nums=1.0;
				/*for(int m=j;m<size;m++)
				{
					f_nums=f_nums*0.9;
				}*/
			
				double value=f*f_muls*f_nums;
				f_pre_value=value;
				bCrash=false;
				f_total_value+=value;


			}

			for(int j=size-5;j<size;j++)
			{
				double vol=pStockRSIData->vec_volume_price[j];
				double vol_m10=vec_ma10[j];
				double vol_m5=vec_ma5[j];

				if(vol<vol_m5)
					m_low_ave_5_nums++;

			}

			for(int j=size-mKdjNums;j<size;j++)
			{
				double vol=pStockRSIData->vec_volume_price[j];
				double vol_m10=vec_ma10[j];
				double vol_m5=vec_ma5[j];

				double f_begin_price=pStockRSIData->vec_open_price[j];
				double f_pre_close_price=pStockRSIData->vec_close_price[j-1];
				double f_close_price=pStockRSIData->vec_close_price[j];

			

				double f_per=(vol-vol_m5)*100.0/vol;
			
				if(f_per<4.0)
				{

					double f_pre_close_per=(f_close_price-f_pre_close_price)*100.0/f_pre_close_price;
					double f_begin_per=(f_close_price-f_begin_price)*100.0/f_begin_price;
					double f_price_per;
					if(f_begin_per<f_pre_close_per)
						f_price_per=f_begin_per;
					else
						f_price_per=f_pre_close_per;
				
					if(f_price_per<-2.0)
					{
						m_low_sub_mark_nums++;
						printf("%s %s f_per=%f f_pre_close_price=%f m_low_sub_mark_nums=%d\n",pDropOffData->strStockCode, pDropOffData->strStockName,f_per,f_price_per,m_low_sub_mark_nums);
					
					}
				}

			}


			/*if(b_close_m5_uping)
			{
				if(f_close_m5>=f_close_m10)
					f_total_value+=5.0;
				if(f_close_m5>=f_close_m20)
					f_total_value+=5.0;
				if(f_close_m10>=f_close_m20)
					f_total_value+=5.0;
			}*/
		
		
			if(bCrash)
				pDropOffData->fAveMultiple=-1000.0;
			else
				pDropOffData->fAveMultiple=f_total_value;
			pDropOffData->fMaxMultiple=m_low_ave_5_nums;
			pDropOffData->mMaxValuePassDay=mUpCoeff_Price_1+mUpCoeff_Vol_1;//m_low_sub_mark_nums;
			CString strRsiInfo;
			strRsiInfo.Format("rsi1=%.2f , rsi2=%.2f , rsi3=%.2f\n",rsi_1,rsi_2,rsi_3);
			//printf("RSI %.2f %.2f %.2f\n",rsi_1,rsi_2,rsi_3);
			pDropOffData->strMaxDate=strRsiInfo;
			strRsiInfo.Format("rsi1=%.2f , rsi2=%.2f , rsi3=%.2f\n",f_min_rsi1,f_min_rsi2,f_min_rsi3);
			pDropOffData->strMinDate=strRsiInfo;

			CString strInfo;
			/*if (f_cr_min_value < 40.0)
				strInfo.Format("nowcr=%.2f maxcr=%.2f d=%d mincr=%.2f d=%d **", cr_now_value, f_cr_max_value, cr_size - m_cr_max_value_index,f_cr_min_value, cr_size - m_cr_min_value_index);
			else
				strInfo.Format("nowcr=%.2f maxcr=%.2f d=%d mincr=%.2f d=%d", cr_now_value, f_cr_max_value, cr_size - m_cr_max_value_index, f_cr_min_value, cr_size - m_cr_min_value_index);
			*/
			strInfo.Format("nowmfi=%.2f maxmfi=%.2f d=%d minmfi=%.2f d=%d", mfi_now_value, f_mfi_max_value, mfi_size - m_mfi_max_value_index, f_mfi_min_value, mfi_size - m_mfi_min_value_index);
			pDropOffData->strInfo = strInfo;

			RSIData rsiData;
			rsiData.rsi_1 = rsi_1;
			rsiData.rsi_2 = rsi_2;
			rsiData.rsi_3 = rsi_3;
			rsiData.f_min_rsi1 = f_min_rsi1;
			rsiData.f_min_rsi2 = f_min_rsi2;
			rsiData.f_min_rsi3 = f_min_rsi3;
			rsiData.cr = cr_now_value;
			rsiData.f_min_cr = f_cr_min_value;
			rsiData.mfi = mfi_now_value;
			rsiData.f_min_mfi = f_mfi_min_value;
			rsiData.strStockCode = pDropOffData->strStockCode;
			rsiData.strStockName = pDropOffData->strStockName;
			rsiData.f_total_value = f_total_value;
			rsiData.m_low_ave_5_nums = m_low_ave_5_nums;
			vecRSIData.push_back(rsiData);

			SAFE_DELETE(pStockMFIData);
			SAFE_DELETE(pStockCRData);
			SAFE_DELETE(pStockRSIData);
			

		}
		catch (...)
		{
			
		}
		
		
	}

	std::sort(vecDropOffData.begin(), vecDropOffData.end(), sortFun);
	

	return TRUE;
}

//计算上涨系数 量1
int  CDlgDropOff::CalcUpCoeff_Vol_1(std::vector<double> & vec_vol,std::vector<double> & vec_vol_ma5,std::vector<double> & vec_vol_ma10,std::vector<double> & vec_price)
{
	
		int length=vec_vol_ma5.size();

		int continuous_vol_down_nums=0;		//连续成交量缩量次数

		int result_value=0;

		double vol_pre=vec_vol[length-5];

		for(int i=length-4;i<length;i++)
		{
			double vol=vec_vol[i];
			if(vol_pre>=vol)
			{
				continuous_vol_down_nums++;
			}
			else
			{
				break;
			}
			vol_pre=vol;
		}

		if(continuous_vol_down_nums>=4)
		{
			result_value=7;
			double vol_pre_value=vec_vol[length-2];
			double vol_value=vec_vol[length-1];

		/*	double f_per=(vol_value*100.0)/vol_pre_value;

			if(f_per>=95.0)
			{
				result_value=3;
			}*/


		}
		else
		{
			continuous_vol_down_nums=0;
			vol_pre=vec_vol[length-4];

			for(int i=length-3;i<length;i++)
			{

				double vol=vec_vol[i];
				if(vol_pre>=vol)
				{
					continuous_vol_down_nums++;
				}
				else
				{
					break;
				}
				vol_pre=vol;
			}


			if(continuous_vol_down_nums>=3)
			{
				result_value=5;
			}
			else
			{
				continuous_vol_down_nums=0;
				vol_pre=vec_vol[length-3];
				for(int i=length-2;i<length;i++)
				{

					double vol=vec_vol[i];
					if(vol_pre>=vol)
					{
						continuous_vol_down_nums++;
					}
					else
					{
						break;
					}
					vol_pre=vol;
				}
				if(continuous_vol_down_nums>=2)
				{
					result_value=2;
				}

			}

		}


		if(result_value>=7)
		{
			/*int length=vec_price.size();

			double price_pre=vec_price[length-5];

			for(int i=length-4;i<length;i++)
			{
				double price=vec_price[i];
				double f_per=((price-price_pre)*100.0)/price_pre;
				
				if(f_per>2.0)
				{
					
					result_value=3;

					break;
				}

				price_pre=price;
			}*/

		}
		else if(result_value>=4)
		{
			/*int length=vec_price.size();

			double price_pre=vec_price[length-4];

			for(int i=length-3;i<length;i++)
			{
				double price=vec_price[i];
				double f_per=((price-price_pre)*100.0)/price_pre;

				if(f_per>2.0)
				{
					result_value=2;
					break;
				}

				price_pre=price;
			}*/

		}
		return result_value;
	
	
}

//计算上涨系数 量
int CDlgDropOff::CalcUpCoeff_Vol_2(std::vector<double> & vec_vol,std::vector<double> & vec_vol_ma5,std::vector<double> & vec_vol_ma10,std::vector<double> & vec_price)
{

	int length=vec_vol_ma5.size();

	int continuous_vol_down_nums_1=0;		//连续成交量缩量次数

	int result_value=0;

	double vol_pre=vec_vol[length-6];

	for(int i=length-5;i<length-3;i++)
	{
		double vol=vec_vol[i];
		if(vol_pre>=vol)
		{
			continuous_vol_down_nums_1++;
		}
		else
		{
			break;
		}
		vol_pre=vol;
	}

	int continuous_vol_down_nums_2=0;
	vol_pre=vec_vol[length-3];
	for(int i=length-2;i<length;i++)
	{
		double vol=vec_vol[i];
		if(vol_pre>=vol)
		{
			continuous_vol_down_nums_2++;
		}
		else
		{
			break;
		}
		vol_pre=vol;

	}

	if( (continuous_vol_down_nums_1>=2) && (continuous_vol_down_nums_2>=2))
	{
		result_value=4;
	}

	if(result_value>=4)
	{
		int length=vec_price.size();

		double price_pre=vec_price[length-6];

		for(int i=length-5;i<length;i++)
		{
			double price=vec_price[i];
			double f_per=((price-price_pre)*100.0)/price_pre;

			if(f_per>2.0)
			{
			
				result_value=3;
				break;
			}

			price_pre=price;
		}

	}

	return result_value;

}

//计算上涨系数 量
int  CDlgDropOff::CalcUpCoeff_Vol_3(std::vector<double> & vec_vol,std::vector<double> & vec_vol_ma5,std::vector<double> & vec_vol_ma10,std::vector<double> & vec_price)
{
	int length=vec_vol_ma5.size();

	int continuous_vol_down_nums=0;		//连续成交量缩量次数


	int result_value=0;

	double vol_pre=vec_vol[length-6];

	for(int i=length-5;i<length;i++)
	{
		double vol=vec_vol[i];
		if(vol_pre>=vol)
		{
			continuous_vol_down_nums++;
		}
		else
		{
			break;
		}
		vol_pre=vol;
	}

	if(continuous_vol_down_nums>=5)
	{

		result_value=9;
	}

	if(result_value>=9)
	{
		int length=vec_price.size();

		double price_pre=vec_price[length-6];

		for(int i=length-5;i<length;i++)
		{
			double price=vec_price[i];
			double f_per=((price-price_pre)*100.0)/price_pre;

			if(f_per>2.0)
			{
				
				if(f_per>4.0)
					result_value=3;
				else if(f_per>3.0)
					result_value=4;
				else
					result_value=6;

				break;
			}

			price_pre=price;
		}

	}

	return result_value;
}

//计算上涨系数 量
int CDlgDropOff::CalcUpCoeff_Vol_4(std::vector<double> & vec_vol,std::vector<double> & vec_vol_ma5,std::vector<double> & vec_vol_ma10,std::vector<double> & vec_price)
{
	int length=vec_vol_ma5.size();

	int continuous_vol_down_nums_1=0;		//连续成交量缩量次数

	int result_value=0;

	double vol_pre=vec_vol[length-8];

	for(int i=length-7;i<length-4;i++)
	{
		double vol=vec_vol[i];
		if(vol_pre>=vol)
		{
			continuous_vol_down_nums_1++;
		}
		else
		{
			break;
		}
		vol_pre=vol;
	}

	int continuous_vol_down_nums_2=0;
	vol_pre=vec_vol[length-4];
	for(int i=length-3;i<length;i++)
	{
		double vol=vec_vol[i];
		if(vol_pre>=vol)
		{
			continuous_vol_down_nums_2++;
		}
		else
		{
			break;
		}
		vol_pre=vol;

	}

	if( (continuous_vol_down_nums_1>=3) && (continuous_vol_down_nums_2>=3))
	{
		result_value=8;
	}

	if(result_value>=8)
	{
		int length=vec_price.size();

		double price_pre=vec_price[length-8];

		for(int i=length-7;i<length;i++)
		{
			double price=vec_price[i];
			double f_per=((price-price_pre)*100.0)/price_pre;

			if(f_per>2.0)
			{
				if(f_per>4.0)
					result_value=3;
				else if(f_per>3.0)
					result_value=4;
				else
					result_value=6;
				break;
			}

			price_pre=price;
		}

	}

	return result_value;
}


//计算上涨系数 量
int CDlgDropOff::CalcUpCoeff_Vol_Addition_1(std::vector<double> & vec_vol,std::vector<double> & vec_price,double rsi_1)
{
	int length=vec_vol.size();
	double pre_vol=vec_vol[length-2];
	double vol=vec_vol[length-1];

	double pre_pre_price=vec_price[length-3];
	double pre_price=vec_price[length-2];
	double price=vec_price[length-1];

	double rsi1=rsi_1;

	double f_price_pert_pre=(pre_price-pre_pre_price)*100.0/pre_pre_price;
	double f_price_pert=(price-pre_price)*100.0/pre_price;

	double f_vol_pert=(vol*100.0)/pre_vol;
	bool bOk=false;
	bool bOk2=false;
	if((f_vol_pert<63.0)&&(f_price_pert<0.5))
	{
		if(f_price_pert_pre<=-2.5||(f_price_pert_pre+f_price_pert)<-3.5)
		{
			if(rsi1>10.0&&rsi1<28.0)
			{
				if(f_price_pert>=-0.5)
				{
					bOk=true;
				}
				else
				{
					bOk2=true;
				}
			}
			else if(rsi1<=10.0)
			{

				bOk=true;
			}
			else
			{
				bOk2=true;
			}

		}
		
	}

	if(bOk)
		return 4;
	else if(bOk2)
		return 3;

	return 0;

}


//计算上涨系数 价
int CDlgDropOff::CalcUpCoeff_Price_1(std::vector<double> & vec_price,std::vector<double> & vec_price_ma5,std::vector<double> & vec_price_ma10)
{
	
		int length=vec_price.size();

		int continuous_price_down_nums=0;		//连续成交量缩量次数

		int result_value=0;

		double price_pre=vec_price[length-5];

		for(int i=length-4;i<length;i++)
		{
			double price=vec_price[i];
			if(price_pre>=price)
			{
				continuous_price_down_nums++;
			}
			else
			{
				break;
			}
			price_pre=price;
		}

		if(continuous_price_down_nums>=4)
		{
			result_value=1;
		}
		
		return result_value;
}

BOOL CDlgDropOff::DoFilterKDJ2(void)
{
	DropOffData *pDropOffData=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	for(int i=0;i<vecDropOffData.size();i++)
	{
		pDropOffData=vecDropOffData[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(pDropOffData->strStockCode);

		if(bUsePreDate)
		{
			CTime mDropOffTime;
			mDataTimeDropOff.GetTime(mDropOffTime);
			strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		}
		else
		{
			CTime mDropOffTime=CTime::GetCurrentTime();
			strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		}


		


		CStockKDJData *pStockKDJData=NULL;
		pStockKDJData=CStockKDJArithmetic::CalcKDJData(pDropOffData->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
		if(pStockKDJData==NULL)
			continue;

		std::vector<double> vec_ma5,vec_ma10;
		vec_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_volume_price);
		vec_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_volume_price);
		int size=vec_ma5.size();

		double f_total_value=0.0;
		
		bool bUpLimit;
		bool bDownLimit;
		for(int j=size-mKdjNums;j<size;j++)
		{
			double pre_end=pStockKDJData->vec_close_price[j-1];
			double end=pStockKDJData->vec_close_price[j];
			double f=-((end-pre_end)*100.0/pre_end);
			bUpLimit=false;
			bDownLimit=false;
			if(f<-9.9)		//涨停
				bUpLimit=true;
			if(f>9.9)
				bDownLimit=true;
			int mMulNums=size-j+1;

			double g;

			g=1.0;

			for(int n=0;n<mMulNums;n++)
			{
				g=g*0.9;

			}


			if(!bUpLimit)
				f=f*g;
			f_total_value+=f;

		}

		
	
		pDropOffData->fAveMultiple=f_total_value;
		pDropOffData->fMaxMultiple=0.0;
		pDropOffData->mMaxValuePassDay=0;
	}

	std::sort(vecDropOffData.begin(), vecDropOffData.end(), sortFun);
	return TRUE;
}

//KDJ过滤
void CDlgDropOff::OnBnClickedBtnKdjFilter()
{
	CDlgKdjPara dlg;
	if(dlg.DoModal()==IDOK)
	{
		mKdjNums=dlg.GetKDJNums();
		mKdjMuls=dlg.GetKDJMuls();
		mRsiPreNums=dlg.GetRsiPreNums();

		//AfxBeginThread(RunFilterKdjProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
		RunFilterKdjProc(this);
	}	
}


static UINT  RunFilterM5M10M20Proc(LPVOID pParam)
{
	CDlgDropOff *pDlgDropOff;
	pDlgDropOff=(CDlgDropOff *)pParam;

	pDlgDropOff->DoFilterM5M10M20Up();
	pDlgDropOff->FilterByReserve();
	pDlgDropOff->SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return 0;
}


static UINT  RunSerialKeepDownProc(LPVOID pParam)
{
	CDlgDropOff *pDlgDropOff;
	pDlgDropOff=(CDlgDropOff *)pParam;

	pDlgDropOff->DoFilterSerialKeepDown();
	pDlgDropOff->FilterByReserve();
	pDlgDropOff->FilterByMerge();
	pDlgDropOff->SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return 0;
}


static UINT  RunFilterTanAngleProc(LPVOID pParam)
{
	CDlgDropOff *pDlgDropOff;
	pDlgDropOff=(CDlgDropOff *)pParam;

	pDlgDropOff->DoFilterTanAngle();
	pDlgDropOff->FilterByReserve();
	pDlgDropOff->SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return 0;
}

static UINT  RunFilterMulTanAngleProc(LPVOID pParam)
{
	CDlgDropOff *pDlgDropOff;
	pDlgDropOff=(CDlgDropOff *)pParam;

	pDlgDropOff->DoFilterMulTanAngle();
	pDlgDropOff->FilterByReserve();
	pDlgDropOff->SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return 0;
}


static UINT  RunFilterSingleTanAngleProc(LPVOID pParam)
{
	CDlgDropOff *pDlgDropOff;
	pDlgDropOff=(CDlgDropOff *)pParam;

	pDlgDropOff->DoFilterSingleTanAngle();
	pDlgDropOff->FilterByReserve();
	pDlgDropOff->SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return 0;
}

static UINT  RunFilterCMMatchProc(LPVOID pParam)
{
	CDlgDropOff *pDlgDropOff;
	pDlgDropOff=(CDlgDropOff *)pParam;

	pDlgDropOff->DoFilterCMMatch();
	pDlgDropOff->FilterByReserve();
	pDlgDropOff->SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return 0;
}


//M5 M10 M20 Up
void CDlgDropOff::OnBnClickedBtn3mUp()
{

	CDlgSFSel dlg;

	if(dlg.DoModal()==IDOK)
	{
		int mSFSel=dlg.GetSFSel();
		if(mSFSel==0)		//K线分析-1
		{

			bReserveFilter=mCheckReserveFilter.GetCheck();
			bMergeFilter=mCheckMergeFilter.GetCheck();
			if(bReserveFilter&&bMergeFilter)
			{
				AfxMessageBox("不能同时两种过滤");
				return;
			}

			/*if(bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve=vecDropOffData;
			}

			if(bMergeFilter)
			{

				vecDropOffData_Merge.clear();
				vecDropOffData_Merge=vecDropOffData;
			}

			vecDropOffData.clear();*/
			//AfxBeginThread(RunSerialKeepDownProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
			RunSerialKeepDownProc(this);
		}
		else if(mSFSel==1)
		{
			bReserveFilter=mCheckReserveFilter.GetCheck();

			if(bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve=vecDropOffData;
			}

			vecDropOffData.clear();
			//AfxBeginThread(RunFilterM5M10M20Proc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
			RunFilterM5M10M20Proc(this);
		}
		else if(mSFSel==2)	//均线三角形
		{

			CDlgTanAngle dlg;
			if(dlg.DoModal()==IDOK)
			{
				mBackDays=dlg.GetBackDays();
				mMaxAngle=dlg.GetMaxAngle();
				f_max_volume_multiple=dlg.GetMaxVolumeMultiple();
				bIgnoreM5=dlg.IsIgnoreM5();
				bUseM120=dlg.IsIgnoreM60();
				bUseAllUp=dlg.IsUseAllUp();
				mMaxInsBack=dlg.GetMaxInsBack();
				f_max_ins_thes=dlg.GetMaxInsThes();
				mKLineType = dlg.GetKLineType();
				bReserveFilter=mCheckReserveFilter.GetCheck();

				if(bReserveFilter)
				{
					vecDropOffData_Reserve.clear();
					vecDropOffData_Reserve=vecDropOffData;
				}

				vecDropOffData.clear();
				vecTanAngleData.clear();
				//AfxBeginThread(RunFilterTanAngleProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
				RunFilterTanAngleProc(this);

			}

			
		}
		else if(mSFSel==3)	//Tan配套
		{

			bReserveFilter=mCheckReserveFilter.GetCheck();

			if(bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve=vecDropOffData;
			}

			vecDropOffData.clear();
			
			//DoFilterTanMatch();
			DoFilterKLinePregnant();

			//AfxBeginThread(RunFilterCMMatchProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
		}
		else if(mSFSel==4)		//多日Tan
		{
			CDlgTanAngle dlg;
			CDlgDays dlg2;
			if(dlg.DoModal()==IDOK)
			{
				if(dlg2.DoModal()==IDOK)
				{
					mMulDays=dlg2.GetDayNums();
					mBackDays=dlg.GetBackDays();
					mMaxAngle=dlg.GetMaxAngle();
					f_max_volume_multiple=dlg.GetMaxVolumeMultiple();
					mMaxInsBack=dlg.GetMaxInsBack();
					f_max_ins_thes=dlg.GetMaxInsThes();
					bIgnoreM5=dlg.IsIgnoreM5();



					bReserveFilter=mCheckReserveFilter.GetCheck();

					if(bReserveFilter)
					{
						vecDropOffData_Reserve.clear();
						vecDropOffData_Reserve=vecDropOffData;
					}

					vecDropOffData.clear();
					vecTanAngleData.clear();
					//AfxBeginThread(RunFilterMulTanAngleProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
					RunFilterMulTanAngleProc(this);
				}
				

			}

		}
		else if(mSFSel==5)	//Tan配套2
		{
			bReserveFilter=mCheckReserveFilter.GetCheck();

			if(bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve=vecDropOffData;
			}

			vecDropOffData.clear();

			DoFilterTanMatch2();
		}
		else if(mSFSel==6)	//RSI
		{
			bReserveFilter=mCheckReserveFilter.GetCheck();

			if(bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve=vecDropOffData;
			}

			vecDropOffData.clear();
			DoFilterRsiMatch();
		}
		else if(mSFSel==7)	//单日Tan
		{
			CDlgTanAngle dlg;
			CDlgDays dlg2;
			if(dlg.DoModal()==IDOK)
			{
				if(dlg2.DoModal()==IDOK)
				{
					mMulDays=dlg2.GetDayNums();
					mBackDays=dlg.GetBackDays();
					mMaxAngle=dlg.GetMaxAngle();
					f_max_volume_multiple=dlg.GetMaxVolumeMultiple();
					bIgnoreM5=dlg.IsIgnoreM5();



					bReserveFilter=mCheckReserveFilter.GetCheck();

					if(bReserveFilter)
					{
						vecDropOffData_Reserve.clear();
						vecDropOffData_Reserve=vecDropOffData;
					}

					vecDropOffData.clear();
					vecTanAngleData.clear();
					//AfxBeginThread(RunFilterSingleTanAngleProc,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0,NULL);
					RunFilterSingleTanAngleProc(this);
				}


			}
		}
		else if(mSFSel==8) //长量均增长
		{
			vecDropOffData.clear();

			DoFilterLongAveGroup();
		}
		else if(mSFSel==9)//Tan配套3
		{
			bReserveFilter=mCheckReserveFilter.GetCheck();

			if(bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve=vecDropOffData;
			}

			vecDropOffData.clear();

			DoFilterTanMatch3();
		}
		else if(mSFSel==10)//Tan配套4
		{
			bReserveFilter=mCheckReserveFilter.GetCheck();

			if(bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve=vecDropOffData;
			}

			vecDropOffData.clear();

			DoFilterTanMatch4();
		}
		else if(mSFSel==11)//Tan配套5
		{
			bReserveFilter=mCheckReserveFilter.GetCheck();

			if(bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve=vecDropOffData;
			}

			vecDropOffData.clear();

			DoFilterTanMatch5();

		}
		else if(mSFSel==12)//Tan配套6
		{
			bReserveFilter=mCheckReserveFilter.GetCheck();

			if(bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve=vecDropOffData;
			}

			vecDropOffData.clear();

			DoFilterTanMatch6();

		}
		else if(mSFSel==13)//Tan配套7
		{
			bReserveFilter=mCheckReserveFilter.GetCheck();

			if(bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve=vecDropOffData;
			}

			//vecDropOffData.clear();
			DoFilterTanMatch7();
		}
		else if(mSFSel==14)//Tan配套8
		{
			bReserveFilter=mCheckReserveFilter.GetCheck();

			if(bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve=vecDropOffData;
			}

			DoFilterTanMatch8();
		}
		else if(mSFSel==15)//TAN配套9(长间隔)
		{

			bReserveFilter = mCheckReserveFilter.GetCheck();

			if (bReserveFilter)
			{
				vecDropOffData_Reserve.clear();
				vecDropOffData_Reserve = vecDropOffData;
			}

			vecDropOffData.clear();
			DoFilterTanMatch9();
		}
		else if(mSFSel==16) //行业选择
		{
			CDlgIndustrySel dlg;
			if (dlg.DoModal() == IDOK)
			{
				IndustryData* pIndustryData = dlg.GetSelIndustryData();
				BOOL bReVerseSel = dlg.IsReVerseSel();

				if (bReVerseSel)
				{
					DoReverseFilterIndustyInfo(pIndustryData);
				}
				else
				{
					DoFilterIndustyInfo(pIndustryData);
				}
				
			}
			
		}

	}

	
}


BOOL CDlgDropOff::DoFilterM5M10M20Up(void)
{

	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		try
		{
			pStockCode=vecStockCodeList[i];
			pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);


			if(bUsePreDate)
			{
				CTime mDropOffTime;
				mDataTimeDropOff.GetTime(mDropOffTime);
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}
			else
			{
				CTime mDropOffTime=CTime::GetCurrentTime();
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}

			CStockKDJData *pStockKDJData=NULL;

			pStockKDJData=CStockKDJArithmetic::CalcKDJData(pStockCode->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
			if(pStockKDJData==NULL)
				continue;

			std::vector<double> vec_ma5,vec_ma10,vec_ma20,vec_ma60;
			vec_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
			vec_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
			vec_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
			vec_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);
			
			//pStockKDJData->vec_close_price
			BOOL  bContiusDown=TRUE;
			BOOL  bContiusAllUp=FALSE;
			BOOL  bM10Big5Big20=FALSE;
			BOOL  bUpM60Value=FALSE;
			double fUpM60Value=0.0;
			int size=pStockKDJData->vec_volume_price.size();

			BOOL bOk=true;

			for(int j=size-3;j<size;j++)		//连续3次前一日成交额大于今日
			{
				double f_pre_volume_price=pStockKDJData->vec_volume_price[j-1];
				double f_now_volume_price=pStockKDJData->vec_volume_price[j];

				if(f_now_volume_price>=f_pre_volume_price)
				{
					bOk=false;
					break;
				}

			}

			if(!bOk)
				continue;


			for(int j=size-3;j<size;j++)	//连续3次涨幅大小在-1.5-1.5
			{
				double f_pre_close_price=pStockKDJData->vec_close_price[j-1];
				double f_now_close_price=pStockKDJData->vec_close_price[j];
				
				double f_per=(f_now_close_price-f_pre_close_price)*100.0/f_pre_close_price;

				f_per=fabs(f_per);
				if(f_per>=1.5)
				{
					bOk=false;
					break;
				}

			}

			if(!bOk)
				continue;
			bOk=false;
			int mNums=0;
			for(int j=size-4;j<size;j++)		//4日内跌幅的数额要大于等于3
			{
				double f_pre_close_price=pStockKDJData->vec_close_price[j-1];
				double f_now_close_price=pStockKDJData->vec_close_price[j];
				double f_per=(f_now_close_price-f_pre_close_price)*100.0/f_pre_close_price;
				if(f_per<0.0)
				{
					mNums++;
				}
			}
			printf("%s %d\n",pStockCode->strStockCode,mNums);
			if(mNums>=3)
				bOk=true;
			if(!bOk)			//不满足4日内跌幅的数额要大于等于3
			{
				bOk=false;
				int mM5Nums=0;
				for(int j=size-4;j<size;j++)
				{
					double f_pre_value=vec_ma5[j-1];
					double f_now_value=vec_ma5[j];
					if(f_now_value>=f_pre_value)
					{
						mM5Nums++;
					}
				}
				printf("%s mM5Nums=%d\n",pStockCode->strStockCode,mM5Nums);
				if(mM5Nums>=3)	//4日内 价格M5均线是连续上升的（上升次数>=3)
					bOk=true;
				
				if(!bOk)
					continue;
				for(int j=size-4;j<size;j++)
				{
					double f_pre_value=vec_ma10[j-1];
					double f_now_value=vec_ma10[j];
					if(f_now_value<f_pre_value)
					{
						bOk=false;
						break;
					}
				}

				if(!bOk)	//4日内 价格M10均线是连续上升的
					continue;
				for(int j=size-4;j<size;j++)
				{
					double f_pre_value=vec_ma20[j-1];
					double f_now_value=vec_ma20[j];
					if(f_now_value<f_pre_value)
					{
						bOk=false;
						break;
					}
				}
				if(!bOk)	//4日内 价格M20均线是连续上升的
					continue;
				bContiusDown=FALSE;

				BOOL bAllUp=true;
				for(int j=size-10;j<size;j++)		//10日内 价格M20均线是连续上升的 bAllUp=true;
				{
					double f_pre_value=vec_ma20[j-1];
					double f_now_value=vec_ma20[j];
					if(f_now_value<f_pre_value)
					{
						bAllUp=false;
						break;
					}
				}

				if(bAllUp)
				{
					for(int j=size-10;j<size;j++)	//10日内 价格M60均线是连续上升的 bAllUp=true;
					{
						double f_pre_value=vec_ma60[j-1];
						double f_now_value=vec_ma60[j];
						if(f_now_value<f_pre_value)
						{
							bAllUp=false;
							break;
						}
					}

				}

				bContiusAllUp=bAllUp;

			}
			else	//满足4日内跌幅的数额要大于等于3
			{
				double f_per=0.0;
				double f_60_value=vec_ma60[size-1];
				double f_5_value=vec_ma5[size-1];
				if(f_5_value>f_60_value)
				{
					f_per=(f_5_value-f_60_value)*100.0/f_60_value;
					printf("%s f_per_60=%f\n",pStockCode->strStockCode,f_per);
					if(f_per>=5.0)
					{
						bUpM60Value=TRUE;
						fUpM60Value=f_per;
					}
				}

				if(f_per<5.0)
				{
					double f_5_value=vec_ma5[size-1];
					double f_10_value=vec_ma10[size-1];
					double f_20_value=vec_ma20[size-1];
					if(f_10_value>f_5_value)
					{
						if(f_5_value>f_20_value)
						{
							bM10Big5Big20=TRUE;
						}

					}
				}

				if(f_per<5.0&&(!bM10Big5Big20))		//在60日线下的暂时不用
					continue;


			}

			if(!bContiusDown&&!bContiusAllUp) //不满足4日内跌幅的数额要大于等于3 同时不是强势股 不用
			{
				continue;		
			}

			
			DropOffData *pDropOffData=new DropOffData();
			pDropOffData->strStockCode=pStockCode->strStockCode;
			pDropOffData->strStockName=pStockCode->strStockName;
			if(bContiusDown)	
			{
				if(bM10Big5Big20)
					pDropOffData->fMaxMultiple=1.0;
				else
					pDropOffData->fMaxMultiple=0.0;
			}
			else	//不满足4日内跌幅的数额要大于等于3
			{
				if(bContiusAllUp)	//TRUE 表示 M20 M60 10日内都上升，是强势股
					pDropOffData->fMaxMultiple=3.0;
				else
					pDropOffData->fMaxMultiple=2.0; //4日内 价格M10均线是连续上升的 
			}
			pDropOffData->fAveMultiple=0.0;
			pDropOffData->strMaxDate=strNowDate;
			pDropOffData->strMinDate=strNowDate;
			if(bUpM60Value)
				pDropOffData->mMaxValuePassDay=fUpM60Value;
			else
				pDropOffData->mMaxValuePassDay=0;
			pDropOffData->fDownTotalRang=0.0;
			vecDropOffData.push_back(pDropOffData);


		}
		catch(...)
		{
			printf("catch DoFilterM5M10M20Up\n");
		}
	}
	return TRUE;
}

//-----------------------------------------------------------------------
#if 0
BOOL  CDlgDropOff::DoFilterSerialKeepDown(void)
{

	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		try
		{
			pStockCode=vecStockCodeList[i];
			pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
			
			/*if(pStockCode->strStockCode=="SH600829")
			{
				int a=0;
				a++;
			}*/

			if(bUsePreDate)
			{
				CTime mDropOffTime;
				mDataTimeDropOff.GetTime(mDropOffTime);
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}
			else
			{
				CTime mDropOffTime=CTime::GetCurrentTime();
				strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}

			CStockKDJData *pStockKDJData=NULL;

			pStockKDJData=CStockKDJArithmetic::CalcKDJData(pStockCode->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
			if(pStockKDJData==NULL)
				continue;

			std::vector<double> vec_ma5,vec_ma10;
			vec_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_volume_price);
			vec_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_volume_price);
			
			std::vector<double> vec_price_ma5,vec_price_ma10,vec_price_ma20;
			vec_price_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
			vec_price_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
			vec_price_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
			int size=pStockKDJData->vec_volume_price.size();

			int mClacSize=14;

			BOOL bOk=TRUE;
			int mNums=0;
			for(int j=size-mClacSize;j<size;j++)		//10日平均成交额要连续小于前一日10日平均成交额
			{
				double f_pre_m10_volume=vec_ma10[j-1];
				double f_now_m10_volume=vec_ma10[j];

				if(f_now_m10_volume>f_pre_m10_volume)
				{
					mNums++;
				}

			}

			if(mNums>=2)
				bOk=FALSE;

			if(!bOk)
				continue;

			mNums=0;
			for(int j=size-mClacSize;j<size;j++)		//5日平均成交额要连续小于10日平均成交额
			{
				double f_now_m10_volume=vec_ma10[j];
				double f_now_m5_volume=vec_ma5[j];
				if(f_now_m5_volume>f_now_m10_volume)
				{
					mNums++;
				}
			}

			if(mNums>=1)
				bOk=FALSE;

			if(!bOk)
				continue;

			int mNumsM10=0;
			int mNumsM5=0;
			for(int j=size-mClacSize;j<size;j++)
			{
				double f_now_volume=pStockKDJData->vec_volume_price[j];
				double f_now_m10_volume=vec_ma10[j];
				double f_now_m5_volume=vec_ma5[j];

				if(f_now_volume>f_now_m10_volume)
				{
					mNumsM10++;
					
					double f_pert=(f_now_volume-f_now_m10_volume)*100.0/f_now_m10_volume;
					if(f_pert>10.0) //当前成交额大于10日平均成交额10%
					{
						double f_pre_close_price=pStockKDJData->vec_close_price[j-1];
						double f_now_close_price=pStockKDJData->vec_close_price[j];
						double f_per=(f_now_close_price-f_pre_close_price)*100.0/f_pre_close_price;
						if(f_per>=-2.0)
						{
							bOk=FALSE;
							break;
						}
							
					}
				}
				if(f_now_volume>f_now_m5_volume)
					mNumsM5++;
			}
		
			if(mNumsM10>=2)
				bOk=FALSE;
			if(mNumsM5>=6)
				bOk=FALSE;
			if(!bOk)
				continue;

			//printf("%s vol big m5 nums %d  vol big m10 nums %d\n",pStockCode->strStockCode,mNumsM5,mNumsM10);

			mNums=0;
			for(int j=size-mClacSize;j<size;j++)//5日平均成交额要连续大于10日平均成交额的70% 
			{
				double f_now_m10_volume=vec_ma10[j];
				double f_now_m5_volume=vec_ma5[j];

				double f_per=f_now_m5_volume*100.0/f_now_m10_volume;
				//printf("%s %f\n",pStockCode->strStockCode,f_per);
				if(f_per<=75.0)
					mNums++;
			}

			if(mNums>1)
			{
				bOk=FALSE;
			}
			if(!bOk)
				continue;


			int m_Low_70_Nums=0;
			int m_70_85_Nums=0;
			int m_85_100_Nums=0;
			int m_100_110_Nums=0;
			int m_Big_110_Nums=0;

			for(int j=size-20;j<size;j++)//5日平均成交额要连续大于10日平均成交额的75% 
			{
				double f_now_m10_volume=vec_ma10[j];
				double f_now_m5_volume=vec_ma5[j];

				double f_per=f_now_m5_volume*100.0/f_now_m10_volume;
				//printf("%s %f\n",pStockCode->strStockCode,f_per);
				if(f_per<=70.0)
					m_Low_70_Nums++;
				else if(f_per>70.0&&f_per<=85.0)
					m_70_85_Nums++;
				else if(f_per>85.0&&f_per<=100.0)
					m_85_100_Nums++;
				else if(f_per>100.0&&f_per<=110.0)
					m_100_110_Nums++;
				else
					m_Big_110_Nums++;

			}
			BOOL bMark2=FALSE;
			if(m_Low_70_Nums==0&&m_Big_110_Nums==0)
			{
				if((m_70_85_Nums+m_85_100_Nums)>=17)
				{
					bMark2=TRUE;
				}

			}
			//printf("%s %d  %d \n",pStockCode->strStockCode,m_70_85_Nums,m_85_100_Nums);


			
			BOOL bMark=FALSE;
			double f_now_price_m5=vec_price_ma5[size-1];

			double f_now_price_m10=vec_price_ma10[size-1];

			double f_now_price_m20=vec_price_ma20[size-1];

			double f_price_m5_m20_pert=f_now_price_m5*100.0/f_now_price_m20;

			printf("%s %f \n",pStockCode->strStockCode,f_price_m5_m20_pert);

			if(f_price_m5_m20_pert>=97.0)
			{
				bMark=TRUE;
			}


		

			DropOffData *pDropOffData=new DropOffData();
			pDropOffData->strStockCode=pStockCode->strStockCode;
			pDropOffData->strStockName=pStockCode->strStockName;
			if(bMark&&bMark2)
				pDropOffData->fMaxMultiple=3.0;
			else
			{
				if(bMark2)
					pDropOffData->fMaxMultiple=2.0;
				else
				{
					if(bMark)
						pDropOffData->fMaxMultiple=1.0;
					else
						pDropOffData->fMaxMultiple=0.0;
				}
			}
			pDropOffData->fAveMultiple=0.0;
			pDropOffData->strMaxDate=strNowDate;
			pDropOffData->strMinDate=strNowDate;
			
			pDropOffData->mMaxValuePassDay=0;
			pDropOffData->fDownTotalRang=0.0;
			vecDropOffData.push_back(pDropOffData);

		}
		catch(...)
		{
			printf("catch DoFilterM5M10M20Up\n");
		}
	}

	return TRUE;
}
#else
BOOL  CDlgDropOff::DoFilterSerialKeepDown(void)
{
	CKLineFilterAlg mKLineFilterAlg;
	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}

	vecKLineFilterData.clear();
	vecKLineFilterData=mKLineFilterAlg.doFilter(mDropOffTime,vecDropOffData);
	vecDropOffData.clear();
	for(int i=0;i<vecKLineFilterData.size();i++)
	{
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecKLineFilterData[i]->strStockCode;
		pDropOffData->strStockName=vecKLineFilterData[i]->strStockName;
		pDropOffData->fMaxMultiple=0;
		pDropOffData->fAveMultiple=0;
		CString strInfo;
		if(vecKLineFilterData[i]->mBollType==BOLL_OUT_UP)
			strInfo="boll out up";
		else if(vecKLineFilterData[i]->mBollType==BOLL_EMBED_UP)
			strInfo="boll embed up";
		else if(vecKLineFilterData[i]->mBollType==BOLL_IN_UP_MIDDLE)
			strInfo="boll in up middle";
		else if(vecKLineFilterData[i]->mBollType==BOLL_EMBED_MIDDLE)
			strInfo="boll embed middle";
		else if(vecKLineFilterData[i]->mBollType==BOLL_IN_MIDDLE_BOTTOM)
			strInfo="boll in middle  bottom";
		else if(vecKLineFilterData[i]->mBollType==BOLL_EMBED_BOTTOM)
			strInfo="boll embed  bottom";
		else if(vecKLineFilterData[i]->mBollType==BOLL_OUT_BOTTOM)
			strInfo="boll out  bottom";
		else
			strInfo="null";
		pDropOffData->strMaxDate=strInfo;

		double f_total_per=vecKLineFilterData[i]->f_total_per;
		double f_up_per_b=vecKLineFilterData[i]->f_up_per_b;
		double f_bottom_per_b=vecKLineFilterData[i]->f_bottom_per_b;
		double f_body_per_b=vecKLineFilterData[i]->f_body_per_b;

		strInfo.Format("total:%.2f up:%.2f bottom:%.2f body:%.2f",f_total_per,f_up_per_b,f_bottom_per_b,f_body_per_b);
		pDropOffData->strMinDate=strInfo;

		pDropOffData->mMaxValuePassDay=0;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=0;
		pDropOffData->mSpecNums=0;

		double f_p4_per=vecKLineFilterData[i]->f_p4_per;
		double f_p3_per=vecKLineFilterData[i]->f_p3_per;
		double f_p2_per=vecKLineFilterData[i]->f_p2_per;
		double f_p1_per=vecKLineFilterData[i]->f_p1_per;
		double f_now_per=vecKLineFilterData[i]->f_now_per;

		strInfo.Format("p4:%.2f p3:%.2f p2:%.2f p1:%.2f now:%.2f",f_p4_per,f_p3_per,f_p2_per,f_p1_per,f_now_per);

		pDropOffData->strInfo=strInfo;
		vecDropOffData.push_back(pDropOffData);
	}


	return TRUE;
}
#endif


BOOL CDlgDropOff::DoFilterKLineMatch(void)
{
	KLineFilterData *pKLineFilterData=NULL;

	for(int i=0;i<vecKLineFilterData.size();i++)
	{
		pKLineFilterData=vecKLineFilterData[i];

		BOOL bOk=FALSE;
		double f_1_per=pKLineFilterData->f_p1_per;
		if(f_1_per<-6.0)
			bOk=TRUE;
		else
		{
			double f_2_per=pKLineFilterData->f_p1_per+pKLineFilterData->f_p2_per;
			if(f_2_per<-9.0)
				bOk=TRUE;
		}

		if(!bOk)
			continue;

		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecKLineFilterData[i]->strStockCode;
		pDropOffData->strStockName=vecKLineFilterData[i]->strStockName;
		pDropOffData->fMaxMultiple=0;
		pDropOffData->fAveMultiple=0;
		CString strInfo;
		if(vecKLineFilterData[i]->mBollType==BOLL_OUT_UP)
			strInfo="boll out up";
		else if(vecKLineFilterData[i]->mBollType==BOLL_EMBED_UP)
			strInfo="boll embed up";
		else if(vecKLineFilterData[i]->mBollType==BOLL_IN_UP_MIDDLE)
			strInfo="boll in up middle";
		else if(vecKLineFilterData[i]->mBollType==BOLL_EMBED_MIDDLE)
			strInfo="boll embed middle";
		else if(vecKLineFilterData[i]->mBollType==BOLL_IN_MIDDLE_BOTTOM)
			strInfo="boll in middle  bottom";
		else if(vecKLineFilterData[i]->mBollType==BOLL_EMBED_BOTTOM)
			strInfo="boll embed  bottom";
		else if(vecKLineFilterData[i]->mBollType==BOLL_OUT_BOTTOM)
			strInfo="boll out  bottom";
		else
			strInfo="null";
		pDropOffData->strMaxDate=strInfo;

		double f_total_per=vecKLineFilterData[i]->f_total_per;
		double f_up_per_b=vecKLineFilterData[i]->f_up_per_b;
		double f_bottom_per_b=vecKLineFilterData[i]->f_bottom_per_b;
		double f_body_per_b=vecKLineFilterData[i]->f_body_per_b;

		strInfo.Format("total:%.2f up:%.2f bottom:%.2f body:%.2f",f_total_per,f_up_per_b,f_bottom_per_b,f_body_per_b);
		pDropOffData->strMinDate=strInfo;

		pDropOffData->mMaxValuePassDay=0;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=0;
		pDropOffData->mSpecNums=0;

		double f_p4_per=vecKLineFilterData[i]->f_p4_per;
		double f_p3_per=vecKLineFilterData[i]->f_p3_per;
		double f_p2_per=vecKLineFilterData[i]->f_p2_per;
		double f_p1_per=vecKLineFilterData[i]->f_p1_per;
		double f_now_per=vecKLineFilterData[i]->f_now_per;

		strInfo.Format("p4:%.2f p3:%.2f p2:%.2f p1:%.2f now:%.2f",f_p4_per,f_p3_per,f_p2_per,f_p1_per,f_now_per);

		pDropOffData->strInfo=strInfo;
		vecDropOffData.push_back(pDropOffData);

	}
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);

	return TRUE;
}
//------------

bool KLinePerfect(TanAngleData* pTanAngleData)
{


	return false;
}



//#define METHOD_GAP
int CalcTanAngleDataValue( TanAngleData * pTanAngleData)
{
	double f_ma5_angle=pTanAngleData->fPara0;
	double f_ma10_angle=pTanAngleData->fPara1;
	double f_ma20_angle=pTanAngleData->fPara2;
	double f_ma60_angle=pTanAngleData->fPara3;
	double f_max_volume_per=pTanAngleData->fPara4;
	double f_ave_volume_per=pTanAngleData->fPara5;
	double f_60_20_cross_price_increase=pTanAngleData->fPara6;
	double f_20_10_cross_price_increase=pTanAngleData->fPara7;
	double f_60_day_increase=pTanAngleData->fPara8;
	double fNowGrow=pTanAngleData->fNowGrow;
	double fNowMaxGrow=pTanAngleData->fNowMaxGrow;
	int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;

	int  mMaxDis=pTanAngleData->mMaxDis;
	
	int m_10_big_20_nums=pTanAngleData->mPara6;
	int m_60_big_20_nums=pTanAngleData->mPara7;

	int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
	int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
	int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
	int m_max_volume_distance=pTanAngleData->mMaxDis;
	int mContiDownNums=pTanAngleData->mContiDownNums;
	int mBigIncreaseNums=pTanAngleData->mBigIncreaseNums;
	int mRsi1BigNums=pTanAngleData->mRsi1BigNums;
	int mNextGrow=pTanAngleData->mNextGrow;
	double f_cur_rsi_1=pTanAngleData->fRsi1;
	int mContiVolDownNums=pTanAngleData->mContiVolDownNums;
	int mStepIndex=pTanAngleData->mStepIndex;

	int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;

	
	if(pTanAngleData->strStockCode=="SZ002752")
	{
		int a=0; 
		a++;

	}
	

int mValue=0;


if( (m_10_big_20_nums>=m_60_big_20_nums)  && (f_ave_volume_per<3.0 && f_ave_volume_per>1.0 && f_max_volume_per<3.2)&&(f_60_20_cross_price_increase<50.0&&f_20_10_cross_price_increase<50.0)  )
{
	if(m_60_big_20_nums<=10)
	{
		if(m_10_big_20_nums<=20)
		{
			mValue+=50;

			if((f_ma5_angle-f_ma10_angle)<-5.0)
				mValue-=30;

			//if(f_ma60_angle<1.0)
			//	mValue -= 30;
		}

	  //if(mStepIndex>0)DoFilterTanMatch9
		//  mValue-=30;
	  
	  if(mRsi1BigNums>=2)
		  mValue -= mRsi1BigNums*5;

	  if (mBigIncreaseNums >= 1)
		  mValue -= mBigIncreaseNums*5;

	  if(f_ave_volume_per<2.0&&f_max_volume_per<2.0)
	  {
		  mValue+=20;
		  if(mRsi1BigNums==0)
		  	  mValue+=10;

		  int mTemp = 40;
		  if (f_ma5_angle < 30.0)
		  {
			  mTemp = 30;
		  }
		 
		  if (mNowIsMaxPriceNums >= mTemp)
			  mValue += 30;
		  else if (mNowIsMaxPriceNums < 15)
			  mValue -= 30;
	  }
	  else
	  {
		  if (mNowIsMaxPriceNums >= 60)
			  mValue += 30;
		  else if (mNowIsMaxPriceNums < 30)
			  mValue -= 30;
	  }
	  
	  if(f_ma5_angle>70.0|| f_ma10_angle>68.0)
		  mValue -= 30;
	}
	 
}

return mValue;


}

bool CmpTanAngleData( TanAngleData * pTanAngleData1,  TanAngleData * pTanAngleData2)  
{
	int value1=CalcTanAngleDataValue(pTanAngleData1);

	int value2=CalcTanAngleDataValue(pTanAngleData2);

	if(value1>value2)
		return true;

	return false;

}
BOOL  CDlgDropOff::DoFilterTanAngle(void)
{
	CTanAngleAlg mTanAngleAlg;
	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}
	
	mTanAngleAlg.SetKLineType(mKLineType);

	vecTanAngleData=mTanAngleAlg.doFilter(mDropOffTime,mBackDays,mMaxAngle,f_max_volume_multiple,bIgnoreM5,bUseM120,bUseAllUp,mMaxInsBack,f_max_ins_thes);

	std::sort(vecTanAngleData.begin(),vecTanAngleData.end(),CmpTanAngleData);  

	int mStockCodeSize = StockDataMgr()->GetStockCodeListSize();
	double f_Tan_Per = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	//printf("总股票数 %d个  算法选出 %d个 占百分之 %f \n", mStockCodeSize, vecTanAngleData.size(), f_Tan_Per);
	int mM5TangleBigNums = 0;
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		TanAngleData* pTanAngleData = vecTanAngleData[i];
		double f_ma5_angle = pTanAngleData->fPara0;
		double f_ma10_angle = pTanAngleData->fPara1;
		if (f_ma5_angle > 75.0)
			mM5TangleBigNums++;
		else if(f_ma10_angle>75.0)
			mM5TangleBigNums++;
	}

	double f_M5_Tan_BigPer = (mM5TangleBigNums * 100.0) / vecTanAngleData.size();

	int  m_launch_stock_nums = 0;
	int  m_small_launch_stock_nums = 0;

	for(int i=0;i<vecTanAngleData.size();i++)
	{
		int mValue=CalcTanAngleDataValue(vecTanAngleData[i]);
		vecTanAngleData[i]->mUserCalcedValue = mValue;
		if(vecTanAngleData[i]->strStockCode=="SH603520")
		{

			int a=0;
			a+=1;
		}
		TanAngleData * pTanAngleData=vecTanAngleData[i];
		double f_ma5_angle=pTanAngleData->fPara0;
		double f_ma10_angle=pTanAngleData->fPara1;
		double f_ma20_angle=pTanAngleData->fPara2;
		double f_ma60_angle=pTanAngleData->fPara3;
		double f_max_volume_per=pTanAngleData->fPara4;
		double f_ave_volume_per=pTanAngleData->fPara5;
		double f_60_20_cross_price_increase=pTanAngleData->fPara6;
		double f_20_10_cross_price_increase=pTanAngleData->fPara7;
		double f_60_day_increase=pTanAngleData->fPara8;
		double fNowGrow=pTanAngleData->fNowGrow;
		double fNowMaxGrow=pTanAngleData->fNowMaxGrow;
		int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;

		int  mMaxDis=pTanAngleData->mMaxDis;

		int m_10_big_20_nums=pTanAngleData->mPara6;
		int m_60_big_20_nums=pTanAngleData->mPara7;

		int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
		int m_max_volume_distance=pTanAngleData->mMaxDis;
		int mContiDownNums=pTanAngleData->mContiDownNums;
		int mBigIncreaseNums=pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums=pTanAngleData->mRsi1BigNums;
		int mNextGrow=pTanAngleData->mNextGrow;
		double f_cur_rsi_1=pTanAngleData->fRsi1;
		//double f_cur_rsi_3= pTanAngleData->fRsi3;
		//double f_min_rsi_1 = pTanAngleData->fMinRsi1;
		int mContiVolDownNums=pTanAngleData->mContiVolDownNums;
		int mStepIndex=pTanAngleData->mStepIndex;

		int mPriceM5ContiUpNums=pTanAngleData->mPriceM5ContiUpNums;
		int mVolM5ContiUpNums=pTanAngleData->mVolM5ContiUpNums ;
		int mVolM10ContiUpNums=pTanAngleData->mVolM10ContiUpNums ;
		

		double f_temp_value=f_60_20_cross_price_increase/f_ave_volume_per;

		
		if (m_10_big_20_nums < 20 && m_60_big_20_nums < 20 && m_continus_price_m20_up_nums < 20 && m_continus_price_m60_up_nums < 20)
		{
			m_launch_stock_nums++;

		}

		if (m_10_big_20_nums < 10 && m_60_big_20_nums < 10 && m_continus_price_m20_up_nums < 10 && m_continus_price_m60_up_nums < 10)
		{
			m_small_launch_stock_nums++;

		}

		double f_temp_rang=5.0;
		if(vecTanAngleData[i]->strStockCode.Find("SZ300")>=0)
			f_temp_rang=10.0;

		int mTemp=118;
		if(pTanAngleData->strStockCode.Find("SZ300")>=0)
			mTemp=70;

		double f_a5_sub_a10=f_ma5_angle-f_ma10_angle;
		double f_a10_sub_a20=f_ma10_angle-f_ma20_angle;
		double f_angle_per=f_a10_sub_a20/f_a5_sub_a10;

		BOOL bOk=FALSE;


		

		
		if(!bOk && f_60_20_cross_price_increase<=21&&f_20_10_cross_price_increase<=13 && mNowIsMaxPriceNums>=mTemp && f_ma5_angle>32.0 && f_ma5_angle<55.0)
		{
			;
			if(f_max_volume_per<2.5&& f_ave_volume_per<2.2)
			{
				if(f_60_20_cross_price_increase<40.0 && f_20_10_cross_price_increase<40.0 )
				{
					if(m_10_big_20_nums<25 && m_60_big_20_nums<13 &&mStepIndex==0)
					{
						bOk=TRUE;
						printf("%s  %s  %d 均线完美,量能合适\n",(LPCSTR)vecTanAngleData[i]->strStockCode,(LPCSTR)vecTanAngleData[i]->strStockName,mValue);
					}

				}


			}
		}
/*
		if (!bOk && f_min_rsi_1 < 15.0)
		{
			bOk = TRUE;
			printf("%s  %s  %d f_min_rsi_1 =%.2f\n", (LPCSTR)vecTanAngleData[i]->strStockCode, (LPCSTR)vecTanAngleData[i]->strStockName, mValue, f_min_rsi_1);

		}
*/
#if 0

		if (mMaxDis == 1 && f_ave_volume_per > 1.0 && f_ave_volume_per < 3.0 && f_max_volume_per < 3.0 && (f_60_20_cross_price_increase < 40.0 && f_20_10_cross_price_increase < 40.0) && fNowMaxGrow < f_temp_rang)
		{
			bOk = TRUE;
			if (f_ma5_angle < 30.0 && mRsi1BigNums >= 2)
				bOk = FALSE;
			if (f_ma60_angle < -5.0)
				bOk = FALSE;
			if (bOk)
				printf("%s  %s  %d 当前上升量最大\n", (LPCSTR)vecTanAngleData[i]->strStockCode, (LPCSTR)vecTanAngleData[i]->strStockName, mValue);


		}

		if(!bOk &&  f_angle_per>2.7&&f_angle_per<3.3)
		{
			if(f_ave_volume_per<2.7 &&f_max_volume_per<3.0&&(f_60_20_cross_price_increase<40.0 && f_20_10_cross_price_increase<40.0))
			{
				if(m_10_big_20_nums<25 && m_60_big_20_nums<15 && mRsi1BigNums<=1)
				{
					bOk=TRUE;
					printf("%s  %s  %d 角度增长平均\n",(LPCSTR)vecTanAngleData[i]->strStockCode,(LPCSTR)vecTanAngleData[i]->strStockName,mValue);
				}

			}
		}

		
		if(!bOk && m_10_big_20_nums<=20 && m_60_big_20_nums<=6)
		{
			if(f_ma5_angle>30.0&&f_ma5_angle<45.0)
			{
				if(f_ma10_angle>26.0&&f_ma10_angle<40.0)
				{
					if(mRsi1BigNums>=2)
					{
						bOk=TRUE;
						printf("%s  %s  %d 经验判断可能还有动能\n",(LPCSTR)vecTanAngleData[i]->strStockCode,(LPCSTR)vecTanAngleData[i]->strStockName,mValue);
					}

				}

			}

		}
		
		if(!bOk && (f_ma60_angle<=25.0 && f_ma60_angle>=3) && f_ma5_angle<70.0  && f_ma10_angle <65.0 && m_60_big_20_nums<45 && m_10_big_20_nums<=40)
		{
			double f_per=f_ave_volume_per/f_max_volume_per;
				
			if(f_per>1.50 &&  f_ave_volume_per<4.8)
			{
					bOk=TRUE;
					printf("%s  %s  %d 量能均线增加恰到好处\n",(LPCSTR)vecTanAngleData[i]->strStockCode,(LPCSTR)vecTanAngleData[i]->strStockName,mValue);

			}

		}
#endif
#if 0
		if (!bOk&&m_60_big_20_nums >= 60 && m_continus_price_m60_up_nums >= 50)
		{
		//	if (f_ave_volume_per < 2.5 && f_max_volume_per < 2.5)
		//	{
		//		if (f_ma5_angle < 65.0 && f_ma10_angle < 60.0)
		//		{
		//			if (f_60_20_cross_price_increase < 70.0 && f_20_10_cross_price_increase < 70.0)
					{

						bOk = TRUE;
						printf("%s  %s  %d 60日均线长牛，可以关注\n", (LPCSTR)vecTanAngleData[i]->strStockCode, (LPCSTR)vecTanAngleData[i]->strStockName, mValue);


					}
					
			//	}
		//	}
			
		}
#endif

		double f_10_sub_20_val = f_ma10_angle - f_ma20_angle;
		double f_5_sub_10_val = f_ma5_angle - f_ma10_angle;
		double f_multiple_val = (f_5_sub_10_val / f_10_sub_20_val);

#if 0
		if (!bOk && f_multiple_val > 2.1)
		{
			double f_temp_val = 45.0;
			if (pTanAngleData->strStockCode.Find("SZ300") >= 0)
			{
				f_temp_val = 50.0;
			}


			if (f_ave_volume_per < 2.7 && f_60_20_cross_price_increase < f_temp_val)
			{


				if (f_60_20_cross_price_increase >= 21 && f_20_10_cross_price_increase >= 16 && mContiDownNums == 0 && mRsi1BigNums > 0)
				{
					bOk = TRUE;
					printf("%s  %s   %d , %f  角度前小后大,但动能可能不足\n", pTanAngleData->strStockCode, pTanAngleData->strStockName, mValue,f_multiple_val);
				}
				else
				{
					bOk = TRUE;

					if ((m_60_big_20_nums - m_10_big_20_nums) > 30 && mBigIncreaseNums > 1)
						printf("%s  %s   %d  , %f,角度前小后大 60日线一直上涨,但短期波动大 \n", pTanAngleData->strStockCode, pTanAngleData->strStockName, mValue,f_multiple_val);

					else if ((m_60_big_20_nums - m_10_big_20_nums) < 0)
					{
						double f_temp_angle = f_ma5_angle - (f_ma60_angle * 2);
						double f_temp_angle2 = f_ma10_angle - (f_ma60_angle * 2);
						if(f_temp_angle>60.0|| f_temp_angle2>60.0)
							printf("%s  %s    %d , %f,角度前小后大 但60日角度偏小，需要仔细分析 \n", pTanAngleData->strStockCode, pTanAngleData->strStockName, mValue, f_multiple_val);
						else
						{
							
							double  f_temp_per = f_20_10_cross_price_increase / f_60_20_cross_price_increase;
							if (f_temp_per > 1.3 && f_temp_per < 1.8)
							{
								printf("%s  %s    %d , %f,角度前小后大 涨幅黄金比例，短期有可能上涨 \n", pTanAngleData->strStockCode, pTanAngleData->strStockName, mValue, f_multiple_val);
							}
							else
							{
								printf("%s  %s    %d , %f,角度前小后大 刚进入60日上涨周期，短期有可能上涨 \n", pTanAngleData->strStockCode, pTanAngleData->strStockName, mValue, f_multiple_val);
							}

						}
							
					}
						
					else
						printf("%s  %s    %d , %f  角度前小后大,但经验值表明有概率出问题\n", pTanAngleData->strStockCode, pTanAngleData->strStockName, mValue,f_multiple_val);

				}


			}
		}

#endif

#if 0
		if (!bOk && (f_10_sub_20_val - f_5_sub_10_val)>5.0)
		{
			if (f_20_10_cross_price_increase < f_60_20_cross_price_increase)
			{
				if (f_60_20_cross_price_increase < 25.0)
				{
					if (f_ma5_angle < 45.0 && f_ma10_angle < 45.0)
					{
						if (f_ma5_angle > f_ma10_angle)
						{
							bOk = TRUE;
							printf("%s  %s  %d 角度前大后小，涨幅前小后大\n", (LPCSTR)vecTanAngleData[i]->strStockCode, (LPCSTR)vecTanAngleData[i]->strStockName, mValue);
						}
						
					}
					
				}
				
			}

		}
#endif


#if 0
		if(!bOk && f_ave_volume_per>6.0 && f_ave_volume_per  <8.5 && f_max_volume_per<5.0)
		{
			if(f_60_20_cross_price_increase<40.0 && f_20_10_cross_price_increase<40.0 )
			{
				BOOL bCheckOk = FALSE;
				if (m_10_big_20_nums < 35 && m_60_big_20_nums < 20)
				{
					if (f_ma5_angle < 62.0 && f_ma10_angle < 60.0)
					{
						bCheckOk = TRUE;
					}
					
				}
				else if (m_10_big_20_nums < 20 && m_60_big_20_nums < 10)
				{
					bCheckOk = TRUE;

				}
				
				if (bCheckOk)
				{
					bOk = TRUE;
					printf("%s  %s  %d 量大涨幅小\n", (LPCSTR)vecTanAngleData[i]->strStockCode, (LPCSTR)vecTanAngleData[i]->strStockName, mValue);

				}
				
			}

		}
#endif

#if 0
		if (!bOk && f_ave_volume_per < 2.5)
		{
			double f_temp_group = f_60_20_cross_price_increase;
			if (f_20_10_cross_price_increase > f_60_20_cross_price_increase)
				f_temp_group = f_20_10_cross_price_increase;

			if (f_temp_group > 75.0)
			{
				bOk = TRUE;
				printf("%s  %s  %d  奇葩强股  \n", (LPCSTR)vecTanAngleData[i]->strStockCode, (LPCSTR)vecTanAngleData[i]->strStockName, mValue);
			}


		}
#endif
		
#if 0
		if ((f_ma5_angle - f_ma60_angle) > 70.0)
		{
			if (f_ma60_angle > -5)
			{
				bOk = TRUE;

				printf("%s  %s  %d  K线走势立地拔高 \n", (LPCSTR)vecTanAngleData[i]->strStockCode, (LPCSTR)vecTanAngleData[i]->strStockName, mValue);

			}

		
		}
#endif
#if 0
		double f_temp_2 = f_ma10_angle - f_ma20_angle;
		double f_temp_1 = f_ma5_angle - f_ma10_angle;
		double f_temp_3 = f_temp_2 / f_temp_1;
		double f_temp_4 = f_ma10_angle;
		if (f_ma5_angle > f_ma10_angle)
			f_temp_4 = f_ma5_angle;
		if ( (f_temp_3>1.4 && f_temp_3<1.8) && (f_temp_4<65.0) &&(f_ave_volume_per<2.2 && f_max_volume_per<2.5)&&!bOk)
		{
					
				bOk = TRUE;
				printf("%s  %s  %d  K线走势均衡 \n", (LPCSTR)vecTanAngleData[i]->strStockCode, (LPCSTR)vecTanAngleData[i]->strStockName, mValue);

		}
#endif

		if (!bOk)
		{
			std::vector<std::string> strIndustryList = IndustryDataMgr()->FindIndustryByStockCode((LPCSTR)vecTanAngleData[i]->strStockCode);
			std::string strIndustry = "";
			if (strIndustryList.size() > 0  && mValue>=40)
				strIndustry = strIndustryList[0];

			printf("%s  %s  %d     %s\n", (LPCSTR)vecTanAngleData[i]->strStockCode, (LPCSTR)vecTanAngleData[i]->strStockName, mValue, strIndustry.c_str());
		}
			
	}

	printf("总股票数 %d个  算法选出 %d个 占百分之 %f  其中Tan5,10>75的有%d,占选出总数的百分之%f\n", mStockCodeSize, vecTanAngleData.size(), f_Tan_Per, mM5TangleBigNums,f_M5_Tan_BigPer);
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecTanAngleData[i]->strStockCode;
		pDropOffData->strStockName=vecTanAngleData[i]->strStockName;
		pDropOffData->fMaxMultiple=vecTanAngleData[i]->fPara2;
		pDropOffData->fAveMultiple=vecTanAngleData[i]->fPara1;
		CString strInfo;
		strInfo.Format("%.2f,up%.2f",vecTanAngleData[i]->fPara0,vecTanAngleData[i]->fPara7);
		pDropOffData->strMaxDate=strInfo;
		strInfo.Format("%.2f,%d  ave:%.2f  %.2f",vecTanAngleData[i]->fPara4,vecTanAngleData[i]->mMaxDis,vecTanAngleData[i]->fPara5,vecTanAngleData[i]->fPara6);
		pDropOffData->strMinDate=strInfo;
		pDropOffData->mMaxValuePassDay=vecTanAngleData[i]->fPara3;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=vecTanAngleData[i]->mPara6;
		pDropOffData->mSpecNums=vecTanAngleData[i]->mPara7;
		strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f",vecTanAngleData[i]->fPara8,vecTanAngleData[i]->mPara8,vecTanAngleData[i]->mPara9,vecTanAngleData[i]->mPara10,vecTanAngleData[i]->mContiDownNums,vecTanAngleData[i]->mContiVolDownNums,vecTanAngleData[i]->mStepIndex,vecTanAngleData[i]->mNowIsMaxPriceNums,
			vecTanAngleData[i]->mBigIncreaseNums,vecTanAngleData[i]->fNowGrow,vecTanAngleData[i]->mRsi1BigNums,vecTanAngleData[i]->fVolumePer,
			vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
		pDropOffData->strInfo=strInfo;
		vecDropOffData.push_back(pDropOffData);
	}
	
	return TRUE;
}


BOOL CDlgDropOff::DoFilterMulTanAngle(void)
{
	CMulTanAngleAlg mMulTanAngleAlg;
	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}


	vecTanAngleData=mMulTanAngleAlg.doFilter(mDropOffTime,mMulDays,mBackDays,mMaxAngle,f_max_volume_multiple,bIgnoreM5,mMaxInsBack,f_max_ins_thes);

	for(int i=0;i<vecTanAngleData.size();i++)
	{
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecTanAngleData[i]->strStockCode;
		pDropOffData->strStockName=vecTanAngleData[i]->strStockName;
		pDropOffData->fMaxMultiple=vecTanAngleData[i]->fPara2;
		pDropOffData->fAveMultiple=vecTanAngleData[i]->fPara1;
		CString strInfo;
		strInfo.Format("%.2f,up%.2f",vecTanAngleData[i]->fPara0,vecTanAngleData[i]->fPara7);
		pDropOffData->strMaxDate=strInfo;
		strInfo.Format("%.2f,%d  ave:%.2f  %.2f",vecTanAngleData[i]->fPara4,vecTanAngleData[i]->mMaxDis,vecTanAngleData[i]->fPara5,vecTanAngleData[i]->fPara6);
		pDropOffData->strMinDate=strInfo;
		pDropOffData->mMaxValuePassDay=vecTanAngleData[i]->fPara3;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=vecTanAngleData[i]->mPara6;
		pDropOffData->mSpecNums=vecTanAngleData[i]->mPara7;
		strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#%d#%d#rb%d",vecTanAngleData[i]->fPara8,vecTanAngleData[i]->mPara8,vecTanAngleData[i]->mPara9,vecTanAngleData[i]->mPara10,vecTanAngleData[i]->mContiDownNums,vecTanAngleData[i]->mContiVolDownNums,vecTanAngleData[i]->mNowIsMaxPriceNums,
			vecTanAngleData[i]->mBigIncreaseNums,vecTanAngleData[i]->mRsi1BigNums);
		pDropOffData->strInfo=strInfo;
		vecDropOffData.push_back(pDropOffData);
	}

	return TRUE;
}

BOOL CDlgDropOff::DoFilterSingleTanAngle(void)
{
	CSingleTanAngleAlg mSingleTanAngleAlg;
	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}


	vecTanAngleData=mSingleTanAngleAlg.doFilter(mDropOffTime,mMulDays,mBackDays,mMaxAngle,f_max_volume_multiple,bIgnoreM5);
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecTanAngleData[i]->strStockCode;
		pDropOffData->strStockName=vecTanAngleData[i]->strStockName;
		pDropOffData->fMaxMultiple=vecTanAngleData[i]->fPara2;
		pDropOffData->fAveMultiple=vecTanAngleData[i]->fPara1;
		CString strInfo;
		strInfo.Format("%.2f,up%.2f",vecTanAngleData[i]->fPara0,vecTanAngleData[i]->fPara7);
		pDropOffData->strMaxDate=strInfo;
		strInfo.Format("%.2f,%d  ave:%.2f  %.2f",vecTanAngleData[i]->fPara4,vecTanAngleData[i]->mMaxDis,vecTanAngleData[i]->fPara5,vecTanAngleData[i]->fPara6);
		pDropOffData->strMinDate=strInfo;
		pDropOffData->mMaxValuePassDay=vecTanAngleData[i]->fPara3;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=vecTanAngleData[i]->mPara6;
		pDropOffData->mSpecNums=vecTanAngleData[i]->mPara7;
		strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#%d#%d#rb%d",vecTanAngleData[i]->fPara8,vecTanAngleData[i]->mPara8,vecTanAngleData[i]->mPara9,vecTanAngleData[i]->mPara10,vecTanAngleData[i]->mContiDownNums,vecTanAngleData[i]->mContiVolDownNums,vecTanAngleData[i]->mNowIsMaxPriceNums,
			vecTanAngleData[i]->mBigIncreaseNums,vecTanAngleData[i]->mRsi1BigNums);
		pDropOffData->strInfo=strInfo;
		vecDropOffData.push_back(pDropOffData);
	}

	return TRUE;
}



BOOL CDlgDropOff::DoFilterCMMatch(void)
{

	CTriAngleAlg mTriAngleAlg;
	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}

	Vec_TriAngleData  vecTriAngleData;

	vecTriAngleData=mTriAngleAlg.doFilter(mDropOffTime);

	for(int i=0;i<vecTriAngleData.size();i++)
	{
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecTriAngleData[i]->strStockCode;
		pDropOffData->strStockName=vecTriAngleData[i]->strStockName;
		pDropOffData->fMaxMultiple=vecTriAngleData[i]->mPara1;
		pDropOffData->fAveMultiple=vecTriAngleData[i]->mPara2;
		pDropOffData->strMaxDate=vecTriAngleData[i]->strDateTime;
		pDropOffData->strMinDate=vecTriAngleData[i]->strDateTime;
		pDropOffData->mMaxValuePassDay=vecTriAngleData[i]->mPara3;
		pDropOffData->fDownTotalRang=0.0;
		vecDropOffData.push_back(pDropOffData);
	}

	return TRUE;
}


BOOL CDlgDropOff::DoFilterTanMatch(void)
{
	CDlgTanAnglePara dlg;
	if(dlg.DoModal()==IDOK)
	{
		double fTan60AngleMin=dlg.GetTan60AngleMin();
		double fTan60AngleMax=dlg.GetTan60AngleMax();

		double f_AveVolMulMin=dlg.GetAveVolMulMin();		
		double f_AveVolMulMax=dlg.GetAveVolMulMax();

		double f_MaxVolMulMin=dlg.GetMaxVolMulMin();
		double f_MaxVolMulMax=dlg.GetMaxVolMulMax();

		double f_max_price_increase=dlg.GetPriceIncrease();

		bool bTanAngleOrderUp=dlg.IsTanAngleOrderUp();
		bool bTanAngleM60AllUp=dlg.IsTanAngleM60AllUp();

		bool bTanAngleM60UpLessM20=dlg.IsTanAngleM60UpLessM20();

		int mMaxTanAngle=dlg.GetMaxTanAngle();

		int mMinMaxTanAngle=dlg.GetMinMaxTanAngle();

		for(int i=0;i<vecTanAngleData.size();i++)
		{
			double fTan60Angle=vecTanAngleData[i]->fPara3;

			if(fTan60Angle>=fTan60AngleMin && fTan60Angle<=fTan60AngleMax)
			{

				double f_AveVolMul=vecTanAngleData[i]->fPara5;
				if(f_AveVolMul>=f_AveVolMulMin&&f_AveVolMul<=f_AveVolMulMax)
				{
					BOOL bOk=FALSE;
					if(bTanAngleOrderUp)
					{
						double f_tan_angle_m5=vecTanAngleData[i]->fPara0;
						double f_tan_angle_m10=vecTanAngleData[i]->fPara1;
						double f_tan_angle_m20=vecTanAngleData[i]->fPara2;
						double f_tan_angle_m60=vecTanAngleData[i]->fPara3;
						if(f_tan_angle_m10>=f_tan_angle_m20)
						{
							if(f_tan_angle_m20>=f_tan_angle_m60)
							{
								//if(f_tan_angle_m5>=f_tan_angle_m10)
									bOk=TRUE;
							}
								
						}

					}
					else
						bOk=TRUE;

					if(bOk)
					{
						if(bTanAngleM60UpLessM20)
						{
							int mM20UpNums=vecTanAngleData[i]->mPara6;
							int mM60UpNums=vecTanAngleData[i]->mPara7;
							if(mM60UpNums>mM20UpNums)
								bOk=FALSE;
						}
						else if(bTanAngleM60AllUp)
						{
							int mM60UpNums=vecTanAngleData[i]->mPara7;
							if(mM60UpNums<90)
								bOk=FALSE;
						}

					}

					if(bOk)
					{
						BOOL bOk2=TRUE;
						double f_ma5_angle=vecTanAngleData[i]->fPara0;
						double f_ma10_angle=vecTanAngleData[i]->fPara1;
						double f_ma20_angle=vecTanAngleData[i]->fPara2;
						
						if(f_ma5_angle>mMaxTanAngle || f_ma10_angle>mMaxTanAngle || f_ma20_angle>mMaxTanAngle )
						{
							bOk2=FALSE;
						}

						if(f_ma5_angle<mMinMaxTanAngle || f_ma10_angle<mMinMaxTanAngle || f_ma20_angle<mMinMaxTanAngle )
						{
							bOk2=FALSE;
						}
						
						double f_price_increase;
						if(vecTanAngleData[i]->fPara6>vecTanAngleData[i]->fPara7)
							f_price_increase=vecTanAngleData[i]->fPara6;
						else
							f_price_increase=vecTanAngleData[i]->fPara7;

						if(f_price_increase>f_max_price_increase)
							bOk2=FALSE;

						if(bOk2)
						{
							double f_max_volume_per=vecTanAngleData[i]->fPara4;
							if(f_max_volume_per>f_MaxVolMulMin && f_max_volume_per<=f_MaxVolMulMax)
							{

								DropOffData *pDropOffData=new DropOffData();
								pDropOffData->strStockCode=vecTanAngleData[i]->strStockCode;
								pDropOffData->strStockName=vecTanAngleData[i]->strStockName;
								pDropOffData->fMaxMultiple=vecTanAngleData[i]->fPara2;
								pDropOffData->fAveMultiple=vecTanAngleData[i]->fPara1;
								CString strInfo;
								strInfo.Format("%.2f,up%.2f",vecTanAngleData[i]->fPara0,vecTanAngleData[i]->fPara7);
								pDropOffData->strMaxDate=strInfo;
								strInfo.Format("%.2f,%d ave:%.2f  %.2f",vecTanAngleData[i]->fPara4,vecTanAngleData[i]->mMaxDis,vecTanAngleData[i]->fPara5,vecTanAngleData[i]->fPara6);
								pDropOffData->strMinDate=strInfo;
								pDropOffData->mMaxValuePassDay=vecTanAngleData[i]->fPara3;
								pDropOffData->fDownTotalRang=0.0;
								pDropOffData->mFilterNums=vecTanAngleData[i]->mPara6;
								pDropOffData->mSpecNums=vecTanAngleData[i]->mPara7;
								strInfo.Format("%.2f,%d,%d,%d#p%d#v%#c%d#%d#%d#rb%d",vecTanAngleData[i]->fPara8,vecTanAngleData[i]->mPara8,vecTanAngleData[i]->mPara9,vecTanAngleData[i]->mPara10,vecTanAngleData[i]->mContiDownNums,vecTanAngleData[i]->mContiVolDownNums,vecTanAngleData[i]->mStepIndex,vecTanAngleData[i]->mNowIsMaxPriceNums,
									vecTanAngleData[i]->mBigIncreaseNums,vecTanAngleData[i]->mRsi1BigNums);
								pDropOffData->strInfo=strInfo;
								vecDropOffData.push_back(pDropOffData);
							}

						}
						

						
					}

					
				}


			}


		}
		SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);

	}
	return TRUE;
}

//K线身怀六甲
//输出KSTAR:
//1日前的收盘价-1日前的开盘价的绝对值/1日前的收盘价>0.04
//并且收盘价-开盘价的绝对值/收盘价<0.005
//并且收盘价和开盘价的较大值<1日前的收盘价和1日前的开盘价的较大值
//并且收盘价和开盘价的较小值>1日前的收盘价和1日前的开盘价的较小值

BOOL CDlgDropOff::DoFilterKLinePregnant(void)
{
	TanAngleData* pTanAngleData = NULL;
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		pTanAngleData = vecTanAngleData[i];


		double f_ma5_angle = pTanAngleData->fPara0;
		double f_ma10_angle = pTanAngleData->fPara1;
		double f_ma20_angle = pTanAngleData->fPara2;
		double f_ma60_angle = pTanAngleData->fPara3;
		double f_max_volume_per = pTanAngleData->fPara4;
		double f_ave_volume_per = pTanAngleData->fPara5;
		double f_60_20_cross_price_increase = pTanAngleData->fPara6;
		double f_20_10_cross_price_increase = pTanAngleData->fPara7;
		double f_60_day_increase = pTanAngleData->fPara8;
		double fNowGrow = pTanAngleData->fNowGrow;
		double fNowMaxGrow = pTanAngleData->fNowMaxGrow;
		int mNowIsMaxPriceNums = pTanAngleData->mNowIsMaxPriceNums;

		int  mMaxDis = pTanAngleData->mMaxDis;

		int m_10_big_20_nums = pTanAngleData->mPara6;
		int m_60_big_20_nums = pTanAngleData->mPara7;

		int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
		int m_max_volume_distance = pTanAngleData->mMaxDis;
		int mContiDownNums = pTanAngleData->mContiDownNums;
		int mBigIncreaseNums = pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums = pTanAngleData->mRsi1BigNums;
		int mNextGrow = pTanAngleData->mNextGrow;
		double f_cur_rsi_1 = pTanAngleData->fRsi1;
		int mContiVolDownNums = pTanAngleData->mContiVolDownNums;
		int mStepIndex = pTanAngleData->mStepIndex;

		int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
		int mVolM5ContiUpNums = pTanAngleData->mVolM5ContiUpNums;
		int mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;


		

		if (pTanAngleData->strStockCode == "SZ000809")
		{
			int a = 0;
			a++; 

		}

		bool bOk = false;
#if 0
		if (f_ave_volume_per < 3.5)
		{

			if (abs(m_continus_price_m10_up_nums - mPriceM5ContiUpNums) <= 2)
			{
				if ( abs(m_continus_price_m10_up_nums - m_continus_price_m60_up_nums) <= 2)
				{
					if ( abs(m_continus_price_m10_up_nums - m_10_big_20_nums) <= 2)
					{
							bOk = true;

					}

				}

			}

		}
#endif

#if 0
		if ((m_continus_price_m20_up_nums - m_continus_price_m60_up_nums) >= 9)
		{
			double f_max = f_ma5_angle;
			if (f_ma5_angle < f_ma10_angle)
				f_max = f_ma10_angle;
			if(f_max>50.0&& f_max<70.0 && mNowIsMaxPriceNums>=110)
				bOk = true;

		}
#endif

#if 0
		double fcustomtotalvalue = pTanAngleData->fcustomtotalvalue;

		double f_max_grow = f_60_20_cross_price_increase;
		if (f_60_20_cross_price_increase < f_20_10_cross_price_increase)
			f_max_grow = f_20_10_cross_price_increase;

		if (f_60_20_cross_price_increase < 10 && f_60_20_cross_price_increase < 20)
		{
			if (fcustomtotalvalue > -60.0 && fcustomtotalvalue < -30.0)
			{
				bOk = true;

			}

		}
#endif
		if (mNowIsMaxPriceNums >= 80)
		{

			if (m_continus_price_m60_up_nums < 20 && m_60_big_20_nums < 20)
			{

				bOk = true;
			}
			
		}

		if (bOk)
		{

			DropOffData* pDropOffData = new DropOffData();
			pDropOffData->strStockCode = vecTanAngleData[i]->strStockCode;
			pDropOffData->strStockName = vecTanAngleData[i]->strStockName;
			pDropOffData->fMaxMultiple = vecTanAngleData[i]->fPara2;
			pDropOffData->fAveMultiple = vecTanAngleData[i]->fPara1;
			CString strInfo;
			strInfo.Format("%.2f,up%.2f", vecTanAngleData[i]->fPara0, vecTanAngleData[i]->fPara7);
			pDropOffData->strMaxDate = strInfo;
			strInfo.Format("%.2f,%d ave:%.2f  %.2f", vecTanAngleData[i]->fPara4, vecTanAngleData[i]->mMaxDis, vecTanAngleData[i]->fPara5, vecTanAngleData[i]->fPara6);
			pDropOffData->strMinDate = strInfo;
			pDropOffData->mMaxValuePassDay = vecTanAngleData[i]->fPara3;
			pDropOffData->fDownTotalRang = 0.0;
			pDropOffData->mFilterNums = vecTanAngleData[i]->mPara6;
			pDropOffData->mSpecNums = vecTanAngleData[i]->mPara7;

			strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums, vecTanAngleData[i]->mContiVolDownNums, vecTanAngleData[i]->mStepIndex, vecTanAngleData[i]->mNowIsMaxPriceNums,
				vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, vecTanAngleData[i]->fVolumePer,
				vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
			pDropOffData->strInfo = strInfo;

			vecDropOffData.push_back(pDropOffData);

		}

		/*int size = pTanAngleData->vec_begin_value.size();

		double f_now_begin_value = pTanAngleData->vec_begin_value[size - 1];
		double f_now_close_value = pTanAngleData->vec_close_value[size - 1];

		double f_now_max_value = f_now_begin_value;
		if (f_now_close_value > f_now_begin_value)
			f_now_max_value = f_now_close_value;

		double f_now_min_value = f_now_begin_value;
		if ( f_now_close_value < f_now_begin_value)
			f_now_min_value = f_now_close_value;


		double f_pre_begin_value = pTanAngleData->vec_begin_value[size - 2];
		double f_pre_close_value = pTanAngleData->vec_close_value[size - 2];

		double f_pre_max_value = f_pre_begin_value;
		if (f_pre_close_value > f_pre_begin_value)
			f_pre_max_value = f_pre_close_value;


		double f_pre_min_value = f_pre_begin_value;
		if (f_pre_close_value <f_pre_begin_value)
			f_pre_min_value = f_pre_close_value;


		double f_temp1=fabs(f_pre_close_value - f_pre_begin_value) / f_pre_close_value;
		if (f_temp1 > 0.04)
		{
			double f_temp2 = fabs(f_now_close_value - f_now_begin_value) / f_now_close_value;
			if (f_temp2 < 0.02)//0.005
			{
				if (f_now_max_value < f_pre_max_value)
				{

					if (f_now_min_value > f_pre_min_value)
					{

						DropOffData* pDropOffData = new DropOffData();
						pDropOffData->strStockCode = vecTanAngleData[i]->strStockCode;
						pDropOffData->strStockName = vecTanAngleData[i]->strStockName;
						pDropOffData->fMaxMultiple = vecTanAngleData[i]->fPara2;
						pDropOffData->fAveMultiple = vecTanAngleData[i]->fPara1;
						CString strInfo;
						strInfo.Format("%.2f,up%.2f", vecTanAngleData[i]->fPara0, vecTanAngleData[i]->fPara7);
						pDropOffData->strMaxDate = strInfo;
						strInfo.Format("%.2f,%d ave:%.2f  %.2f", vecTanAngleData[i]->fPara4, vecTanAngleData[i]->mMaxDis, vecTanAngleData[i]->fPara5, vecTanAngleData[i]->fPara6);
						pDropOffData->strMinDate = strInfo;
						pDropOffData->mMaxValuePassDay = vecTanAngleData[i]->fPara3;
						pDropOffData->fDownTotalRang = 0.0;
						pDropOffData->mFilterNums = vecTanAngleData[i]->mPara6;
						pDropOffData->mSpecNums = vecTanAngleData[i]->mPara7;

						strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums, vecTanAngleData[i]->mContiVolDownNums, vecTanAngleData[i]->mStepIndex, vecTanAngleData[i]->mNowIsMaxPriceNums,
							vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, vecTanAngleData[i]->fVolumePer,
							vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums);
						pDropOffData->strInfo = strInfo;

						vecDropOffData.push_back(pDropOffData);


					}

				}

			}

		}*/

	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);
	return TRUE;

	return TRUE;
}


BOOL CDlgDropOff::DoFilterTanMatch2(void)
{
	TanAngleData *pTanAngleData=NULL;
#if 0
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];
		int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums=pTanAngleData->mPara10;

		double f_max_volume_per=pTanAngleData->fPara4;
		double f_ave_volume_per=pTanAngleData->fPara5;

		double f_ma5_angle=pTanAngleData->fPara0;
		double f_ma10_angle=pTanAngleData->fPara1;
		double f_ma20_angle=pTanAngleData->fPara2;
		double f_ma60_angle=pTanAngleData->fPara3;

		double f_per=(fabs(f_ma10_angle-f_ma20_angle)*100.0)/f_ma20_angle;
		double f_per_10_5=(fabs(f_ma5_angle-f_ma10_angle)*100.0)/f_ma10_angle;
		if(f_per<10.0&&f_per_10_5<20.0)
		{
			BOOL bOk1=FALSE;
			if(f_ma60_angle<35&&f_ma20_angle<45)
			{
				double f_60_20_cross_price_increase=pTanAngleData->fPara6;
				double f_20_10_cross_price_increase=pTanAngleData->fPara7;
				double f_60_day_increase=pTanAngleData->fPara8;
				int m_10_big_20_nums=pTanAngleData->mPara6;
				int m_60_big_20_nums=pTanAngleData->mPara7;
				int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
				int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
				int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
				int m_max_volume_distance=pTanAngleData->mMaxDis;

				if(m_60_big_20_nums<50&&m_10_big_20_nums<50)
				{
					if(m_continus_price_m10_up_nums<=50&&m_continus_price_m20_up_nums<=50&&m_continus_price_m60_up_nums<=50)
					{
						bOk1=TRUE;
					}
				}
			}
			if(bOk1)
			{
				DropOffData *pDropOffData=new DropOffData();
				pDropOffData->strStockCode=vecTanAngleData[i]->strStockCode;
				pDropOffData->strStockName=vecTanAngleData[i]->strStockName;
				pDropOffData->fMaxMultiple=vecTanAngleData[i]->fPara1;
				pDropOffData->fAveMultiple=vecTanAngleData[i]->fPara2;
				CString strInfo;
				strInfo.Format("%.2f,up%.2f",vecTanAngleData[i]->fPara0,vecTanAngleData[i]->fPara7);
				pDropOffData->strMaxDate=strInfo;
				strInfo.Format("%.2f,%d ave:%.2f  %.2f",vecTanAngleData[i]->fPara4,vecTanAngleData[i]->mMaxDis,vecTanAngleData[i]->fPara5,vecTanAngleData[i]->fPara6);
				pDropOffData->strMinDate=strInfo;
				pDropOffData->mMaxValuePassDay=vecTanAngleData[i]->fPara3;
				pDropOffData->fDownTotalRang=0.0;
				pDropOffData->mFilterNums=vecTanAngleData[i]->mPara6;
				pDropOffData->mSpecNums=vecTanAngleData[i]->mPara7;
				strInfo.Format("%.2f,%d,%d,%d#%d#%d#%d#rb%d",vecTanAngleData[i]->fPara8,vecTanAngleData[i]->mPara8,vecTanAngleData[i]->mPara9,vecTanAngleData[i]->mPara10,vecTanAngleData[i]->mContiDownNums,vecTanAngleData[i]->mNowIsMaxPriceNums,
					vecTanAngleData[i]->mBigIncreaseNums,vecTanAngleData[i]->mRsi1BigNums);
				pDropOffData->strInfo=strInfo;
				vecDropOffData.push_back(pDropOffData);

			}

			

		}

	
	}
#else
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];
		
		double f_ma5_angle = pTanAngleData->fPara0;
		double f_ma10_angle = pTanAngleData->fPara1;
		double f_ma20_angle = pTanAngleData->fPara2;
		double f_ma60_angle = pTanAngleData->fPara3;
		double f_max_volume_per = pTanAngleData->fPara4;
		double f_ave_volume_per = pTanAngleData->fPara5;
		double f_60_20_cross_price_increase = pTanAngleData->fPara6;
		double f_20_10_cross_price_increase = pTanAngleData->fPara7;
		double f_60_day_increase = pTanAngleData->fPara8;
		double fNowGrow = pTanAngleData->fNowGrow;
		double fNowMaxGrow = pTanAngleData->fNowMaxGrow;
		int mNowIsMaxPriceNums = pTanAngleData->mNowIsMaxPriceNums;

		int  mMaxDis = pTanAngleData->mMaxDis;

		int m_10_big_20_nums = pTanAngleData->mPara6;
		int m_60_big_20_nums = pTanAngleData->mPara7;

		int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
		int m_max_volume_distance = pTanAngleData->mMaxDis;
		int mContiDownNums = pTanAngleData->mContiDownNums;
		int mBigIncreaseNums = pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums = pTanAngleData->mRsi1BigNums;
		int mNextGrow = pTanAngleData->mNextGrow;
		double f_cur_rsi_1 = pTanAngleData->fRsi1;
		int mContiVolDownNums = pTanAngleData->mContiVolDownNums;
		int mStepIndex = pTanAngleData->mStepIndex;

		int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
		int mVolM5ContiUpNums = pTanAngleData->mVolM5ContiUpNums;
		int mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;

		double fcustomtotalvalue = pTanAngleData->fcustomtotalvalue;

		double f_max_grow = f_60_20_cross_price_increase;
		if (f_60_20_cross_price_increase < f_20_10_cross_price_increase)
			f_max_grow = f_20_10_cross_price_increase;
		//if((fabs(fcustomtotalvalue)/ f_max_grow)>3.0)

		
		if ((fcustomtotalvalue<-70.0) && (f_max_grow<60.0))//
		{

			DropOffData* pDropOffData = new DropOffData();
			pDropOffData->strStockCode = vecTanAngleData[i]->strStockCode;
			pDropOffData->strStockName = vecTanAngleData[i]->strStockName;
			pDropOffData->fMaxMultiple = vecTanAngleData[i]->fPara2;
			pDropOffData->fAveMultiple = vecTanAngleData[i]->fPara1;
			CString strInfo;
			strInfo.Format("%.2f,up%.2f", vecTanAngleData[i]->fPara0, vecTanAngleData[i]->fPara7);
			pDropOffData->strMaxDate = strInfo;
			strInfo.Format("%.2f,%d ave:%.2f  %.2f", vecTanAngleData[i]->fPara4, vecTanAngleData[i]->mMaxDis, vecTanAngleData[i]->fPara5, vecTanAngleData[i]->fPara6);
			pDropOffData->strMinDate = strInfo;
			pDropOffData->mMaxValuePassDay = vecTanAngleData[i]->fPara3;
			pDropOffData->fDownTotalRang = 0.0;
			pDropOffData->mFilterNums = vecTanAngleData[i]->mPara6;
			pDropOffData->mSpecNums = vecTanAngleData[i]->mPara7;
			
			strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums, vecTanAngleData[i]->mContiVolDownNums, vecTanAngleData[i]->mStepIndex, vecTanAngleData[i]->mNowIsMaxPriceNums,
				vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, vecTanAngleData[i]->fVolumePer,
				vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
			pDropOffData->strInfo = strInfo;

			vecDropOffData.push_back(pDropOffData);
		
		}
		else
		{
			continue;
		}

	}

#endif

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
}


int  CalcInPriceM10M20(std::vector<double> vec_high_value, std::vector<double> vec_low_value, std::vector<double> vec_price_m5, std::vector<double> vec_price_m10, std::vector<double> vec_price_m20)
{
	int size= vec_high_value.size();
	std::vector<double> vec_up_m10_value;
	std::vector<double> vec_up_m20_value;
	for (int i = 0; i < size; i++)
	{
		double f_value = vec_price_m5[i]+(vec_price_m5[i]- vec_price_m10[i]);
		vec_up_m10_value.push_back(f_value);
		f_value = vec_price_m5[i] + (vec_price_m5[i] - vec_price_m20[i]);
		vec_up_m20_value.push_back(f_value);
	}

	int mNums = 0;
	for (int i = size - 1; i >= size - 20; i--)
	{

		if (vec_high_value[i] < vec_up_m20_value[i])
		{
			if (vec_low_value[i] > vec_price_m10[i])
			{
				mNums++;

			}
			else
			{

				break;
			}

		}
		else
		{
			break;
		}

	}
	return mNums;

}

int  CalcInBollMiddleUpNums(std::vector<double> vec_high_value, std::vector<double> vec_low_value, std::vector<double> vec_boll_up, std::vector<double> vec_boll_middle)
{
	int size = vec_high_value.size();
	if (size < 22)
		return 0;

	int mNums = 0;
	for (int i = size -1; i >= size-20; i--)
	{
		if (vec_high_value[i] < vec_boll_up[i])
		{
			if (vec_low_value[i] > vec_boll_middle[i])
			{
				mNums++;

			}
			else
			{

				break;
			}

		}
		else
		{
			break;
		}

	}

	return mNums;
}

BOOL CDlgDropOff::DoFilterTanMatch3(void)
{
	TanAngleData *pTanAngleData=NULL;
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];

		double f_ma5_angle = pTanAngleData->fPara0;
		double f_ma10_angle = pTanAngleData->fPara1;
		double f_ma20_angle = pTanAngleData->fPara2;
		double f_ma60_angle = pTanAngleData->fPara3;
		double f_max_volume_per = pTanAngleData->fPara4;
		double f_ave_volume_per = pTanAngleData->fPara5;
		double f_60_20_cross_price_increase = pTanAngleData->fPara6;
		double f_20_10_cross_price_increase = pTanAngleData->fPara7;
		double f_60_day_increase = pTanAngleData->fPara8;
		double fNowGrow = pTanAngleData->fNowGrow;
		double fNowMaxGrow = pTanAngleData->fNowMaxGrow;
		int mNowIsMaxPriceNums = pTanAngleData->mNowIsMaxPriceNums;

		int  mMaxDis = pTanAngleData->mMaxDis;

		int m_10_big_20_nums = pTanAngleData->mPara6;
		int m_60_big_20_nums = pTanAngleData->mPara7;

		int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
		int m_max_volume_distance = pTanAngleData->mMaxDis;
		int mContiDownNums = pTanAngleData->mContiDownNums;
		int mBigIncreaseNums = pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums = pTanAngleData->mRsi1BigNums;
		int mNextGrow = pTanAngleData->mNextGrow;
		double f_cur_rsi_1 = pTanAngleData->fRsi1;
		int mContiVolDownNums = pTanAngleData->mContiVolDownNums;
		int mStepIndex = pTanAngleData->mStepIndex;

		int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
		int mVolM5ContiUpNums = pTanAngleData->mVolM5ContiUpNums;
		int mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;
		
		/*if (pTanAngleData->strStockCode == "SZ002487")
		{
			int a = 0;
			a++;

		}*/


		int mInBollMiddleUpNums = CalcInBollMiddleUpNums(pTanAngleData->vec_high_value, pTanAngleData->vec_low_value, pTanAngleData->vec_boll_up, pTanAngleData->vec_boll_middle);
		int mInPriceM10M20 = CalcInPriceM10M20(pTanAngleData->vec_high_value, pTanAngleData->vec_low_value, pTanAngleData->vec_price_m5, pTanAngleData->vec_price_m10, pTanAngleData->vec_price_m20);
		
		
		
		if (mInPriceM10M20 >=8)
		{
			//double f_value = f_ma5_angle / m_continus_price_m20_up_nums;
			//double f_value2 = f_ma10_angle / m_continus_price_m20_up_nums;

			DropOffData* pDropOffData = new DropOffData();
			pDropOffData->strStockCode = vecTanAngleData[i]->strStockCode;
			pDropOffData->strStockName = vecTanAngleData[i]->strStockName;
			pDropOffData->fMaxMultiple = vecTanAngleData[i]->fPara2;
			pDropOffData->fAveMultiple = vecTanAngleData[i]->fPara1;
			printf("%s  %s  InBoll= %d  InPriceM10M20=%d\n", pDropOffData->strStockCode, pDropOffData->strStockName, mInBollMiddleUpNums, mInPriceM10M20);

			CString strInfo;
			strInfo.Format("%.2f,up%.2f", vecTanAngleData[i]->fPara0, vecTanAngleData[i]->fPara7);
			pDropOffData->strMaxDate = strInfo;
			strInfo.Format("%.2f,%d ave:%.2f  %.2f", vecTanAngleData[i]->fPara4, vecTanAngleData[i]->mMaxDis, vecTanAngleData[i]->fPara5, vecTanAngleData[i]->fPara6);
			pDropOffData->strMinDate = strInfo;
			pDropOffData->mMaxValuePassDay = vecTanAngleData[i]->fPara3;
			pDropOffData->fDownTotalRang = 0.0;
			pDropOffData->mFilterNums = vecTanAngleData[i]->mPara6;
			pDropOffData->mSpecNums = vecTanAngleData[i]->mPara7;

			strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums, vecTanAngleData[i]->mContiVolDownNums, vecTanAngleData[i]->mStepIndex, vecTanAngleData[i]->mNowIsMaxPriceNums,
				vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, vecTanAngleData[i]->fVolumePer,
				vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
			pDropOffData->strInfo = strInfo;

			vecDropOffData.push_back(pDropOffData);

		}
		else
		{
			continue;
		}
	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
}

//全均衡
BOOL CDlgDropOff::DoFilterTanMatch4(void)
{

	TanAngleData *pTanAngleData=NULL;
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];

		double f_ma5_angle = pTanAngleData->fPara0;
		double f_ma10_angle = pTanAngleData->fPara1;
		double f_ma20_angle = pTanAngleData->fPara2;
		double f_ma60_angle = pTanAngleData->fPara3;
		double f_max_volume_per = pTanAngleData->fPara4;
		double f_ave_volume_per = pTanAngleData->fPara5;
		double f_60_20_cross_price_increase = pTanAngleData->fPara6;
		double f_20_10_cross_price_increase = pTanAngleData->fPara7;
		double f_60_day_increase = pTanAngleData->fPara8;
		double fNowGrow = pTanAngleData->fNowGrow;
		double fNowMaxGrow = pTanAngleData->fNowMaxGrow;
		int mNowIsMaxPriceNums = pTanAngleData->mNowIsMaxPriceNums;

		int  mMaxDis = pTanAngleData->mMaxDis;

		int m_10_big_20_nums = pTanAngleData->mPara6;
		int m_60_big_20_nums = pTanAngleData->mPara7;

		int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
		int m_max_volume_distance = pTanAngleData->mMaxDis;
		int mContiDownNums = pTanAngleData->mContiDownNums;
		int mBigIncreaseNums = pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums = pTanAngleData->mRsi1BigNums;
		int mNextGrow = pTanAngleData->mNextGrow;
		double f_cur_rsi_1 = pTanAngleData->fRsi1;
		int mContiVolDownNums = pTanAngleData->mContiVolDownNums;
		int mStepIndex = pTanAngleData->mStepIndex;

		int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
		int mVolM5ContiUpNums = pTanAngleData->mVolM5ContiUpNums;
		int mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;

		if(mBigIncreaseNums>0||mRsi1BigNums>2) 
			continue;

		double f_per=f_20_10_cross_price_increase/m_10_big_20_nums;
		if(f_per>1.2 )//1.2
			continue;
		f_per=f_60_20_cross_price_increase/m_60_big_20_nums;
		if(f_per> 1.2)//1.2
			continue;

		if(f_ave_volume_per>2.6)
			continue;

		if(m_continus_price_m10_up_nums>20||m_continus_price_m20_up_nums>20||m_continus_price_m60_up_nums>20)
			continue;


		
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecTanAngleData[i]->strStockCode;
		pDropOffData->strStockName=vecTanAngleData[i]->strStockName;
		pDropOffData->fMaxMultiple=vecTanAngleData[i]->fPara2;
		pDropOffData->fAveMultiple=vecTanAngleData[i]->fPara1;
		CString strInfo;
		strInfo.Format("%.2f,up%.2f",vecTanAngleData[i]->fPara0,vecTanAngleData[i]->fPara7);
		pDropOffData->strMaxDate=strInfo;
		strInfo.Format("%.2f,%d ave:%.2f  %.2f",vecTanAngleData[i]->fPara4,vecTanAngleData[i]->mMaxDis,vecTanAngleData[i]->fPara5,vecTanAngleData[i]->fPara6);
		pDropOffData->strMinDate=strInfo;
		pDropOffData->mMaxValuePassDay=vecTanAngleData[i]->fPara3;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=vecTanAngleData[i]->mPara6;
		pDropOffData->mSpecNums=vecTanAngleData[i]->mPara7;
		//strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#rb%d",vecTanAngleData[i]->fPara8,vecTanAngleData[i]->mPara8,vecTanAngleData[i]->mPara9,vecTanAngleData[i]->mPara10,vecTanAngleData[i]->mContiDownNums,vecTanAngleData[i]->mContiVolDownNums,vecTanAngleData[i]->mStepIndex,vecTanAngleData[i]->mNowIsMaxPriceNums,
		//	vecTanAngleData[i]->mBigIncreaseNums,vecTanAngleData[i]->mRsi1BigNums);
		//pDropOffData->strInfo=strInfo;
		
		strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums, vecTanAngleData[i]->mContiVolDownNums, vecTanAngleData[i]->mStepIndex, vecTanAngleData[i]->mNowIsMaxPriceNums,
			vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, vecTanAngleData[i]->fVolumePer,
			vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
		pDropOffData->strInfo = strInfo;



		vecDropOffData.push_back(pDropOffData);

	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
}


BOOL CDlgDropOff::DoFilterTanMatch5(void)
{

#if 1
	TanAngleData* pTanAngleData = NULL;
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		pTanAngleData = vecTanAngleData[i];

		double f_ma5_angle = pTanAngleData->fPara0;
		double f_ma10_angle = pTanAngleData->fPara1;
		double f_ma20_angle = pTanAngleData->fPara2;
		double f_ma60_angle = pTanAngleData->fPara3;
		double f_max_volume_per = pTanAngleData->fPara4;
		double f_ave_volume_per = pTanAngleData->fPara5;
		double f_60_20_cross_price_increase = pTanAngleData->fPara6;
		double f_20_10_cross_price_increase = pTanAngleData->fPara7;
		double f_60_day_increase = pTanAngleData->fPara8;
		double fNowGrow = pTanAngleData->fNowGrow;
		double fNowMaxGrow = pTanAngleData->fNowMaxGrow;
		int mNowIsMaxPriceNums = pTanAngleData->mNowIsMaxPriceNums;

		int  mMaxDis = pTanAngleData->mMaxDis;

		int m_10_big_20_nums = pTanAngleData->mPara6;
		int m_60_big_20_nums = pTanAngleData->mPara7;

		int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
		int m_max_volume_distance = pTanAngleData->mMaxDis;
		int mContiDownNums = pTanAngleData->mContiDownNums;
		int mBigIncreaseNums = pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums = pTanAngleData->mRsi1BigNums;
		int mNextGrow = pTanAngleData->mNextGrow;
		double f_cur_rsi_1 = pTanAngleData->fRsi1;
		int mContiVolDownNums = pTanAngleData->mContiVolDownNums;
		int mStepIndex = pTanAngleData->mStepIndex;

		int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
		int mVolM5ContiUpNums = pTanAngleData->mVolM5ContiUpNums;
		int mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;


		bool bok1 = false;
		
		double fVolumePerForM30 = pTanAngleData->fVolumePerForM30;
		double fVolumePerForM20 = pTanAngleData->fVolumePerForM20;
		double fVolumePer = pTanAngleData->fVolumePer;
		double fVolumePerForM5 = pTanAngleData->fVolumePerForM5;
		f_20_10_cross_price_increase = pTanAngleData->fPara7;
		f_60_20_cross_price_increase = pTanAngleData->fPara6;
		m_10_big_20_nums = pTanAngleData->mPara6;
		m_60_big_20_nums = pTanAngleData->mPara7;

		double fcustomtotalvalue = pTanAngleData->fcustomtotalvalue;
		fcustomtotalvalue = fabs(fcustomtotalvalue);
		double f_max_increase = f_60_20_cross_price_increase;
		if (f_max_increase < f_20_10_cross_price_increase)
			f_max_increase = f_20_10_cross_price_increase;

		double f_custom_per = fcustomtotalvalue / f_max_increase;

		double f_max_vol_per = fVolumePerForM30;
		if (f_max_vol_per < fVolumePerForM20)
			f_max_vol_per = fVolumePerForM20;

#if 0
		if (fVolumePerForM30 > fVolumePerForM20 && fVolumePerForM20 > fVolumePer && fVolumePer > fVolumePerForM5)
		{
			double f_per = f_20_10_cross_price_increase / m_10_big_20_nums;
			double f_per2 = f_60_20_cross_price_increase / m_60_big_20_nums;
			if (f_per > f_per2 )  //&& f_per < 4.95
			{
				mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
				m_continus_price_m10_up_nums = pTanAngleData->mPara8;
				m_continus_price_m20_up_nums = pTanAngleData->mPara9;
				m_continus_price_m60_up_nums = pTanAngleData->mPara10;
				if (m_continus_price_m60_up_nums < 10 && m_continus_price_m20_up_nums < 15 && m_continus_price_m10_up_nums < 15 && mPriceM5ContiUpNums < 15)
				{
					//if(f_ave_volume_per<4.0 && fVolumePerForM30<4.5)
						bok1 = true;
				}
			}
		}
#else
		/*if (m_60_big_20_nums < 0 && m_10_big_20_nums < 15 && f_ma60_angle <= 0.0 && f_custom_per<1.5 && f_max_vol_per<3.0)
		//if ( (m_60_big_20_nums + m_10_big_20_nums +f_ma60_angle )<10.0)
		{
			bok1 = true;
		}
		*/

		if (fVolumePerForM5 < fVolumePer && fVolumePer< fVolumePerForM20 && fVolumePerForM20< fVolumePerForM30)
		{
			if (f_ave_volume_per < 10.0 && (f_ave_volume_per>fVolumePerForM30) && (f_max_volume_per< f_ave_volume_per))
			{
				double f_per = f_20_10_cross_price_increase / m_10_big_20_nums;
				if (f_per < 8.0)
				{
					f_per = f_60_20_cross_price_increase / m_60_big_20_nums;
					if (f_per < 8.0)
						bok1 = true;
				}

			}
				
		}
		/*if (f_ma10_angle > 60.0 && f_ma10_angle < 70.0)
		{
			if(f_ma5_angle>65.0 && f_ma5_angle<77.0)
				bok1 = true;

		}*/
#endif

		
		


		if (bok1)
		{
			DropOffData* pDropOffData = new DropOffData();
			pDropOffData->strStockCode = vecTanAngleData[i]->strStockCode;
			pDropOffData->strStockName = vecTanAngleData[i]->strStockName;
			pDropOffData->fMaxMultiple = vecTanAngleData[i]->fPara2;
			pDropOffData->fAveMultiple = vecTanAngleData[i]->fPara1;
			CString strInfo;
			strInfo.Format("%.2f,up%.2f", vecTanAngleData[i]->fPara0, vecTanAngleData[i]->fPara7);
			pDropOffData->strMaxDate = strInfo;
			strInfo.Format("%.2f,%d ave:%.2f  %.2f", vecTanAngleData[i]->fPara4, vecTanAngleData[i]->mMaxDis, vecTanAngleData[i]->fPara5, vecTanAngleData[i]->fPara6);
			pDropOffData->strMinDate = strInfo;
			pDropOffData->mMaxValuePassDay = vecTanAngleData[i]->fPara3;
			pDropOffData->fDownTotalRang = 0.0;
			pDropOffData->mFilterNums = vecTanAngleData[i]->mPara6;
			pDropOffData->mSpecNums = vecTanAngleData[i]->mPara7;

			strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums, vecTanAngleData[i]->mContiVolDownNums, vecTanAngleData[i]->mStepIndex, vecTanAngleData[i]->mNowIsMaxPriceNums,
				vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, vecTanAngleData[i]->fVolumePer,
				vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
			pDropOffData->strInfo = strInfo;

			vecDropOffData.push_back(pDropOffData);

		}
		else
			continue;

	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);
	return TRUE;

#else

	TanAngleData* pTanAngleData = NULL;
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		pTanAngleData = vecTanAngleData[i];

		double f_ma5_angle = pTanAngleData->fPara0;
		double f_ma10_angle = pTanAngleData->fPara1;
		double f_ma20_angle = pTanAngleData->fPara2;
		double f_ma60_angle = pTanAngleData->fPara3;
		double f_max_volume_per = pTanAngleData->fPara4;
		double f_ave_volume_per = pTanAngleData->fPara5;
		double f_60_20_cross_price_increase = pTanAngleData->fPara6;
		double f_20_10_cross_price_increase = pTanAngleData->fPara7;
		double f_60_day_increase = pTanAngleData->fPara8;
		double fNowGrow = pTanAngleData->fNowGrow;
		double fNowMaxGrow = pTanAngleData->fNowMaxGrow;
		int mNowIsMaxPriceNums = pTanAngleData->mNowIsMaxPriceNums;

		int  mMaxDis = pTanAngleData->mMaxDis;

		int m_10_big_20_nums = pTanAngleData->mPara6;
		int m_60_big_20_nums = pTanAngleData->mPara7;

		int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
		int m_max_volume_distance = pTanAngleData->mMaxDis;
		int mContiDownNums = pTanAngleData->mContiDownNums;
		int mBigIncreaseNums = pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums = pTanAngleData->mRsi1BigNums;
		int mNextGrow = pTanAngleData->mNextGrow;
		double f_cur_rsi_1 = pTanAngleData->fRsi1;
		int mContiVolDownNums = pTanAngleData->mContiVolDownNums;
		int mStepIndex = pTanAngleData->mStepIndex;

		int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
		int mVolM5ContiUpNums = pTanAngleData->mVolM5ContiUpNums;
		int mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;

		

		double f_temp = f_60_20_cross_price_increase;

		if (f_20_10_cross_price_increase > f_60_20_cross_price_increase)
			f_temp = f_20_10_cross_price_increase;

		double f_temp_2 = f_temp / f_ave_volume_per;

		
		bool bok1 = false;
		if (f_temp > 70.0 && f_ave_volume_per < 2.8 )
			bok1 = true;


		if (bok1)
		{
			DropOffData* pDropOffData = new DropOffData();
			pDropOffData->strStockCode = vecTanAngleData[i]->strStockCode;
			pDropOffData->strStockName = vecTanAngleData[i]->strStockName;
			pDropOffData->fMaxMultiple = vecTanAngleData[i]->fPara2;
			pDropOffData->fAveMultiple = vecTanAngleData[i]->fPara1;
			CString strInfo;
			strInfo.Format("%.2f,up%.2f", vecTanAngleData[i]->fPara0, vecTanAngleData[i]->fPara7);
			pDropOffData->strMaxDate = strInfo;
			strInfo.Format("%.2f,%d ave:%.2f  %.2f", vecTanAngleData[i]->fPara4, vecTanAngleData[i]->mMaxDis, vecTanAngleData[i]->fPara5, vecTanAngleData[i]->fPara6);
			pDropOffData->strMinDate = strInfo;
			pDropOffData->mMaxValuePassDay = vecTanAngleData[i]->fPara3;
			pDropOffData->fDownTotalRang = 0.0;
			pDropOffData->mFilterNums = vecTanAngleData[i]->mPara6;
			pDropOffData->mSpecNums = vecTanAngleData[i]->mPara7;

			strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums, vecTanAngleData[i]->mContiVolDownNums, vecTanAngleData[i]->mStepIndex, vecTanAngleData[i]->mNowIsMaxPriceNums,
				vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, vecTanAngleData[i]->fVolumePer,
				vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
			pDropOffData->strInfo = strInfo;

			vecDropOffData.push_back(pDropOffData);

		}
		else
			continue;

	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);
	return TRUE;
#endif
}

BOOL CDlgDropOff::DoFilterTanMatch6(void)
{
#if 0
	CDlgTanPara2 dlg;
	BOOL bOK=FALSE;
	if(dlg.DoModal()==IDOK)
	{
		f_AveVolMulMin=dlg.GetAveVolMulMin();
		f_AveVolMulMax=dlg.GetAveVolMulMax();
		bIgnorM5Angle=dlg.IsIgnorM5Angle();
		bUseContiUpNums=dlg.IsUserUseContiUpNums();
		bOK=TRUE;

	}
	if(!bOK)
		return FALSE;

	TanAngleData *pTanAngleData=NULL;
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];

		double f_ma5_angle=pTanAngleData->fPara0;
		double f_ma10_angle=pTanAngleData->fPara1;
		double f_ma20_angle=pTanAngleData->fPara2;
		double f_ma60_angle=pTanAngleData->fPara3;
		double f_max_volume_per=pTanAngleData->fPara4;
		double f_ave_volume_per=pTanAngleData->fPara5;
		double f_60_20_cross_price_increase=pTanAngleData->fPara6;
		double f_20_10_cross_price_increase=pTanAngleData->fPara7;
		double f_60_day_increase=pTanAngleData->fPara8;
		int m_10_big_20_nums=pTanAngleData->mPara6;
		int m_60_big_20_nums=pTanAngleData->mPara7;
		int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
		int m_max_volume_distance=pTanAngleData->mMaxDis;
		int mContiDownNums=pTanAngleData->mContiDownNums;
		int mContiVolDownNums=pTanAngleData->mContiVolDownNums;

		int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;
		int mNextGrow=pTanAngleData->mNextGrow;
		int mBigIncreaseNums=pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums=pTanAngleData->mRsi1BigNums;
		double fNextGrow=pTanAngleData->fNextGrow;
		double f_volume_per=pTanAngleData->fVolumePer;
		double f_cur_rsi_1=pTanAngleData->fRsi1;
		std::vector<double> vec_rsi_1=pTanAngleData->vec_rsi_1;
		std::vector<double>  vec_close_value=pTanAngleData->vec_close_value;
		std::vector<double>  vec_begin_value=pTanAngleData->vec_begin_value;
		std::vector<double>  vec_high_value=pTanAngleData->vec_high_value;
		std::vector<double>  vec_low_value=pTanAngleData->vec_low_value;
		std::vector<double> vec_price_m5=pTanAngleData->vec_price_m5;
		std::vector<double> vec_price_m10=pTanAngleData->vec_price_m10;

		std::vector<double> vec_volume_ma5=pTanAngleData->vec_volume_m5;
		std::vector<double> vec_volume_ma10=pTanAngleData->vec_volume_m10;

		std::vector<double>  vec_volume_value=pTanAngleData->vec_volume_value;
		

		int mSize=vec_volume_value.size();
		double f_now_volume_value=vec_volume_value[mSize-1];
		double f_now_volume_ma10=vec_volume_ma10[mSize-1];
		BOOL bOK1=FALSE;
		if(f_ma10_angle>f_ma20_angle)
		{
			if(bIgnorM5Angle)
			{
				if(f_ma10_angle>f_ma5_angle)
				{
					double f_per=(f_ma10_angle-f_ma5_angle)*100.0/f_ma10_angle;
					if(f_per<15.0)
						bOK1=TRUE;
				}
			}
			else
			{
				if(f_ma5_angle>f_ma10_angle)
					bOK1=TRUE;
			}
			
		}

		if(!bOK1)
			continue;

		if(bUseContiUpNums)
		{
			if(m_continus_price_m10_up_nums>20||m_continus_price_m20_up_nums>20||m_continus_price_m60_up_nums>20)
				continue;
		}
		
		if(f_ave_volume_per>f_AveVolMulMax||f_ave_volume_per<f_AveVolMulMin)
			continue;

		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecTanAngleData[i]->strStockCode;
		pDropOffData->strStockName=vecTanAngleData[i]->strStockName;
		pDropOffData->fMaxMultiple=vecTanAngleData[i]->fPara2;
		pDropOffData->fAveMultiple=vecTanAngleData[i]->fPara1;
		CString strInfo;
		strInfo.Format("%.2f,up%.2f",vecTanAngleData[i]->fPara0,vecTanAngleData[i]->fPara7);
		pDropOffData->strMaxDate=strInfo;
		strInfo.Format("%.2f,%d ave:%.2f  %.2f",vecTanAngleData[i]->fPara4,vecTanAngleData[i]->mMaxDis,vecTanAngleData[i]->fPara5,vecTanAngleData[i]->fPara6);
		pDropOffData->strMinDate=strInfo;
		pDropOffData->mMaxValuePassDay=vecTanAngleData[i]->fPara3;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=vecTanAngleData[i]->mPara6;
		pDropOffData->mSpecNums=vecTanAngleData[i]->mPara7;
		strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#rb%d#%.2f",vecTanAngleData[i]->fPara8,vecTanAngleData[i]->mPara8,vecTanAngleData[i]->mPara9,vecTanAngleData[i]->mPara10,vecTanAngleData[i]->mContiDownNums,vecTanAngleData[i]->mContiVolDownNums,vecTanAngleData[i]->mStepIndex,vecTanAngleData[i]->mNowIsMaxPriceNums,
			vecTanAngleData[i]->mBigIncreaseNums,vecTanAngleData[i]->mRsi1BigNums,f_volume_per);
		pDropOffData->strInfo=strInfo;
		vecDropOffData.push_back(pDropOffData);

	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
#else

TanAngleData* pTanAngleData = NULL;
for (int i = 0; i < vecTanAngleData.size(); i++)
{
	pTanAngleData = vecTanAngleData[i];

	double f_ma5_angle = pTanAngleData->fPara0;
	double f_ma10_angle = pTanAngleData->fPara1;
	double f_ma20_angle = pTanAngleData->fPara2;
	double f_ma60_angle = pTanAngleData->fPara3;
	double f_max_volume_per = pTanAngleData->fPara4;
	double f_ave_volume_per = pTanAngleData->fPara5;
	double f_60_20_cross_price_increase = pTanAngleData->fPara6;
	double f_20_10_cross_price_increase = pTanAngleData->fPara7;
	double f_60_day_increase = pTanAngleData->fPara8;
	double fNowGrow = pTanAngleData->fNowGrow;
	double fNowMaxGrow = pTanAngleData->fNowMaxGrow;
	int mNowIsMaxPriceNums = pTanAngleData->mNowIsMaxPriceNums;

	int  mMaxDis = pTanAngleData->mMaxDis;

	int m_10_big_20_nums = pTanAngleData->mPara6;
	int m_60_big_20_nums = pTanAngleData->mPara7;

	int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
	int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
	int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
	int m_max_volume_distance = pTanAngleData->mMaxDis;
	int mContiDownNums = pTanAngleData->mContiDownNums;
	int mBigIncreaseNums = pTanAngleData->mBigIncreaseNums;
	int mRsi1BigNums = pTanAngleData->mRsi1BigNums;
	int mNextGrow = pTanAngleData->mNextGrow;
	double f_cur_rsi_1 = pTanAngleData->fRsi1;
	int mContiVolDownNums = pTanAngleData->mContiVolDownNums;
	int mStepIndex = pTanAngleData->mStepIndex;

	int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
	int mVolM5ContiUpNums = pTanAngleData->mVolM5ContiUpNums;
	int mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;

	int mMaxValuePassDay = pTanAngleData->fPara3;

	double fVolumePerForM30 = pTanAngleData->fVolumePerForM30;
	double fVolumePerForM20 = pTanAngleData->fVolumePerForM20;
	double fVolumePer = pTanAngleData->fVolumePer;
	double fVolumePerForM5 = pTanAngleData->fVolumePerForM5;
	f_20_10_cross_price_increase = pTanAngleData->fPara7;
	f_60_20_cross_price_increase = pTanAngleData->fPara6;
	m_10_big_20_nums = pTanAngleData->mPara6;
	m_60_big_20_nums = pTanAngleData->mPara7;

	double fcustomtotalvalue = pTanAngleData->fcustomtotalvalue;
	fcustomtotalvalue = fabs(fcustomtotalvalue);
	double f_max_increase = f_60_20_cross_price_increase;
	if (f_max_increase < f_20_10_cross_price_increase)
		f_max_increase = f_20_10_cross_price_increase;

	double f_custom_per = fcustomtotalvalue / f_max_increase;

	double f_max_vol_per = fVolumePerForM30;
	if (f_max_vol_per < fVolumePerForM20)
		f_max_vol_per = fVolumePerForM20;
	
	if (pTanAngleData->strStockCode == "SH600854")
	{
		int a = 0;
		a++;

	}
	
	bool bok1 = false;
	
	//if (fNowGrow < -8.0)
	//	bok1 = true;


	if (fVolumePerForM5 < fVolumePer && fVolumePer < fVolumePerForM20 && fVolumePerForM20 < fVolumePerForM30)
	{
		if (f_ave_volume_per < 10.0 && (f_ave_volume_per > fVolumePerForM30) && (f_max_volume_per < f_ave_volume_per))
		{
			double f_per = f_20_10_cross_price_increase / m_10_big_20_nums;
			if (f_per < 8.0)
			{
				f_per = f_60_20_cross_price_increase / m_60_big_20_nums;
				if (f_per < 8.0 && mContiDownNums==0 && mBigIncreaseNums==0 && mNowIsMaxPriceNums==0)
					bok1 = true;
			}

		}

	}

	
	/*bool bok1 = false;
	if (m_10_big_20_nums >=6 && m_10_big_20_nums <=16)
		bok1 = true;


	bool bok2 = false;
	if (m_60_big_20_nums >= 1 && m_60_big_20_nums <= 8)
		bok2 = true;

	bool bok3 = false;
	double f_temp = f_ma10_angle - f_ma20_angle;
	
	double f_temp2 = fabs(f_ma5_angle - f_ma10_angle);
	double f_temp3 = f_temp / f_temp2;
	if(f_temp3>6.0)
		bok3 = true;

	if (bok1 && bok2 && bok3)*/
	if(bok1)
	{
		DropOffData* pDropOffData = new DropOffData();
		pDropOffData->strStockCode = vecTanAngleData[i]->strStockCode;
		pDropOffData->strStockName = vecTanAngleData[i]->strStockName;
		pDropOffData->fMaxMultiple = vecTanAngleData[i]->fPara2;
		pDropOffData->fAveMultiple = vecTanAngleData[i]->fPara1;
		CString strInfo;
		strInfo.Format("%.2f,up%.2f", vecTanAngleData[i]->fPara0, vecTanAngleData[i]->fPara7);
		pDropOffData->strMaxDate = strInfo;
		strInfo.Format("%.2f,%d ave:%.2f  %.2f", vecTanAngleData[i]->fPara4, vecTanAngleData[i]->mMaxDis, vecTanAngleData[i]->fPara5, vecTanAngleData[i]->fPara6);
		pDropOffData->strMinDate = strInfo;
		pDropOffData->mMaxValuePassDay = vecTanAngleData[i]->fPara3;
		pDropOffData->fDownTotalRang = 0.0;
		pDropOffData->mFilterNums = vecTanAngleData[i]->mPara6;
		pDropOffData->mSpecNums = vecTanAngleData[i]->mPara7;

		strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums/*P*/, vecTanAngleData[i]->mContiVolDownNums/*v*/, vecTanAngleData[i]->mStepIndex/*c*/, vecTanAngleData[i]->mNowIsMaxPriceNums,
			vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, vecTanAngleData[i]->fVolumePer,
			vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
		pDropOffData->strInfo = strInfo;

		vecDropOffData.push_back(pDropOffData);

	}
	else
		continue;

}

SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);
return TRUE;

#endif
}

//增长均衡
BOOL CDlgDropOff::DoFilterTanMatch7(void)
{
	vecDropOffData.clear();
	TanAngleData* pTanAngleData = NULL;
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		pTanAngleData = vecTanAngleData[i];

		double f_ma5_angle = pTanAngleData->fPara0;
		double f_ma10_angle = pTanAngleData->fPara1;
		double f_ma20_angle = pTanAngleData->fPara2;
		double f_ma60_angle = pTanAngleData->fPara3;
		double f_max_volume_per = pTanAngleData->fPara4;
		double f_ave_volume_per = pTanAngleData->fPara5;
		double f_60_20_cross_price_increase = pTanAngleData->fPara6;
		double f_20_10_cross_price_increase = pTanAngleData->fPara7;
		double f_60_day_increase = pTanAngleData->fPara8;
		double fNowGrow = pTanAngleData->fNowGrow;
		double fNowMaxGrow = pTanAngleData->fNowMaxGrow;
		int mNowIsMaxPriceNums = pTanAngleData->mNowIsMaxPriceNums;

		int  mMaxDis = pTanAngleData->mMaxDis;

		int m_10_big_20_nums = pTanAngleData->mPara6;
		int m_60_big_20_nums = pTanAngleData->mPara7;

		int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
		int m_max_volume_distance = pTanAngleData->mMaxDis;
		int mContiDownNums = pTanAngleData->mContiDownNums;
		int mBigIncreaseNums = pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums = pTanAngleData->mRsi1BigNums;
		int mNextGrow = pTanAngleData->mNextGrow;
		double f_cur_rsi_1 = pTanAngleData->fRsi1;
		int mContiVolDownNums = pTanAngleData->mContiVolDownNums;
		int mStepIndex = pTanAngleData->mStepIndex;

		int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
		int mVolM5ContiUpNums = pTanAngleData->mVolM5ContiUpNums;
		int mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;

		double f_temp = f_ma10_angle;

		if (f_ma5_angle > f_ma10_angle)
			f_temp = f_ma5_angle;
		double f_value = f_60_20_cross_price_increase / f_20_10_cross_price_increase;
		//if (f_value > 0.95 && f_value < 1.05 && f_ave_volume_per < 4.6 && f_temp<70.0)
		if (f_value > 0.92 && f_value < 1.08 )
		{

			DropOffData* pDropOffData = new DropOffData();
			pDropOffData->strStockCode = vecTanAngleData[i]->strStockCode;
			pDropOffData->strStockName = vecTanAngleData[i]->strStockName;
			pDropOffData->fMaxMultiple = vecTanAngleData[i]->fPara2;
			pDropOffData->fAveMultiple = vecTanAngleData[i]->fPara1;

			CString strInfo;
			strInfo.Format("%.2f,up%.2f", vecTanAngleData[i]->fPara0, vecTanAngleData[i]->fPara7);
			pDropOffData->strMaxDate = strInfo;
			strInfo.Format("%.2f,%d ave:%.2f  %.2f", vecTanAngleData[i]->fPara4, vecTanAngleData[i]->mMaxDis, vecTanAngleData[i]->fPara5, vecTanAngleData[i]->fPara6);
			pDropOffData->strMinDate = strInfo;
			pDropOffData->mMaxValuePassDay = vecTanAngleData[i]->fPara3;
			pDropOffData->fDownTotalRang = 0.0;
			pDropOffData->mFilterNums = vecTanAngleData[i]->mPara6;
			pDropOffData->mSpecNums = vecTanAngleData[i]->mPara7;

			strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums, vecTanAngleData[i]->mContiVolDownNums, vecTanAngleData[i]->mStepIndex, vecTanAngleData[i]->mNowIsMaxPriceNums,
				vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, vecTanAngleData[i]->fVolumePer,
				vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
			pDropOffData->strInfo = strInfo;

			vecDropOffData.push_back(pDropOffData);


		}

	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);
	return TRUE;
}


#if 0
BOOL CDlgDropOff::DoFilterTanMatch8(void)
{
	TanAngleData *pTanAngleData=NULL;
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];

		double f_ma5_angle=pTanAngleData->fPara0;
		double f_ma10_angle=pTanAngleData->fPara1;
		double f_ma20_angle=pTanAngleData->fPara2;
		double f_ma60_angle=pTanAngleData->fPara3;
		double f_max_volume_per=pTanAngleData->fPara4;
		double f_ave_volume_per=pTanAngleData->fPara5;
		double f_60_20_cross_price_increase=pTanAngleData->fPara6;
		double f_20_10_cross_price_increase=pTanAngleData->fPara7;
		double f_60_day_increase=pTanAngleData->fPara8;
		int m_10_big_20_nums=pTanAngleData->mPara6;
		int m_60_big_20_nums=pTanAngleData->mPara7;
		int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
		int m_max_volume_distance=pTanAngleData->mMaxDis;
		int mContiDownNums=pTanAngleData->mContiDownNums;
		int mContiVolDownNums=pTanAngleData->mContiVolDownNums;

		int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;
		int mNextGrow=pTanAngleData->mNextGrow;
		int mBigIncreaseNums=pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums=pTanAngleData->mRsi1BigNums;
		double fNextGrow=pTanAngleData->fNextGrow;
		double f_cur_rsi_1=pTanAngleData->fRsi1;
		std::vector<double> vec_rsi_1=pTanAngleData->vec_rsi_1;
		std::vector<double>  vec_close_value=pTanAngleData->vec_close_value;
		std::vector<double>  vec_begin_value=pTanAngleData->vec_begin_value;
		std::vector<double>  vec_high_value=pTanAngleData->vec_high_value;
		std::vector<double>  vec_low_value=pTanAngleData->vec_low_value;
		std::vector<double> vec_price_m5=pTanAngleData->vec_price_m5;
		std::vector<double> vec_price_m10=pTanAngleData->vec_price_m10;
		std::vector<double>  vec_boll_up=pTanAngleData->vec_boll_up;
		std::vector<double>  vec_boll_middle=pTanAngleData->vec_boll_middle;
		std::vector<double> vec_boll_bottom=pTanAngleData->vec_boll_bottom;

		int mSize=vec_boll_up.size();
		int mOkNums=0;
		for(int j=mSize-5;j<mSize-2;j++)
		{
			double f_high_val=vec_high_value[j];
			double f_low_val=vec_low_value[j];
			double f_boll_up=vec_boll_up[j];
			double f_boll_bottom=vec_boll_bottom[j];
			if(f_high_val<f_boll_up)
			{
				if(f_low_val>f_boll_bottom)
					mOkNums++;
			}
		}

		if(mOkNums<3)
			continue;

		double f_now_high=vec_high_value[mSize-1];
		double f_p_high=vec_high_value[mSize-2];
		
		double f_now_low=vec_low_value[mSize-1];
		double f_p_low=vec_low_value[mSize-2];
		
		double f_now_boll_up=vec_boll_up[mSize-1];
		double f_p_boll_up=vec_boll_up[mSize-2];
		
		
		BOOL bOk=FALSE;
		if(f_now_high>f_now_boll_up)
		{
			if(f_now_low<f_now_boll_up)
				bOk=TRUE;
		}

		if(!bOk)
			continue;

		bOk=FALSE;
		if(f_p_high>f_p_boll_up)
		{
			if(f_p_low<f_p_boll_up)
				bOk=TRUE;
		}
		if(!bOk)
			continue;




		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecTanAngleData[i]->strStockCode;
		pDropOffData->strStockName=vecTanAngleData[i]->strStockName;
		pDropOffData->fMaxMultiple=vecTanAngleData[i]->fPara2;
		pDropOffData->fAveMultiple=vecTanAngleData[i]->fPara1;
		CString strInfo;
		strInfo.Format("%.2f,up%.2f",vecTanAngleData[i]->fPara0,vecTanAngleData[i]->fPara7);
		pDropOffData->strMaxDate=strInfo;
		strInfo.Format("%.2f,%d ave:%.2f  %.2f",vecTanAngleData[i]->fPara4,vecTanAngleData[i]->mMaxDis,vecTanAngleData[i]->fPara5,vecTanAngleData[i]->fPara6);
		pDropOffData->strMinDate=strInfo;
		pDropOffData->mMaxValuePassDay=vecTanAngleData[i]->fPara3;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=vecTanAngleData[i]->mPara6;
		pDropOffData->mSpecNums=vecTanAngleData[i]->mPara7;
		strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#%d#%d#rb%d",vecTanAngleData[i]->fPara8,vecTanAngleData[i]->mPara8,vecTanAngleData[i]->mPara9,vecTanAngleData[i]->mPara10,vecTanAngleData[i]->mContiDownNums,vecTanAngleData[i]->mContiVolDownNums,vecTanAngleData[i]->mNowIsMaxPriceNums,
			vecTanAngleData[i]->mBigIncreaseNums,vecTanAngleData[i]->mRsi1BigNums);
		pDropOffData->strInfo=strInfo;
		vecDropOffData.push_back(pDropOffData);

	}
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
}
#else

BOOL CDlgDropOff::DoFilterTanMatch8(void)
{

	CDlgKLineModeSel  dlg;
	if(dlg.DoModal()==IDOK)
	{

		mKLineSelMode=dlg.GetKLineMode();
	}
	else
	{
		return FALSE;

	}
	

	TanAngleData *pTanAngleData=NULL;
	Vec_TanAngleData vecTanAngleData2;

	for(int i=0;i<vecDropOffData.size();i++)
	{
		CString strStockCode=vecDropOffData[i]->strStockCode;

		for(int j=0;j<vecTanAngleData.size();j++)
		{
			if(vecTanAngleData[j]->strStockCode==strStockCode)
			{
				vecTanAngleData2.push_back(vecTanAngleData[j]);
				break;
			}

		}
	}
	vecDropOffData.clear();
	for(int i=0;i<vecTanAngleData2.size();i++)
	{
		pTanAngleData=vecTanAngleData2[i];

		double f_ma5_angle=pTanAngleData->fPara0;
		double f_ma10_angle=pTanAngleData->fPara1;
		double f_ma20_angle=pTanAngleData->fPara2;
		double f_ma60_angle=pTanAngleData->fPara3;
		double f_max_volume_per=pTanAngleData->fPara4;
		double f_ave_volume_per=pTanAngleData->fPara5;
		double f_60_20_cross_price_increase=pTanAngleData->fPara6;
		double f_20_10_cross_price_increase=pTanAngleData->fPara7;
		double f_60_day_increase=pTanAngleData->fPara8;
		int m_10_big_20_nums=pTanAngleData->mPara6;
		int m_60_big_20_nums=pTanAngleData->mPara7;
		int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
		int m_max_volume_distance=pTanAngleData->mMaxDis;
		int mContiDownNums=pTanAngleData->mContiDownNums;
		int mContiVolDownNums=pTanAngleData->mContiVolDownNums;

		int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;
		int mNextGrow=pTanAngleData->mNextGrow;
		int mBigIncreaseNums=pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums=pTanAngleData->mRsi1BigNums;
		double fNextGrow=pTanAngleData->fNextGrow;
		double f_volume_per=pTanAngleData->fVolumePer;
		double f_cur_rsi_1=pTanAngleData->fRsi1;
		double fcustomtotalvalue = pTanAngleData->fcustomtotalvalue;
		std::vector<double> vec_rsi_1=pTanAngleData->vec_rsi_1;
		std::vector<double>  vec_close_value=pTanAngleData->vec_close_value;
		std::vector<double>  vec_begin_value=pTanAngleData->vec_begin_value;
		std::vector<double>  vec_high_value=pTanAngleData->vec_high_value;
		std::vector<double>  vec_low_value=pTanAngleData->vec_low_value;
		std::vector<double> vec_price_m5=pTanAngleData->vec_price_m5;
		std::vector<double> vec_price_m10=pTanAngleData->vec_price_m10;
		std::vector<double>  vec_boll_up=pTanAngleData->vec_boll_up;
		std::vector<double>  vec_boll_middle=pTanAngleData->vec_boll_middle;
		std::vector<double> vec_boll_bottom=pTanAngleData->vec_boll_bottom;

		std::vector<double> vec_volume_ma5=pTanAngleData->vec_volume_m5;
		std::vector<double> vec_volume_ma10=pTanAngleData->vec_volume_m10;

		std::vector<double>  vec_volume_value=pTanAngleData->vec_volume_value;

		Vec_KLineDesData vecKLineDesData;
		int mSize=vec_boll_up.size();

		KLineDesData *  pKLineDesData=NULL;
		

		for(int j=mSize-16;j<mSize;j++)
		{
			double f_begin=vec_begin_value[j];
			double f_close=vec_close_value[j];
			double f_high=vec_high_value[j];
			double f_low=vec_low_value[j];
			pKLineDesData=CalcKLineDesData(f_begin,f_close,f_high,f_low);
			double f_p_close=vec_close_value[j-1];
			double f_per=(f_close-f_p_close)*100.0/f_p_close;
			if(pKLineDesData)
			{
				pKLineDesData->f_group_per=f_per;
				vecKLineDesData.push_back(pKLineDesData);
			}
		}

		int mKLineSize=vecKLineDesData.size();



		if(pTanAngleData->strStockCode=="SZ000021")
		{
			int a=0;
			a++;
		}
	
		KLineDesData *  p_Now_KLineDesData=vecKLineDesData[mKLineSize-1];
		KLineDesData *  p_P_KLineDesData=vecKLineDesData[mKLineSize-2];
		KLineDesData *  p_P2_KLineDesData=vecKLineDesData[mKLineSize-3];


		double f_now_close_price=vec_close_value[mSize-1];
		double f_p_close_price=vec_close_value[mSize-2];
		double f_p2_close_price=vec_close_value[mSize-3];
		double f_p3_close_price=vec_close_value[mSize-4];

		double f_now_per=(f_now_close_price-f_p_close_price)*100.0/f_p_close_price;

		double f_p_per=(f_p_close_price-f_p2_close_price)*100.0/f_p2_close_price;

		double f_p2_per=(f_p2_close_price-f_p3_close_price)*100.0/f_p3_close_price;


		double f_now_volume_value=vec_volume_value[mSize-1];
		double f_now_volume_ma10=vec_volume_ma10[mSize-1];

		BOOL bOK=FALSE;
		
		if(mKLineSelMode==0)	//光头强突
		{
			double f_p_begin_price=vec_begin_value[mSize-2];
			
			if(f_now_per>1.4 )//&& (f_p_per>0|| f_p_close_price>f_p_begin_price)
			{

				double f_now_up_per=p_Now_KLineDesData->f_up_per_b;
				double f_now_body_per=p_Now_KLineDesData->f_body_per_b;
				printf("%s %f %f\n",pTanAngleData->strStockCode,f_now_up_per,f_now_body_per);
				double f_up_per_thold = 10.0;
				if (f_now_per < 2.0)
					f_up_per_thold = 15.0;
				if(f_now_up_per< f_up_per_thold &&f_now_body_per>35.0)
				{
					bOK=TRUE;
				}
			}

		}
		else if(mKLineSelMode==1) //量价均衡
		{

			double f_60_20_cross_price_increase = pTanAngleData->fPara6;
			double f_20_10_cross_price_increase = pTanAngleData->fPara7;

			double f_max = f_60_20_cross_price_increase;
			if (f_20_10_cross_price_increase > f_60_20_cross_price_increase)
				f_max = f_20_10_cross_price_increase;

			fcustomtotalvalue = fabs(fcustomtotalvalue);

			double f_per = fcustomtotalvalue / f_max;

			if (f_per > 1.3 && f_per < 1.7)
			{
				bOK = TRUE;
			}

			/*if (f_now_per<3.0)
			{
				double  f_now_botton_per=p_Now_KLineDesData->f_bottom_per_b;
				if(f_now_botton_per>45.0)
				{
					bOK=TRUE;
				}

			}*/
		}
		else if(mKLineSelMode==2)  //三连阳
		{

			if(f_now_per>0 && f_p_per>0 && f_p2_per>0)
			{
				bOK=TRUE;
			}
		}
		else if(mKLineSelMode==3) //中阳线
		{
			if (f_now_per > 1.0 && f_now_per<4.0)
			{

				double f_now_body_per = p_Now_KLineDesData->f_body_per_b;
				if ( f_now_body_per>65.0)
				{
					bOK = TRUE;
				}
			}

		}
		else if(mKLineSelMode==4)		//阴阳阳
		{
			if(f_now_per>0&&f_p_per>0&&f_p2_per<-1.0)
			{
				bOK=TRUE;
			}
		}

		
		if(!bOK)
			continue;
		printf("%s\n",pTanAngleData->strStockCode);
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=pTanAngleData->strStockCode;
		pDropOffData->strStockName=pTanAngleData->strStockName;
		pDropOffData->fMaxMultiple=pTanAngleData->fPara2;
		pDropOffData->fAveMultiple=pTanAngleData->fPara1;
		CString strInfo;
		strInfo.Format("%.2f,up%.2f",pTanAngleData->fPara0,pTanAngleData->fPara7);
		pDropOffData->strMaxDate=strInfo;
		strInfo.Format("%.2f,%d ave:%.2f  %.2f",pTanAngleData->fPara4,pTanAngleData->mMaxDis,pTanAngleData->fPara5,pTanAngleData->fPara6);
		pDropOffData->strMinDate=strInfo;
		pDropOffData->mMaxValuePassDay=pTanAngleData->fPara3;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=pTanAngleData->mPara6;
		pDropOffData->mSpecNums=pTanAngleData->mPara7;
		
		//strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#rb%d#%.2f",pTanAngleData->fPara8,pTanAngleData->mPara8,pTanAngleData->mPara9,pTanAngleData->mPara10,pTanAngleData->mContiDownNums,pTanAngleData->mContiVolDownNums,pTanAngleData->mStepIndex,pTanAngleData->mNowIsMaxPriceNums,
		//	pTanAngleData->mBigIncreaseNums,pTanAngleData->mRsi1BigNums,f_volume_per);
		
	//	strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f", pTanAngleData->fPara8, pTanAngleData->mPara8, pTanAngleData->mPara9, pTanAngleData->mPara10, pTanAngleData->mContiDownNums, pTanAngleData->mContiVolDownNums, pTanAngleData->mStepIndex, pTanAngleData->mNowIsMaxPriceNums,
		//	pTanAngleData->mBigIncreaseNums, pTanAngleData->fNowGrow, pTanAngleData->mRsi1BigNums, pTanAngleData->fVolumePer);
		

		strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", pTanAngleData->fPara8, pTanAngleData->mPara8, pTanAngleData->mPara9, pTanAngleData->mPara10, pTanAngleData->mContiDownNums, pTanAngleData->mContiVolDownNums, pTanAngleData->mStepIndex, pTanAngleData->mNowIsMaxPriceNums,
			pTanAngleData->mBigIncreaseNums, pTanAngleData->fNowGrow, pTanAngleData->mRsi1BigNums, pTanAngleData->fVolumePer,
			pTanAngleData->mVolM5ContiUpNums, pTanAngleData->mVolM10ContiUpNums, pTanAngleData->mPriceM5ContiUpNums, pTanAngleData->fcustomtotalvalue);


		pDropOffData->strInfo=strInfo;
		vecDropOffData.push_back(pDropOffData);
		for(int j=0;j<mKLineSize;j++)
		{
			SAFE_DELETE(vecKLineDesData[j]);
		}
		vecKLineDesData.clear();

	}
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
}

#endif

BOOL CDlgDropOff::DoFilterTanMatch9(void)
{
#if 0
	TanAngleData* pTanAngleData = NULL;
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		pTanAngleData = vecTanAngleData[i];

		double f_ma5_angle = pTanAngleData->fPara0;
		double f_ma10_angle = pTanAngleData->fPara1;
		double f_ma20_angle = pTanAngleData->fPara2;
		double f_ma60_angle = pTanAngleData->fPara3;
		double f_max_volume_per = pTanAngleData->fPara4;
		double f_ave_volume_per = pTanAngleData->fPara5;
		double f_60_20_cross_price_increase = pTanAngleData->fPara6;
		double f_20_10_cross_price_increase = pTanAngleData->fPara7;
		double f_60_day_increase = pTanAngleData->fPara8;
		double fNowGrow = pTanAngleData->fNowGrow;
		double fNowMaxGrow = pTanAngleData->fNowMaxGrow;
		int mNowIsMaxPriceNums = pTanAngleData->mNowIsMaxPriceNums;

		int  mMaxDis = pTanAngleData->mMaxDis;

		int m_10_big_20_nums = pTanAngleData->mPara6;
		int m_60_big_20_nums = pTanAngleData->mPara7;

		int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
		int m_max_volume_distance = pTanAngleData->mMaxDis;
		int mContiDownNums = pTanAngleData->mContiDownNums;
		int mBigIncreaseNums = pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums = pTanAngleData->mRsi1BigNums;
		int mNextGrow = pTanAngleData->mNextGrow;
		double f_cur_rsi_1 = pTanAngleData->fRsi1;
		int mContiVolDownNums = pTanAngleData->mContiVolDownNums;
		int mStepIndex = pTanAngleData->mStepIndex;

		int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
		int mVolM5ContiUpNums = pTanAngleData->mVolM5ContiUpNums;
		int mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;

		if (mMaxDis>=10)
		{
			
			DropOffData* pDropOffData = new DropOffData();
			pDropOffData->strStockCode = vecTanAngleData[i]->strStockCode;
			pDropOffData->strStockName = vecTanAngleData[i]->strStockName;
			pDropOffData->fMaxMultiple = vecTanAngleData[i]->fPara2;
			pDropOffData->fAveMultiple = vecTanAngleData[i]->fPara1;
			
			CString strInfo;
			strInfo.Format("%.2f,up%.2f", vecTanAngleData[i]->fPara0, vecTanAngleData[i]->fPara7);
			pDropOffData->strMaxDate = strInfo;
			strInfo.Format("%.2f,%d ave:%.2f  %.2f", vecTanAngleData[i]->fPara4, vecTanAngleData[i]->mMaxDis, vecTanAngleData[i]->fPara5, vecTanAngleData[i]->fPara6);
			pDropOffData->strMinDate = strInfo;
			pDropOffData->mMaxValuePassDay = vecTanAngleData[i]->fPara3;
			pDropOffData->fDownTotalRang = 0.0;
			pDropOffData->mFilterNums = vecTanAngleData[i]->mPara6;
			pDropOffData->mSpecNums = vecTanAngleData[i]->mPara7;

			strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums, vecTanAngleData[i]->mContiVolDownNums, vecTanAngleData[i]->mStepIndex, vecTanAngleData[i]->mNowIsMaxPriceNums,
				vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, vecTanAngleData[i]->fVolumePer,
				vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
			pDropOffData->strInfo = strInfo;

			vecDropOffData.push_back(pDropOffData);

		}
		else
		{
			continue;
		}
	}

#else

	TanAngleData* pTanAngleData = NULL;
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		pTanAngleData = vecTanAngleData[i];

		double f_ma5_angle = pTanAngleData->fPara0;
		double f_ma10_angle = pTanAngleData->fPara1;
		double f_ma20_angle = pTanAngleData->fPara2;
		double f_ma60_angle = pTanAngleData->fPara3;
		double f_max_volume_per = pTanAngleData->fPara4;
		double f_ave_volume_per = pTanAngleData->fPara5;
		double f_60_20_cross_price_increase = pTanAngleData->fPara6;
		double f_20_10_cross_price_increase = pTanAngleData->fPara7;
		double f_60_day_increase = pTanAngleData->fPara8;
		double fNowGrow = pTanAngleData->fNowGrow;
		double fNowMaxGrow = pTanAngleData->fNowMaxGrow;
		int mNowIsMaxPriceNums = pTanAngleData->mNowIsMaxPriceNums;

		int  mMaxDis = pTanAngleData->mMaxDis;

		int m_10_big_20_nums = pTanAngleData->mPara6;
		int m_60_big_20_nums = pTanAngleData->mPara7;

		int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
		int m_max_volume_distance = pTanAngleData->mMaxDis;
		int mContiDownNums = pTanAngleData->mContiDownNums;
		int mBigIncreaseNums = pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums = pTanAngleData->mRsi1BigNums;
		int mNextGrow = pTanAngleData->mNextGrow;
		double f_cur_rsi_1 = pTanAngleData->fRsi1;
		int mContiVolDownNums = pTanAngleData->mContiVolDownNums;
		int mStepIndex = pTanAngleData->mStepIndex;

		int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
		
		int mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;

		double fVolumePerForM30 = pTanAngleData->fVolumePerForM30;
		double fVolumePerForM20 = pTanAngleData->fVolumePerForM20;
		double fVolumePer = pTanAngleData->fVolumePer;
		double fVolumePerForM5 = pTanAngleData->fVolumePerForM5;

		bool bOk = false;
#if 0
		if (fVolumePerForM30 > fVolumePerForM20)
		{
			if (fVolumePerForM20 > fVolumePer)
			{
				if (fVolumePer > fVolumePerForM5)
				{
					bOk = true;

				}

			}

		}
		bool bOk2 = false;
		double f_per = fVolumePerForM30 / fVolumePerForM5;
		if (f_per >= 2.0 && fVolumePerForM30 < 3.5 && fVolumePerForM30>1.3) //1.5
			bOk2 = true;
		int    mMinRsi3Interval = pTanAngleData->mMinRsi3Interval;
		double f_temp = fVolumePerForM30 / mMinRsi3Interval;
		bool bOk3 = false;
		if(f_temp>0.05)
			bOk3 = true;

		bool bOk4 = false;
		if(mBigIncreaseNums<1 && mRsi1BigNums < 1)
			bOk4 = true;
		//bool bOk5 = false;
		//if(mVolM5ContiUpNums<=5&& mVolM10ContiUpNums<=10)
		//	bOk5 = true;
		double fMinRsi3 = pTanAngleData->fMinRsi3;
		double fMinRsi1 = pTanAngleData->fMinRsi1;
		mMinRsi3Interval = pTanAngleData->mMinRsi3Interval;
		bool bOk6 = false;
		if (fMinRsi1 < 19.0 && fMinRsi3 < 39.0 ) //&& mMinRsi3Interval<40
		{
			bOk6= true;
		}

		f_20_10_cross_price_increase = pTanAngleData->fPara7;
		m_10_big_20_nums = pTanAngleData->mPara6;

		double f_day10_increase = f_20_10_cross_price_increase / m_10_big_20_nums;
		bool bOk7 = false;
		if(f_day10_increase >=1.0&& f_day10_increase<=3.0)
			bOk7 = true;

		f_60_20_cross_price_increase = pTanAngleData->fPara6;
		m_60_big_20_nums = pTanAngleData->mPara7;
		double f_day20_increase = f_60_20_cross_price_increase / m_60_big_20_nums;
		bool bOk8 = false;
		if (f_day20_increase >= 1.0&& f_day20_increase<=4.5)
			bOk8 = true;

		double f_max = f_20_10_cross_price_increase;
		if (f_60_20_cross_price_increase > f_max)
			f_max = f_60_20_cross_price_increase;


		double f_10_20_per = f_20_10_cross_price_increase / f_60_20_cross_price_increase;
		bool bOk9 = false;
		if (f_10_20_per > 1.0 && f_10_20_per < 2.0)
		{
			bOk9 = true;
		}

		bool bOk10 = false;
		if (f_max > 10.0 && f_max < 30.0)
		{
			bOk10 = true;
		}

		if (bOk && bOk2 && bOk4 && (f_cur_rsi_1 < 90.0) && bOk10) //bOk6&& 
#else

		if(f_ave_volume_per>7.0)
#endif
		{

			DropOffData* pDropOffData = new DropOffData();
			pDropOffData->strStockCode = vecTanAngleData[i]->strStockCode;
			pDropOffData->strStockName = vecTanAngleData[i]->strStockName;
			pDropOffData->fMaxMultiple = vecTanAngleData[i]->fPara2;
			pDropOffData->fAveMultiple = vecTanAngleData[i]->fPara1;

			CString strInfo;
			strInfo.Format("%.2f,up%.2f", vecTanAngleData[i]->fPara0, vecTanAngleData[i]->fPara7);
			pDropOffData->strMaxDate = strInfo;
			strInfo.Format("%.2f,%d ave:%.2f  %.2f", vecTanAngleData[i]->fPara4, vecTanAngleData[i]->mMaxDis, vecTanAngleData[i]->fPara5, vecTanAngleData[i]->fPara6);
			pDropOffData->strMinDate = strInfo;
			pDropOffData->mMaxValuePassDay = vecTanAngleData[i]->fPara3;
			pDropOffData->fDownTotalRang = 0.0;
			pDropOffData->mFilterNums = vecTanAngleData[i]->mPara6;
			pDropOffData->mSpecNums = vecTanAngleData[i]->mPara7;

			strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums, vecTanAngleData[i]->mContiVolDownNums, vecTanAngleData[i]->mStepIndex, vecTanAngleData[i]->mNowIsMaxPriceNums,
				vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, vecTanAngleData[i]->fVolumePer,
				vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
			pDropOffData->strInfo = strInfo;

			vecDropOffData.push_back(pDropOffData);

		}
		else
		{
			continue;
		}
	}

#endif
	SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);
	return TRUE;

}

KLineDesData*  CDlgDropOff::CalcKLineDesData(double f_begin,double f_close,double f_high,double f_low)
{
	KLineDesData *pKLineDesData;

	pKLineDesData=new KLineDesData();

	double f_total_per=(f_high-f_low)*100.0/f_low;
	if(f_total_per<0.01)
	{
		pKLineDesData->f_body_per_b=0.0;
		pKLineDesData->f_bottom_per_b=0.0;
		pKLineDesData->f_group_per=0.0;
		pKLineDesData->f_total_per=0.0;
		pKLineDesData->f_up_per_b=0.0;
		return pKLineDesData;
	}


	double f_up_per,f_bottom_per,f_body_per;
	if(f_close>f_begin)		//up
	{
		f_up_per=(f_high-f_close)*100.0/f_low;

		f_bottom_per=(f_begin-f_low)*100.0/f_low;

		f_body_per=(f_close-f_begin)*100.0/f_low;
	}
	else		//down
	{
		f_up_per=(f_high-f_begin)*100.0/f_low;

		f_bottom_per=(f_close-f_low)*100.0/f_low;

		f_body_per=(f_begin-f_close)*100.0/f_low;
	}

	double f_up_per_b=f_up_per*100.0/f_total_per;
	double f_bottom_per_b=f_bottom_per*100.0/f_total_per;
	double f_body_per_b=f_body_per*100.0/f_total_per;

	pKLineDesData->f_group_per=0.0;
	pKLineDesData->f_total_per=f_total_per;
	pKLineDesData->f_up_per_b=f_up_per_b;
	pKLineDesData->f_bottom_per_b=f_bottom_per_b;
	pKLineDesData->f_body_per_b=f_body_per_b;
	return pKLineDesData;

}

BOOL  CDlgDropOff::DoFilterMulTanMatch(void)
{
	Vec_TanAngleData vecResult;
	CMulTanAngleAss mulTanAngleAss;

	CTanAngleAlg mTanAngleAlg;
	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}

	/*int nums=vecTanAngleData.size();
	CString strInfo;
	strInfo.Format("%d",nums);
	AfxMessageBox(strInfo);*/

	vecResult=mulTanAngleAss.doFilter(vecTanAngleData,mDropOffTime);

	for(int i=0;i<vecResult.size();i++)
	{
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecResult[i]->strStockCode;
		pDropOffData->strStockName=vecResult[i]->strStockName;
		pDropOffData->fMaxMultiple=vecResult[i]->fPara1;
		pDropOffData->fAveMultiple=vecResult[i]->fPara2;
		CString strInfo;
		strInfo.Format("%.2f,up%.2f",vecResult[i]->fPara0,vecResult[i]->fPara7);
		pDropOffData->strMaxDate=strInfo;
		strInfo.Format("%.2f,%d  ave:%.2f   %.2f",vecResult[i]->fPara4,vecTanAngleData[i]->mMaxDis,vecTanAngleData[i]->fPara5,vecTanAngleData[i]->fPara6);
		pDropOffData->strMinDate=strInfo;
		pDropOffData->mMaxValuePassDay=vecResult[i]->fPara3;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=vecResult[i]->mPara6;
		pDropOffData->mSpecNums=vecResult[i]->mPara7;
		strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#%d#%d#rb%d",vecTanAngleData[i]->fPara8,vecTanAngleData[i]->mPara8,vecTanAngleData[i]->mPara9,vecTanAngleData[i]->mPara10,vecTanAngleData[i]->mContiDownNums,vecTanAngleData[i]->mContiVolDownNums,vecTanAngleData[i]->mNowIsMaxPriceNums,
			vecTanAngleData[i]->mBigIncreaseNums,vecTanAngleData[i]->mRsi1BigNums);
		pDropOffData->strInfo=strInfo;
		vecDropOffData.push_back(pDropOffData);
	}

	vecTanAngleData.clear();
	vecTanAngleData=vecResult;

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
}


BOOL CDlgDropOff::DoFilterLimitUpMatch(void)
{
	
	Vec_LimitUpData vecLimitUpData;
	CLimitUpAlg mLimitUpAlg;
	vecLimitUpData.clear();
	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}
	vecLimitUpData=mLimitUpAlg.doFilter(mDropOffTime);

	for(int i=0;i<vecLimitUpData.size();i++)
	{
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecLimitUpData[i]->strStockCode;
		pDropOffData->strStockName=vecLimitUpData[i]->strStockName;

		
		pDropOffData->fMaxMultiple = vecLimitUpData[i]->f_macd_per_2;
		pDropOffData->fAveMultiple= vecLimitUpData[i]->f_macd_per;
		pDropOffData->strMaxDate="";
		pDropOffData->strMinDate="";
		pDropOffData->mMaxValuePassDay=0;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=0;
		pDropOffData->mSpecNums=0;
		pDropOffData->strInfo="";
		vecDropOffData.push_back(pDropOffData);
	}


	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);

	return TRUE;
}

BOOL CDlgDropOff::DoFilterRsiMatch(void)
{
	Vec_RsiAlgData vecRsiAlgData;
	CRsiReverseAlg mRsiReverseAlg;
	vecDropOffData.clear();
	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}
	vecRsiAlgData=mRsiReverseAlg.doFilter(mDropOffTime);

	for(int i=0;i<vecRsiAlgData.size();i++)
	{
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecRsiAlgData[i]->strStockCode;
		pDropOffData->strStockName=vecRsiAlgData[i]->strStockName;
		
		pDropOffData->fMaxMultiple=vecRsiAlgData[i]->f_m5_m10_per;
		pDropOffData->fAveMultiple=0;
		CString strInfo;
		strInfo.Format("%.2f,%.2f,%.2f,%s",vecRsiAlgData[i]->f_pre_rsi1,vecRsiAlgData[i]->f_pre_rsi2,vecRsiAlgData[i]->f_pre_rsi3,vecRsiAlgData[i]->strMinDateTime);
		pDropOffData->strMaxDate=strInfo;
		strInfo.Format("%.2f,%.2f,%.2f,%s",vecRsiAlgData[i]->f_later_rsi1,vecRsiAlgData[i]->f_later_rsi2,vecRsiAlgData[i]->f_later_rsi3,vecRsiAlgData[i]->strMaxDateTime);
		pDropOffData->strMinDate=strInfo;
		pDropOffData->mMaxValuePassDay=0;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=0;
		pDropOffData->mSpecNums=0;
		pDropOffData->strInfo="";
		vecDropOffData.push_back(pDropOffData);
	}


	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);

	return TRUE;
}

void CDlgDropOff::OnRclickListItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if(pNMItemActivate->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU_RIGHT ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );

	}
	*pResult = 0;
}


void CDlgDropOff::OnMenuToRight()
{
	DropOffData *pDropOffData=NULL;
	for(uint16  i=0; i<mListCtrlItem.GetItemCount(); i++)
	{
		if( mListCtrlItem.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			pDropOffData=reinterpret_cast<DropOffData *>(mListCtrlItem.GetItemData(i));
			break;
		}
	}

	if(!pDropOffData)
		return;

	DropOffData *pDropOffData_Right=NULL;

	bool bFound=false;

	for(int j=0;j<vecDropOffData_Second.size();j++)
	{
		pDropOffData_Right=vecDropOffData_Second[j];
		if(pDropOffData->strStockCode==pDropOffData_Right->strStockCode)
		{
			pDropOffData_Right->mSpecNums++;
			bFound=true;
			break;
		}
	}

	if(!bFound)
	{
		vecDropOffData_Second.push_back(pDropOffData);
	}


	

	SetTimer(DROPOFF_EVENT_REFRESH_DATA_SECOND,300,0);


}

// Filter下一涨停股
BOOL CDlgDropOff::DoFilterNextGrowMatch(void)
{
	CStockDayTable* pStockDayTable = NULL;
	CString strNowDate;
	Vec_DropOffData  vecDropOffData_Bk;
	if (vecRSIData.size() > 0)
	{
		DropOffData* pDropOffData = NULL;
		

		for (int i = 0; i < vecDropOffData.size(); i++)
		{
			pDropOffData = vecDropOffData[i];

			pStockDayTable = StockDataMgr()->GetStockDayTable(pDropOffData->strStockCode);

			if (bUsePreDate)
			{
				CTime mDropOffTime;
				mDataTimeDropOff.GetTime(mDropOffTime);
				strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}
			else
			{
				CTime mDropOffTime = CTime::GetCurrentTime();
				strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);
			}

			int mNowIndex = pStockDayTable->GetStockDayIndex(strNowDate);
			Vec_StockDayData vecStockDayData = pStockDayTable->GetStockDayDataList();

			int size = vecStockDayData.size();

			if ((size - mNowIndex) < 4) //4
				continue;

			int mNextIndex = mNowIndex + 3;  //3
			double f_now_close_price = vecStockDayData[mNowIndex]->GetEndPrice();

			double f_next_close_price = vecStockDayData[mNextIndex]->GetEndPrice();

			double f_per = (f_next_close_price - f_now_close_price) * 100.0 / f_now_close_price;

			if (f_per > 3.0) //10.0
			{

				vecDropOffData_Bk.push_back(pDropOffData);
			}

		}

		vecDropOffData.clear();
		vecDropOffData = vecDropOffData_Bk;
		FilterByReserve();
		FilterByMerge();
		SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);

		return TRUE;
	}

	vecDropOffData.clear();
	TanAngleData *pTanAngleData=NULL;
	
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];

		pStockDayTable=StockDataMgr()->GetStockDayTable(pTanAngleData->strStockCode);

		if(bUsePreDate)
		{
			CTime mDropOffTime;
			mDataTimeDropOff.GetTime(mDropOffTime);
			strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		}
		else
		{
			CTime mDropOffTime=CTime::GetCurrentTime();
			strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		}

		int mNowIndex=pStockDayTable->GetStockDayIndex(strNowDate);
		Vec_StockDayData vecStockDayData=pStockDayTable->GetStockDayDataList();

		int size=vecStockDayData.size();

		if((size-mNowIndex)<4) //4
			continue;

		int mNextIndex=mNowIndex+3;  //3
		double f_now_close_price=vecStockDayData[mNowIndex]->GetEndPrice();

		double f_next_close_price=vecStockDayData[mNextIndex]->GetEndPrice();

		double f_per=(f_next_close_price-f_now_close_price)*100.0/f_now_close_price;

		printf("%s f_per=%f\n",pTanAngleData->strStockCode,f_per);
		if(f_per> 3.0) //10.0
		{
			if(f_per>10.0)
				vecTanAngleData[i]->mNextGrow=2;
			else if(f_per>7.0)
				vecTanAngleData[i]->mNextGrow=1;
			else
				vecTanAngleData[i]->mNextGrow=0;
			vecTanAngleData[i]->fNextGrow=f_per;
			DropOffData *pDropOffData=new DropOffData();
			pDropOffData->strStockCode=vecTanAngleData[i]->strStockCode;
			pDropOffData->strStockName=vecTanAngleData[i]->strStockName;
			pDropOffData->fMaxMultiple=vecTanAngleData[i]->fPara2;
			pDropOffData->fAveMultiple=vecTanAngleData[i]->fPara1;
			CString strInfo;
			strInfo.Format("%.2f,up%.2f",vecTanAngleData[i]->fPara0,vecTanAngleData[i]->fPara7);
			pDropOffData->strMaxDate=strInfo;
			strInfo.Format("%.2f,%d ave:%.2f  %.2f",vecTanAngleData[i]->fPara4,vecTanAngleData[i]->mMaxDis,vecTanAngleData[i]->fPara5,vecTanAngleData[i]->fPara6);
			pDropOffData->strMinDate=strInfo;
			pDropOffData->mMaxValuePassDay=vecTanAngleData[i]->fPara3;
			pDropOffData->fDownTotalRang=0.0;
			pDropOffData->mFilterNums=vecTanAngleData[i]->mPara6;
			pDropOffData->mSpecNums=vecTanAngleData[i]->mPara7;
			//strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#rb%d#%.2f",vecTanAngleData[i]->fPara8,vecTanAngleData[i]->mPara8,vecTanAngleData[i]->mPara9,vecTanAngleData[i]->mPara10,
			//	vecTanAngleData[i]->mContiDownNums,vecTanAngleData[i]->mContiVolDownNums,vecTanAngleData[i]->mStepIndex,vecTanAngleData[i]->mNowIsMaxPriceNums,vecTanAngleData[i]->mBigIncreaseNums,vecTanAngleData[i]->mRsi1BigNums,f_per);
			strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums, vecTanAngleData[i]->mContiVolDownNums, vecTanAngleData[i]->mStepIndex, vecTanAngleData[i]->mNowIsMaxPriceNums,
				vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, f_per,
				vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
			pDropOffData->strInfo=strInfo;
			vecDropOffData.push_back(pDropOffData);

		}
		else
		{
			if(f_per>10.0)
				vecTanAngleData[i]->mNextGrow=2;
			else if(f_per>7.0)
				vecTanAngleData[i]->mNextGrow=1;
			else
				vecTanAngleData[i]->mNextGrow=0;
			vecTanAngleData[i]->fNextGrow=f_per;
		}

	}


	return TRUE;
}

// 下一涨停股
void CDlgDropOff::OnBnClickedBtnNextGroup()
{
	if(bReserveFilter)
	{
		vecDropOffData_Reserve.clear();
		vecDropOffData_Reserve=vecDropOffData;
	}

	

	


	DoFilterNextGrowMatch();
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
}

//加入演算
BOOL  CDlgDropOff::doAddCalcu(void)
{
	CalcuData *pCalcuData=new CalcuData();

	CString strNowDate=vecTanAngleData[0]->strDateTime;
	pCalcuData->strDateTime=strNowDate;

	CStockDayTable*pStockDayTable=NULL;
	CStockRSIData* pStockRSIData=NULL;
	pStockDayTable=StockDataMgr()->GetStockDayTable("SH000001");
	pStockRSIData=CStockRSIArithmetic::CalcRSIData("SH000001",strNowDate,125,K_LINE_DAY,6,12,24); 
	pCalcuData->mStockExpStatus=0;
	pCalcuData->strResult="";
	pCalcuData->vec_exp_rsi_1_value=pStockRSIData->vec_rsi_1_value;
	pCalcuData->vec_exp_rsi_2_value=pStockRSIData->vec_rsi_2_value;
	pCalcuData->vec_exp_rsi_3_value=pStockRSIData->vec_rsi_3_value;

	pCalcuData->vecTanAngleData.assign(vecTanAngleData.begin(),vecTanAngleData.end());

	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pCalcuData->vecTanAngleData[i]->vec_rsi_1=vecTanAngleData[i]->vec_rsi_1;
		pCalcuData->vecTanAngleData[i]->vec_close_value=vecTanAngleData[i]->vec_close_value;
		pCalcuData->vecTanAngleData[i]->vec_begin_value=vecTanAngleData[i]->vec_begin_value;
		pCalcuData->vecTanAngleData[i]->vec_high_value=vecTanAngleData[i]->vec_high_value;
		pCalcuData->vecTanAngleData[i]->vec_low_value=vecTanAngleData[i]->vec_low_value;
		pCalcuData->vecTanAngleData[i]->vec_price_m5=vecTanAngleData[i]->vec_price_m5;
		pCalcuData->vecTanAngleData[i]->vec_price_m10=vecTanAngleData[i]->vec_price_m10;
		pCalcuData->vecTanAngleData[i]->vec_boll_up=vecTanAngleData[i]->vec_boll_up;
		pCalcuData->vecTanAngleData[i]->vec_boll_middle=vecTanAngleData[i]->vec_boll_middle;
		pCalcuData->vecTanAngleData[i]->vec_boll_bottom=vecTanAngleData[i]->vec_boll_bottom;
	}

	BOOL bFound=FALSE;
	for(int i=0;i<vecCalcuData.size();i++)
	{
		if(strNowDate==vecCalcuData[i]->strDateTime)
		{
			bFound=TRUE;
			break;
		}

	}

	if(!bFound)
	{
		vecCalcuData.push_back(pCalcuData);
		AfxMessageBox("加入成功");
	}
	else
	{
		AfxMessageBox("已经有该日期数据");
	}
	
	return TRUE;
}

//加入演算
/*void CDlgDropOff::OnBnClickedBtnAddCalcu()
{
	TanAngleData *pTanAngleData=NULL;
	BOOL  bCanAddCalcu=FALSE;
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];
		if(pTanAngleData->mNextGrow>0)
		{
			bCanAddCalcu=TRUE;
			break;
		}
	}
	if(!bCanAddCalcu)
	{

		AfxMessageBox("未推算，不能加入演算");
		return;
	}
	doAddCalcu();


}*/

//演算
/*void CDlgDropOff::OnBnClickedBtnCalcu()
{
	
	CDlgCalcu dlg;
	dlg.CopyCalcuData(vecCalcuData);
	dlg.DoModal();

}
*/

//长量均增长
BOOL CDlgDropOff::DoFilterLongAveGroup(void)
{

#if 0
	Vec_LongAveGroupAlgData vecLongAveGroupAlgData;
	CLongAveGroupAlg mLongAveGroupAlg;
	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}


	vecLongAveGroupAlgData=mLongAveGroupAlg.doFilter(mDropOffTime);

	for(int i=0;i<vecLongAveGroupAlgData.size();i++)
	{
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecLongAveGroupAlgData[i]->strStockCode;
		pDropOffData->strStockName=vecLongAveGroupAlgData[i]->strStockName;
		pDropOffData->fMaxMultiple=0.0;
		pDropOffData->fAveMultiple=0.0;
		pDropOffData->strMaxDate="";
		pDropOffData->strMinDate="";
		pDropOffData->mMaxValuePassDay=0;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=0;
		pDropOffData->mSpecNums=0;
		pDropOffData->strInfo="";
		vecDropOffData.push_back(pDropOffData);
	}
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
#else
	Vec_StepStepAlgData vecStepStepAlgData;
	CStepStepAlg  mStepStepAlg;
	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}

	vecStepStepAlgData=mStepStepAlg.doFilter(mDropOffTime);

	for(int i=0;i<vecStepStepAlgData.size();i++)
	{
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecStepStepAlgData[i]->strStockCode;
		pDropOffData->strStockName=vecStepStepAlgData[i]->strStockName;
		pDropOffData->fMaxMultiple=vecStepStepAlgData[i]->fCurStepPer;
		pDropOffData->fAveMultiple=vecStepStepAlgData[i]->fTotalStepPer;
		CString strInfo;
		strInfo.Format("#cur%.2f #ave%.2f #tol%.2f",vecStepStepAlgData[i]->fCurStepPer,vecStepStepAlgData[i]->fAveStepPer,vecStepStepAlgData[i]->fTotalStepPer);
		pDropOffData->strMaxDate=strInfo;

		strInfo.Format("m20 %d m60 %d m120 %d",vecStepStepAlgData[i]->m20ContiNums,vecStepStepAlgData[i]->m60ContiNums,vecStepStepAlgData[i]->m120ContiNums);

		pDropOffData->strMinDate=strInfo;
		pDropOffData->mMaxValuePassDay=vecStepStepAlgData[i]->mStepNums;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=0;
		pDropOffData->mSpecNums=0;

		double f_p4_per=vecStepStepAlgData[i]->f_p4_per;
		double f_p3_per=vecStepStepAlgData[i]->f_p3_per;
		double f_p2_per=vecStepStepAlgData[i]->f_p2_per;
		double f_p1_per=vecStepStepAlgData[i]->f_p1_per;
		double f_now_per=vecStepStepAlgData[i]->f_now_per;
		double f_per=f_p4_per+f_p3_per+f_p2_per+f_p1_per+f_now_per;

		strInfo.Format("p4:%.2f p3:%.2f p2:%.2f p1:%.2f now:%.2f t:%.2f",f_p4_per,f_p3_per,f_p2_per,f_p1_per,f_now_per,f_per);

		pDropOffData->strInfo=strInfo;
		vecDropOffData.push_back(pDropOffData);
	}
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;


#endif
}

BOOL CDlgDropOff::DoFilterThreeLow(void)
{

	CThreeLowFilterAlg mThreeLowFilterAlg;
	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}

	vecThreeLowData.clear();
	vecThreeLowData=mThreeLowFilterAlg.doFilter(mDropOffTime,vecDropOffData);
	vecDropOffData.clear();
	for(int i=0;i<vecThreeLowData.size();i++)
	{
		DropOffData *pDropOffData=new DropOffData();
		pDropOffData->strStockCode=vecThreeLowData[i]->strStockCode;
		pDropOffData->strStockName=vecThreeLowData[i]->strStockName;
		pDropOffData->fMaxMultiple=0;
		pDropOffData->fAveMultiple=0;
		CString strInfo;
		pDropOffData->strMaxDate="";


		double f_rsi_1=vecThreeLowData[i]->f_rsi_1;
		double f_rsi_2=vecThreeLowData[i]->f_rsi_2;
		double f_rsi_3=vecThreeLowData[i]->f_rsi_3;
		strInfo.Format("rsi1:%.2f rsi2:%.2f rsi3:%.2f",f_rsi_1,f_rsi_2,f_rsi_3);
		pDropOffData->strMinDate=strInfo;

		pDropOffData->mMaxValuePassDay=0;
		pDropOffData->fDownTotalRang=0.0;
		pDropOffData->mFilterNums=0;
		pDropOffData->mSpecNums=0;

		
		double f_p2_per=vecThreeLowData[i]->f_p2_per;
		double f_p1_per=vecThreeLowData[i]->f_p1_per;
		double f_now_per=vecThreeLowData[i]->f_now_per;
		double f_per=f_p2_per+f_p1_per+f_now_per;
		strInfo.Format("p2:%.2f  p1:%.2f now:%.2f t:%.2f",f_p2_per,f_p1_per,f_now_per,f_per);

		pDropOffData->strInfo=strInfo;
		vecDropOffData.push_back(pDropOffData);
	}

	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
}

BOOL CDlgDropOff::DoFilterOneLine(void)
{

	CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}
	vecDropOffData.clear();
	
	TanAngleData *pTanAngleData=NULL;
	CString strNowDate;
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];
		CGeneralAnalyze mGeneralAnalyze;
		Vec_GeneraDataDivid vecGeneraDataDivid;
		vecGeneraDataDivid=mGeneralAnalyze.doAnalyzeVec(mDropOffTime,pTanAngleData->strStockCode);
		if(pTanAngleData->strStockCode=="SZ300283")
		{
			int a=0;
			a++;

		}
		
		if(vecGeneraDataDivid.size()==1)
		{
			int mDataSize=90;
			GeneraDataDivid *pGeneraDataDivid=vecGeneraDataDivid[0];
			int mNums=pGeneraDataDivid->mDividBegin-pGeneraDataDivid->mDividEnd+1;
			int mNowNums=mDataSize-pGeneraDataDivid->mDividBegin;

			int mSize=pTanAngleData->vec_close_value.size();
			BOOL bBigUp6=FALSE;
			BOOL bBigUp10=FALSE;
			double f_last_8_total_per=0.0;
			double f_last_16_total_per=0.0;
			
			BOOL bBigUp6_16=FALSE;
			BOOL bBigUp10_16=FALSE;
			for(int j=mSize-16;j<mSize;j++)
			{

				double f_per_close=pTanAngleData->vec_close_value[j-1];
				double f_now_close=pTanAngleData->vec_close_value[j];
				double f_per=(f_now_close-f_per_close)*100.0/f_per_close;
				f_last_16_total_per+=f_per;

				if(f_per>6.0)
				{
					bBigUp6_16=TRUE;
				}

				if(f_per>9.5)
				{
					bBigUp10_16=TRUE;
				}

			}

			for(int j=mSize-8;j<mSize;j++)
			{
				double f_per_close=pTanAngleData->vec_close_value[j-1];
				double f_now_close=pTanAngleData->vec_close_value[j];
				double f_per=(f_now_close-f_per_close)*100.0/f_per_close;

				if(f_per>6.0)
				{
					bBigUp6=TRUE;
				}
				if(f_per>9.5)
				{
					bBigUp10=TRUE;
				}

				f_last_8_total_per+=f_per;

			}
			

			if(mNums>35 &&(mNowNums<(mNums/2)))
			{
				DropOffData *pDropOffData=new DropOffData();
				pDropOffData->strStockCode=pTanAngleData->strStockCode;
				pDropOffData->strStockName=pTanAngleData->strStockName;
				pDropOffData->fMaxMultiple=f_last_8_total_per;
				pDropOffData->fAveMultiple=f_last_16_total_per;
				if(bBigUp6)
					pDropOffData->strMaxDate="";
				else
				{
					if(!bBigUp6_16)
						pDropOffData->strMaxDate="Not BigUp6_16";
					else
						pDropOffData->strMaxDate="Not BigUp6";
				}

				if(bBigUp10)
					pDropOffData->strMinDate="";
				else
				{
					if(!bBigUp10_16)
						pDropOffData->strMinDate="Not BigUp10_16";
					else
						pDropOffData->strMinDate="Not BigUp10";
				}

				pDropOffData->mMaxValuePassDay=0;
				pDropOffData->fDownTotalRang=0.0;
				pDropOffData->mFilterNums=0;
				pDropOffData->mSpecNums=0;
				pDropOffData->strInfo="";
				vecDropOffData.push_back(pDropOffData);
			}
			
		}
	}
	SetTimer(DROPOFF_EVENT_REFRESH_DATA,300,0);
	return TRUE;
}





void CDlgDropOff::OnMenuAngleDetail()
{
	DropOffData *pDropOffData=NULL;
	for(uint16  i=0; i<mListCtrlItem.GetItemCount(); i++)
	{
		if( mListCtrlItem.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			pDropOffData=reinterpret_cast<DropOffData *>(mListCtrlItem.GetItemData(i));
			break;
		}
	}

	if(!pDropOffData)
		return;

	TanAngleData *pTanAngleData=NULL;
	BOOL bFound=FALSE;
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];
		if(pTanAngleData->strStockCode==pDropOffData->strStockCode)
		{
			bFound=TRUE;
			break;
		}
	}

	if(!bFound)
		return;

	CDlgAngleDetail dlg;
	dlg.SetTanAngleData(pTanAngleData);
	dlg.DoModal();

	/*CTime mDropOffTime;
	if(bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime=CTime::GetCurrentTime();
	}


	CGeneralAnalyze mGeneralAnalyze;

	CString strInfo=mGeneralAnalyze.doAnalyze(mDropOffTime,pTanAngleData->strStockCode);
	AfxMessageBox(strInfo);
	*/
#if 0
	CString strInfo = "";

	strInfo += pTanAngleData->strDateTime;
	strInfo += "   | ";
	strInfo += pTanAngleData->strStockCode;
	strInfo += "   | ";
	strInfo += pTanAngleData->strStockName;
	strInfo += "   | ";

	CString strTemp;
	strTemp.Format("%.2f  %.2f    | ", pTanAngleData->fPara2, pTanAngleData->fPara1);
	strInfo += strTemp;

	strTemp.Format("%.2f,up%.2f    | ", pTanAngleData->fPara0, pTanAngleData->fPara7);
	strInfo += strTemp;

	strTemp.Format("%.2f,%d  ave:%.2f  %.2f     | ", pTanAngleData->fPara4, pTanAngleData->mMaxDis, pTanAngleData->fPara5, pTanAngleData->fPara6);
	strInfo += strTemp;

	strTemp.Format("%d | %d | %d | ", (int)pTanAngleData->fPara3,pTanAngleData->mPara6, pTanAngleData->mPara7);
	strInfo += strTemp;

	//strTemp.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f", pTanAngleData->fPara8, pTanAngleData->mPara8, pTanAngleData->mPara9, pTanAngleData->mPara10, pTanAngleData->mContiDownNums, pTanAngleData->mContiVolDownNums, pTanAngleData->mStepIndex, pTanAngleData->mNowIsMaxPriceNums,
	//	pTanAngleData->mBigIncreaseNums, pTanAngleData->fNowGrow, pTanAngleData->mRsi1BigNums, pTanAngleData->fVolumePer);
	//strInfo += strTemp;


	strTemp.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", pTanAngleData->fPara8, pTanAngleData->mPara8, pTanAngleData->mPara9, pTanAngleData->mPara10, pTanAngleData->mContiDownNums, pTanAngleData->mContiVolDownNums, pTanAngleData->mStepIndex, pTanAngleData->mNowIsMaxPriceNums,
		pTanAngleData->mBigIncreaseNums, pTanAngleData->fNowGrow, pTanAngleData->mRsi1BigNums, pTanAngleData->fVolumePer,
		pTanAngleData->mVolM5ContiUpNums, pTanAngleData->mVolM10ContiUpNums, pTanAngleData->mPriceM5ContiUpNums, pTanAngleData->fcustomtotalvalue);
	strInfo += strTemp;


	

	if (OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char* buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, strInfo.GetLength() + 1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(strInfo));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT, clipbuffer);
		CloseClipboard();
	}

	AfxMessageBox(strInfo);
#endif
}







void CDlgDropOff::OnMenuNextGrowp()
{
	DropOffData* pDropOffData = NULL;
	for (uint16 i = 0; i < mListCtrlItem.GetItemCount(); i++)
	{
		if (mListCtrlItem.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			pDropOffData = reinterpret_cast<DropOffData*>(mListCtrlItem.GetItemData(i));
			break;
		}
	}

	if (!pDropOffData)
		return;


	CStockDayTable* pStockDayTable = NULL;
	CString strNowDate;

	pStockDayTable = StockDataMgr()->GetStockDayTable(pDropOffData->strStockCode);

	if (bUsePreDate)
	{
		CTime mDropOffTime;
		mDataTimeDropOff.GetTime(mDropOffTime);
		strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);
	}
	else
	{
		CTime mDropOffTime = CTime::GetCurrentTime();
		strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);
	}

	int mNowIndex = pStockDayTable->GetStockDayIndex(strNowDate);
	Vec_StockDayData vecStockDayData = pStockDayTable->GetStockDayDataList();

	int mCalNextDays = 5;
	int size = vecStockDayData.size();

	if ((size - mNowIndex) < (mCalNextDays + 1)) //4
		return;

	int mNextIndex = mNowIndex + mCalNextDays;  //3
	double f_now_close_price = vecStockDayData[mNowIndex]->GetEndPrice();

	double f_next_close_price = vecStockDayData[mNextIndex]->GetEndPrice();

	double f_per = (f_next_close_price - f_now_close_price) * 100.0 / f_now_close_price;

	strNowDate = vecStockDayData[mNextIndex]->GetDate();

	CString strInfo;
	if(f_per>=0.0)
		strInfo.Format("%d 交易日后 %s f_per=%f, 盈利 ,是否显示K线\n", mCalNextDays, pDropOffData->strStockCode, f_per);
	else
		strInfo.Format("%d 交易日后 %s f_per=%f, 亏本 ,是否显示K线\n", mCalNextDays, pDropOffData->strStockCode, f_per);

	int result = AfxMessageBox(strInfo, MB_YESNO);
	if (IDYES == result)
	{
		//return FALSE;
		CTime mDropOffTime;
		if (bUsePreDate)
		{
			mDataTimeDropOff.GetTime(mDropOffTime);
		}
		else
		{
			mDropOffTime = CTime::GetCurrentTime();
		}


		CString strStockCode = pDropOffData->strStockCode;

		CStockDayTable* pStockDayTable = NULL;
		pStockDayTable = StockDataMgr()->GetStockDayTable(strStockCode);

		//CString strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		CString strBeginDate = pStockDayTable->GetStockDayDatePreOfIndexReverse(strNowDate, 90);//90

		CDlgStockChart* pDlgStockChart;
		pDlgStockChart = new CDlgStockChart(this);
		pDlgStockChart->Create(IDD_DLG_STOCK_CHART);
		pDlgStockChart->SetStockDayTable(pStockDayTable);
		pDlgStockChart->SetBeginDate(strBeginDate);
		pDlgStockChart->SetEndDate(strNowDate);
		pDlgStockChart->Init();
		pDlgStockChart->ShowWindow(SW_SHOWNORMAL);
		pDlgStockChart->CenterWindow(this);


	}

	//AfxMessageBox(strInfo);

}


void CDlgDropOff::OnMenuNextGrowp3()
{
	DropOffData* pDropOffData = NULL;
	for (uint16 i = 0; i < mListCtrlItem.GetItemCount(); i++)
	{
		if (mListCtrlItem.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			pDropOffData = reinterpret_cast<DropOffData*>(mListCtrlItem.GetItemData(i));
			break;
		}
	}

	if (!pDropOffData)
		return;

	
	CStockDayTable* pStockDayTable = NULL;
	CString strNowDate;

	pStockDayTable = StockDataMgr()->GetStockDayTable(pDropOffData->strStockCode);

	if (bUsePreDate)
	{
		CTime mDropOffTime;
		mDataTimeDropOff.GetTime(mDropOffTime);
		strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);
	}
	else
	{
		CTime mDropOffTime = CTime::GetCurrentTime();
		strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);
	}

	int mNowIndex = pStockDayTable->GetStockDayIndex(strNowDate);
	Vec_StockDayData vecStockDayData = pStockDayTable->GetStockDayDataList();

	int mCalNextDays = 3;
	int size = vecStockDayData.size();

	if ((size - mNowIndex) < (mCalNextDays + 1)) //4
		return;

	int mNextIndex = mNowIndex + mCalNextDays;  //3
	double f_now_close_price = vecStockDayData[mNowIndex]->GetEndPrice();

	double f_next_close_price = vecStockDayData[mNextIndex]->GetEndPrice();

	double f_per = (f_next_close_price - f_now_close_price) * 100.0 / f_now_close_price;

	strNowDate = vecStockDayData[mNextIndex]->GetDate();

	CString strInfo;

	if(f_per>=0.0)
		strInfo.Format("%d 交易日后 %s f_per=%f, 盈利 ,是否显示K线\n", mCalNextDays, pDropOffData->strStockCode, f_per);
	else
		strInfo.Format("%d 交易日后 %s f_per=%f, 亏本 ,是否显示K线\n", mCalNextDays, pDropOffData->strStockCode, f_per);
	int result = AfxMessageBox(strInfo, MB_YESNO);
	if (IDYES == result)
	{
		//return FALSE;
		CTime mDropOffTime;
		if (bUsePreDate)
		{
			mDataTimeDropOff.GetTime(mDropOffTime);
		}
		else
		{
			mDropOffTime = CTime::GetCurrentTime();
		}


		CString strStockCode = pDropOffData->strStockCode;

		CStockDayTable* pStockDayTable = NULL;
		pStockDayTable = StockDataMgr()->GetStockDayTable(strStockCode);

		//CString strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		CString strBeginDate = pStockDayTable->GetStockDayDatePreOfIndexReverse(strNowDate, 90); //90

		CDlgStockChart* pDlgStockChart;
		pDlgStockChart = new CDlgStockChart(this);
		pDlgStockChart->Create(IDD_DLG_STOCK_CHART);
		pDlgStockChart->SetStockDayTable(pStockDayTable);
		pDlgStockChart->SetBeginDate(strBeginDate);
		pDlgStockChart->SetEndDate(strNowDate);
		pDlgStockChart->Init();
		pDlgStockChart->ShowWindow(SW_SHOWNORMAL);
		pDlgStockChart->CenterWindow(this);


	}

	
	//strInfo.Format("%d 交易日后 %s f_per=%f\n", mCalNextDays, pDropOffData->strStockCode, f_per);

	//AfxMessageBox(strInfo);
}


void CDlgDropOff::OnMenuNextGrowp8()
{
	DropOffData* pDropOffData = NULL;
	for (uint16 i = 0; i < mListCtrlItem.GetItemCount(); i++)
	{
		if (mListCtrlItem.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			pDropOffData = reinterpret_cast<DropOffData*>(mListCtrlItem.GetItemData(i));
			break;
		}
	}

	if (!pDropOffData)
		return;


	CStockDayTable* pStockDayTable = NULL;
	CString strNowDate;

	pStockDayTable = StockDataMgr()->GetStockDayTable(pDropOffData->strStockCode);

	if (bUsePreDate)
	{
		CTime mDropOffTime;
		mDataTimeDropOff.GetTime(mDropOffTime);
		strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);
	}
	else
	{
		CTime mDropOffTime = CTime::GetCurrentTime();
		strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);
	}

	int mNowIndex = pStockDayTable->GetStockDayIndex(strNowDate);
	Vec_StockDayData vecStockDayData = pStockDayTable->GetStockDayDataList();

	int mCalNextDays = 8;
	int size = vecStockDayData.size();

	if ((size - mNowIndex) < (mCalNextDays + 1)) //4
		return;

	int mNextIndex = mNowIndex + mCalNextDays;  //3
	double f_now_close_price = vecStockDayData[mNowIndex]->GetEndPrice();

	double f_next_close_price = vecStockDayData[mNextIndex]->GetEndPrice();

	double f_per = (f_next_close_price - f_now_close_price) * 100.0 / f_now_close_price;

	CString strInfo;
	if(f_per>=0.0)
		strInfo.Format("%d 交易日后 %s f_per=%f 盈利\n", mCalNextDays, pDropOffData->strStockCode, f_per);
	else
		strInfo.Format("%d 交易日后 %s f_per=%f 亏本\n", mCalNextDays, pDropOffData->strStockCode, f_per);

	AfxMessageBox(strInfo);
}


void CDlgDropOff::OnMenuShellWeb()
{
	// TODO: 在此添加命令处理程序代码

	DropOffData* pDropOffData = NULL;
	for (uint16 i = 0; i < mListCtrlItem.GetItemCount(); i++)
	{
		if (mListCtrlItem.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			pDropOffData = reinterpret_cast<DropOffData*>(mListCtrlItem.GetItemData(i));
			break;
		}
	}

	if (!pDropOffData)
		return;

	CString strTemp = pDropOffData->strStockCode.Mid(2);
	CString strInfo = "ab-";
	strInfo += strTemp;

	CString strWebUrl;
	strWebUrl.Format("https://gushitong.baidu.com/stock/%s", strInfo);
	ShellExecute(NULL, "open", strWebUrl, NULL, NULL, SW_SHOWNORMAL);

}



//个股K线分析

void CDlgDropOff::OnMenuKLineAnalyze()
{
	DropOffData* pDropOffData = NULL;
	for (uint16 i = 0; i < mListCtrlItem.GetItemCount(); i++)
	{
		if (mListCtrlItem.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			pDropOffData = reinterpret_cast<DropOffData*>(mListCtrlItem.GetItemData(i));
			break;
		}
	}

	if (!pDropOffData)
		return;


#if 0
	CTime mDropOffTime;
	if (bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime = CTime::GetCurrentTime();
	}


	CString strStockCode = pDropOffData->strStockCode;
	CString strStockName = pDropOffData->strStockName;

	CKLineFilterAlg  mKLineFilterAlg;

	Vec_KLineFilterData2 vecKLineFilterData2 = mKLineFilterAlg.doFilter2(strStockCode, strStockName, mDropOffTime);

	mKLineFilterAlg.AnalyzeSingleKLineTrend(vecKLineFilterData2);
#endif

	CTime mDropOffTime;
	if (bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime = CTime::GetCurrentTime();
	}


	CString strStockCode = pDropOffData->strStockCode;

	CStockDayTable* pStockDayTable=NULL;
	pStockDayTable= StockDataMgr()->GetStockDayTable(strStockCode);

	CString strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);
	CString strBeginDate = pStockDayTable->GetStockDayDatePreOfIndexReverse(strNowDate, 90); //90

	CDlgStockChart* pDlgStockChart;
	pDlgStockChart = new CDlgStockChart(this);
	pDlgStockChart->Create(IDD_DLG_STOCK_CHART);
	pDlgStockChart->SetStockDayTable(pStockDayTable);
	pDlgStockChart->SetBeginDate(strBeginDate);
	pDlgStockChart->SetEndDate(strNowDate);
	pDlgStockChart->Init();
	pDlgStockChart->ShowWindow(SW_SHOWNORMAL);
	pDlgStockChart->CenterWindow(this);
	
}


//行业信息统计


typedef struct
{
	std::string  strIndustryName;
	int mAccordNums;
	int mTotalNums;
	float f_per;
	std::string  strTotalInfo;
}IndustryDataStat;
typedef	std::vector<IndustryDataStat* > Vec_IndustryDataStatList;

bool sortIndustyInfo(const IndustryDataStat* pData1, const IndustryDataStat* pData2)
{
	return pData1->f_per > pData2->f_per;//降序排列  
}

typedef struct
{
	std::string strIndusty;
	int mNums;
	float f_per;
}IndustyStatResult;
BOOL CDlgDropOff::DoIndustyInfoStat(void)
{
	std::map<std::string, int > industyMapNum;
	std::map<std::string, int > industyMapAllNum;

	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		TanAngleData* pTanAngleData = vecTanAngleData[i];
		double f_ma5_angle = pTanAngleData->fPara0;
		double f_ma10_angle = pTanAngleData->fPara1;
		double f_ma20_angle = pTanAngleData->fPara2;
		double f_ma60_angle = pTanAngleData->fPara3;
		double f_max_volume_per = pTanAngleData->fPara4;
		double f_ave_volume_per = pTanAngleData->fPara5;
		double f_60_20_cross_price_increase = pTanAngleData->fPara6;
		double f_20_10_cross_price_increase = pTanAngleData->fPara7;
		double f_60_day_increase = pTanAngleData->fPara8;

		double f_up_per = f_60_20_cross_price_increase;
		if (f_60_20_cross_price_increase < f_20_10_cross_price_increase)
			f_up_per = f_20_10_cross_price_increase;

		if (f_up_per < 10.0)
		{
			std::string strCode = (LPCSTR)pTanAngleData->strStockCode;
			std::vector<std::string> vecIndusty = IndustryDataMgr()->FindIndustryByStockCode(strCode);
			if (vecIndusty.size() > 0)
			{
				industyMapNum[vecIndusty[0]]++;
			}
		}

		{
			std::string strCode = (LPCSTR)pTanAngleData->strStockCode;
			std::vector<std::string> vecIndusty = IndustryDataMgr()->FindIndustryByStockCode(strCode);
			if (vecIndusty.size() > 0)
			{
				industyMapAllNum[vecIndusty[0]]++;
			}
		}
		
	}

	std::vector<IndustyStatResult*> vecIndustyStatAllResult;
	std::map<std::string, int >::iterator iternum;
	iternum = industyMapAllNum.begin();
	while (iternum != industyMapAllNum.end())
	{
		int nums = iternum->second;

		int mStockNums = IndustryDataMgr()->GetIndustryStockNums(iternum->first);
		double  f_per = (double)nums * 100.0 / (double)mStockNums;

		

		IndustyStatResult* pIndustyStatResult = new IndustyStatResult();
		pIndustyStatResult->strIndusty = iternum->first;
		pIndustyStatResult->mNums = nums;
		pIndustyStatResult->f_per = f_per;
		vecIndustyStatAllResult.push_back(pIndustyStatResult);

		iternum++;
	}


	std::vector<IndustyStatResult*> vecIndustyStatResult;

	
	printf("----------------涨幅10%以内--------------------------\n");
	iternum = industyMapNum.begin();
	while (iternum != industyMapNum.end())
	{
		int nums = iternum->second;
		
		int mStockNums = IndustryDataMgr()->GetIndustryStockNums(iternum->first);
		double  f_per = (double)nums * 100.0 / (double)mStockNums;

		printf("%s  %d  占比%.2f\n", iternum->first.c_str(),nums, f_per);
		
		IndustyStatResult* pIndustyStatResult = new IndustyStatResult();
		pIndustyStatResult->strIndusty = iternum->first;
		pIndustyStatResult->mNums = nums;
		pIndustyStatResult->f_per = f_per;
		vecIndustyStatResult.push_back(pIndustyStatResult);

		iternum++;
	}
	printf("-----------------------------------------------\n");

	std::map<std::string,std::vector<std::string> > industyMap;


	for (int i = 0; i < vecDropOffData.size(); i++)
	{
		CString strStockCode = vecDropOffData[i]->strStockCode;
		CString strStockName = vecDropOffData[i]->strStockName;

		std::vector<std::string> vecIndusty = IndustryDataMgr()->FindIndustryByStockCode((LPCSTR)strStockCode);
		for (int j = 0; j < vecIndusty.size(); j++)
		{
			std::string strTemp = (LPCSTR)strStockCode;
			strTemp += " ";
			strTemp += (LPCSTR)strStockName;
			industyMap[vecIndusty[j]].push_back(strTemp);
		}
	}

	Vec_IndustryDataStatList vecIndustryDataStatList;
	IndustryDataStat* pIndustryDataStat = NULL;
	std::map<std::string, std::vector<std::string> >::iterator iter;
	
	iter = industyMap.begin();
	while (iter != industyMap.end()) 
	{
		std::string strInfo;
		for (int n = 0; n < iter->second.size(); n++)
		{
			strInfo += iter->second[n];
			strInfo += "  ";
		}
		int mStockNums = IndustryDataMgr()->GetIndustryStockNums(iter->first);
		double  f_per = (double)iter->second.size()*100.0 / (double)mStockNums;
		pIndustryDataStat = new IndustryDataStat();
		pIndustryDataStat->strIndustryName = iter->first.c_str();
		pIndustryDataStat->mAccordNums = iter->second.size();
		pIndustryDataStat->strTotalInfo = strInfo;
		pIndustryDataStat->mTotalNums = mStockNums;
		pIndustryDataStat->f_per = f_per;
		vecIndustryDataStatList.push_back(pIndustryDataStat);
		//printf("行业 %s 有 %d 个  %s ,行业共有%d只股占比%.2f \n", iter->first.c_str(), iter->second.size(),strInfo.c_str(), mStockNums, f_per);
		iter++;
	}

	std::sort(vecIndustryDataStatList.begin(), vecIndustryDataStatList.end(), sortIndustyInfo);

	for (int i = 0; i < vecIndustryDataStatList.size(); i++)
	{
		double f_per_10 = -1.0;
		double f_per_all = -1.0;
		pIndustryDataStat = vecIndustryDataStatList[i];
		for (int j = 0; j < vecIndustyStatResult.size(); j++)
		{
			if (vecIndustyStatResult[j]->strIndusty == pIndustryDataStat->strIndustryName)
			{
				f_per_10 = vecIndustyStatResult[j]->f_per;
				break;
			}
		}

		for (int j = 0; j < vecIndustyStatAllResult.size(); j++)
		{
			if (vecIndustyStatAllResult[j]->strIndusty == pIndustryDataStat->strIndustryName)
			{
				f_per_all = vecIndustyStatAllResult[j]->f_per;
			}
		}

	//	printf("f_per=%f  f_per_10=%f\n", pIndustryDataStat->f_per, f_per_10);
		double f_cmp_bs = pIndustryDataStat->f_per / f_per_10;
		if (f_per_10 < -0.5)
			f_cmp_bs = 0.0;
		double f_cmp_all= pIndustryDataStat->f_per / f_per_all;
		if (f_per_all < -0.5)
			f_cmp_all = 0.0;
		printf("行业 %s 有 %d 个  %s ,行业共有%d只股占比%.2f  十比率%.2f  \n", pIndustryDataStat->strIndustryName.c_str(), pIndustryDataStat->mAccordNums,
			pIndustryDataStat->strTotalInfo.c_str(), pIndustryDataStat->mTotalNums, pIndustryDataStat->f_per, f_cmp_bs);
		printf("----------------------------------------------\n");
	}
	for (int j = 0; j < vecIndustyStatResult.size(); j++)
	{
		delete vecIndustyStatResult[j];
		vecIndustyStatResult[j] = NULL;
	}
	vecIndustyStatResult.clear();

	for (int j = 0; j < vecIndustyStatAllResult.size(); j++)
	{
		delete vecIndustyStatAllResult[j];
		vecIndustyStatAllResult[j] = NULL;
	}
	vecIndustyStatAllResult.clear();
	
	CTime mDropOffTime;
	if (bUsePreDate)
	{
		mDataTimeDropOff.GetTime(mDropOffTime);
	}
	else
	{
		mDropOffTime = CTime::GetCurrentTime();
	}

	CDlgIndustryInfo dlgIndustryInfo;
	dlgIndustryInfo.SetStockDateTime(mDropOffTime);
	dlgIndustryInfo.DoModal();

	return TRUE;
}

//行业选择
BOOL  CDlgDropOff::DoFilterIndustyInfo(IndustryData* pIndustryData)
{

	if (!pIndustryData)
		return FALSE;
	
	
	
	vecDropOffData.clear();
	DropOffData* pDropOffData = NULL;

	TanAngleData* pTanAngleData = NULL;

	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		pTanAngleData = vecTanAngleData[i];
		double f_ma5_angle = pTanAngleData->fPara0;
		double f_ma10_angle = pTanAngleData->fPara1;
		double f_ma20_angle = pTanAngleData->fPara2;
		double f_ma60_angle = pTanAngleData->fPara3;
		double f_max_volume_per = pTanAngleData->fPara4;
		double f_ave_volume_per = pTanAngleData->fPara5;
		double f_60_20_cross_price_increase = pTanAngleData->fPara6;
		double f_20_10_cross_price_increase = pTanAngleData->fPara7;
		double f_60_day_increase = pTanAngleData->fPara8;
		double fNowGrow = pTanAngleData->fNowGrow;
		double fNowMaxGrow = pTanAngleData->fNowMaxGrow;
		int mNowIsMaxPriceNums = pTanAngleData->mNowIsMaxPriceNums;

		int  mMaxDis = pTanAngleData->mMaxDis;

		int m_10_big_20_nums = pTanAngleData->mPara6;
		int m_60_big_20_nums = pTanAngleData->mPara7;

		int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
		int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
		int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
		int m_max_volume_distance = pTanAngleData->mMaxDis;
		int mContiDownNums = pTanAngleData->mContiDownNums;
		int mBigIncreaseNums = pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums = pTanAngleData->mRsi1BigNums;
		int mNextGrow = pTanAngleData->mNextGrow;
		double f_cur_rsi_1 = pTanAngleData->fRsi1;
		int mContiVolDownNums = pTanAngleData->mContiVolDownNums;
		int mStepIndex = pTanAngleData->mStepIndex;

		int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
		int mVolM5ContiUpNums = pTanAngleData->mVolM5ContiUpNums;
		int mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;

		std::string strCodeName = (LPCSTR)pTanAngleData->strStockCode;

		bool bFound = false;
		for (int j = 0; j < pIndustryData->vecIndustryCfg.size(); j++)
		{
			if (pIndustryData->vecIndustryCfg[j] == strCodeName)
			{

				DropOffData* pDropOffData = new DropOffData();
				pDropOffData->strStockCode = vecTanAngleData[i]->strStockCode;
				pDropOffData->strStockName = vecTanAngleData[i]->strStockName;
				pDropOffData->fMaxMultiple = vecTanAngleData[i]->fPara2;
				pDropOffData->fAveMultiple = vecTanAngleData[i]->fPara1;
				CString strInfo;
				strInfo.Format("%.2f,up%.2f", vecTanAngleData[i]->fPara0, vecTanAngleData[i]->fPara7);
				pDropOffData->strMaxDate = strInfo;
				strInfo.Format("%.2f,%d  ave:%.2f  %.2f", vecTanAngleData[i]->fPara4, vecTanAngleData[i]->mMaxDis, vecTanAngleData[i]->fPara5, vecTanAngleData[i]->fPara6);
				pDropOffData->strMinDate = strInfo;
				pDropOffData->mMaxValuePassDay = vecTanAngleData[i]->fPara3;
				pDropOffData->fDownTotalRang = 0.0;
				pDropOffData->mFilterNums = vecTanAngleData[i]->mPara6;
				pDropOffData->mSpecNums = vecTanAngleData[i]->mPara7;
				strInfo.Format("%.2f,%d,%d,%d#p%d#v%d#c%d#%d#%d#%.2f#rb%d#%.2f#vw%d#vs%d#pw%d#%.2f", vecTanAngleData[i]->fPara8, vecTanAngleData[i]->mPara8, vecTanAngleData[i]->mPara9, vecTanAngleData[i]->mPara10, vecTanAngleData[i]->mContiDownNums, vecTanAngleData[i]->mContiVolDownNums, vecTanAngleData[i]->mStepIndex, vecTanAngleData[i]->mNowIsMaxPriceNums,
					vecTanAngleData[i]->mBigIncreaseNums, vecTanAngleData[i]->fNowGrow, vecTanAngleData[i]->mRsi1BigNums, vecTanAngleData[i]->fVolumePer,
					vecTanAngleData[i]->mVolM5ContiUpNums, vecTanAngleData[i]->mVolM10ContiUpNums, vecTanAngleData[i]->mPriceM5ContiUpNums, vecTanAngleData[i]->fcustomtotalvalue);
				pDropOffData->strInfo = strInfo;
				vecDropOffData.push_back(pDropOffData);
			}
		}

		

	}
	

	SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);

	return TRUE;
}


//行业选择
BOOL  CDlgDropOff::DoReverseFilterIndustyInfo(IndustryData* pIndustryData)
{
	if (!pIndustryData)
		return FALSE;
	vecDropOffData.clear();
	Vec_StockCodeList vecStockCodeList = StockDataMgr()->GetStockCodeList();
	StockCode* pStockCode = NULL;
	for (int i = 0; i < vecStockCodeList.size(); i++)
	{
		pStockCode = vecStockCodeList[i];
		std::string strCodeName = (LPCSTR)pStockCode->strStockCode;
		for (int j = 0; j < vecTanAngleData.size(); j++)
		{
			std::string strCodeName2 = (LPCSTR)vecTanAngleData[j]->strStockCode;
			if (strCodeName == strCodeName2)
				continue;
		}
		bool bFound = false;
		for (int j = 0; j < pIndustryData->vecIndustryCfg.size(); j++)
		{
			if (pIndustryData->vecIndustryCfg[j] == strCodeName)
			{
				DropOffData* pDropOffData = new DropOffData();
				pDropOffData->strStockCode = pStockCode->strStockCode;
				pDropOffData->strStockName = pStockCode->strStockName;
				pDropOffData->fMaxMultiple = 0;
				pDropOffData->fAveMultiple = 0;
				pDropOffData->strMaxDate = "";
				pDropOffData->strMinDate = "";
				pDropOffData->mMaxValuePassDay = 0;
				pDropOffData->fDownTotalRang = 0.0;
				pDropOffData->mFilterNums = 0;
				pDropOffData->mSpecNums = 0;
				pDropOffData->strInfo = "";
				vecDropOffData.push_back(pDropOffData);
			}
		}

	}
	SetTimer(DROPOFF_EVENT_REFRESH_DATA, 300, 0);
	return TRUE;

}

//回测
void CDlgDropOff::OnBnClickedBtnBackFlow()
{
	CDlgBackFlow dlg;
	dlg.DoModal();
}


BOOL CDlgDropOff::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)//屏蔽ESC和ENTER键
			return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CDlgDropOff::OnEraseBkgnd(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);
	pDC->FillSolidRect(rectClient, RGB(240, 240, 240));

	return TRUE;

	//return CDialogEx::OnEraseBkgnd(pDC);
}
