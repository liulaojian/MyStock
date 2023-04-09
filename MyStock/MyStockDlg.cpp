
// MyStockDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "MyStockDlg.h"
#include "afxdialogex.h"
#include "EnvDataMgr.h"
#include "DlgStockDateSel.h"
#include "Convert.h"

//#include "HistoryStrategy.h"
#include "CurveSinCmpMethod.h"
#include "DlgCurveSinCmp.h"

#include "DlgHistoryCmpResult.h"

#include "DlgLoopBackSetting.h"
#include "StrategyMgr.h"

#include "DlgCurveSinCmp2.h"

#include "HistoryLoopBack.h"
#include "CurveSinCmpLoopBack.h"
#include "LoopBackMgr.h"

#include "SystemMgr.h"
#include "DlgStockPriceFilter.h"
#include "zbTypeDef.h"
#include "StockPriceFilter.h"

#include "DlgPowerArithResult.h"
#include "DlgSetting.h"

#include "DlgUpdateStockData.h"


#include "StockDataInfoDb.h"

#include  "StockCCIArithmetic.h"
#include "StockRSIArithmetic.h"
#include "StockMACDArithmetic.h"
#include "StockOBVArithmetic.h"
#include "StockSARArithmetic.h"
#include "StockASIArithmetic.h"
#include "StockKDJArithmetic.h"
#include "StockBOLLArithmetic.h"
#include "StockProfitLossArithmetic.h"
#include "StockWRArithmetic.h"
#include "DlgFindStockDestribute.h"
#include "DlgDropOff.h"

#include "IndustryDataMgr.h"
#include "ConceptDataMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyStockDlg 对话框




CMyStockDlg::CMyStockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyStockDlg::IDD, pParent),pDlgStockChart(NULL),pDlgLoopBackLog(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyStockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STOCK, mStockListCtrl);
}

BEGIN_MESSAGE_MAP(CMyStockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyStockDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_TEST, &CMyStockDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_LOOPBACK, &CMyStockDlg::OnBnClickedBtnLoopback)
	ON_BN_CLICKED(IDC_BTN_MONITOR2, &CMyStockDlg::OnBnClickedBtnMonitor)
	ON_BN_CLICKED(IDC_BTN_POWER_ARITH, &CMyStockDlg::OnBnClickedBtnPowerArith)
	ON_BN_CLICKED(IDC_BTN_SETTING, &CMyStockDlg::OnBnClickedBtnSetting)
	ON_BN_CLICKED(IDC_BTN_UPDATEDATA, &CMyStockDlg::OnBnClickedBtnUpdatedata)
	ON_BN_CLICKED(IDC_BTN_MONITOR_LOOPBACK, &CMyStockDlg::OnBnClickedBtnMonitorLoopback)
	ON_BN_CLICKED(IDC_BTN_STATIC_ANALYSIS, &CMyStockDlg::OnBnClickedBtnStaticAnalysis)
	ON_BN_CLICKED(IDC_BTN_STOCK_METHOD, &CMyStockDlg::OnBnClickedBtnStockMethod)
END_MESSAGE_MAP()


// CMyStockDlg 消息处理程序

BOOL CMyStockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


#ifndef _DEBUG
	GetDlgItem(IDC_BTN_TEST)->ShowWindow(SW_HIDE);
