// DlgUpdateStockData.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgUpdateStockData.h"
#include "afxdialogex.h"
#include "StockDataMgr.h"
//#include "StockDataInfoDb.h"
#include "T_FreeVector.h"

// CDlgUpdateStockData 对话框

IMPLEMENT_DYNAMIC(CDlgUpdateStockData, CDialogEx)

CDlgUpdateStockData::CDlgUpdateStockData(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgUpdateStockData::IDD, pParent)
{

}

CDlgUpdateStockData::~CDlgUpdateStockData()
{
}

void CDlgUpdateStockData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STOCK, mListStock);
}


BEGIN_MESSAGE_MAP(CDlgUpdateStockData, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_UPDATE_5MIN_DATA, &CDlgUpdateStockData::OnBnClickedBtnUpdate5minData)
	ON_BN_CLICKED(IDC_BTN_SAVEDB, &CDlgUpdateStockData::OnBnClickedBtnSavedb)
END_MESSAGE_MAP()


// CDlgUpdateStockData 消息处理程序


BOOL CDlgUpdateStockData::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mUpdateStockPos=0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgUpdateStockData::OnTimer(UINT_PTR nIDEvent)
{
	
	if(nIDEvent==UPDATE_EVENT_UPDATE_MIN5_DATA)
	{
		Vec_StockCodeList vecStockCodeList;
		StockCode *pStockCode;
		vecStockCodeList=StockDataMgr()->GetStockCodeList();

		
		pStockCode=vecStockCodeList[mUpdateStockPos];
		if(!pStockCode)
		{
			KillTimer(UPDATE_EVENT_UPDATE_MIN5_DATA);
			mUpdateStockPos=0;
			GetDlgItem(IDC_BTN_UPDATE_5MIN_DATA)->EnableWindow(TRUE);
			return;
		}

		if(UpdateStock5MinTable(pStockCode->strStockCode))
		{

			CString strInfo;
			strInfo.Format("%s %s 5分钟数据更新完毕",pStockCode->strStockCode,StockDataMgr()->GetStockName(pStockCode->strStockCode));
			mListStock.AddString(strInfo);


			CStockMin5Table *pStockMin5Table=NULL;
			pStockMin5Table=StockDataMgr()->GetStockMin5Table(pStockCode->strStockCode);
			if(pStockMin5Table)
			{
				CString strLastDate;
				strLastDate=pStockMin5Table->GetLastStockMin5DataDate();
				if(strLastDate!="")
				{
					CStockDayData *pStockDayData=NULL;
					pStockDayData=pStockMin5Table->BuildStockDayData(strLastDate);
					if(pStockDayData)
					{
						CStockDayTable *pStockDayTable=NULL;
						pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
						if(pStockDayTable->AddOrUpdateStockDayData(pStockDayData))
						{
							CString strInfo;
							strInfo.Format("%s %s 合并到天数据完成",pStockCode->strStockCode,StockDataMgr()->GetStockName(pStockCode->strStockCode));
							mListStock.AddString(strInfo);
						}
					}
				}
				
			}
			
			mUpdateStockPos++;
		}


		if(mUpdateStockPos>=vecStockCodeList.size())
		{
			KillTimer(UPDATE_EVENT_UPDATE_MIN5_DATA);
			mUpdateStockPos=0;
			GetDlgItem(IDC_BTN_UPDATE_5MIN_DATA)->EnableWindow(TRUE);
			return;
		}

	}
	else if(nIDEvent==UPDATE_EVENT_SAVE_DATA_TO_DB)
	{
		/*Vec_StockCodeList vecStockCodeList;
		StockCode *pStockCode;
		vecStockCodeList=StockDataMgr()->GetStockCodeList();
		pStockCode=vecStockCodeList[mUpdateStockPos];
		if(!pStockCode)
		{
			KillTimer(UPDATE_EVENT_SAVE_DATA_TO_DB);
			mUpdateStockPos=0;
			GetDlgItem(IDC_BTN_SAVEDB)->EnableWindow(TRUE);
			return;
		}
		CStockDayTable *pStockDayTable=NULL;
		pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
		CStockMin5Table *pStockMin5Table=NULL;
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(pStockCode->strStockCode);
		if(pStockDayTable)
		{
			Vec_DbStockDayData vecDbStockDayData;
			vecDbStockDayData=StockDataInfoDb()->ConvertVecStockDayDataToVecDbStockDayData(pStockDayTable->GetStockDayDataList());
			StockDataInfoDb()->StockDay_Table_InsertVec(pStockCode->strStockCode,vecDbStockDayData);
			CFreeVector<Vec_DbStockDayData>::freeVector(vecDbStockDayData);

			if(pStockMin5Table)
			{
				Vec_DbStock5MinData vecDbStock5MinData;
				vecDbStock5MinData=StockDataInfoDb()->ConvertVecStockMin5DataToVecDbStock5MinData(pStockMin5Table->GetStockMin5DataList());
				StockDataInfoDb()->StockMin5_Table_InsertVec(pStockCode->strStockCode,vecDbStock5MinData);
				CFreeVector<Vec_DbStock5MinData>::freeVector(vecDbStock5MinData);
			}
			

			CString strInfo;
			strInfo.Format("%s %s 数据保存到数据库完毕",pStockCode->strStockCode,StockDataMgr()->GetStockName(pStockCode->strStockCode));
			mListStock.AddString(strInfo);


		}
		
		mUpdateStockPos++;

		if(mUpdateStockPos>=vecStockCodeList.size())
		{
			KillTimer(UPDATE_EVENT_SAVE_DATA_TO_DB);
			mUpdateStockPos=0;
			GetDlgItem(IDC_BTN_SAVEDB)->EnableWindow(TRUE);
			StockDataInfoDb()->DataBaseClose();
			return;
		}
		*/
	}
	CDialogEx::OnTimer(nIDEvent);
}


BOOL  CDlgUpdateStockData::UpdateStock5MinTable(CString strStockCode)
{
	CStockMin5Table *pStockMin5Table=NULL;
	pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);
	if(!pStockMin5Table)
		return FALSE;

	if(pStockMin5Table->AddNearestStockData(pStockMin5Table->GetNearestStockDataFormHttp(100)))
	{
		return TRUE;
	}

	return FALSE;
}

//更新五分钟数据
void CDlgUpdateStockData::OnBnClickedBtnUpdate5minData()
{
	mListStock.ResetContent();
	mUpdateStockPos=0;
	SetTimer(UPDATE_EVENT_UPDATE_MIN5_DATA,200,0);
	GetDlgItem(IDC_BTN_UPDATE_5MIN_DATA)->EnableWindow(FALSE);
	
}

//数据存数据库
void CDlgUpdateStockData::OnBnClickedBtnSavedb()
{
	mListStock.ResetContent();
	mUpdateStockPos=0;
	SetTimer(UPDATE_EVENT_SAVE_DATA_TO_DB,50,0);
	GetDlgItem(IDC_BTN_SAVEDB)->EnableWindow(FALSE);
}
