// DlgBackFlow.cpp: 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgBackFlow.h"
#include "afxdialogex.h"
#include "Convert.h"
#include "StockDataMgr.h"
#include "KLineFilterAlg.h"
#include "IndustryDataMgr.h"
#include <thread>
#include <map>
#include <algorithm>
// CDlgBackFlow 对话框

IMPLEMENT_DYNAMIC(CDlgBackFlow, CDialogEx)

CDlgBackFlow::CDlgBackFlow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_BACKFLOW, pParent)
{
	::InitializeCriticalSection(&backFlowInfoLock);
}

CDlgBackFlow::~CDlgBackFlow()
{
}

void CDlgBackFlow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_BEGIN, mBeginDateCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, mEndDateCtrl);
	DDX_Control(pDX, IDC_LIST_BACKFLOW, mListBackFlow);
	DDX_Control(pDX, IDC_CMB_FIRST_FILTER, mCmbFirst);
	DDX_Control(pDX, IDC_CMB_SECOND_FILTER, mCmbSecond);
}


BEGIN_MESSAGE_MAP(CDlgBackFlow, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_BACKFLOW, &CDlgBackFlow::OnBnClickedBtnBackflow)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_SAVE, &CDlgBackFlow::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// CDlgBackFlow 消息处理程序


BOOL CDlgBackFlow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString strExpStockCode = "SH000001";
	pExpStockDayTable = StockDataMgr()->GetStockDayTable(strExpStockCode);

	mCmbFirst.ResetContent();
	int ret;

	ret = mCmbFirst.AddString("TAN配套4(启动均衡)");
	mCmbFirst.SetItemData(ret, FIRST_FILTTER_TAN4);

	ret = mCmbFirst.AddString("TAN配套6(选步长5)");
	mCmbFirst.SetItemData(ret, FIRST_FILTTER_TAN6);

	ret = mCmbFirst.AddString("TAN配套9");
	mCmbFirst.SetItemData(ret, FIRST_FILTTER_TAN9);

	ret = mCmbFirst.AddString("TAN配套3(均衡发展)");
	mCmbFirst.SetItemData(ret, FIRST_FILTTER_TAN3);

	ret = mCmbFirst.AddString("UserVlue");
	mCmbFirst.SetItemData(ret, FIRST_FILTTER_USERVALUE);

	mCmbFirst.SetCurSel(0);

	mCmbSecond.ResetContent();

	ret = mCmbSecond.AddString("无");
	mCmbSecond.SetItemData(ret, SECOND_FILTTER_NONE);

	ret = mCmbSecond.AddString("高人一等");
	mCmbSecond.SetItemData(ret, SECOND_FILTTER_HIGH_ONE);

	ret = mCmbSecond.AddString("卡均线中");
	mCmbSecond.SetItemData(ret, SECOND_FILTTER_AVE_LINE_BW_MIDDLE);
	mCmbSecond.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void do_backflow_thread(CDlgBackFlow* pDlgBackFlow)
{
	pDlgBackFlow->doBackFlow();
}

void CDlgBackFlow::OnBnClickedBtnBackflow()
{

	int	iItem = mCmbFirst.GetCurSel();
	if (iItem < 0) return;

	mFirstSelMode = mCmbFirst.GetItemData(iItem);

	iItem = mCmbSecond.GetCurSel();
	if (iItem < 0) return;
	mSecondSelMode = mCmbSecond.GetItemData(iItem);

	CTime mBeginTime, mEndTime;
	mBeginDateCtrl.GetTime(mBeginTime);
	mEndDateCtrl.GetTime(mEndTime);


	CString strTempBeginDate = pExpStockDayTable->GetNearestStockDayDate(mBeginTime);
	CString strTempEndDate = pExpStockDayTable->GetNearestStockDayDate(mEndTime);


	mBeginTime = ConverStringToCTime(strTempBeginDate);
	mEndTime = ConverStringToCTime(strTempEndDate);

	CTimeSpan span = mEndTime - mBeginTime;

	int iDay = span.GetDays();
	if (iDay <= 0)
	{
		AfxMessageBox("开始时间大于等于结束时间");
		return;
	}

	fTotalMoney = 100000.0;
	strTotalInfo = "";
	mBeginPos = pExpStockDayTable->GetNearestStockDayIndex(strTempBeginDate);
	mEndPos = pExpStockDayTable->GetNearestStockDayIndex(strTempEndDate);

	strBeginDate = strTempBeginDate;
	strEndDate = strTempEndDate;

	mBeginDateCtrl.SetTime(&mBeginTime);
	mEndDateCtrl.SetTime(&mEndTime);

	if (t_backflow.joinable())
		t_backflow.join();
	t_backflow = std::thread(do_backflow_thread, this);
	t_backflow.detach();
	mListBackFlow.ResetContent();
	SetTimer(EVENT_BACKFLOW_INFO, 10, 0);
}