#endif

	mStockListCtrl.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT ); //设置报表风格



	mStockListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 

	mStockListCtrl.InsertColumn( COLUMN_ID, "顺序ID号", LVCFMT_LEFT, 80 );
	
	mStockListCtrl.InsertColumn( COLUMN_STOCK_CODE, "股票代码", LVCFMT_LEFT, 115 );

	mStockListCtrl.InsertColumn( COLUMN_STOCK_NAME, "股票名称", LVCFMT_LEFT, 115 );

	mStockListCtrl.InsertColumn( COLUMN_STOCK_DAY_BEGIN, "日数据开始", LVCFMT_LEFT, 140 );
	mStockListCtrl.InsertColumn( COLUMN_STOCK_DAY_END, "日数据结束", LVCFMT_LEFT, 140 );

	mStockListCtrl.InsertColumn( COLUMN_STOCK_MIN_BEGIN, "分数据开始", LVCFMT_LEFT, 140);
	mStockListCtrl.InsertColumn( COLUMN_STOCK_MIN_END, "分数据结束", LVCFMT_LEFT, 140 );

	SystemMgr()->DoGetMyStockXmlFile();
	SystemMgr()->DoGetTitle();

	CString strTitle=SystemMgr()->GetTitle();
	SetWindowText(strTitle);

	//CString strXmlInfo=SystemMgr()->BuildStockXmlInfo();
	//SystemMgr()->SaveStockXmlInfo(strXmlInfo);

	

	StockDataMgr()->Init();
	EnvDataMgr()->Init();
	StrategyMgr()->Init();
	
	IndustryDataMgr()->Init();
	ConceptDataMgr()->Init();

	//StockDataInfoDb()->CreateTable();
	

	vecStockCodeList=StockDataMgr()->GetStockCodeList();

	SetTimer(TIMER_EVENT_REFRESH_DATA,200,0);

	pDlgStockChart=new CDlgStockChart(this);
	pDlgStockChart->Create(IDD_DLG_STOCK_CHART);

	pDlgStockMonitor=new DlgStockMonitor(this);
	pDlgStockMonitor->Create(IDD_DLG_MONITOR);

	//pDlgPowerArithResult=new CDlgPowerArithResult(this);
	//pDlgPowerArithResult->Create(IDD_DLG_POWER_ARITH_RESULT);

	pDlgStockMonitorKDJ=new CDlgStockMonitorKDJ(this);
	pDlgStockMonitorKDJ->Create(IDD_DLG_MONITOR_KDJ);

	pDlgSniperLoopBack=new CDlgSniperLoopBack(this);
	pDlgSniperLoopBack->Create(IDD_DLG_SNIPER_LOOPBACK);

	//CStockCCIArithmetic::CalcCCIData("SH600036","2018/02/23 1500",125,K_LINE_60MIN,14);

	//CStockRSIArithmetic::CalcRSIData("SH000001","2018/02/23",125,K_LINE_DAY,6,12,24);
	//CStockMACDArithmetic::CalcMACDData("SH000001","2018/02/23",125,K_LINE_DAY,12,26,9);
	//CStockOBVArithmetic::CalcOBVData("SH600016","2018/02/23",125,K_LINE_DAY,30);
	//CStockSARArithmetic::CalcSARData("SH600016","2018/02/23",128,K_LINE_DAY,4);
	//CStockASIArithmetic::CalcASIData("SH000001","2018/02/23",125,K_LINE_DAY,6);
	//CStockKDJArithmetic::CalcKDJData("SH000001","2018/02/28",125,K_LINE_DAY,9,3,3);
	//CStockBOLLArithmetic::CalcBOLLData("SH600016","2018/02/28",125,K_LINE_DAY,20);
	//CStockProfitLossArithmetic::CalcProfitLossData("SZ000858","2018/03/20",240,50);

	/*
	CStockKDJData* pStockKDJData=NULL;
	pStockKDJData=CStockKDJArithmetic::CalcKDJData("SH603993","2018/03/09 1400",250,K_LINE_60MIN,9,3,3);

	
	double f_10_power,f_20_power,f_40_power,f_60_power,f_120_power,f_240_power;
	if(pStockKDJData)
	{
		
		CKLineDataBean::CalcPowerValue(pStockKDJData->vec_close_price,pStockKDJData->vec_volume_price,10,f_10_power);
		CKLineDataBean::CalcPowerValue(pStockKDJData->vec_close_price,pStockKDJData->vec_volume_price,20,f_20_power);
		CKLineDataBean::CalcPowerValue(pStockKDJData->vec_close_price,pStockKDJData->vec_volume_price,40,f_40_power);
		CKLineDataBean::CalcPowerValue(pStockKDJData->vec_close_price,pStockKDJData->vec_volume_price,60,f_60_power);
		CKLineDataBean::CalcPowerValue(pStockKDJData->vec_close_price,pStockKDJData->vec_volume_price,120,f_120_power);
		CKLineDataBean::CalcPowerValue(pStockKDJData->vec_close_price,pStockKDJData->vec_volume_price,240,f_240_power);
	}


	CStockKDJData* pStockKDJData2=NULL;
	pStockKDJData2=CStockKDJArithmetic::CalcKDJData("SH603993","2018/02/28 1030",250,K_LINE_60MIN,9,3,3);
	double f_10_power_2,f_20_power_2,f_40_power_2,f_60_power_2,f_120_power_2,f_240_power_2;
	if(pStockKDJData2)
	{
		CKLineDataBean::CalcPowerValue(pStockKDJData2->vec_close_price,pStockKDJData2->vec_volume_price,10,f_10_power_2);
		CKLineDataBean::CalcPowerValue(pStockKDJData2->vec_close_price,pStockKDJData2->vec_volume_price,20,f_20_power_2);
		CKLineDataBean::CalcPowerValue(pStockKDJData2->vec_close_price,pStockKDJData2->vec_volume_price,40,f_40_power_2);
		CKLineDataBean::CalcPowerValue(pStockKDJData2->vec_close_price,pStockKDJData2->vec_volume_price,60,f_60_power_2);
		CKLineDataBean::CalcPowerValue(pStockKDJData2->vec_close_price,pStockKDJData2->vec_volume_price,120,f_120_power_2);
		CKLineDataBean::CalcPowerValue(pStockKDJData2->vec_close_price,pStockKDJData2->vec_volume_price,240,f_240_power_2);
	}*/

	/*
	CStocWRData* pStocWRData=NULL;
	pStocWRData=CStockWRArithmetic::CalcWRData("SZ002052","2018/04/27",250,K_LINE_DAY,10,6);*/


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyStockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyStockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyStockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CMyStockDlg::RefreshData(void)
{
	CString strConv,strTemp;
	int nRow;

	CString strDayBeginDate="";
	CString strDayEndDate="";

	CString strMinBeginDate="";
	CString strMinEndDate="";

	int i=0;
	for(i=0;i<vecStockCodeList.size();i++)
	{
		strConv.Format("%4d",i+1);
		nRow=i;
		if(nRow>=mStockListCtrl.GetItemCount())
			mStockListCtrl.InsertItem(i,strConv);
		else
			mStockListCtrl.SetItemText(nRow, COLUMN_ID,strConv);
		mStockListCtrl.SetItemText(nRow, COLUMN_STOCK_CODE,vecStockCodeList[i]->strStockCode);
		mStockListCtrl.SetItemText(nRow, COLUMN_STOCK_NAME,vecStockCodeList[i]->strStockName);

		strDayBeginDate=StockDataMgr()->GetStockDayBeginDate(vecStockCodeList[i]->strStockCode);
		strDayEndDate=StockDataMgr()->GetStockDayEndDate(vecStockCodeList[i]->strStockCode);
		mStockListCtrl.SetItemText(nRow, COLUMN_STOCK_DAY_BEGIN,strDayBeginDate);
		mStockListCtrl.SetItemText(nRow, COLUMN_STOCK_DAY_END,strDayEndDate);

		strMinBeginDate=StockDataMgr()->GetStockMin5BeginDateTime(vecStockCodeList[i]->strStockCode);
		strMinEndDate=StockDataMgr()->GetStockMin5EndDateTime(vecStockCodeList[i]->strStockCode);
		mStockListCtrl.SetItemText(nRow, COLUMN_STOCK_MIN_BEGIN,strMinBeginDate);
		mStockListCtrl.SetItemText(nRow, COLUMN_STOCK_MIN_END,strMinEndDate);

		

		mStockListCtrl.SetItemData(nRow,reinterpret_cast<DWORD_PTR>(vecStockCodeList[i]));
	}
	return true;
}

void CMyStockDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==TIMER_EVENT_REFRESH_DATA)
	{

		RefreshData();
		KillTimer(TIMER_EVENT_REFRESH_DATA);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMyStockDlg::OnBnClickedButton1()
{
	int mSel=mStockListCtrl.GetNextItem(-1,LVIS_SELECTED); 
	
	if(mSel==-1)
	{
		AfxMessageBox("选择个股票!");
		return;
	}
	StockCode *pStockCode;

	pStockCode=reinterpret_cast<StockCode *>(mStockListCtrl.GetItemData(mSel));
	CStockDayTable *pStockDayTable=NULL;
	if(pStockCode)
		pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);

	if(pStockDayTable)
	{
		CDlgStockDateSel dlg;
		CTime mBeginDateTime,mEndDateTime;

		mBeginDateTime=ConverStringToCTime(pStockDayTable->GetStockDayDateReverseIndex(15));
		mEndDateTime=ConverStringToCTime(pStockDayTable->GetStockEndDate());

		dlg.SetBeginTime(mBeginDateTime);
		dlg.SetEndTime(mEndDateTime);
		if(dlg.DoModal()==IDOK)
		{
			mBeginDateTime=dlg.GetBeginTime();
			mEndDateTime=dlg.GetEndTime();

			

			CString strBeginDateTime=pStockDayTable->GetNearestStockDayDate(mBeginDateTime);
			CString strEndDateTime=pStockDayTable->GetNearestStockDayDate(mEndDateTime);

			mBeginDateTime=ConverStringToCTime(strBeginDateTime);
			mEndDateTime=ConverStringToCTime(strEndDateTime);

			CTimeSpan span=mEndDateTime-mBeginDateTime;

			int iDay=span.GetDays();

			if(iDay>90)
			{
				AfxMessageBox("历史分析法不支持大于90天的跨度");
				return;
			}
			/*CHistoryStrategy *pHistoryStrategy=NULL;
			pHistoryStrategy=new CHistoryStrategy();
			pHistoryStrategy->SetStockDayTable(pStockDayTable);
			pHistoryStrategy->SetBeginDayDate(strBeginDateTime);
			pHistoryStrategy->SetEndDayDate(strEndDateTime);
			pHistoryStrategy->Init();
			pHistoryStrategy->TraverseStockDayData();*/
			

			CDlgCurveSinCmp *pDlgCurveSinCmp=NULL;
			pDlgCurveSinCmp=new CDlgCurveSinCmp();
			pDlgCurveSinCmp->SetStockDayTable(pStockDayTable);
			pDlgCurveSinCmp->SetBeginDayDate(strBeginDateTime);
			pDlgCurveSinCmp->SetEndDayDate(strEndDateTime);
			if(pDlgCurveSinCmp->DoModal()!=IDOK)
				return;

			CCurveSinCmpMethod *pCurveSinCmpMethod=NULL;
			pCurveSinCmpMethod=new CCurveSinCmpMethod();
			pCurveSinCmpMethod->SetDlgCmpMethod(pDlgCurveSinCmp);
			pCurveSinCmpMethod->SetCmpMethodParas(pDlgCurveSinCmp->GetCmpMethodParas());
			pCurveSinCmpMethod->SetStockDayTable(pStockDayTable);
			pCurveSinCmpMethod->SetBeginDate(strBeginDateTime);
			pCurveSinCmpMethod->SetEndDate(strEndDateTime);
			if(pCurveSinCmpMethod->Init())
			{
				GetDlgItem(IDC_STATIC_LABEL)->SetWindowText("正在预测计算中，请耐心等待...");
				if(pCurveSinCmpMethod->TraverseData())
				{
					GetDlgItem(IDC_STATIC_LABEL)->SetWindowText("股票");
					Vec_HistoryResultList vecHistoryResultList;
					vecHistoryResultList=pCurveSinCmpMethod->GetHistoryResultList();
					CString strTitle;
					strTitle.Format("开始日期 %s  结束日期 %s 历史预测法结果",strBeginDateTime,strEndDateTime);
					CDlgHistoryCmpResult dlg;
					dlg.SetTitle(strTitle);
					dlg.SetStockDayTable(pStockDayTable);
					dlg.SetHistoryResultList(vecHistoryResultList);
					dlg.DoModal();

				}
				GetDlgItem(IDC_STATIC_LABEL)->SetWindowText("股票");
			}
			


			/*if(pDlgStockChart)
			{
				pDlgStockChart->SetStockDayTable(pStockDayTable);
				pDlgStockChart->ShowWindow(SW_SHOWNORMAL);
				pDlgStockChart->CenterWindow(this);
			}*/
		}

		
	}
	
}

