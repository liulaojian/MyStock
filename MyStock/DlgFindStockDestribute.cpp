// DlgFindStockDestribute.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgFindStockDestribute.h"
#include "afxdialogex.h"
#include "StockDataMgr.h"
#include "Convert.h"
#include "T_FreeVector.h"
#include "CommonMacro.h"
#include "DlgStockPriceDestribute.h"
#include "StockLimitUpAnalysize.h"
#include "StockKDJAnalysize.h"
#include "StockM5M20Analysize.h"
#include "StockM20M40Analysize.h"
#include "StockMiddleUpAnalysize.h"
#include "StockMinMinMinAnalysize.h"

#include "StockWRAnalysize.h"
// CDlgFindStockDestribute 对话框

IMPLEMENT_DYNAMIC(CDlgFindStockDestribute, CDialogEx)

CDlgFindStockDestribute::CDlgFindStockDestribute(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgFindStockDestribute::IDD, pParent)
{
	mLastDayNums=240;
}

CDlgFindStockDestribute::~CDlgFindStockDestribute()
{
}

void CDlgFindStockDestribute::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN, mBeginDateTimeCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, mEndDateTimeCtrl);
	DDX_Control(pDX, IDC_LIST_STOCK, mStockList);
	DDX_Control(pDX, IDC_SCRIPTCONTROL1, mScriptControl);
	DDX_Control(pDX, IDC_MENUBTN_OTHER, mMenuBtnOther);
}


BEGIN_MESSAGE_MAP(CDlgFindStockDestribute, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CALC, &CDlgFindStockDestribute::OnBnClickedBtnCalc)
	ON_BN_CLICKED(IDC_BTN_FIND, &CDlgFindStockDestribute::OnBnClickedBtnFind)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_STOCK, &CDlgFindStockDestribute::OnRclickListStock)
	ON_UPDATE_COMMAND_UI(ID_MENU_OPEN_PRICE_DESTRIBUTE, &CDlgFindStockDestribute::OnUpdateMenuOpenPriceDestribute)
	ON_COMMAND(ID_MENU_OPEN_PRICE_DESTRIBUTE, &CDlgFindStockDestribute::OnMenuOpenPriceDestribute)
	ON_BN_CLICKED(IDC_BTN_FIND_SINGLE, &CDlgFindStockDestribute::OnBnClickedBtnFindSingle)
	ON_BN_CLICKED(IDC_BTN_FIND_SINGLE2, &CDlgFindStockDestribute::OnBnClickedBtnFindSingle2)
	ON_BN_CLICKED(IDC_BTN_CALC_NOCHANGE, &CDlgFindStockDestribute::OnBnClickedBtnCalcNochange)
	ON_BN_CLICKED(IDC_BTN_LOOK_HIGH, &CDlgFindStockDestribute::OnBnClickedBtnLookHigh)
	ON_BN_CLICKED(IDC_MENUBTN_OTHER, &CDlgFindStockDestribute::OnBnClickedMenubtnOther)
END_MESSAGE_MAP()


// CDlgFindStockDestribute 消息处理程序


BOOL CDlgFindStockDestribute::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mStockList.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT ); //设置报表风格



	mStockList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 

	mStockList.InsertColumn( PRICE_COLUMN_ID, "顺序ID号", LVCFMT_LEFT, 80 );
	mStockList.InsertColumn( PRICE_COLUMN_STOCK_CODE, "股票代码", LVCFMT_LEFT, 100 );
	mStockList.InsertColumn( PRICE_COLUMN_STOCK_NAME, "股票名称", LVCFMT_LEFT, 100 );
	mStockList.InsertColumn( PRICE_COLUMN_UP_0_3, "Up 0-3", LVCFMT_LEFT, 100 );
	mStockList.InsertColumn( PRICE_COLUMN_UP_3_6, "Up 3-6", LVCFMT_LEFT, 100 );
	mStockList.InsertColumn( PRICE_COLUMN_UP_6_10, "Up 6-10", LVCFMT_LEFT, 100 );
	mStockList.InsertColumn( PRICE_COLUMN_UP_10, "Up 10", LVCFMT_LEFT, 100 );
	mStockList.InsertColumn( PRICE_COLUMN_DOWN_0_3, "Down 0-3", LVCFMT_LEFT, 100 );
	mStockList.InsertColumn( PRICE_COLUMN_DOWN_3_6, "Down 3-6", LVCFMT_LEFT, 100 );
	mStockList.InsertColumn( PRICE_COLUMN_DOWN_6_10, "Down 6-10", LVCFMT_LEFT, 100 );
	mStockList.InsertColumn( PRICE_COLUMN_DOWN_10, "Down 10", LVCFMT_LEFT, 100 );
	
	pExpStockDayTable=StockDataMgr()->GetStockDayTable("SH000001");

	strEndDate=pExpStockDayTable->GetStockDayDateReverseIndex(0);
	strBeginDate=pExpStockDayTable->GetStockDayDateReverseIndex(mLastDayNums);
	CTime mBeginDate=ConverStringToCTime(strBeginDate);
	CTime mEndDate=ConverStringToCTime(strEndDate);
	mBeginDateTimeCtrl.SetTime(&mBeginDate);
	mEndDateTimeCtrl.SetTime(&mEndDate);


	CMenu* pMenu = new CMenu;
	pMenu->LoadMenu(IDR_MENU_BTN_OTHER);

	mMenuBtnOther.m_hMenu=pMenu->GetSubMenu(0)->GetSafeHmenu();


	CalcStockProfitLossData();

	SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CDlgFindStockDestribute::CalcStockProfitLossData(void)
{
	CStockProfitLossData *pStockProfitLossData=NULL;
	for(int i=0;i<vecStockProfitLossData.size();i++)
	{
		pStockProfitLossData=vecStockProfitLossData[i];
		if(!pStockProfitLossData)
			continue;
		CFreeVector<Vec_ProfitLossInfoList>::freeVector(pStockProfitLossData->vec_profitloss);
	}
	CFreeVector<Vec_StockProfitLossData>::freeVector(vecStockProfitLossData);


	CTime mBeginDate,mEndDate;
	mBeginDateTimeCtrl.GetTime(mBeginDate);
	mEndDateTimeCtrl.GetTime(mEndDate);

	strBeginDate=ConverCTimeToString(mBeginDate);
	strEndDate=ConverCTimeToString(mEndDate);

	Vec_CString vecStockCodeList;
	vecStockCodeList=StockDataMgr()->GetStockCodeStringList();
	for(int i=0;i<vecStockCodeList.size();i++)
	{

		CStockProfitLossData* pStockProfitLossData=NULL;
		pStockProfitLossData=CStockProfitLossArithmetic::CalcProfitLossData(vecStockCodeList[i],strEndDate,240,50);
		if(pStockProfitLossData)
		{
			//pStockProfitLossData->CalcVolumeDownSectionRange()
			if(mLastDayNums==240)
				pStockProfitLossData->CalcVolumeSectionRange();
			else
				pStockProfitLossData->CalcVolumeSectionRange(mLastDayNums);
			vecStockProfitLossData.push_back(pStockProfitLossData);
		}
	}


	return TRUE;
}