static int CalcTanAngleDataValue(TanAngleData* pTanAngleData)
{
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


	if (pTanAngleData->strStockCode == "SZ002752")
	{
		int a = 0;
		a++;

	}


	int mValue = 0;


	if ((m_10_big_20_nums >= m_60_big_20_nums) && (f_ave_volume_per < 3.0 && f_ave_volume_per>1.0 && f_max_volume_per < 3.2) && (f_60_20_cross_price_increase < 50.0 && f_20_10_cross_price_increase < 50.0))
	{
		if (m_60_big_20_nums <= 10)
		{
			if (m_10_big_20_nums <= 20)
			{
				mValue += 50;

				if ((f_ma5_angle - f_ma10_angle) < -5.0)
					mValue -= 30;

				//if (f_ma60_angle < 1.0)
				//	mValue -= 30;
			}

			//if (mStepIndex > 0)
			//	mValue -= 30;

			if (mRsi1BigNums >= 2)
				mValue -= mRsi1BigNums * 5;

			if (mBigIncreaseNums >= 1)
				mValue -= mBigIncreaseNums * 5;

			if (f_ave_volume_per < 2.0 && f_max_volume_per < 2.0)
			{
				mValue += 20;
				if (mRsi1BigNums == 0)
					mValue += 10;

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

			if (f_ma5_angle > 70.0 || f_ma10_angle > 68.0)
				mValue -= 30;
		}

	}

	return mValue;


}

static bool CmpTanAngleData(TanAngleData* pTanAngleData1, TanAngleData* pTanAngleData2)
{
	int value1 = CalcTanAngleDataValue(pTanAngleData1);

	int value2 = CalcTanAngleDataValue(pTanAngleData2);

	if (value1 > value2)
		return true;

	return false;

}

bool CDlgBackFlow::doBackFlow(void)
{
	CString strInfo;
	strInfo.Format("开始 %s 回测", (LPCSTR)strBeginDate);
	AddBackFlowInfo(strInfo);

	while (true)
	{
		doOneBackFlow();
		mBackFlowNums++;

		int mPos = mBeginPos + mNowPassPos;//BUY_SALE_DAY * mBackFlowNums;
		if (mPos >= mEndPos)
		{
			doOneBackFlow();
			break;
		}
	}

	return true;
}

void CDlgBackFlow::AddBackFlowInfo(CString strInfo)
{
	BackFlowInfo* Info = new BackFlowInfo();
	Info->strInfo = strInfo;
	PushBackFlowInfo(Info);
}
void CDlgBackFlow::PushBackFlowInfo(BackFlowInfo* Info)
{
	LockBackFlowInfo();
	quQueueBackFlowInfo.push(Info);
	UnlockBackFlowInfo();
}

BackFlowInfo* CDlgBackFlow::PopBackFlowInfo(void)
{
	BackFlowInfo* backFlowInfo;
	LockBackFlowInfo();
	backFlowInfo = quQueueBackFlowInfo.pop();
	UnlockBackFlowInfo();
	return backFlowInfo;
}



void CDlgBackFlow::OnTimer(UINT_PTR nIDEvent)
{
	if (EVENT_BACKFLOW_INFO == nIDEvent)
	{
		doHandleBackFlowInfo();
	}
	CDialogEx::OnTimer(nIDEvent);
}



bool CDlgBackFlow::doHandleBackFlowInfo(void)
{
	BackFlowInfo* backFlowInfo = PopBackFlowInfo();
	if (backFlowInfo)
	{
		strTotalInfo += backFlowInfo->strInfo;
		strTotalInfo += "\n";
		mListBackFlow.AddString(backFlowInfo->strInfo);
		delete backFlowInfo;
		backFlowInfo = NULL;
	}
	return 0;

}

bool CDlgBackFlow::IsTanPerContiLow(void)
{
	if (vecTanPer.size() < 3)
		return false;

	int size = vecTanPer.size();
	double f_now = vecTanPer[size - 1];
	double f_p1= vecTanPer[size - 2];
	double f_p2= vecTanPer[size - 3];

	if (f_now < f_p1)
	{
		if (f_p2 < f_p1)
			return true;
	}

	return false;
}

bool CDlgBackFlow::IsTanPerContiHigh(void)
{
	if (vecTanPer.size() < 3)
		return false;

	int size = vecTanPer.size();
	double f_now = vecTanPer[size - 1];
	double f_p1 = vecTanPer[size - 2];
	double f_p2 = vecTanPer[size - 3];

	if (f_now > f_p1)
	{
		if (f_p1 > f_p2)
			return true;
	}

	return false;

}

bool CDlgBackFlow::doOneBackFlow(void)
{


	CString strNowDate = CalcNowDate();
	if (strNowDate == "")
		return false;

	fTotalMoney = SaleStock(strNowDate);


	Vec_TanAngleData vecTanAngleData;
	CTime mNowDate = ConverStringToCTime(strNowDate);
	CTanAngleAlg* pNowTanAngleAlg = new CTanAngleAlg();

	int mBackDays = 5;
	int mMaxAngle = 90;
	double f_max_volume_multiple = 10.0;
	bool bIgnoreM5 = true;//false;
	bool bUseM120 = false;
	bool bUseAllUp = false;
	int mMaxInsBack = 8;
	double f_max_ins_thes = 6.0;

	vecTanAngleData = pNowTanAngleAlg->doFilter(mNowDate, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
	std::sort(vecTanAngleData.begin(), vecTanAngleData.end(), CmpTanAngleData);

	int mStockCodeSize = StockDataMgr()->GetStockCodeListSize();
	f_Tan_Per = (vecTanAngleData.size() * 100.0) / mStockCodeSize;
	vecTanPer.push_back(f_Tan_Per);
	industyMapAllNum.clear();

	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		int mValue = CalcTanAngleDataValue(vecTanAngleData[i]);
		vecTanAngleData[i]->mUserCalcedValue = mValue;
		std::string strCode = (LPCSTR)vecTanAngleData[i]->strStockCode;
		std::vector<std::string> vecIndusty = IndustryDataMgr()->FindIndustryByStockCode(strCode);
		if (vecIndusty.size() > 0)
		{
			industyMapAllNum[vecIndusty[0]]++;
		}
	}


	VecStockTempInfo vecStock5;
	if (mFirstSelMode == FIRST_FILTTER_TAN4)
		vecStock5 = DoFilterTanMatch4(vecTanAngleData);
	else if (mFirstSelMode == FIRST_FILTTER_TAN6)
		vecStock5 = DoFilterTanMatch6(vecTanAngleData);
	else if (mFirstSelMode == FIRST_FILTTER_TAN9)
		vecStock5 = DoFilterTanMatch9(vecTanAngleData);
	else if (mFirstSelMode == FIRST_FILTTER_TAN3)
		vecStock5 = DoFilterKLinePregnant(vecTanAngleData);
	else
		vecStock5 = DoFilterUserValue(vecTanAngleData);

	VecStockTempInfo result;
	if (mSecondSelMode == SECOND_FILTTER_HIGH_ONE)
		result = DoFilterKLineBadFilter(vecStock5, mNowDate);
	else if (mSecondSelMode == SECOND_FILTTER_AVE_LINE_BW_MIDDLE)
		result = DoFilterKLineNineTurn(vecStock5, mNowDate);
	else
		result = vecStock5;

	if (result.size() == 0)
	{
		CString strInfo;
		strInfo.Format("%s 没有发现符合条件股票", (LPCSTR)strNowDate);
		AddBackFlowInfo(strInfo);
		mNowPassPos += 1;
	}
	else
	{
		BuyStock(result, strNowDate);
		mNowPassPos += BUY_SALE_DAY;
	}
	return true;
}

bool CDlgBackFlow::BuyStock(VecStockTempInfo& vecResult, CString strDate)
{
	if (vecResult.size() == 0)
		return false;
	//int mPos = pExpStockDayTable->GetStockDayIndex(strDate);



	vecHoldStockInfo.clear();
	double f_one_money = fTotalMoney / vecResult.size();
	CStockDayTable* pStockDayTable = NULL;
	for (int i = 0; i < vecResult.size(); i++)
	{
		pStockDayTable = StockDataMgr()->GetStockDayTable(vecResult[i]);
		int pos = pStockDayTable->GetStockDayIndex(strDate);
		CStockDayData* pStockNowDayData = pStockDayTable->GetStockDayDataByIndex(pos);
		CString strNowStockDate = pStockNowDayData->GetDate();
		double f_now_price = pStockNowDayData->GetEndPrice();
		CStockDayData* pStockDayData = pStockDayTable->GetStockDayDataByIndex(pos + 1);
		if (pStockDayData)
		{
			double f_price = ( pStockDayData->GetMaxPrice()- pStockDayData->GetMinPrice())/3.0+ pStockDayData->GetMinPrice(); //GetBeginPrice  //GetEndPrice
			double f_increase_per = (f_price - f_now_price) * 100.0 / f_now_price;
			BOOL b_increase_limit = false;
			if (vecResult[i].Left(3) == "SH6" || vecResult[i].Left(3) == "SZ0")
			{
				if (f_increase_per > 9.92)
					b_increase_limit = true;
			}
			else
			{
				if (f_increase_per > 19.92)
					b_increase_limit = true;
			}
			double f_HoldNums = f_one_money / f_price;
			if (!b_increase_limit)
			{
				HoldStockInfo* pHoldStockInfo = new HoldStockInfo();
				pHoldStockInfo->fHoldNums = f_HoldNums;
				pHoldStockInfo->fStockPrice = f_price;
				pHoldStockInfo->strStockCode = vecResult[i];
				vecHoldStockInfo.push_back(pHoldStockInfo);
				fTotalMoney -= f_one_money;
				if (fTotalMoney < 0.0)
					fTotalMoney = 0.0;
			}

			CString strStockDate = pStockDayData->GetDate();
			CString strStockName = StockDataMgr()->GetStockName(vecResult[i]);

			CString strInfo;
			if (b_increase_limit)
			{
				strInfo.Format("%s %s %s 开盘涨停 %.2f ,无法购买", (LPCSTR)strStockDate, (LPCSTR)vecResult[i], (LPCSTR)strStockName, f_increase_per);
			}
			else
			{
				strInfo.Format("%s 发现 %s 购买 %s %s %.2f股 单价 %.2f元,剩余资金 %.2f", (LPCSTR)strNowStockDate,(LPCSTR)strStockDate, (LPCSTR)vecResult[i], (LPCSTR)strStockName,
					f_HoldNums, f_price, fTotalMoney);
			}
			AddBackFlowInfo(strInfo);
		}

	}

	return true;
}

double  CDlgBackFlow::SaleStock(CString strDate)
{
	HoldStockInfo* pHoldStockInfo = NULL;
	CStockDayTable* pStockDayTable = NULL;
	for (int i = 0; i < vecHoldStockInfo.size(); i++)
	{
		pHoldStockInfo = vecHoldStockInfo[i];
		double f_pre_one_price = pHoldStockInfo->fHoldNums * pHoldStockInfo->fStockPrice;
		pStockDayTable = StockDataMgr()->GetStockDayTable(pHoldStockInfo->strStockCode);
		int pos = pStockDayTable->GetStockDayIndex(strDate);
		CStockDayData* pStockDayData = pStockDayTable->GetStockDayDataByIndex(pos);
		CStockDayData* pP1StockDayData = pStockDayTable->GetStockDayDataByIndex(pos-1);
		double f_price = 2.0*(pStockDayData->GetMaxPrice() - pStockDayData->GetMinPrice()) / 3.0 + pStockDayData->GetMinPrice();//pStockDayData->GetEndPrice();
		double f_p1_low_price = pP1StockDayData->GetMinPrice();
		double f_p1_high_price = pP1StockDayData->GetMaxPrice();
		double f_low_price = pStockDayData->GetMinPrice();
		double f_high_price = pStockDayData->GetMaxPrice();

		double f_now_one_price = f_price * pHoldStockInfo->fHoldNums;
		double f_p1_low_one_price = f_p1_low_price * pHoldStockInfo->fHoldNums;
		double f_p1_high_one_price = f_p1_high_price * pHoldStockInfo->fHoldNums;
		double f_low_one_price = f_low_price * pHoldStockInfo->fHoldNums;
		double f_high_one_price = f_high_price * pHoldStockInfo->fHoldNums;

		double f_per = (f_now_one_price - f_pre_one_price) * 100.0 / f_pre_one_price;
		double f_p1_low_per= (f_p1_low_one_price - f_pre_one_price) * 100.0 / f_pre_one_price;
		double f_p1_high_per = (f_p1_high_one_price - f_pre_one_price) * 100.0 / f_pre_one_price;

		double f_low_per = (f_low_one_price - f_pre_one_price) * 100.0 / f_pre_one_price;
		double f_high_per = (f_high_one_price - f_pre_one_price) * 100.0 / f_pre_one_price;


		bool bLowUp7 = false;
		/*if ( f_p1_low_per<-7.0 || f_low_per<-7.0)
		{
			bLowUp7 = true;
			f_now_one_price = 0.93 * f_pre_one_price;
		}*/

		bool bHighUp10 = false;
		/*if (f_p1_high_per > 10.0 || f_high_per > 10.0)
		{
			bHighUp10 = true;
			f_now_one_price = 1.1 * f_pre_one_price;
		}*/

		f_now_one_price = f_now_one_price * 0.9985;		//手续费，印花税
		fTotalMoney += f_now_one_price;
		CString strStockName = StockDataMgr()->GetStockName(pHoldStockInfo->strStockCode);
		CString strInfo;
		if(bLowUp7)
			strInfo.Format("%s 亏损超-7 中途强制卖出 %s %s %.2f股 单价 %.2f元,盈利 %.2f,(实际-7.0),剩余资金 %.2f", (LPCSTR)strDate, (LPCSTR)pHoldStockInfo->strStockCode, (LPCSTR)strStockName,
				pHoldStockInfo->fHoldNums, f_price, f_per, fTotalMoney);
		else if(bHighUp10)
			strInfo.Format("%s 盈利>10 中途卖出 %s %s %.2f股 单价 %.2f元,盈利 %.2f,(实际10.0),剩余资金 %.2f", (LPCSTR)strDate, (LPCSTR)pHoldStockInfo->strStockCode, (LPCSTR)strStockName,
				pHoldStockInfo->fHoldNums, f_price, f_per, fTotalMoney);
		else
			strInfo.Format("%s 卖出 %s %s %.2f股 单价 %.2f元,盈利 %.2f,剩余资金 %.2f", (LPCSTR)strDate, (LPCSTR)pHoldStockInfo->strStockCode, (LPCSTR)strStockName,
				pHoldStockInfo->fHoldNums, f_price, f_per, fTotalMoney);
		AddBackFlowInfo(strInfo);

	}

	for (int i = 0; i < vecHoldStockInfo.size(); i++)
	{
		delete vecHoldStockInfo[i];
		vecHoldStockInfo[i] = NULL;
	}
	vecHoldStockInfo.clear();


	return fTotalMoney;
}
CString CDlgBackFlow::CalcNowDate(void)
{
	int mNowPos = mBeginPos + mNowPassPos;// BUY_SALE_DAY* mBackFlowNums;
	if (mNowPos >= mEndPos)
		mNowPos = mEndPos;
	CStockDayData* pStockDayData;
	pStockDayData = pExpStockDayTable->GetStockDayDataByIndex(mNowPos);
	if (pStockDayData)
		return pStockDayData->GetDate();
	return "";
}


VecStockTempInfo CDlgBackFlow::DoFilterTanMatch4(Vec_TanAngleData& vecTanAngleData)
{
	VecStockTempInfo vecStockTempInfo;
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
		double fVolumePer = pTanAngleData->fVolumePer;
		double fVolumePerForM5 = pTanAngleData->fVolumePerForM5;
		if (mBigIncreaseNums > 0 || mRsi1BigNums > 2)
			continue;

		double f_per = f_20_10_cross_price_increase / m_10_big_20_nums;
		if (f_per > 1.2)
			continue;
		f_per = f_60_20_cross_price_increase / m_60_big_20_nums;
		if (f_per > 1.2)
			continue;

		if (f_ave_volume_per > 2.6)
			continue;

		if (m_continus_price_m10_up_nums > 20 || m_continus_price_m20_up_nums > 20 || m_continus_price_m60_up_nums > 20)
			continue;

		//if (fVolumePer > 1.8)
		//	continue;

		vecStockTempInfo.push_back(pTanAngleData->strStockCode);



	}


	return vecStockTempInfo;
}


