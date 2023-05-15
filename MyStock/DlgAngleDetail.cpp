// DlgAngleDetail.cpp: 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgAngleDetail.h"
#include "afxdialogex.h"


// CDlgAngleDetail 对话框

IMPLEMENT_DYNAMIC(CDlgAngleDetail, CDialogEx)

CDlgAngleDetail::CDlgAngleDetail(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIG_ANGLE_DETARL, pParent)
{

}

CDlgAngleDetail::~CDlgAngleDetail()
{
}

void CDlgAngleDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mListDetail);
}


BEGIN_MESSAGE_MAP(CDlgAngleDetail, CDialogEx)
END_MESSAGE_MAP()


// CDlgAngleDetail 消息处理程序


BOOL CDlgAngleDetail::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!pTanAngleData)
		return FALSE;

	CString strTitle = "均线角度详细 ";

	strTitle += pTanAngleData->strStockCode;
	strTitle += "  ";
	strTitle += pTanAngleData->strStockName;

	SetWindowText(strTitle);

	CString strInfo;
	double f_ma5_angle = pTanAngleData->fPara0;
	strInfo.Format("5日均线角度 %.2f", f_ma5_angle);
	mListDetail.AddString(strInfo);
	

	double f_ma10_angle = pTanAngleData->fPara1;
	strInfo.Format("10日均线角度 %.2f", f_ma10_angle);
	mListDetail.AddString(strInfo);


	double f_ma20_angle = pTanAngleData->fPara2;
	strInfo.Format("20日均线角度 %.2f", f_ma20_angle);
	mListDetail.AddString(strInfo);

	double f_ma60_angle = pTanAngleData->fPara3;
	strInfo.Format("60日均线角度 %.2f", f_ma60_angle);
	mListDetail.AddString(strInfo);


	double f_max_volume_per = pTanAngleData->fPara4;
	strInfo.Format("最大成交易量倍数 %.2f", f_max_volume_per);
	mListDetail.AddString(strInfo);

	int  mMaxDis = pTanAngleData->mMaxDis;
	strInfo.Format("最大成交易量距离今日 %d 日", mMaxDis);
	mListDetail.AddString(strInfo);

	double f_ave_volume_per = pTanAngleData->fPara5;
	strInfo.Format("平均成交易量倍数 %.2f", f_ave_volume_per);
	mListDetail.AddString(strInfo);


	double f_20_10_cross_price_increase = pTanAngleData->fPara7;
	strInfo.Format("10日均线上穿20日后的涨幅 %.2f", f_20_10_cross_price_increase);
	mListDetail.AddString(strInfo);

	double f_60_20_cross_price_increase = pTanAngleData->fPara6;
	strInfo.Format("20日均线上穿60日后的涨幅 %.2f", f_60_20_cross_price_increase);
	mListDetail.AddString(strInfo);


	double f_60_day_increase = pTanAngleData->fPara8;
	strInfo.Format("60日均线上升趋势以来的涨幅 %.2f", f_60_day_increase);
	mListDetail.AddString(strInfo);


	double fNowGrow = pTanAngleData->fNowGrow;
	strInfo.Format("对比昨日,今日涨幅 %.2f", fNowGrow);
	mListDetail.AddString(strInfo);


	double fNowMaxGrow = pTanAngleData->fNowMaxGrow;
	strInfo.Format("对比昨日,今日最大价格涨幅 %.2f", fNowMaxGrow);
	mListDetail.AddString(strInfo);


	int mNowIsMaxPriceNums = pTanAngleData->mNowIsMaxPriceNums;
	strInfo.Format("今日收盘价格是%d日以来的最高价格", mNowIsMaxPriceNums);
	mListDetail.AddString(strInfo);
	

	int m_10_big_20_nums = pTanAngleData->mPara6;
	strInfo.Format("10日均线大于20日均线 %d 日", m_10_big_20_nums);
	mListDetail.AddString(strInfo);


	int m_60_big_20_nums = pTanAngleData->mPara7;
	strInfo.Format("20日均线大于60日均线 %d 日", m_60_big_20_nums);
	mListDetail.AddString(strInfo);

	double f_per = f_20_10_cross_price_increase / m_10_big_20_nums;
	strInfo.Format("10日均线上穿20日后的涨幅/10日均线大于20日均线天数=%.2f", f_per);
	mListDetail.AddString(strInfo);

	f_per = f_60_20_cross_price_increase / m_60_big_20_nums;
	strInfo.Format("20日均线上穿60日后的涨幅/20日均线大于60日均线天数=%.2f", f_per);
	mListDetail.AddString(strInfo);
	
	int mPriceM5ContiUpNums = pTanAngleData->mPriceM5ContiUpNums;
	strInfo.Format("5日均线连续上升 %d日", mPriceM5ContiUpNums);
	mListDetail.AddString(strInfo);

	int m_continus_price_m10_up_nums = pTanAngleData->mPara8;
	strInfo.Format("10日均线连续上涨 %d 日", m_continus_price_m10_up_nums);
	mListDetail.AddString(strInfo);

	int m_continus_price_m20_up_nums = pTanAngleData->mPara9;
	strInfo.Format("20日均线连续上涨 %d 日", m_continus_price_m20_up_nums);
	mListDetail.AddString(strInfo);

	int m_continus_price_m60_up_nums = pTanAngleData->mPara10;
	strInfo.Format("60日均线连续上涨 %d 日", m_continus_price_m60_up_nums);
	mListDetail.AddString(strInfo);

	
	/*double fcustomvalue = -pTanAngleData->fcustomtotalvalue;
	f_per = f_20_10_cross_price_increase / m_10_big_20_nums;
	double f_per2 = f_60_20_cross_price_increase / m_60_big_20_nums;
	if (m_continus_price_m20_up_nums == 0)
		m_continus_price_m20_up_nums = 1;
	float fMyValue;
	
	float f_temp1 = 0;
	if (m_continus_price_m20_up_nums > 50)
		f_temp1 = m_continus_price_m20_up_nums + m_continus_price_m10_up_nums+ mPriceM5ContiUpNums;
	else if (m_continus_price_m20_up_nums > 45)
		f_temp1 = m_continus_price_m20_up_nums + pow(m_continus_price_m10_up_nums, 0.5) + mPriceM5ContiUpNums;
	else if (m_continus_price_m20_up_nums > 40)
		f_temp1 = m_continus_price_m20_up_nums + pow(m_continus_price_m10_up_nums, 0.5) + pow(mPriceM5ContiUpNums, 0.5);
	else if (m_continus_price_m20_up_nums > 35)
		f_temp1 = pow(m_continus_price_m20_up_nums, 0.5) + pow(m_continus_price_m10_up_nums, 0.5) + pow(mPriceM5ContiUpNums, 0.5);
	else
		f_temp1 = pow(m_continus_price_m20_up_nums, 0.5);
	
	float f_temp2 = 0;

	if (f_per > 4.0)
		f_temp2 = pow(f_per, 1.40);
	else if (f_per > 3.5)
		f_temp2 = pow(f_per, 1.30);
	else if (f_per > 3.0)
		f_temp2 = pow(f_per, 1.20);
	else if (f_per > 2.5)
		f_temp2 = pow(f_per, 1.10);
	else
		f_temp2 = f_per;

	if (f_per2 > 6.0)
		f_temp2 = f_temp2 * 2.0;
	else if (f_per2 > 5.5)
		f_temp2 = f_temp2 * 1.4;
	else if (f_per2 > 5.0)
		f_temp2 = f_temp2 * 1.2;
	

	float fMyValue_t1 = f_temp1 +(fabs(f_ma20_angle) + pow(fabs(f_ma10_angle), 0.5) + pow(fabs(f_ma5_angle), 0.33)) * f_temp2;
	fMyValue = fMyValue_t1;
	float f_increase = f_20_10_cross_price_increase > f_60_20_cross_price_increase ? f_20_10_cross_price_increase : f_60_20_cross_price_increase;

	if (pTanAngleData->fcustomtotalvalue < 0)
	{
		if (f_increase > fcustomvalue)
		{
			float f_compne = f_increase - fcustomvalue;
				fMyValue = fMyValue + f_compne;
		}
		
	}
	
		
	//fMyValue = (fcustomvalue / fMyValue_t1 +1.0)* fMyValue_t1;

	//fMyValue = pow((fcustomvalue / fMyValue_t1 + 1.0),2.0) * fMyValue_t1;
	//fMyValue = fcustomvalue / fMyValue_t1;


	strInfo.Format("角度综合值 %.2f", fMyValue);
	mListDetail.AddString(strInfo);*/


	int mContiDownNums = pTanAngleData->mContiDownNums;
	strInfo.Format("最低价格连续 %d 日下降", mContiDownNums);
	mListDetail.AddString(strInfo);


	int mBigIncreaseNums = pTanAngleData->mBigIncreaseNums;
	strInfo.Format("大幅度上涨有 %d 次", mBigIncreaseNums);
	mListDetail.AddString(strInfo);


	int mRsi1BigNums = pTanAngleData->mRsi1BigNums;
	strInfo.Format("RSI1 高位有 %d 次", mRsi1BigNums);
	mListDetail.AddString(strInfo);


	
	double f_cur_rsi_1 = pTanAngleData->fRsi1;
	strInfo.Format("当前RSI1值 %.2f", f_cur_rsi_1);
	mListDetail.AddString(strInfo);

	double f_cur_rsi_2 = pTanAngleData->fRsi2;
	strInfo.Format("当前RSI2值 %.2f", f_cur_rsi_2);
	mListDetail.AddString(strInfo);

	double f_cur_rsi_3 = pTanAngleData->fRsi3;
	strInfo.Format("当前RSI3值 %.2f", f_cur_rsi_3);
	mListDetail.AddString(strInfo);

	double fMinRsi1 = pTanAngleData->fMinRsi1;
	strInfo.Format("最小RSI1值 %.2f", fMinRsi1);
	mListDetail.AddString(strInfo);

	double fMinRsi2 = pTanAngleData->fMinRsi2;
	strInfo.Format("最小RSI2值 %.2f", fMinRsi2);
	mListDetail.AddString(strInfo);

	double fMinRsi3 = pTanAngleData->fMinRsi3;
	strInfo.Format("最小RSI3值 %.2f", fMinRsi3);
	mListDetail.AddString(strInfo);

	int    mMinRsi3Interval = pTanAngleData->mMinRsi3Interval;
	strInfo.Format("最小RSI3值距离当前  %d日", mMinRsi3Interval);
	mListDetail.AddString(strInfo);

	
	int mContiVolDownNums = pTanAngleData->mContiVolDownNums;
	strInfo.Format("交易量连续下降 %d日", mContiVolDownNums);
	mListDetail.AddString(strInfo);


	int mStepIndex = pTanAngleData->mStepIndex;
	strInfo.Format("股价启动前交易量10日均线大于5日均线并连续下降 %d日", mStepIndex);
	mListDetail.AddString(strInfo);




	int mVolM5ContiUpNums = pTanAngleData->mVolM5ContiUpNums;
	strInfo.Format("交易量5日均线连续上升 %d日", mVolM5ContiUpNums);
	mListDetail.AddString(strInfo);


	int mVolM10ContiUpNums = pTanAngleData->mVolM10ContiUpNums;
	strInfo.Format("交易量10日均线连续上升 %d日", mVolM10ContiUpNums);
	mListDetail.AddString(strInfo);

	double fVolumePerForM30 = pTanAngleData->fVolumePerForM30;
	strInfo.Format("今日交易量和交易量30日均线比值%.2f", fVolumePerForM30);
	mListDetail.AddString(strInfo);

	double fVolumePerForM20 = pTanAngleData->fVolumePerForM20;
	strInfo.Format("今日交易量和交易量20日均线比值%.2f", fVolumePerForM20);
	mListDetail.AddString(strInfo);

	double fVolumePer = pTanAngleData->fVolumePer;
	strInfo.Format("今日交易量和交易量10日均线比值%.2f", fVolumePer);
	mListDetail.AddString(strInfo);

	double fVolumePerForM5= pTanAngleData->fVolumePerForM5;
	strInfo.Format("今日交易量和交易量5日均线比值%.2f", fVolumePerForM5);
	mListDetail.AddString(strInfo);


	double fcustomtotalvalue = pTanAngleData->fcustomtotalvalue;
	strInfo.Format("自制算法计算的值%.2f", fcustomtotalvalue);
	mListDetail.AddString(strInfo);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