//测试
void CMyStockDlg::OnBnClickedBtnTest()
{
	/*CDlgStockChart *pDlgStockChart;
	CStockDayTable *pStockDayTable=NULL;
	pStockDayTable=StockDataMgr()->GetStockDayTable("SH000001");
	pDlgStockChart=new CDlgStockChart(this);
	pDlgStockChart->Create(IDD_DLG_STOCK_CHART);
	pDlgStockChart->SetStockDayTable(pStockDayTable);
	pDlgStockChart->SetBeginDate("2017/11/14");
	pDlgStockChart->SetEndDate("2017/12/05");
	pDlgStockChart->Init();
	pDlgStockChart->ShowWindow(SW_SHOWNORMAL);
	pDlgStockChart->CenterWindow(this);*/
	CString strXmlInfo=SystemMgr()->BuildStockXmlInfo();
	SystemMgr()->SaveStockXmlInfo(strXmlInfo);
	AfxMessageBox("Over");
}



//历史回测
void CMyStockDlg::OnBnClickedBtnLoopback()
{
	int mSel=mStockListCtrl.GetNextItem(-1,LVIS_SELECTED); 

	if(mSel==-1)
	{
		AfxMessageBox("选择个股票!");
		return;
	}
	StockCode *pStockCode;

	pStockCode=reinterpret_cast<StockCode *>(mStockListCtrl.GetItemData(mSel));
	CStockDayTable *pStockDayTable=NULL;
	if(pStockCode)
	{
		if(pStockCode->strStockCode=="SH000001" || pStockCode->strStockCode=="SH000016" || pStockCode->strStockCode=="SH000300")
		{
			AfxMessageBox("不能是指数");
			return;
		}
		pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
	}
	if(pStockDayTable)
	{
		CDlgLoopBackSetting dlg;
		dlg.SetStockDayTable(pStockDayTable);
		if(dlg.DoModal()==IDOK)
		{
			float f_total_fund=dlg.GetTotalFund();

			float f_stamp_tax=dlg.GetStampTax();

			float f_service_charge=dlg.GetServiceCharge();

			float f_min_service_charge=dlg.GetMinServiceCharge();


			CString strBeginDate=dlg.GetBeginDate();
			CString strEndDate=dlg.GetEndDate();
			CString strCmpMethodDes=dlg.GetCmpMethodDes();
			int  mCmpMethodNums=dlg.GetCmpMethodNums();

			CString strStockExpName=dlg.GetStockExpName();

			CString strStrockExpCode=StockDataMgr()->GetStockCode(strStockExpName);

			CString strCmpMethodName="";
			strCmpMethodName=StrategyMgr()->GetCmpMethodNameByDes(strCmpMethodDes);
			if(strCmpMethodName!="")
			{
				CDlgCurveSinCmp2 *pDlgCurveSinCmp2=NULL;
				pDlgCurveSinCmp2=new CDlgCurveSinCmp2();
				pDlgCurveSinCmp2->SetStockDayTable(pStockDayTable);
				pDlgCurveSinCmp2->SetCmpMethodNums(mCmpMethodNums);
				if(pDlgCurveSinCmp2->DoModal()==IDOK)
				{
					CmpMethodParas mParas=pDlgCurveSinCmp2->GetCmpMethodParas();

					CCurveSinCmpLoopBack *pCurveSinCmpLoopBack=new CCurveSinCmpLoopBack();

					pCurveSinCmpLoopBack->SetTotalFund(f_total_fund);
					pCurveSinCmpLoopBack->SetStampTax(f_stamp_tax);
					pCurveSinCmpLoopBack->SetServiceCharge(f_service_charge);
					pCurveSinCmpLoopBack->SetMinServiceCharge(f_min_service_charge);
					pCurveSinCmpLoopBack->SetBeginDate(strBeginDate);
					pCurveSinCmpLoopBack->SetEndDate(strEndDate);
					pCurveSinCmpLoopBack->SetStockCode(pStockCode->strStockCode);
					pCurveSinCmpLoopBack->SetStockExp(strStrockExpCode);
					pCurveSinCmpLoopBack->SetCmpMethodName(strCmpMethodName);
					pCurveSinCmpLoopBack->SetCmpMethodParas(mParas);
					pCurveSinCmpLoopBack->SetCmpMethodNums(mCmpMethodNums);

					pDlgLoopBackLog=new CDlgLoopBackLog(this);
					pCurveSinCmpLoopBack->SetDlgLoopBackCallBack(pDlgLoopBackLog);
					pDlgLoopBackLog->Create(IDD_DLG_LOOPBACK_LOG);
					pDlgLoopBackLog->ShowWindow(SW_SHOWNORMAL);
					pDlgLoopBackLog->CenterWindow(this);
					LoopBackMgr()->doRunLoopBack(pCurveSinCmpLoopBack);

				}
			}
		}
	}
}