BOOL CDlgFindStockDestribute::CalcStockProfitLossDataNoChange(void)
{

	Vec_CString vecStockCodeList;

	CStockProfitLossData *pStockProfitLossData=NULL;
	for(int i=0;i<vecStockProfitLossData.size();i++)
	{
		pStockProfitLossData=vecStockProfitLossData[i];
		if(!pStockProfitLossData)
			continue;
		vecStockCodeList.push_back(pStockProfitLossData->strStockCode);
		CFreeVector<Vec_ProfitLossInfoList>::freeVector(pStockProfitLossData->vec_profitloss);
	}
	CFreeVector<Vec_StockProfitLossData>::freeVector(vecStockProfitLossData);


	CTime mBeginDate,mEndDate;
	mBeginDateTimeCtrl.GetTime(mBeginDate);
	mEndDateTimeCtrl.GetTime(mEndDate);

	strBeginDate=ConverCTimeToString(mBeginDate);
	strEndDate=ConverCTimeToString(mEndDate);

	for(int i=0;i<vecStockCodeList.size();i++)
	{

		CStockProfitLossData* pStockProfitLossData=NULL;
		pStockProfitLossData=CStockProfitLossArithmetic::CalcProfitLossData(vecStockCodeList[i],strEndDate,240,50);
		if(pStockProfitLossData)
		{
			//pStockProfitLossData->CalcVolumeDownSectionRange()
			if(mLastDayNums==240)
				pStockProfitLossData->CalcVolumeSectionRange();
			else
				pStockProfitLossData->CalcVolumeSectionRange(mLastDayNums);
			vecStockProfitLossData.push_back(pStockProfitLossData);
		}
	}


	return TRUE;
}

CStockProfitLossData* CDlgFindStockDestribute::GetStockProfitLossData(CString strStockCode)
{
	CStockProfitLossData* pStockProfitLossData=NULL;
	for(int i=0;i<vecStockProfitLossData.size();i++)
	{
		pStockProfitLossData=vecStockProfitLossData[i];
		if(!pStockProfitLossData)
			continue;
		if(pStockProfitLossData->strStockCode==strStockCode)
			return pStockProfitLossData;
	}
	return NULL;
}


BOOL CDlgFindStockDestribute::CalcUp0_3(CStockProfitLossData* pStockProfitLossData,double & f_duty)
{
	if(!pStockProfitLossData)
		return FALSE;
	if(pStockProfitLossData->vec_up_range.size()!=50)
		return FALSE;

	f_duty=pStockProfitLossData->vec_up_range[0]+pStockProfitLossData->vec_up_range[1]+pStockProfitLossData->vec_up_range[2];

	return TRUE;
}

BOOL CDlgFindStockDestribute::CalcUp3_6(CStockProfitLossData* pStockProfitLossData,double & f_duty)
{
	if(!pStockProfitLossData)
		return FALSE;
	if(pStockProfitLossData->vec_up_range.size()!=50)
		return FALSE;

	f_duty=pStockProfitLossData->vec_up_range[3]+pStockProfitLossData->vec_up_range[4]+pStockProfitLossData->vec_up_range[5];

	return TRUE;
}


BOOL CDlgFindStockDestribute::CalcUp6_10(CStockProfitLossData* pStockProfitLossData,double & f_duty)
{
	if(!pStockProfitLossData)
		return FALSE;
	if(pStockProfitLossData->vec_up_range.size()!=50)
		return FALSE;

	f_duty=pStockProfitLossData->vec_up_range[6]+pStockProfitLossData->vec_up_range[7]+pStockProfitLossData->vec_up_range[8]+pStockProfitLossData->vec_up_range[9];

	return TRUE;
}


BOOL CDlgFindStockDestribute::CalcUp10(CStockProfitLossData* pStockProfitLossData,double & f_duty)
{
	if(!pStockProfitLossData)
		return FALSE;
	if(pStockProfitLossData->vec_up_range.size()!=50)
		return FALSE;
	f_duty=0.0;
	for(int i=10;i<=49;i++)
	{
		f_duty+=pStockProfitLossData->vec_up_range[i];
	}
	
	return TRUE;
}

