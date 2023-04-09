// DlgCalcuInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgCalcuInfo.h"
#include "afxdialogex.h"


// CDlgCalcuInfo 对话框

IMPLEMENT_DYNAMIC(CDlgCalcuInfo, CDialogEx)

CDlgCalcuInfo::CDlgCalcuInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCalcuInfo::IDD, pParent)
{
	pCalcuData=NULL;
}

CDlgCalcuInfo::~CDlgCalcuInfo()
{
}

void CDlgCalcuInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INFO, mDataInfoListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgCalcuInfo, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgCalcuInfo 消息处理程序


BOOL CDlgCalcuInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mDataInfoListCtrl.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT ); //设置报表风格


	mDataInfoListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 

	mDataInfoListCtrl.InsertColumn( CALCUINFO_COLUMN_ID, "顺序ID号", LVCFMT_LEFT, 60 );
	mDataInfoListCtrl.InsertColumn( CALCUINFO_COLUMN_STOCK_CODE, "股票代码", LVCFMT_LEFT, 90 );
	mDataInfoListCtrl.InsertColumn( CALCUINFO_COLUMN_STOCK_NAME, "股票名称", LVCFMT_LEFT, 90 );

	mDataInfoListCtrl.InsertColumn( CALCUINFO_COLUMN_ANGLE, "角度", LVCFMT_LEFT, 200 );
	mDataInfoListCtrl.InsertColumn( CALCUINFO_COLUMN_INFO_1, "信息1", LVCFMT_LEFT, 200 );
	mDataInfoListCtrl.InsertColumn( CALCUINFO_COLUMN_INFO_2, "信息2", LVCFMT_LEFT, 200 );
	mDataInfoListCtrl.InsertColumn( CALCUINFO_COLUMN_INFO_3, "信息3", LVCFMT_LEFT, 200 );

	SetTimer(CALCUINFOEVENT_REFRESH_DATA,300,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL CDlgCalcuInfo::RefreshData(void)
{
	CString strConv,strTemp;
	int nRow;
	mDataInfoListCtrl.DeleteAllItems();
	
	Vec_TanAngleData vecTanAngleData;
	TanAngleData *pTanAngleData=NULL;
	for(int i=0;i<pCalcuData->vecTanAngleData.size();i++)
	{
		pTanAngleData=pCalcuData->vecTanAngleData[i];
		if(pTanAngleData->mCalcuSel>0)
			vecTanAngleData.push_back(pCalcuData->vecTanAngleData[i]);
	}


	int i=0;
	
	for(i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];
		
		strConv.Format("%4d",i+1);
		nRow=i;
		if(nRow>=mDataInfoListCtrl.GetItemCount())
			mDataInfoListCtrl.InsertItem(i,strConv);
		else
			mDataInfoListCtrl.SetItemText(nRow, CALCUINFO_COLUMN_ID,strConv);

		mDataInfoListCtrl.SetItemText(nRow, CALCUINFO_COLUMN_STOCK_CODE,pTanAngleData->strStockCode);
		mDataInfoListCtrl.SetItemText(nRow, CALCUINFO_COLUMN_STOCK_NAME,pTanAngleData->strStockName);
		//printf("%s  %s\n",pTanAngleData->strStockCode,pTanAngleData->strStockName);
		
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
		int mBigIncreaseNums=pTanAngleData->mBigIncreaseNums;
		int mRsi1BigNums=pTanAngleData->mRsi1BigNums;
		int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;
		int mNextGrow=pTanAngleData->mNextGrow;
		double fNextGrow=pTanAngleData->fNextGrow;
		double f_cur_rsi_1=pTanAngleData->fRsi1;

		CString strInfo;

		strInfo.Format("%.2f,  %.2f,  %.2f,  %.2f",f_ma60_angle,f_ma20_angle,f_ma10_angle,f_ma5_angle);
		mDataInfoListCtrl.SetItemText(nRow, CALCUINFO_COLUMN_ANGLE,strInfo);
		
		strInfo.Format("max:%.2f,%d,ave:%.2f,  up%.2f  %.2f   %.2f",f_max_volume_per,m_max_volume_distance,f_ave_volume_per,f_20_10_cross_price_increase,f_60_20_cross_price_increase,f_60_day_increase);
		mDataInfoListCtrl.SetItemText(nRow, CALCUINFO_COLUMN_INFO_1,strInfo);


		strInfo.Format("%d,%d   %d,%d,%d  #%d#%d#rb%d#rsi%.2f",m_10_big_20_nums,m_60_big_20_nums,m_continus_price_m10_up_nums,m_continus_price_m20_up_nums,m_continus_price_m60_up_nums,mNowIsMaxPriceNums,mBigIncreaseNums,mRsi1BigNums,f_cur_rsi_1);
		mDataInfoListCtrl.SetItemText(nRow, CALCUINFO_COLUMN_INFO_2,strInfo);
		
		if(mNextGrow==0)
			strInfo.Format("后三日负增长%.2f",fNextGrow);
		else
			strInfo.Format("后三日增长%.2f",fNextGrow);
		mDataInfoListCtrl.SetItemText(nRow, CALCUINFO_COLUMN_INFO_3,strInfo);
		
		mDataInfoListCtrl.SetItemData(nRow,reinterpret_cast<DWORD_PTR>(pTanAngleData));

	}

	if(i<mDataInfoListCtrl.GetItemCount())
	{
		for(int j=i;j<mDataInfoListCtrl.GetItemCount();j++)
			mDataInfoListCtrl.DeleteItem(j);
	}

	return TRUE;
}


void CDlgCalcuInfo::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==CALCUINFOEVENT_REFRESH_DATA)
	{
		KillTimer(CALCUINFOEVENT_REFRESH_DATA);
		RefreshData();
	}
	CDialogEx::OnTimer(nIDEvent);
}