//超跌监控
void CMyStockDlg::OnBnClickedBtnMonitor()
{

	/*if(!pDlgStockMonitor)
		return;
	if(!pDlgStockMonitor->GetSafeHwnd())
	{
		AfxMessageBox("先关闭监控窗口");
		return;
	}
	CDlgStockPriceFilter dlg;
	if(dlg.DoModal()==IDOK)
	{
		Vec_CString vecStockCodeList=StockDataMgr()->GetStockCodeStringList();
		CStockPriceFilter mStockPriceFilter;
		int mDayNums=dlg.GetDayNums();
		float f_up_percent=dlg.GetUpPercent();
		float f_down_percent=dlg.GetDownPercent();
		mStockPriceFilter.SetStockCodeList(vecStockCodeList);
		mStockPriceFilter.SetDayNums(mDayNums);
		mStockPriceFilter.SetUpPercent(f_up_percent);
		mStockPriceFilter.SetDownPercent(f_down_percent);

		Vec_CString vecFilterStockCodeList=mStockPriceFilter.FilterStock();

		
		pDlgStockMonitor->SetDayNums(mDayNums);
		pDlgStockMonitor->SetUpPercent(f_up_percent);
		pDlgStockMonitor->SetDownPercent(f_down_percent);
		pDlgStockMonitor->SetStockCodeList(vecFilterStockCodeList);
		pDlgStockMonitor->Init();
		pDlgStockMonitor->ShowWindow(SW_SHOWNORMAL);
		pDlgStockMonitor->CenterWindow(this);
	}
	*/

	if(!pDlgStockMonitorKDJ)
		return;
	if(!pDlgStockMonitorKDJ->GetSafeHwnd())
	{
		AfxMessageBox("先关闭监控窗口");
		return;
	}
	pDlgStockMonitorKDJ->ShowWindow(SW_SHOWNORMAL);
	pDlgStockMonitorKDJ->CenterWindow(this);
}

