// DlgStockPriceDestribute.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgStockPriceDestribute.h"
#include "afxdialogex.h"
#include "StockDataMgr.h"

// CDlgStockPriceDestribute 对话框

IMPLEMENT_DYNAMIC(CDlgStockPriceDestribute, CDialogEx)

CDlgStockPriceDestribute::CDlgStockPriceDestribute(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgStockPriceDestribute::IDD, pParent)
{
	pStockProfitLossData=NULL;
	mDestributeDayNums=0;
}

CDlgStockPriceDestribute::~CDlgStockPriceDestribute()
{
}

void CDlgStockPriceDestribute::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STOCK_UP, mEditStockUp);
	DDX_Control(pDX, IDC_EDIT_STOCK_DOWN, mEditStockDown);
	DDX_Control(pDX, IDC_COMBO_DAYNUMS, mCmbDayNums);
}


BEGIN_MESSAGE_MAP(CDlgStockPriceDestribute, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_RECALC, &CDlgStockPriceDestribute::OnBnClickedBtnRecalc)
END_MESSAGE_MAP()


// CDlgStockPriceDestribute 消息处理程序


BOOL CDlgStockPriceDestribute::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if(pStockProfitLossData==NULL)
		return FALSE;


	mCmbDayNums.ResetContent();
	int ret=mCmbDayNums.AddString("240日(总周期240日)");
	mCmbDayNums.SetItemData(ret,STOCKPRICE_DESTRIBUTE_240);

	ret=mCmbDayNums.AddString("20日(总周期240日)");
	mCmbDayNums.SetItemData(ret,STOCKPRICE_DESTRIBUTE_20);

	ret=mCmbDayNums.AddString("30日(总周期240日)");
	mCmbDayNums.SetItemData(ret,STOCKPRICE_DESTRIBUTE_30);

	ret=mCmbDayNums.AddString("40日(总周期240日)");
	mCmbDayNums.SetItemData(ret,STOCKPRICE_DESTRIBUTE_40);

	ret=mCmbDayNums.AddString("60日(总周期240日)");
	mCmbDayNums.SetItemData(ret,STOCKPRICE_DESTRIBUTE_60);

	ret=mCmbDayNums.AddString("120日(总周期240日)");
	mCmbDayNums.SetItemData(ret,STOCKPRICE_DESTRIBUTE_120);

	mCmbDayNums.SetCurSel(0);


	AnalysisStockProfitLossData();



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



BOOL CDlgStockPriceDestribute::AnalysisStockProfitLossData(void)
{
	CString strNowDate=pStockProfitLossData->strEndDate;
	CString strStockCode=pStockProfitLossData->strStockCode;
	CStockDayTable *pStockDayTable=NULL;

	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);


	if(!pStockDayTable)
		return FALSE;

	int mPos=pStockDayTable->GetStockDayIndex(strNowDate);

	if(mPos<0)
		return FALSE;

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

		long long mVolume=pStockProfitLossData->GetStockVolumeBwPrice(f_low_price,f_high_price,mDestributeDayNums);
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
	mEditStockUp.SetWindowText(strUpTotalInfo);

	CString strDownTotalInfo="";
	long long mDownTotalVolume=0;
	for(int i=0;i<50;i++)
	{
		double f_low_price,f_high_price;
		f_high_price=f_now_price-(i*f_down_per_range);
		f_low_price=f_now_price-((i+1)*f_down_per_range);

		long long mVolume=pStockProfitLossData->GetStockVolumeBwPrice(f_low_price,f_high_price,mDestributeDayNums);
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

	mEditStockDown.SetWindowText(strDownTotalInfo);

	CString strStockInfo;
	CString strStockName=StockDataMgr()->GetStockName(strStockCode);

	double f_up_total_rang=((double)mUpTotalVolume*100.0)/(double)(mUpTotalVolume+mDownTotalVolume);

	double f_down_total_rang=((double)mDownTotalVolume*100.0)/(double)(mUpTotalVolume+mDownTotalVolume);

	strStockInfo.Format("%s   %s  总股本 %I64d  现股价  %.2f  高于占 %.2f  低于占 %.2f ",strStockCode,strStockName,pStockProfitLossData->mTotalStockVolume,f_now_price,f_up_total_rang,f_down_total_rang);

	GetDlgItem(IDC_STATIC_STOCK)->SetWindowText(strStockInfo);
	return TRUE;
}

//重新计算
void CDlgStockPriceDestribute::OnBnClickedBtnRecalc()
{
	int iItem = mCmbDayNums.GetCurSel();
	if(iItem<0) return ;
	int mType=mCmbDayNums.GetItemData(iItem);

	switch(mType)
	{
	case STOCKPRICE_DESTRIBUTE_240:
		mDestributeDayNums=0;
		break;
	case STOCKPRICE_DESTRIBUTE_20:
		mDestributeDayNums=20;
		break;
	case STOCKPRICE_DESTRIBUTE_30:
		mDestributeDayNums=30;
		break;
			
	case STOCKPRICE_DESTRIBUTE_40:
		mDestributeDayNums=40;
		break;

	case STOCKPRICE_DESTRIBUTE_60:
		mDestributeDayNums=60;
		break;

	case STOCKPRICE_DESTRIBUTE_120:
		mDestributeDayNums=120;
		break;

	default:
		return;
	}

	mEditStockUp.Clear();
	mEditStockDown.Clear();

	AnalysisStockProfitLossData();
}