BOOL CDlgFindStockDestribute::CalcDown0_3(CStockProfitLossData* pStockProfitLossData,double & f_duty)
{

	if(!pStockProfitLossData)
		return FALSE;
	if(pStockProfitLossData->vec_down_range.size()!=50)
		return FALSE;

	f_duty=pStockProfitLossData->vec_down_range[0]+pStockProfitLossData->vec_down_range[1]+pStockProfitLossData->vec_down_range[2];


	return TRUE;
}

BOOL CDlgFindStockDestribute::CalcDown3_6(CStockProfitLossData* pStockProfitLossData,double & f_duty)
{
	if(!pStockProfitLossData)
		return FALSE;
	if(pStockProfitLossData->vec_down_range.size()!=50)
		return FALSE;

	f_duty=pStockProfitLossData->vec_down_range[3]+pStockProfitLossData->vec_down_range[4]+pStockProfitLossData->vec_down_range[5];


	return TRUE;
}

BOOL CDlgFindStockDestribute::CalcDown6_10(CStockProfitLossData* pStockProfitLossData,double & f_duty)
{
	if(!pStockProfitLossData)
		return FALSE;
	if(pStockProfitLossData->vec_down_range.size()!=50)
		return FALSE;

	f_duty=pStockProfitLossData->vec_down_range[6]+pStockProfitLossData->vec_down_range[7]+pStockProfitLossData->vec_down_range[8]+pStockProfitLossData->vec_down_range[9];
	
	return TRUE;
}

BOOL CDlgFindStockDestribute::CalcDown10(CStockProfitLossData* pStockProfitLossData,double & f_duty)
{

	if(!pStockProfitLossData)
		return FALSE;
	if(pStockProfitLossData->vec_down_range.size()!=50)
		return FALSE;
	f_duty=0.0;
	for(int i=10;i<=49;i++)
	{
		f_duty+=pStockProfitLossData->vec_down_range[i];
	}


	return TRUE;
}


bool CDlgFindStockDestribute::RefreshData(void)
{
	CString strConv,strTemp;
	int nRow;
	mStockList.DeleteAllItems();
	int i=0;
	CStockProfitLossData* pStockProfitLossData=NULL;

	for(i=0;i<vecStockProfitLossData.size();i++)
	{
		pStockProfitLossData=vecStockProfitLossData[i];
		if(!pStockProfitLossData)
			continue;
		strConv.Format("%4d",i+1);
		nRow=i;
		if(nRow>=mStockList.GetItemCount())
			mStockList.InsertItem(i,strConv);
		else
			mStockList.SetItemText(nRow, PRICE_COLUMN_ID,strConv);

		CString strStockName=StockDataMgr()->GetStockName(pStockProfitLossData->strStockCode);

		mStockList.SetItemText(nRow, PRICE_COLUMN_STOCK_CODE,pStockProfitLossData->strStockCode);
		mStockList.SetItemText(nRow, PRICE_COLUMN_STOCK_NAME,strStockName);


		CString strTemp;

		double f_duty=-99999.0;
		CalcUp0_3(pStockProfitLossData,f_duty);
		strTemp.Format("%.2f",f_duty);
		mStockList.SetItemText(nRow, PRICE_COLUMN_UP_0_3,strTemp);

		f_duty=-99999.0;
		CalcUp3_6(pStockProfitLossData,f_duty);
		strTemp.Format("%.2f",f_duty);
		mStockList.SetItemText(nRow, PRICE_COLUMN_UP_3_6,strTemp);


		f_duty=-99999.0;
		CalcUp6_10(pStockProfitLossData,f_duty);
		strTemp.Format("%.2f",f_duty);
		mStockList.SetItemText(nRow, PRICE_COLUMN_UP_6_10,strTemp);

		f_duty=-99999.0;
		CalcUp10(pStockProfitLossData,f_duty);
		strTemp.Format("%.2f",f_duty);
		mStockList.SetItemText(nRow, PRICE_COLUMN_UP_10,strTemp);


		f_duty=-99999.0;
		CalcDown0_3(pStockProfitLossData,f_duty);
		strTemp.Format("%.2f",f_duty);
		mStockList.SetItemText(nRow, PRICE_COLUMN_DOWN_0_3,strTemp);

		f_duty=-99999.0;
		CalcDown3_6(pStockProfitLossData,f_duty);
		strTemp.Format("%.2f",f_duty);
		mStockList.SetItemText(nRow, PRICE_COLUMN_DOWN_3_6,strTemp);


		f_duty=-99999.0;
		CalcDown6_10(pStockProfitLossData,f_duty);
		strTemp.Format("%.2f",f_duty);
		mStockList.SetItemText(nRow, PRICE_COLUMN_DOWN_6_10,strTemp);

		f_duty=-99999.0;
		CalcDown10(pStockProfitLossData,f_duty);
		strTemp.Format("%.2f",f_duty);
		mStockList.SetItemText(nRow, PRICE_COLUMN_DOWN_10,strTemp);


		mStockList.SetItemData(nRow,reinterpret_cast<DWORD_PTR>(pStockProfitLossData));
	
	}

	if(i<mStockList.GetItemCount())
	{
		for(int j=i;j<mStockList.GetItemCount();j++)
			mStockList.DeleteItem(j);
	}

	return true;
}

void CDlgFindStockDestribute::OnTimer(UINT_PTR nIDEvent)
{
	if(PRICE_EVENT_REFRESH_DATA==nIDEvent)
	{
		RefreshData();
		KillTimer(PRICE_EVENT_REFRESH_DATA);
	}
	CDialogEx::OnTimer(nIDEvent);
}