VecStockTempInfo CDlgBackFlow::DoFilterKLineBadFilter(VecStockTempInfo& vecStockTempInfo, CTime mNowDate)
{
	VecStockTempInfo result;

	for (int i = 0; i < vecStockTempInfo.size(); i++)
	{
		CString strStockCode = vecStockTempInfo[i];
		CString strStockName = StockDataMgr()->GetStockName(strStockCode);

		CKLineFilterAlg  mKLineFilterAlg;

		Vec_KLineFilterData2 vecKLineFilterData2 = mKLineFilterAlg.doFilter2(strStockCode, strStockName, mNowDate);

		if (!CKLineFilterAlg::IsKLineBadTrend(vecKLineFilterData2))
		{
			result.push_back(strStockCode);
		}
		CKLineFilterAlg::FreeVecKLineFilterData2(vecKLineFilterData2);
	}

	return result;
}



VecStockTempInfo CDlgBackFlow::DoFilterTanMatch6(Vec_TanAngleData& vecTanAngleData)
{

	VecStockTempInfo vecStockTempInfo;
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
		double fVolumePer = pTanAngleData->fVolumePer;
		double fVolumePerForM5 = pTanAngleData->fVolumePerForM5;



		bool bok1 = false;
		if (m_10_big_20_nums >= 6 && m_10_big_20_nums <= 16)
			bok1 = true;


		bool bok2 = false;
		if (m_60_big_20_nums >= 1 && m_60_big_20_nums <= 8)
			bok2 = true;

		bool bok3 = false;
		double f_temp = f_ma10_angle - f_ma20_angle;

		double f_temp2 = fabs(f_ma5_angle - f_ma10_angle);
		double f_temp3 = f_temp / f_temp2;
		if (f_temp3 > 6.0)
			bok3 = true;

		bool bok4 = false;
		//if (fVolumePer <= 1.8)
		//	bok4 = true;

		if (bok1 && bok2 && bok3) //&& bok4
		{

			vecStockTempInfo.push_back(pTanAngleData->strStockCode);
		}
		else
			continue;

	}

	return vecStockTempInfo;

}