//股票狙击回测
void CMyStockDlg::OnBnClickedBtnMonitorLoopback()
{
	if(!pDlgSniperLoopBack)
		return;
	if(!pDlgSniperLoopBack->GetSafeHwnd())
	{
		AfxMessageBox("先关闭回测窗口");
		return;
	}
	pDlgSniperLoopBack->ShowWindow(SW_SHOWNORMAL);
	pDlgSniperLoopBack->CenterWindow(this);
}


//能量算法列表
void CMyStockDlg::OnBnClickedBtnPowerArith()
{
	/*if(pDlgPowerArithResult->GetSafeHwnd() && pDlgPowerArithResult->IsWindowVisible())
	{
		pDlgPowerArithResult->ShowWindow(SW_SHOWNORMAL);
		pDlgPowerArithResult->CenterWindow(this);
	}
	else
	{
		pDlgPowerArithResult->Init();
		pDlgPowerArithResult->ShowWindow(SW_SHOWNORMAL);
		pDlgPowerArithResult->CenterWindow(this);
	}*/
	
}

//设置
void CMyStockDlg::OnBnClickedBtnSetting()
{
	CDlgSetting dlg;
	dlg.DoModal();
}

//更新数据
void CMyStockDlg::OnBnClickedBtnUpdatedata()
{
	CDlgUpdateStockData dlg;
	dlg.DoModal();
	SetTimer(TIMER_EVENT_REFRESH_DATA,200,0);
}


//价格分布查找股票

void CMyStockDlg::OnBnClickedBtnStaticAnalysis()
{
	CDlgFindStockDestribute dlg;
	dlg.DoModal();
}


void CMyStockDlg::OnBnClickedBtnStockMethod()
{
	CDlgDropOff dlg;
	dlg.DoModal();
	
}