//重新计算
void CDlgFindStockDestribute::OnBnClickedBtnCalc()
{
	CTime mBeginDate,mEndDate;
	mBeginDateTimeCtrl.GetTime(mBeginDate);
	mEndDateTimeCtrl.GetTime(mEndDate);

	strBeginDate=ConverCTimeToString(mBeginDate);
	strEndDate=ConverCTimeToString(mEndDate);

	Vec_StockDayData vecStockDayData;
	pExpStockDayTable->LockData();
	vecStockDayData=pExpStockDayTable->GetStockDayDataList();
	pExpStockDayTable->UnlockData();


	int mBeginPos=pExpStockDayTable->GetStockDayIndex(strBeginDate);

	if(mBeginPos==-1)
	{
		AfxMessageBox("开始日期不存在股票数据");
		return;
	}

	int mEndPos=pExpStockDayTable->GetStockDayIndex(strEndDate);

	if(mEndPos==-1)
	{
		
		AfxMessageBox("结束日期不存在股票数据");
		return;
	}

	if((mEndPos-mBeginPos)<20)
	{
		AfxMessageBox("开始结束日期不能少于20股票交易日");
		return;
	}

	if((mEndPos-mBeginPos)>240)
	{
		AfxMessageBox("开始结束日期不能大于240股票交易日");
		return;
	}

	mLastDayNums=mEndPos-mBeginPos;

	CalcStockProfitLossData();

	SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);
}


CString CDlgFindStockDestribute::LoadScript(CString strScriptFile)
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

BOOL CDlgFindStockDestribute::CheckDuty(CString strScript,double f_duty_up_0_2,double f_duty_up_2_4,double f_duty_up_4_6,double f_duty_up_6_8,double f_duty_up_8_10,double f_duty_up_10,
	double f_duty_down_0_2,double f_duty_down_2_4,double f_duty_down_4_6,double f_duty_down_6_8,double f_duty_down_8_10,double f_duty_down_10)
{
	
	DEBUG_TRY
	mScriptControl.AddCode((LPCSTR)strScript);
	CString strCode;
	strCode.Format("checkduty(%.2f,%.2f,%.2f,%.2f,%.2f,%.2f, %.2f,%.2f,%.2f,%.2f,%.2f,%.2f)",f_duty_up_0_2,f_duty_up_2_4,f_duty_up_4_6,f_duty_up_6_8,f_duty_up_8_10,f_duty_up_10,
				f_duty_down_0_2,f_duty_down_2_4,f_duty_down_4_6,f_duty_down_6_8,f_duty_down_8_10,f_duty_down_10);

	VARIANT A = mScriptControl.Eval((LPCSTR)strCode);

	int mResult=A.intVal;

	mScriptControl.Reset();

	if(mResult>0)
		return TRUE;
	else
		return FALSE;

	DEBUG_CATCH2("%s", __FUNCTION__);
	return FALSE;
}

//查找
void CDlgFindStockDestribute::OnBnClickedBtnFind()
{

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

	CString strScript=LoadScript(bufJsFilePath);

	if(strScript=="")
		return ;


	Vec_StockProfitLossData  vecNewStockProfitLossData;
		
	CStockProfitLossData* pStockProfitLossData=NULL;

	for(int i=0;i<vecStockProfitLossData.size();i++)
	{
		pStockProfitLossData=vecStockProfitLossData[i];
		if(!pStockProfitLossData)
		{
			continue;
		}

		double f_duty_up_0_2,f_duty_up_2_4,f_duty_up_4_6,f_duty_up_6_8,f_duty_up_8_10,f_duty_up_10;
		double f_duty_down_0_2,f_duty_down_2_4,f_duty_down_4_6,f_duty_down_6_8,f_duty_down_8_10,f_duty_down_10;

		f_duty_up_0_2=pStockProfitLossData->vec_up_range[0]+pStockProfitLossData->vec_up_range[1];
		f_duty_up_2_4=pStockProfitLossData->vec_up_range[2]+pStockProfitLossData->vec_up_range[3];
		f_duty_up_4_6=pStockProfitLossData->vec_up_range[4]+pStockProfitLossData->vec_up_range[5];
		f_duty_up_6_8=pStockProfitLossData->vec_up_range[6]+pStockProfitLossData->vec_up_range[7];
		f_duty_up_8_10=pStockProfitLossData->vec_up_range[8]+pStockProfitLossData->vec_up_range[9];

		f_duty_up_10=0.0;
		for(int j=10;j<=49;j++)
		{
			f_duty_up_10+=pStockProfitLossData->vec_up_range[j];
		}


		f_duty_down_0_2=pStockProfitLossData->vec_down_range[0]+pStockProfitLossData->vec_down_range[1];
		f_duty_down_2_4=pStockProfitLossData->vec_down_range[2]+pStockProfitLossData->vec_down_range[3];
		f_duty_down_4_6=pStockProfitLossData->vec_down_range[4]+pStockProfitLossData->vec_down_range[5];
		f_duty_down_6_8=pStockProfitLossData->vec_down_range[6]+pStockProfitLossData->vec_down_range[7];
		f_duty_down_8_10=pStockProfitLossData->vec_down_range[8]+pStockProfitLossData->vec_down_range[9];

		f_duty_down_10=0.0;

		for(int j=10;j<=49;j++)
		{
			f_duty_down_10+=pStockProfitLossData->vec_down_range[j];
		}

		if(CheckDuty(strScript,f_duty_up_0_2,f_duty_up_2_4,f_duty_up_4_6,f_duty_up_6_8,f_duty_up_8_10,f_duty_up_10,
					f_duty_down_0_2,f_duty_down_2_4,f_duty_down_4_6,f_duty_down_6_8,f_duty_down_8_10,f_duty_down_10))
		{

			CStockDayTable *pStockDayTable;

			pStockDayTable=StockDataMgr()->GetStockDayTable(pStockProfitLossData->strStockCode);
			if(pStockDayTable)
			{
				Vec_StockDayData vecStockDayData;
				pStockDayTable->LockData();
				vecStockDayData=pStockDayTable->GetStockDayDataList();
				pStockDayTable->UnlockData();

				if(vecStockDayData[vecStockDayData.size()-1]->GetTotalVolume()>0)
				{
					vecNewStockProfitLossData.push_back(pStockProfitLossData);
				}

			}
		}


	}
	
	vecStockProfitLossData.clear();
	vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
	SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);

}