VecStockTempInfo CDlgBackFlow::DoFilterKLineNineTurn(VecStockTempInfo& vecStockTempInfo, CTime mNowDate)
{

	VecStockTempInfo result;

	for (int i = 0; i < vecStockTempInfo.size(); i++)
	{
		CString strStockCode = vecStockTempInfo[i];
		CString strStockName = StockDataMgr()->GetStockName(strStockCode);

		CKLineFilterAlg  mKLineFilterAlg;

		Vec_KLineFilterData2 vecKLineFilterData2 = mKLineFilterAlg.doFilter2(strStockCode, strStockName, mNowDate);

		if (CKLineFilterAlg::IsKLineNineTurn(vecKLineFilterData2))
		{
			result.push_back(strStockCode);
		}
		CKLineFilterAlg::FreeVecKLineFilterData2(vecKLineFilterData2);
	}


	return result;
}

VecStockTempInfo CDlgBackFlow::DoFilterTanMatch9(Vec_TanAngleData& vecTanAngleData)
{
	VecStockTempInfo vecStockTempInfo;
	TanAngleData* pTanAngleData = NULL;

	int mOkNums = 0;
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
		int mUserCalcedValue = pTanAngleData->mUserCalcedValue;
		double fcustomtotalvalue = pTanAngleData->fcustomtotalvalue;
		fcustomtotalvalue = fabs(fcustomtotalvalue);
		double f_max_increase = f_60_20_cross_price_increase;
		if (f_max_increase < f_20_10_cross_price_increase)
			f_max_increase = f_20_10_cross_price_increase;

		double f_custom_per = fcustomtotalvalue / f_max_increase;

		double f_max_vol_per = fVolumePerForM30;
		if (f_max_vol_per < fVolumePerForM20)
			f_max_vol_per = fVolumePerForM20;

		bool bOrder = false;
		if (fVolumePerForM5 < fVolumePer)
		{
			if (fVolumePer < fVolumePerForM20)
				bOrder = true;
		}
	
		bool bOk = false;
		bool bDnPass = false;
		int size = pTanAngleData->vec_close_value.size();
		double f_close_price=pTanAngleData->vec_close_value[size - 1];
		double f_pre_close_price = pTanAngleData->vec_close_value[size - 2];
		double f_close_per = (f_close_price - f_pre_close_price) * 100.0 / f_pre_close_price;
		if (f_close_per < -5.0)
		{
			if (f_ma5_angle > 65.0)
				bDnPass = true;
		}

		double f_per_2 = f_60_20_cross_price_increase / m_60_big_20_nums;
		double f_per_1 = f_20_10_cross_price_increase / m_10_big_20_nums;

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
		if (f_temp > 0.05)
			bOk3 = true;

		bool bOk4 = false;
		if (mBigIncreaseNums < 1 && mRsi1BigNums < 1)
			bOk4 = true;
		//bool bOk5 = false;
		//if(mVolM5ContiUpNums<=5&& mVolM10ContiUpNums<=10)
		//	bOk5 = true;
		double fMinRsi3 = pTanAngleData->fMinRsi3;
		double fMinRsi1 = pTanAngleData->fMinRsi1;
		mMinRsi3Interval = pTanAngleData->mMinRsi3Interval;
		bool bOk6 = false;
		if (fMinRsi1 < 19.0 && fMinRsi3 < 38.0)//&& mMinRsi3Interval <= 45
		{
			bOk6 = true;
		}
#else
		int mIndustyNums = 0;
		std::string strIndustryName = "";
		int mIndustryStockNums = 0;
		double f_industry_per = 0.0;
		std::vector<std::string> vecIndusty = IndustryDataMgr()->FindIndustryByStockCode((LPCSTR)pTanAngleData->strStockCode);
		if (vecIndusty.size() > 0)
		{
			strIndustryName = vecIndusty[0];
			mIndustyNums = industyMapAllNum[vecIndusty[0]];
			mIndustryStockNums = IndustryDataMgr()->GetIndustryStockNums(strIndustryName);
			f_industry_per = (double)mIndustyNums * 100.0 / (double)mIndustryStockNums;
		}

		double fMinRsi1 = pTanAngleData->fMinRsi1;
		int    mMinRsi3Interval = pTanAngleData->mMinRsi3Interval;

	
	//	if(fMinRsi1<10.0 && mMinRsi3Interval<30 && m_60_big_20_nums < 5 && m_10_big_20_nums < 15 && f_ma60_angle <= 0.0 && f_custom_per < 2.0 && f_max_vol_per < 4.0 && mOkNums <= 3)
		if (m_60_big_20_nums < 5 && m_10_big_20_nums < 15 && f_ma60_angle <= 0.0 && fcustomtotalvalue>0 && mOkNums <= 3 && (f_industry_per > 10.0))
		//if (m_60_big_20_nums < 5 && m_10_big_20_nums < 15 && f_ma60_angle <= 10.0 && f_custom_per < 2.5 && f_max_vol_per < 3.0 && f_per_1 < 3.0 && mOkNums <= 3 && (f_industry_per > 10.0))
	//	if (bOk && bOk2 && bOk4 && (f_cur_rsi_1 < 90.0) && (f_industry_per < 5.0)) //&& bOk6  
		//210922  21-1-6 22-4-1 173625
		//if(mUserCalcedValue>=80 && f_industry_per>=10.0 && mOkNums <= 2)
		//210922  21-1-6 22-4-1
		//if (m_60_big_20_nums < 5 && m_10_big_20_nums < 15 && f_ma60_angle <=0.0 && f_custom_per<1.5  && f_max_vol_per <2.0 && f_per_1<2.0 && mOkNums<=3 && (f_industry_per>10.0))  //7.0
		//189313
		//if (m_60_big_20_nums < 5 && m_10_big_20_nums < 15 && f_ma60_angle <= 0.0 && f_custom_per < 2.0 && f_max_vol_per < 4.0 && mOkNums <= 3 && (f_industry_per > 10.0 && f_industry_per<65.0))
		
		//112664
		//if (m_60_big_20_nums < 5 && m_10_big_20_nums < 15 && f_ma60_angle <= 0.0 && f_custom_per < 2.0 && f_max_vol_per < 4.0 && mOkNums <= 3 && (f_industry_per > 20.0))
		
		//138002
		//if (m_60_big_20_nums < 5 && m_10_big_20_nums < 15 && f_ma60_angle <= 0.0 && f_custom_per < 2.0 && f_max_vol_per < 4.0 && mOkNums <= 3 && (f_industry_per > 10.0 && f_industry_per<20.0))
		
		//174054
		//if (m_60_big_20_nums < 5 && m_10_big_20_nums < 15 && f_ma60_angle <= 0.0 && f_custom_per < 2.0 && f_max_vol_per < 4.0 && mOkNums <= 3 && (f_industry_per > 5.0 ))

		//186148
		//if (m_60_big_20_nums < 5 && m_10_big_20_nums < 15 && f_ma60_angle <= 0.0 && f_custom_per < 2.0 && f_max_vol_per < 4.0 && mOkNums <= 3 && (f_industry_per > 15.0))
#endif

		{

			vecStockTempInfo.push_back(pTanAngleData->strStockCode);
			mOkNums++;
		}
		else
		{
			continue;
		}
	}

	return vecStockTempInfo;

}

