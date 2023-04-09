
// MyStockDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMyStockDlg �Ի���




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


// CMyStockDlg ��Ϣ�������

BOOL CMyStockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


#ifndef _DEBUG
	GetDlgItem(IDC_BTN_TEST)->ShowWindow(SW_HIDE);
#endif

	mStockListCtrl.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT ); //���ñ�����



	mStockListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 

	mStockListCtrl.InsertColumn( COLUMN_ID, "˳��ID��", LVCFMT_LEFT, 80 );
	
	mStockListCtrl.InsertColumn( COLUMN_STOCK_CODE, "��Ʊ����", LVCFMT_LEFT, 115 );

	mStockListCtrl.InsertColumn( COLUMN_STOCK_NAME, "��Ʊ����", LVCFMT_LEFT, 115 );

	mStockListCtrl.InsertColumn( COLUMN_STOCK_DAY_BEGIN, "�����ݿ�ʼ", LVCFMT_LEFT, 140 );
	mStockListCtrl.InsertColumn( COLUMN_STOCK_DAY_END, "�����ݽ���", LVCFMT_LEFT, 140 );

	mStockListCtrl.InsertColumn( COLUMN_STOCK_MIN_BEGIN, "�����ݿ�ʼ", LVCFMT_LEFT, 140);
	mStockListCtrl.InsertColumn( COLUMN_STOCK_MIN_END, "�����ݽ���", LVCFMT_LEFT, 140 );

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


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyStockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		AfxMessageBox("ѡ�����Ʊ!");
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
				AfxMessageBox("��ʷ��������֧�ִ���90��Ŀ��");
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
				GetDlgItem(IDC_STATIC_LABEL)->SetWindowText("����Ԥ������У������ĵȴ�...");
				if(pCurveSinCmpMethod->TraverseData())
				{
					GetDlgItem(IDC_STATIC_LABEL)->SetWindowText("��Ʊ");
					Vec_HistoryResultList vecHistoryResultList;
					vecHistoryResultList=pCurveSinCmpMethod->GetHistoryResultList();
					CString strTitle;
					strTitle.Format("��ʼ���� %s  �������� %s ��ʷԤ�ⷨ���",strBeginDateTime,strEndDateTime);
					CDlgHistoryCmpResult dlg;
					dlg.SetTitle(strTitle);
					dlg.SetStockDayTable(pStockDayTable);
					dlg.SetHistoryResultList(vecHistoryResultList);
					dlg.DoModal();

				}
				GetDlgItem(IDC_STATIC_LABEL)->SetWindowText("��Ʊ");
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

//����
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



//��ʷ�ز�
void CMyStockDlg::OnBnClickedBtnLoopback()
{
	int mSel=mStockListCtrl.GetNextItem(-1,LVIS_SELECTED); 

	if(mSel==-1)
	{
		AfxMessageBox("ѡ�����Ʊ!");
		return;
	}
	StockCode *pStockCode;

	pStockCode=reinterpret_cast<StockCode *>(mStockListCtrl.GetItemData(mSel));
	CStockDayTable *pStockDayTable=NULL;
	if(pStockCode)
	{
		if(pStockCode->strStockCode=="SH000001" || pStockCode->strStockCode=="SH000016" || pStockCode->strStockCode=="SH000300")
		{
			AfxMessageBox("������ָ��");
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

//�������
void CMyStockDlg::OnBnClickedBtnMonitor()
{

	/*if(!pDlgStockMonitor)
		return;
	if(!pDlgStockMonitor->GetSafeHwnd())
	{
		AfxMessageBox("�ȹرռ�ش���");
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
		AfxMessageBox("�ȹرռ�ش���");
		return;
	}
	pDlgStockMonitorKDJ->ShowWindow(SW_SHOWNORMAL);
	pDlgStockMonitorKDJ->CenterWindow(this);
}

//��Ʊ�ѻ��ز�
void CMyStockDlg::OnBnClickedBtnMonitorLoopback()
{
	if(!pDlgSniperLoopBack)
		return;
	if(!pDlgSniperLoopBack->GetSafeHwnd())
	{
		AfxMessageBox("�ȹرջزⴰ��");
		return;
	}
	pDlgSniperLoopBack->ShowWindow(SW_SHOWNORMAL);
	pDlgSniperLoopBack->CenterWindow(this);
}


//�����㷨�б�
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

//����
void CMyStockDlg::OnBnClickedBtnSetting()
{
	CDlgSetting dlg;
	dlg.DoModal();
}

//��������
void CMyStockDlg::OnBnClickedBtnUpdatedata()
{
	CDlgUpdateStockData dlg;
	dlg.DoModal();
	SetTimer(TIMER_EVENT_REFRESH_DATA,200,0);
}


//�۸�ֲ����ҹ�Ʊ

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