void CDlgFindStockDestribute::OnRclickListStock(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if(pNMItemActivate->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU_PRICR_FIND ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );

	}

	*pResult = 0;
}

//打开股价分布图
void CDlgFindStockDestribute::OnUpdateMenuOpenPriceDestribute(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CDlgFindStockDestribute::OnMenuOpenPriceDestribute()
{
	CStockProfitLossData* pStockProfitLossData=NULL;
	for(int  i=0; i<mStockList.GetItemCount(); i++)
	{
		if( mStockList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			pStockProfitLossData=reinterpret_cast<CStockProfitLossData *>(mStockList.GetItemData(i));

			break;
		}
	}

	if(pStockProfitLossData==NULL)
		return;

	CString strStockCode=pStockProfitLossData->strStockCode;

	CTime mEndTime;
	mEndDateTimeCtrl.GetTime(mEndTime);
	CString strEndDate=ConverCTimeToString(mEndTime);
	
	pStockProfitLossData=CStockProfitLossArithmetic::CalcProfitLossData(strStockCode,strEndDate,240,50);

	CDlgStockPriceDestribute dlg;
	dlg.SetStockProfitLossData(pStockProfitLossData);
	dlg.DoModal();

}

//查找单峰
void CDlgFindStockDestribute::OnBnClickedBtnFindSingle()
{
	Vec_StockProfitLossData  vecNewStockProfitLossData;

	CStockProfitLossData* pStockProfitLossData=NULL;

	for(int i=0;i<vecStockProfitLossData.size();i++)
	{
		pStockProfitLossData=vecStockProfitLossData[i];
		if(!pStockProfitLossData)
		{
			continue;
		}
		std::vector<double> vec_range;

		for(int i=pStockProfitLossData->vec_down_range.size()-1;i>=0;i--)
		{
			vec_range.push_back(pStockProfitLossData->vec_down_range[i]);
		}

		for(int i=0;i<pStockProfitLossData->vec_up_range.size();i++)
		{
			vec_range.push_back(pStockProfitLossData->vec_up_range[i]);
		}


		int mContinuNums=0;
		int f_total_range=0;
		for(int i=0;i<vec_range.size();i++)
		{

			double f_range_val=vec_range[i];

			if(f_range_val>=2.0)
			{
				mContinuNums++;
				f_total_range+=f_range_val;
			}
			else
			{
				mContinuNums=0;
				f_total_range=0.0;
			}

			if(f_total_range>60.0 && mContinuNums<=15)
			{
				CStockDayTable *pStockDayTable;

				pStockDayTable=StockDataMgr()->GetStockDayTable(pStockProfitLossData->strStockCode);
				if(pStockDayTable)
				{
					Vec_StockDayData vecStockDayData;
					pStockDayTable->LockData();
					vecStockDayData=pStockDayTable->GetStockDayDataList();
					pStockDayTable->UnlockData();

					if(vecStockDayData[vecStockDayData.size()-1]->GetTotalVolume()>0)
					{
						vecNewStockProfitLossData.push_back(pStockProfitLossData);
						break;
					}

				}
			}

			if(mContinuNums>10)
			{
				mContinuNums=0;
				f_total_range=0.0;
			}


		}
	}

	vecStockProfitLossData.clear();
	vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
	SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);

}

//查找单峰2(小)
void CDlgFindStockDestribute::OnBnClickedBtnFindSingle2()
{
	Vec_StockProfitLossData  vecNewStockProfitLossData;

	CStockProfitLossData* pStockProfitLossData=NULL;

	for(int i=0;i<vecStockProfitLossData.size();i++)
	{
		pStockProfitLossData=vecStockProfitLossData[i];
		if(!pStockProfitLossData)
		{
			continue;
		}
		std::vector<double> vec_range;

		for(int i=pStockProfitLossData->vec_down_range.size()-1;i>=0;i--)
		{
			vec_range.push_back(pStockProfitLossData->vec_down_range[i]);
		}

		for(int i=0;i<pStockProfitLossData->vec_up_range.size();i++)
		{
			vec_range.push_back(pStockProfitLossData->vec_up_range[i]);
		}


		int mContinuNums=0;
		int f_total_range=0;
		for(int i=0;i<vec_range.size();i++)
		{

			double f_range_val=vec_range[i];

			if(f_range_val>=2.0)
			{
				mContinuNums++;
				f_total_range+=f_range_val;
			}
			else
			{
				mContinuNums=0;
				f_total_range=0.0;
			}

			if(f_total_range>25.0 && mContinuNums<=8)
			{
				CStockDayTable *pStockDayTable;

				pStockDayTable=StockDataMgr()->GetStockDayTable(pStockProfitLossData->strStockCode);
				if(pStockDayTable)
				{
					Vec_StockDayData vecStockDayData;
					pStockDayTable->LockData();
					vecStockDayData=pStockDayTable->GetStockDayDataList();
					pStockDayTable->UnlockData();

					if(vecStockDayData[vecStockDayData.size()-1]->GetTotalVolume()>0)
					{
						vecNewStockProfitLossData.push_back(pStockProfitLossData);
						break;
					}

				}
			}

			if(mContinuNums>10)
			{
				mContinuNums=0;
				f_total_range=0.0;
			}


		}
	}

	vecStockProfitLossData.clear();
	vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
	SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);
}