VecStockTempInfo CDlgBackFlow::DoFilterKLinePregnant(Vec_TanAngleData& vecTanAngleData)
{
	VecStockTempInfo vecStockTempInfo;
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

		double fcustomtotalvalue = pTanAngleData->fcustomtotalvalue;



		bool bOk = false;



		if (mNowIsMaxPriceNums >= 80)
		{

			if (m_continus_price_m60_up_nums < 20 && m_60_big_20_nums < 20)
			{
				
				if(m_continus_price_m20_up_nums<20 && m_continus_price_m10_up_nums<20 && mPriceM5ContiUpNums<20)
				//if (f_cur_rsi_1 > 90.0)
				{
					double f_per0 = f_20_10_cross_price_increase / m_10_big_20_nums;

					double f_per1 = f_60_20_cross_price_increase / m_60_big_20_nums;

					double f_max = f_60_20_cross_price_increase;
					if (f_20_10_cross_price_increase > f_max)
						f_max = f_20_10_cross_price_increase;
					mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;
					if (f_max < 30.0 && mVolM10ContiUpNums<10)
					{
						double fVolumePerForM5 = pTanAngleData->fVolumePerForM5;
						double fVolumePerForM20 = pTanAngleData->fVolumePerForM20;
						double fVolumePer = pTanAngleData->fVolumePer;
						double fVolumePerForM30 = pTanAngleData->fVolumePerForM30;

						if(fVolumePerForM30 > fVolumePerForM20 && fVolumePerForM30> fVolumePerForM5 && fVolumePerForM20> fVolumePerForM5 && fVolumePerForM30 < 4.5)
						//if (fVolumePerForM30 > fVolumePer && fVolumePer > fVolumePerForM5 && fVolumePerForM30 < 5.0)
						{
							if (f_per0 < 4.5 && f_per1 < 4.5)
							{
								if (f_ave_volume_per < 5.0)
								{
									bOk = true;
								}
							}
						}
					}
					
					
				}


			}

		}

		if (bOk)
		{
			vecStockTempInfo.push_back(pTanAngleData->strStockCode);


		}


	}

	return vecStockTempInfo;
}