//不变计算
void CDlgFindStockDestribute::OnBnClickedBtnCalcNochange()
{
	CTime mBeginDate,mEndDate;
	mBeginDateTimeCtrl.GetTime(mBeginDate);
	mEndDateTimeCtrl.GetTime(mEndDate);

	strBeginDate=ConverCTimeToString(mBeginDate);
	strEndDate=ConverCTimeToString(mEndDate);

	Vec_StockDayData vecStockDayData;
	pExpStockDayTable->LockData();
	vecStockDayData=pExpStockDayTable->GetStockDayDataList();
	pExpStockDayTable->UnlockData();


	int mBeginPos=pExpStockDayTable->GetStockDayIndex(strBeginDate);

	if(mBeginPos==-1)
	{
		AfxMessageBox("开始日期不存在股票数据");
		return;
	}

	int mEndPos=pExpStockDayTable->GetStockDayIndex(strEndDate);

	if(mEndPos==-1)
	{

		AfxMessageBox("结束日期不存在股票数据");
		return;
	}

	if((mEndPos-mBeginPos)<20)
	{
		AfxMessageBox("开始结束日期不能少于20股票交易日");
		return;
	}

	if((mEndPos-mBeginPos)>240)
	{
		AfxMessageBox("开始结束日期不能大于240股票交易日");
		return;
	}

	mLastDayNums=mEndPos-mBeginPos;

	CalcStockProfitLossDataNoChange();

	SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);
}

//追高
void CDlgFindStockDestribute::OnBnClickedBtnLookHigh()
{
	Vec_StockProfitLossData  vecNewStockProfitLossData;

	CStockProfitLossData* pStockProfitLossData=NULL;

	for(int i=0;i<vecStockProfitLossData.size();i++)
	{
		pStockProfitLossData=vecStockProfitLossData[i];
		if(!pStockProfitLossData)
		{
			continue;
		}
		
		double f_duty_up_0_2,f_duty_up_2_4,f_duty_up_4_6,f_duty_up_6_8,f_duty_up_8_10,f_duty_up_10;
		double f_duty_down_0_2,f_duty_down_2_4,f_duty_down_4_6,f_duty_down_6_8,f_duty_down_8_10,f_duty_down_10;

		f_duty_up_0_2=pStockProfitLossData->vec_up_range[0]+pStockProfitLossData->vec_up_range[1];
		f_duty_up_2_4=pStockProfitLossData->vec_up_range[2]+pStockProfitLossData->vec_up_range[3];
		f_duty_up_4_6=pStockProfitLossData->vec_up_range[4]+pStockProfitLossData->vec_up_range[5];
		f_duty_up_6_8=pStockProfitLossData->vec_up_range[6]+pStockProfitLossData->vec_up_range[7];
		f_duty_up_8_10=pStockProfitLossData->vec_up_range[8]+pStockProfitLossData->vec_up_range[9];

		f_duty_up_10=0.0;
		for(int j=10;j<=49;j++)
		{
			f_duty_up_10+=pStockProfitLossData->vec_up_range[j];
		}

		double f_duty_up_20=0.0;
		for(int j=20;j<=49;j++)
		{
			f_duty_up_20+=pStockProfitLossData->vec_up_range[j];
		}

		double f_up_total=f_duty_up_0_2+f_duty_up_2_4+f_duty_up_4_6+f_duty_up_6_8+f_duty_up_8_10+f_duty_up_10;

		f_duty_down_0_2=pStockProfitLossData->vec_down_range[0]+pStockProfitLossData->vec_down_range[1];
		f_duty_down_2_4=pStockProfitLossData->vec_down_range[2]+pStockProfitLossData->vec_down_range[3];
		f_duty_down_4_6=pStockProfitLossData->vec_down_range[4]+pStockProfitLossData->vec_down_range[5];
		f_duty_down_6_8=pStockProfitLossData->vec_down_range[6]+pStockProfitLossData->vec_down_range[7];
		f_duty_down_8_10=pStockProfitLossData->vec_down_range[8]+pStockProfitLossData->vec_down_range[9];

		f_duty_down_10=0.0;

		for(int j=10;j<=49;j++)
		{
			f_duty_down_10+=pStockProfitLossData->vec_down_range[j];
		}

		double f_duty_down_20=0.0;

		for(int j=20;j<=49;j++)
		{
			f_duty_down_20+=pStockProfitLossData->vec_down_range[j];
		}

		if(f_up_total<4.0 && f_duty_down_20>50.0)
		{
			CStockDayTable *pStockDayTable;

			pStockDayTable=StockDataMgr()->GetStockDayTable(pStockProfitLossData->strStockCode);
			if(pStockDayTable)
			{
				Vec_StockDayData vecStockDayData;
				pStockDayTable->LockData();
				vecStockDayData=pStockDayTable->GetStockDayDataList();
				pStockDayTable->UnlockData();

				if(vecStockDayData[vecStockDayData.size()-1]->GetTotalVolume()>0)
				{
					vecNewStockProfitLossData.push_back(pStockProfitLossData);
				
				}

			}
		}
	}

	vecStockProfitLossData.clear();
	vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
	SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);
}