VecStockTempInfo CDlgBackFlow::DoFilterUserValue(Vec_TanAngleData& vecTanAngleData)
{
	VecStockTempInfo vecStockTempInfo;
	TanAngleData* pTanAngleData = NULL;
	for (int i = 0; i < vecTanAngleData.size(); i++)
	{
		pTanAngleData = vecTanAngleData[i];
		double fVolumePerForM30 = pTanAngleData->fVolumePerForM30;
		double fVolumePerForM20 = pTanAngleData->fVolumePerForM20;
		double fVolumePer = pTanAngleData->fVolumePer;
		double fVolumePerForM5 = pTanAngleData->fVolumePerForM5;
		double f_20_10_cross_price_increase = pTanAngleData->fPara7;
		double f_60_20_cross_price_increase = pTanAngleData->fPara6;
		int m_10_big_20_nums = pTanAngleData->mPara6;
		int m_60_big_20_nums = pTanAngleData->mPara7;
		if(fVolumePerForM30> fVolumePerForM20 && fVolumePerForM20> fVolumePer && fVolumePer> fVolumePerForM5)
		{
			double f_per = f_20_10_cross_price_increase / m_10_big_20_nums;
			double f_per2 = f_60_20_cross_price_increase / m_60_big_20_nums;
			if (f_per > f_per2 && f_per<4.95)
			{
				int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
				int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
				int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
				int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
				if (m_continus_price_m60_up_nums < 10 && m_continus_price_m20_up_nums < 15 && m_continus_price_m10_up_nums < 15 && mPriceM5ContiUpNums < 15)
				{
					double f_ave_volume_per = pTanAngleData->fPara5;
					if (f_ave_volume_per < 4.0 && fVolumePerForM30 < 4.5)
						vecStockTempInfo.push_back(pTanAngleData->strStockCode);
				}
			}
		}
		/*if (pTanAngleData->mUserCalcedValue >= 80)
		{
			vecStockTempInfo.push_back(pTanAngleData->strStockCode);
		}*/
	}
	return vecStockTempInfo;
}

void CDlgBackFlow::OnBnClickedBtnSave()
{
	CString m_path;
	static TCHAR szFilter[] =
		_T("Txt Files (*.txt)|*.txt|");

	CFileDialog hFileDlg(FALSE, "*.txt", NULL,
		OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST,
		szFilter,
		NULL);
	if (hFileDlg.DoModal() == IDOK)
	{
		m_path = hFileDlg.GetPathName();
		UpdateData(FALSE);
		CStdioFile saveFile;




		if (saveFile.Open(m_path, CFile::modeCreate | CFile::modeWrite))
		{
			saveFile.WriteString(strTotalInfo);
			saveFile.Close();
		}


	}

}