//其他功能
void CDlgFindStockDestribute::OnBnClickedMenubtnOther()
{
	if(mMenuBtnOther.m_nMenuResult==ID_MENU_MOST_PROBALE_RAISE)
	{
		Vec_StockProfitLossData  vecNewStockProfitLossData;

		CStockProfitLossData* pStockProfitLossData=NULL;

		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
			{
				continue;
			}

			CStockLimitUpAnalysize *pStockLimitUpAnalysize=new CStockLimitUpAnalysize(pStockProfitLossData->strStockCode);
			double f_bander_chip_per=0.0;
			double f_now_down_per=0.0;
			double f_min_down_per=0.0;
			if(pStockLimitUpAnalysize->AnalysisStock(pStockProfitLossData->strEndDate,FALSE,f_bander_chip_per,f_now_down_per,f_min_down_per))
			{
				
				//if(f_bander_chip_per>30.0 && f_bander_chip_per<40.0)
				//PrintfDebug("Not Selected %s  %.2f\n",pStockProfitLossData->strStockCode,f_bander_chip_per);
				if(f_min_down_per>6.0)
				{
					if(f_bander_chip_per>34.0)
					{
						PrintfDebug("%s  %.2f   %.2f\n",pStockProfitLossData->strStockCode,f_bander_chip_per,f_now_down_per);
						vecNewStockProfitLossData.push_back(pStockProfitLossData);
					}
				}
				else
				{
					if(f_bander_chip_per>51.0)	
					{
						PrintfDebug("%s  %.2f   %.2f\n",pStockProfitLossData->strStockCode,f_bander_chip_per,f_now_down_per);
						vecNewStockProfitLossData.push_back(pStockProfitLossData);
					}
				}
				
			}
		}

		vecStockProfitLossData.clear();
		vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
		SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);
	}
	else if(mMenuBtnOther.m_nMenuResult==ID_MENU_MOST_PROBALE_RAISE_MIN)
	{
		Vec_StockProfitLossData  vecNewStockProfitLossData;

		CStockProfitLossData* pStockProfitLossData=NULL;

		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
			{
				continue;
			}

			CStockLimitUpAnalysize *pStockLimitUpAnalysize=new CStockLimitUpAnalysize(pStockProfitLossData->strStockCode);
			double f_bander_chip_per=0.0;
			double f_now_down_per=0.0;
			double f_min_down_per=0.0;
			if(pStockLimitUpAnalysize->AnalysisStock(pStockProfitLossData->strEndDate,TRUE,f_bander_chip_per,f_now_down_per,f_min_down_per))
			{

				
				
				if(f_bander_chip_per>15.0 && f_bander_chip_per<25.0)
				{
					CStockDayTable *pStockDayTable=NULL;
					pStockDayTable=StockDataMgr()->GetStockDayTable(pStockProfitLossData->strStockCode);

					if(pStockDayTable)
					{

						CStockDayData *pStockDayData=pStockDayTable->GetStockDayDataByDate(pStockProfitLossData->strEndDate);
						if(pStockDayData)
						{
							if(pStockDayData->GetTotalVolume()>0)
							{
								PrintfDebug("%s  %.2f   %.2f\n",pStockProfitLossData->strStockCode,f_bander_chip_per,f_now_down_per);
								vecNewStockProfitLossData.push_back(pStockProfitLossData);
							}
						}

					}

				}
				
			}
		}

		vecStockProfitLossData.clear();
		vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
		SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);
	}
	else if(mMenuBtnOther.m_nMenuResult==ID_MENU_KDJ_ANALYSIZE)
	{
		Vec_StockProfitLossData  vecNewStockProfitLossData;

		CStockProfitLossData* pStockProfitLossData=NULL;

		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
			{
				continue;
			}

			CStockKDJAnalysize *pStockKDJAnalysize=new CStockKDJAnalysize(pStockProfitLossData->strStockCode);
			if(pStockKDJAnalysize->AnalysisStock(pStockProfitLossData->strEndDate,20.0))
			{
				vecNewStockProfitLossData.push_back(pStockProfitLossData);
				SAFE_DELETE(pStockKDJAnalysize);
			}

		}


		vecStockProfitLossData.clear();
		vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
		SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);
	}
	else if(mMenuBtnOther.m_nMenuResult==ID_MENU_KDJ_ANALYSIZE_HIGH)
	{
		Vec_StockProfitLossData  vecNewStockProfitLossData;

		CStockProfitLossData* pStockProfitLossData=NULL;

		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
			{
				continue;
			}

			CStockKDJAnalysize *pStockKDJAnalysize=new CStockKDJAnalysize(pStockProfitLossData->strStockCode);
			if(pStockKDJAnalysize->AnalysisStock(pStockProfitLossData->strEndDate,15.0))
			{
				vecNewStockProfitLossData.push_back(pStockProfitLossData);
				SAFE_DELETE(pStockKDJAnalysize);
			}

		}


		vecStockProfitLossData.clear();
		vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
		SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);
	}
	else if(mMenuBtnOther.m_nMenuResult==ID_MENU_KDJ_ANALYSIZE_LOW)
	{
		Vec_StockProfitLossData  vecNewStockProfitLossData;

		CStockProfitLossData* pStockProfitLossData=NULL;

		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
			{
				continue;
			}

			CStockKDJAnalysize *pStockKDJAnalysize=new CStockKDJAnalysize(pStockProfitLossData->strStockCode);
			if(pStockKDJAnalysize->AnalysisStock(pStockProfitLossData->strEndDate,25.0))
			{
				vecNewStockProfitLossData.push_back(pStockProfitLossData);
				SAFE_DELETE(pStockKDJAnalysize);
			}

		}


		vecStockProfitLossData.clear();
		vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
		SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);
	}
	else if(mMenuBtnOther.m_nMenuResult==ID_MENU_MAYBE_GOOD_STOCK)
	{

		/*
		Vec_StockProfitLossData  vecNewStockProfitLossData;

		CStockProfitLossData* pStockProfitLossData=NULL;

		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
			{
				continue;
			}

			CStockM5M20Analysize *pStockM5M20Analysize=new CStockM5M20Analysize(pStockProfitLossData->strStockCode);
			double f_bander_chip_per=0.0;
			double f_now_down_per=0.0;
			double f_max_now_dif_per=0.0;
			if(pStockM5M20Analysize->AnalysisStock(pStockProfitLossData->strEndDate,TRUE,f_bander_chip_per,f_now_down_per,f_max_now_dif_per))
			{
				//PrintfDebug("%d   %s  \n",i,pStockProfitLossData->strStockCode);

				
				if(f_max_now_dif_per>50.0)
				{
					if(f_now_down_per<4.0)
					{
						if(f_bander_chip_per>20.0 && f_bander_chip_per<35.0)	
						{
							PrintfDebug("%s  %.2f   %.2f  %.2f\n",pStockProfitLossData->strStockCode,f_bander_chip_per,f_now_down_per,f_max_now_dif_per);
							vecNewStockProfitLossData.push_back(pStockProfitLossData);
							SAFE_DELETE(pStockM5M20Analysize);
						}
					}
					else if(f_now_down_per>4.0 && f_now_down_per<8.0)
					{
						if(f_bander_chip_per>25.0 && f_bander_chip_per<40.0)	
						{
							PrintfDebug("%s  %.2f   %.2f  %.2f\n",pStockProfitLossData->strStockCode,f_bander_chip_per,f_now_down_per,f_max_now_dif_per);
							vecNewStockProfitLossData.push_back(pStockProfitLossData);
							SAFE_DELETE(pStockM5M20Analysize);
						}
					}
				}
				
				
				
			}

		}
		vecStockProfitLossData.clear();
		vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
		SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);

		*/


		Vec_StockProfitLossData  vecNewStockProfitLossData;

		CStockProfitLossData* pStockProfitLossData=NULL;

		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
			{
				continue;
			}

			CStockMiddleUpAnalysize *pStockMiddleUpAnalysize=new CStockMiddleUpAnalysize(pStockProfitLossData->strStockCode);
			double f_bander_chip_per=0.0;
			if(pStockMiddleUpAnalysize->AnalysisStock(pStockProfitLossData->strEndDate,f_bander_chip_per))
			{
				if(f_bander_chip_per>70.0)		//45
				{
					PrintfDebug("%s  %.2f\n",pStockProfitLossData->strStockCode,f_bander_chip_per);
					vecNewStockProfitLossData.push_back(pStockProfitLossData);
					SAFE_DELETE(pStockMiddleUpAnalysize);
				}
				
			}

		}


		vecStockProfitLossData.clear();
		vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
		SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);


	}
	else if(mMenuBtnOther.m_nMenuResult==ID_MENU_M20_UP_M40)
	{
		/*Vec_StockProfitLossData  vecNewStockProfitLossData;

		CStockProfitLossData* pStockProfitLossData=NULL;

		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
			{
				continue;
			}

			CStockM20M40Analysize *pStockM20M40Analysize=new CStockM20M40Analysize(pStockProfitLossData->strStockCode);
			if(pStockM20M40Analysize->AnalysisStock(pStockProfitLossData->strEndDate))
			{
				vecNewStockProfitLossData.push_back(pStockProfitLossData);
				SAFE_DELETE(pStockM20M40Analysize);
			}

		}


		vecStockProfitLossData.clear();
		vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
		SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);*/

		/*
		Vec_StockProfitLossData  vecNewStockProfitLossData;

		CStockProfitLossData* pStockProfitLossData=NULL;

		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
			{
				continue;
			}

			CStockMinMinMinAnalysize *pStockMinMinMinAnalysize=new CStockMinMinMinAnalysize(pStockProfitLossData->strStockCode);
			if(pStockMinMinMinAnalysize->AnalysisStock(pStockProfitLossData->strEndDate))
			{
				vecNewStockProfitLossData.push_back(pStockProfitLossData);
				SAFE_DELETE(pStockMinMinMinAnalysize);
			}

		}
		vecStockProfitLossData.clear();
		vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
		SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);
		*/


		Vec_StockProfitLossData  vecNewStockProfitLossData;

		CStockProfitLossData* pStockProfitLossData=NULL;

		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
			{
				continue;
			}

			CStockWRAnalysize *pStockWRAnalysize=new CStockWRAnalysize(pStockProfitLossData->strStockCode);
			if(pStockWRAnalysize->AnalysisStock(pStockProfitLossData->strEndDate))
			{
				vecNewStockProfitLossData.push_back(pStockProfitLossData);
				SAFE_DELETE(pStockWRAnalysize);
			}

		}
		vecStockProfitLossData.clear();
		vecStockProfitLossData.assign(vecNewStockProfitLossData.begin(),vecNewStockProfitLossData.end());
		SetTimer(PRICE_EVENT_REFRESH_DATA,200,0);
	}
	
}
