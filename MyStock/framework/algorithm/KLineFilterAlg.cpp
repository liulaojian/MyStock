#include "stdafx.h"
#include <stdio.h>
#include "KLineFilterAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include <math.h> 
#include "CommonMacro.h"
#include "StockBOLLArithmetic.h"
#include "Convert.h"

CKLineFilterAlg::CKLineFilterAlg()
{

}


CKLineFilterAlg::~CKLineFilterAlg()
{

}

int  CKLineFilterAlg::CalcBollType(double f_boll_up,double f_boll_middle,double f_boll_bottom,double f_close,double f_begin,double f_high,double f_low)
{
	if(f_low>f_boll_up)
		return BOLL_OUT_UP;

	if(f_boll_up>f_low&&f_boll_up<f_high)
		return BOLL_EMBED_UP;

	if(f_high<f_boll_up&&f_low>f_boll_middle)
		return BOLL_IN_UP_MIDDLE;

	if(f_high>f_boll_middle && f_low<f_boll_middle)
		return BOLL_EMBED_MIDDLE;

	if(f_high<f_boll_middle && f_low>f_boll_bottom)
		return BOLL_IN_MIDDLE_BOTTOM;

	if(f_high>f_boll_bottom && f_low<f_boll_bottom)
		return BOLL_EMBED_BOTTOM;
	
	if(f_high<f_boll_bottom && f_low<f_boll_bottom)
		return BOLL_OUT_BOTTOM;

	return  -1;
}

Vec_KLineFilterData  CKLineFilterAlg::doFilter(CTime mDropOffTime,Vec_DropOffData & vecDropOffData)
{
	Vec_KLineFilterData vecKLineFilterData;

	DropOffData * pDropOffData=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	CStockKDJData *pStockKDJData=NULL;
	CStockBOLLData *pStockBOLLData=NULL;
	for(int i=0;i<vecDropOffData.size();i++)
	{
		pDropOffData=vecDropOffData[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(pDropOffData->strStockCode);

		strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		if(pStockKDJData)
		{
			SAFE_DELETE(pStockKDJData);
		}
		pStockKDJData=NULL;


		pStockKDJData=CStockKDJArithmetic::CalcKDJData(pDropOffData->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
		if(pStockKDJData==NULL)
			continue;
		if(pDropOffData->strStockCode=="SZ000799")
		{

			int a=0;
			a++;
		}
		if(pStockBOLLData)
		{
			SAFE_DELETE(pStockBOLLData);
		}
		pStockBOLLData=NULL;

		pStockBOLLData=CStockBOLLArithmetic::CalcBOLLData(pDropOffData->strStockCode,strNowDate,125,K_LINE_DAY,20);
		if(!pStockBOLLData)
			continue;


		std::vector<double> vec_price_ma5,vec_price_ma10,vec_price_ma20,vec_price_ma60,vec_price_ma120;
		vec_price_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
		vec_price_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
		vec_price_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
		vec_price_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);
		vec_price_ma120=CStockKDJArithmetic::CalcMA(120,pStockKDJData->vec_close_price);

		int mSize=pStockKDJData->vec_close_price.size();
		
		double f_now_close_price=pStockKDJData->vec_close_price[mSize-1];
		
		double f_p_close_price=pStockKDJData->vec_close_price[mSize-2];

		double f_p2_close_price=pStockKDJData->vec_close_price[mSize-3];

		double f_p3_close_price=pStockKDJData->vec_close_price[mSize-4];

		double f_p4_close_price=pStockKDJData->vec_close_price[mSize-5];

		double f_p5_close_price=pStockKDJData->vec_close_price[mSize-6];

		double f_p4_per=(f_p4_close_price-f_p5_close_price)*100.0/f_p5_close_price;
		double f_p3_per=(f_p3_close_price-f_p4_close_price)*100.0/f_p4_close_price;
		double f_p2_per=(f_p2_close_price-f_p3_close_price)*100.0/f_p3_close_price;
		double f_p_per=(f_p_close_price-f_p2_close_price)*100.0/f_p2_close_price;
		double f_now_per=(f_now_close_price-f_p_close_price)*100.0/f_p_close_price;

		


		double f_now_begin_price=pStockKDJData->vec_open_price[mSize-1];

		double f_now_high_price=pStockKDJData->vec_high_price[mSize-1];

		double f_now_low_price=pStockKDJData->vec_low_price[mSize-1];

		int mBollSize=pStockBOLLData->vec_boll.size();

		double f_now_boll_up=pStockBOLLData->vec_up[mBollSize-1];
		double f_now_boll_middle=pStockBOLLData->vec_boll[mBollSize-1];
		double f_now_boll_bottom=pStockBOLLData->vec_down[mBollSize-1];



		int mBollType=CalcBollType(f_now_boll_up,f_now_boll_middle,f_now_boll_bottom,
							f_now_close_price,f_now_begin_price,f_now_high_price,f_now_low_price);

		double f_total_per=(f_now_high_price-f_now_low_price)*100.0/f_now_low_price;
		if(f_total_per<0.01)
			continue;
		double f_up_per,f_bottom_per,f_body_per;
		if(f_now_close_price>f_now_begin_price)		//up
		{
			f_up_per=(f_now_high_price-f_now_close_price)*100.0/f_now_low_price;

			f_bottom_per=(f_now_begin_price-f_now_low_price)*100.0/f_now_low_price;

			f_body_per=(f_now_close_price-f_now_begin_price)*100.0/f_now_low_price;
		}
		else		//down
		{
			f_up_per=(f_now_high_price-f_now_begin_price)*100.0/f_now_low_price;

			f_bottom_per=(f_now_close_price-f_now_low_price)*100.0/f_now_low_price;

			f_body_per=(f_now_begin_price-f_now_close_price)*100.0/f_now_low_price;
		}

		//printf("%s  %.2f  %.2f %.2f %.2f\n",pDropOffData->strStockCode,f_total_per,f_up_per,f_bottom_per,f_body_per);

		double f_up_per_b=f_up_per*100.0/f_total_per;
		double f_bottom_per_b=f_bottom_per*100.0/f_total_per;
		double f_body_per_b=f_body_per*100.0/f_total_per;
		
		if(f_body_per_b>16.0)
			continue;

		//double f_per=(f_up_per_b-f_bottom_per_b)*100.0/f_bottom_per_b;

	//	if(f_per>10.0)
		//	continue;

		printf("%s  %.2f ,%.2f ,%.2f ,%.2f\n",(LPCSTR)pDropOffData->strStockCode,f_total_per,f_up_per_b,f_bottom_per_b,f_body_per_b);


		//if(f_p_per>-4.0)
		//	continue;

		//if(f_now_per>2.0)
		//	continue;
		
		
		KLineFilterData *pKLineFilterData=new KLineFilterData();
		pKLineFilterData->strStockCode=pDropOffData->strStockCode;
		pKLineFilterData->strStockName=pDropOffData->strStockName;

		pKLineFilterData->strDateTime=strNowDate;

		pKLineFilterData->f_total_per=f_total_per;
		pKLineFilterData->f_up_per_b=f_up_per_b;
		pKLineFilterData->f_bottom_per_b=f_bottom_per_b;
		pKLineFilterData->f_body_per_b=f_body_per_b;

		pKLineFilterData->f_p4_per=f_p4_per;
		pKLineFilterData->f_p3_per=f_p3_per;
		pKLineFilterData->f_p2_per=f_p2_per;
		pKLineFilterData->f_p1_per=f_p_per;
		pKLineFilterData->f_now_per=f_now_per;
		pKLineFilterData->mBollType=mBollType;
		

		vecKLineFilterData.push_back(pKLineFilterData);

	}

	return vecKLineFilterData;


}




Vec_KLineFilterData2  CKLineFilterAlg::doFilter2(CString strStockCode, CString strStockName, CTime mNowTime)
{
	Vec_KLineFilterData2 vecKLineFilterData2;

	CStockDayTable* pStockDayTable = NULL;
	CString strNowDate;
	
	CStockRSIData* pStockRSIData = NULL;
	
	pStockDayTable = StockDataMgr()->GetStockDayTable(strStockCode);
	strNowDate = pStockDayTable->GetNearestStockDayDate(mNowTime);
	
	pStockRSIData = CStockRSIArithmetic::CalcRSIData(strStockCode, strNowDate, 155, K_LINE_DAY, 6, 12, 24);

	std::vector<double> vec_price_ma5, vec_price_ma10, vec_price_ma20;
	vec_price_ma5 = CStockKDJArithmetic::CalcMA(5, pStockRSIData->vec_close_price);
	vec_price_ma10 = CStockKDJArithmetic::CalcMA(10, pStockRSIData->vec_close_price);
	vec_price_ma20 = CStockKDJArithmetic::CalcMA(20, pStockRSIData->vec_close_price);
	
	std::vector<double> vec_volume_ma5, vec_volume_ma10;
	vec_volume_ma5 = CStockKDJArithmetic::CalcMA(5, pStockRSIData->vec_volume_price);
	vec_volume_ma10 = CStockKDJArithmetic::CalcMA(10, pStockRSIData->vec_volume_price);


	int mSize = pStockRSIData->vec_close_price.size();
	if (mSize < 120)
		return vecKLineFilterData2;

	for (int i = mSize - 120; i < mSize ; i++)
	{
		double f_now_close_price = pStockRSIData->vec_close_price[i];

		double f_now_begin_price = pStockRSIData->vec_open_price[i];

		double f_now_high_price = pStockRSIData->vec_high_price[i];

		double f_now_low_price = pStockRSIData->vec_low_price[i];

		double f_now_volume = pStockRSIData->vec_volume_price[i];

		double f_now_m5 = vec_price_ma5[i];
		double f_now_m10 = vec_price_ma10[i];
		double f_now_m20 = vec_price_ma20[i];


		double f_now_m5_volume = vec_volume_ma5[i];
		double f_now_m10_volume = vec_volume_ma10[i];

		int m_rsi_size = pStockRSIData->vec_rsi_1_value.size();

		double f_rsi_1 = pStockRSIData->vec_rsi_1_value[m_rsi_size -(mSize-i)];
		double f_rsi_2 = pStockRSIData->vec_rsi_2_value[m_rsi_size - (mSize - i)];
		double f_rsi_3 = pStockRSIData->vec_rsi_3_value[m_rsi_size - (mSize - i)];

		double f_total_per = (f_now_high_price - f_now_low_price) * 100.0 / f_now_low_price;
		if (f_total_per < 0.01)
		{
			KLineFilterData2* pKLineFilterData = new KLineFilterData2();
			pKLineFilterData->strStockCode = strStockCode;
			pKLineFilterData->strStockName = strStockName;

			pKLineFilterData->f_total_per = 0.0;
			pKLineFilterData->f_up_per_b = 0.0;
			pKLineFilterData->f_bottom_per_b = 0.0;
			pKLineFilterData->f_body_per_b = 0.0;

			long m_now_time = pStockRSIData->vec_time[i];
			CTime time(m_now_time);
			CString strDateTime = ConverCTimeToString(time);
			pKLineFilterData->strDateTime = strDateTime;

			pKLineFilterData->f_begin_price = f_now_begin_price;
			pKLineFilterData->f_close_price = f_now_close_price;
			pKLineFilterData->f_high_price = f_now_high_price;
			pKLineFilterData->f_low_price = f_now_low_price;

			pKLineFilterData->f_m5_price = vec_price_ma5[i];
			pKLineFilterData->f_m10_price = vec_price_ma10[i];
			pKLineFilterData->f_m20_price = vec_price_ma20[i];

			pKLineFilterData->f_rsi_1 = f_rsi_1;
			pKLineFilterData->f_rsi_2 = f_rsi_2;
			pKLineFilterData->f_rsi_3 = f_rsi_3;

			pKLineFilterData->f_now_volume = f_now_volume;
			pKLineFilterData->f_m5_volume = f_now_m5_volume;
			pKLineFilterData->f_m10_volume = f_now_m10_volume;


			continue;

		}
			


		double f_up_per, f_bottom_per, f_body_per;
		if (f_now_close_price > f_now_begin_price)		//up
		{
			f_up_per = (f_now_high_price - f_now_close_price) * 100.0 / f_now_low_price;

			f_bottom_per = (f_now_begin_price - f_now_low_price) * 100.0 / f_now_low_price;

			f_body_per = (f_now_close_price - f_now_begin_price) * 100.0 / f_now_low_price;
		}
		else		//down
		{
			f_up_per = (f_now_high_price - f_now_begin_price) * 100.0 / f_now_low_price;

			f_bottom_per = (f_now_close_price - f_now_low_price) * 100.0 / f_now_low_price;

			f_body_per = (f_now_begin_price - f_now_close_price) * 100.0 / f_now_low_price;
		}

		
		double f_up_per_b = f_up_per * 100.0 / f_total_per;
		double f_bottom_per_b = f_bottom_per * 100.0 / f_total_per;
		double f_body_per_b = f_body_per * 100.0 / f_total_per;


		KLineFilterData2* pKLineFilterData = new KLineFilterData2();
		pKLineFilterData->strStockCode = strStockCode;
		pKLineFilterData->strStockName = strStockName;

		
		pKLineFilterData->f_total_per = f_total_per;
		pKLineFilterData->f_up_per_b = f_up_per_b;
		pKLineFilterData->f_bottom_per_b = f_bottom_per_b;
		pKLineFilterData->f_body_per_b = f_body_per_b;

		long m_now_time = pStockRSIData->vec_time[i];
		CTime time(m_now_time);
		CString strDateTime = ConverCTimeToString(time);
		pKLineFilterData->strDateTime = strDateTime;

		pKLineFilterData->f_begin_price = f_now_begin_price;
		pKLineFilterData->f_close_price = f_now_close_price;
		pKLineFilterData->f_high_price = f_now_high_price;
		pKLineFilterData->f_low_price = f_now_low_price;

		pKLineFilterData->f_rsi_1 = f_rsi_1;
		pKLineFilterData->f_rsi_2 = f_rsi_2;
		pKLineFilterData->f_rsi_3 = f_rsi_3;

		pKLineFilterData->f_m5_price = f_now_m5;
		pKLineFilterData->f_m10_price = f_now_m10;
		pKLineFilterData->f_m20_price = f_now_m20;

		pKLineFilterData->f_now_volume = f_now_volume;
		pKLineFilterData->f_m5_volume = f_now_m5_volume;
		pKLineFilterData->f_m10_volume = f_now_m10_volume;

		vecKLineFilterData2.push_back(pKLineFilterData);

	}

	if (pStockRSIData)
	{
		SAFE_DELETE(pStockRSIData);
	}
	pStockRSIData = NULL;

	return vecKLineFilterData2;


}


int  CalcMNPriceContiUp(std::vector<double> vecPriceMN)
{
	int size = vecPriceMN.size();

	if (size < 80)
		return 0;
	int mContiUpNums = 0;
	int mContiDownNums = 0;
	for (int i = size - 1; i >= size - 75; i--)
	{
		double f_now_mn = vecPriceMN[i];
		double f_pre_mn = vecPriceMN[i - 1];
		if (f_now_mn >= f_pre_mn)
		{
			mContiUpNums++;
			mContiDownNums = 0;
		}
		else
		{
			mContiDownNums++;
			if (mContiDownNums >= 2)
				break;
		}
	}

	return mContiUpNums;
}

KLineContinusMNData  CKLineFilterAlg::doCalcMNPriceContiUp(CString strStockCode, CString strStockName, CTime mNowTime)
{
	KLineContinusMNData mKLineContinusMNData;

	mKLineContinusMNData.strStockCode = strStockCode;
	mKLineContinusMNData.strStockName = strStockName;

	CStockDayTable* pStockDayTable = NULL;
	CString strNowDate;

	CStockRSIData* pStockRSIData = NULL;

	pStockDayTable = StockDataMgr()->GetStockDayTable(strStockCode);
	strNowDate = pStockDayTable->GetNearestStockDayDate(mNowTime);

	pStockRSIData = CStockRSIArithmetic::CalcRSIData(strStockCode, strNowDate, 125, K_LINE_DAY, 6, 12, 24);

	std::vector<double> vec_price_ma5, vec_price_ma10, vec_price_ma20;
	vec_price_ma5 = CStockKDJArithmetic::CalcMA(5, pStockRSIData->vec_close_price);
	vec_price_ma10 = CStockKDJArithmetic::CalcMA(10, pStockRSIData->vec_close_price);
	vec_price_ma20 = CStockKDJArithmetic::CalcMA(20, pStockRSIData->vec_close_price);


	mKLineContinusMNData.m_continus_price_m5_up_nums = CalcMNPriceContiUp(vec_price_ma5);
	mKLineContinusMNData.m_continus_price_m10_up_nums= CalcMNPriceContiUp(vec_price_ma10);
	mKLineContinusMNData.m_continus_price_m20_up_nums = CalcMNPriceContiUp(vec_price_ma20);

	if (pStockRSIData)
	{
		SAFE_DELETE(pStockRSIData);
	}
	pStockRSIData = NULL;

	return mKLineContinusMNData;
}
//K线算法(大阴跟十字星)
BOOL CKLineFilterAlg::IsKLineFourDownFilter(Vec_KLineFilterData2& vecKLineFilterData2)
{

	
	int Size = vecKLineFilterData2.size();
	if (Size < 6)
		return FALSE;

	KLineFilterData2* pKLineFilterDataNow = vecKLineFilterData2[Size - 1];
	KLineFilterData2* pKLineFilterDataP1 = vecKLineFilterData2[Size - 2];
	KLineFilterData2* pKLineFilterDataP2 = vecKLineFilterData2[Size - 3];
	KLineFilterData2* pKLineFilterDataP3 = vecKLineFilterData2[Size - 4];
	
	if (pKLineFilterDataNow->strStockCode == "SH600620")
	{
		int a = 0;
		a++;
	}
	
	double f_now_close = pKLineFilterDataNow->f_close_price;
	
	double f_p1_close = pKLineFilterDataP1->f_close_price;
	double f_p1_begin = pKLineFilterDataP1->f_begin_price;


	double f_p2_close = pKLineFilterDataP2->f_close_price;
	double f_p3_close = pKLineFilterDataP3->f_close_price;

	double f_p1_per = (f_p1_close - f_p1_begin) * 100.0 / f_p1_close;
	double f_rsi_1 = pKLineFilterDataNow->f_rsi_1;
	if (f_p1_per < -3.0)
	{
		if (pKLineFilterDataNow->f_body_per_b <20.0)
		{
			return TRUE;
		}

	}

	return FALSE;

}


// 十字星反转
//阴十字星 第二日阳线包含整个阴十字星
BOOL  CKLineFilterAlg::IsCrossStartRevertFilter(Vec_KLineFilterData2 & vecKLineFilterData2, KLineContinusMNData& mKLineContinusMNData)
{
	int Size = vecKLineFilterData2.size();
	if (Size < 60)
		return FALSE;

	KLineFilterData2* pKLineFilterDataNow = vecKLineFilterData2[Size - 1];
	KLineFilterData2* pKLineFilterDataP1 = vecKLineFilterData2[Size - 2];

	if (pKLineFilterDataNow->strStockCode == "SZ002475")
	{
		int a = 0;
		a++;
	}

	KLineFilterData2* pKLineFilterData = NULL;
	double f_min_price = 99999.0;
	int m_min_price_index = -1;
	for (int i = 0; i < Size; i++)
	{
		pKLineFilterData = vecKLineFilterData2[i];
		if (pKLineFilterData->f_low_price < f_min_price)
		{
			m_min_price_index = i;
			f_min_price = pKLineFilterData->f_low_price;
		}
	}

	

	double f_now_begin = pKLineFilterDataNow->f_begin_price;
	double f_now_close = pKLineFilterDataNow->f_close_price;
	double f_now_low = pKLineFilterDataNow->f_low_price;
	double f_now_high = pKLineFilterDataNow->f_high_price;
	double f_now_m5 = pKLineFilterDataNow->f_m5_price;
	bool bNowCrossM5 = false;

	if (f_now_begin< f_now_m5 && f_now_close>f_now_m5)
		bNowCrossM5 = true;

	

	
	double f_p1_begin = pKLineFilterDataP1->f_begin_price;
	double f_p1_close = pKLineFilterDataP1->f_close_price;
	double f_p1_low = pKLineFilterDataP1->f_low_price;
	double f_p1_high = pKLineFilterDataP1->f_high_price;
	double f_p1_m5 = pKLineFilterDataP1->f_m5_price;
	bool bP1BelowM5 = false;
	if (f_p1_high < f_p1_m5)
		bP1BelowM5 = true;

	double f_now_per = (f_now_close - f_now_begin) * 100.0 / f_now_close;

	

	if (pKLineFilterDataP1->f_total_per < 3.0)
	{
		if (f_p1_close < f_p1_begin)
		{
			if (pKLineFilterDataP1->f_body_per_b < 35.0)
			{
				if (f_now_per < 2.6)
				{
					if (f_now_close > f_p1_high)
					{
						if(f_now_low< f_p1_low || f_now_per<2.6) //|| (bNowCrossM5 && bP1BelowM5)
						{
							int mode = 0;
							if(f_now_per < 2.0)
								mode++;
							//if(bNowCrossM5 && bP1BelowM5)
							//	mode+=2;

							//double f_volume_per = pKLineFilterDataP1->f_now_volume / pKLineFilterDataP1->f_m10_volume;
							printf("%s  %s f_rsi_3=%f  \n", (LPCSTR)pKLineFilterDataNow->strStockCode, (LPCSTR)pKLineFilterDataNow->strStockName, pKLineFilterData->f_rsi_3);

//							printf("%s  %s f_volume_per=%f  m10_up_nums=%d  m20_up_nums=%d\n", (LPCSTR)pKLineFilterDataNow->strStockCode, (LPCSTR)pKLineFilterDataNow->strStockName, f_volume_per, mKLineContinusMNData.m_continus_price_m10_up_nums, mKLineContinusMNData.m_continus_price_m20_up_nums);
							//printf("%s %s mode= %d , m5_up_nums=%d , m10_up_nums=%d , m20_up_nums=%d\n ", (LPCSTR)pKLineFilterDataNow->strStockCode, (LPCSTR)pKLineFilterDataNow->strStockName, mode,
							//	mKLineContinusMNData.m_continus_price_m5_up_nums, mKLineContinusMNData.m_continus_price_m10_up_nums, mKLineContinusMNData.m_continus_price_m20_up_nums);
							return TRUE;
						}
						
					}

				}

			}
		}
		

	}

	return FALSE;
}

//是否为上影阴线
BOOL IsUpShadowNegativeLine(KLineFilterData2* pKLineFilterData)
{
	
	if ((pKLineFilterData->f_up_per_b + pKLineFilterData->f_body_per_b) >= 65.0)
	{
		if (pKLineFilterData->f_up_per_b > 50.0 && pKLineFilterData->f_body_per_b < 30.0)
		{
			double f_now_low_price = pKLineFilterData->f_low_price;
			double f_now_m5_price = pKLineFilterData->f_m5_price;
			double f_now_close_price = pKLineFilterData->f_close_price;
			double f_now_begin_price = pKLineFilterData->f_begin_price;

			if (f_now_close_price <= f_now_begin_price)
			{
				//	printf("%s %s  %s  K线为上影阴线\n", (LPCSTR)pKLineFilterData->strStockCode, (LPCSTR)pKLineFilterData->strStockName, (LPCSTR)pKLineFilterData->strDateTime);
				return TRUE;
			}
		}

	}
	else
	{
		if (pKLineFilterData->f_up_per_b > 65.0 && pKLineFilterData->f_body_per_b < 20.0)
		{
			double f_now_close_price = pKLineFilterData->f_close_price;
			double f_now_begin_price = pKLineFilterData->f_begin_price;
			if (f_now_close_price <= f_now_begin_price)
			{
				return TRUE;
			}
		}

	}
	
	
	return FALSE;

}



//是否为上影阳线
BOOL IsUpShadowPositiveLine(KLineFilterData2* pKLineFilterData)
{
	if (pKLineFilterData->f_up_per_b > 50.0 && pKLineFilterData->f_body_per_b < 30.0)
	{
		double f_now_low_price = pKLineFilterData->f_low_price;
		double f_now_m5_price = pKLineFilterData->f_m5_price;
		double f_now_close_price = pKLineFilterData->f_close_price;
		double f_now_begin_price = pKLineFilterData->f_begin_price;

		if (f_now_close_price > f_now_begin_price)
		{
			printf("%s %s  %s  K线为上影阳线\n", (LPCSTR)pKLineFilterData->strStockCode, (LPCSTR)pKLineFilterData->strStockName, (LPCSTR)pKLineFilterData->strDateTime);
			return TRUE;
		}
	}
	return FALSE;
}

//是否为下影阴线
BOOL IsDownShadowNegativeLine(KLineFilterData2* pKLineFilterData)
{
	if (pKLineFilterData->f_bottom_per_b > 50.0 && pKLineFilterData->f_body_per_b < 30.0)
	{
		double f_now_close_price = pKLineFilterData->f_close_price;
		double f_now_begin_price = pKLineFilterData->f_begin_price;

		if (f_now_close_price <= f_now_begin_price)
		{
			printf("%s %s  %s  K线为下影阴线\n", (LPCSTR)pKLineFilterData->strStockCode, (LPCSTR)pKLineFilterData->strStockName, (LPCSTR)pKLineFilterData->strDateTime);
			return TRUE;
		}
	}
	return FALSE;
}

//是否为下影阳线
BOOL IsDownShadowPositiveLine(KLineFilterData2* pKLineFilterData)
{
	if (pKLineFilterData->f_bottom_per_b > 50.0 && pKLineFilterData->f_body_per_b < 30.0)
	{
		double f_now_close_price = pKLineFilterData->f_close_price;
		double f_now_begin_price = pKLineFilterData->f_begin_price;

		if (f_now_close_price > f_now_begin_price)
		{
			printf("%s %s  %s  K线为下影阳线\n", (LPCSTR)pKLineFilterData->strStockCode, (LPCSTR)pKLineFilterData->strStockName, (LPCSTR)pKLineFilterData->strDateTime);
			return TRUE;
		}

	}
	return FALSE;
}

#define  MX_LOW_PRICE_ALL   0			 

#define  MX_CROSS_PRICE_HEAD	1

#define  MX_CROSS_PRICE_BODY 2

#define  MX_CROSS_PRICE_FOOT 3

#define  MX_HIGH_PRICE_ALL   4		

#define  MX_TYPE_M5	0
#define  MX_TYPE_M10 1
#define  MX_TYPE_M20 2

int GetMXPosition(KLineFilterData2* pKLineFilterData,int mxtype)
{
	double f_now_close_price = pKLineFilterData->f_close_price;
	double f_now_begin_price = pKLineFilterData->f_begin_price;
	double f_now_high_price = pKLineFilterData->f_high_price;
	double f_now_low_price = pKLineFilterData->f_low_price;
	double f_now_mx_price;
	if(mxtype== MX_TYPE_M5)
		f_now_mx_price = pKLineFilterData->f_m5_price;
	else if (mxtype == MX_TYPE_M10)
		f_now_mx_price = pKLineFilterData->f_m10_price;
	else if (mxtype == MX_TYPE_M20)
		f_now_mx_price = pKLineFilterData->f_m20_price;
	else
		f_now_mx_price = pKLineFilterData->f_m5_price;

	if (f_now_mx_price < f_now_low_price)
		return MX_LOW_PRICE_ALL;
	if (f_now_mx_price > f_now_high_price)
		return MX_HIGH_PRICE_ALL;


	BOOL bUp = FALSE;

	if (f_now_close_price >= f_now_begin_price)
		bUp = TRUE;

	if (bUp)
	{
		if (f_now_mx_price >= f_now_begin_price && f_now_mx_price <= f_now_close_price)
			return MX_CROSS_PRICE_BODY;

		if (f_now_mx_price >= f_now_close_price && f_now_mx_price <= f_now_high_price)
			return MX_CROSS_PRICE_HEAD;

		if (f_now_mx_price >= f_now_low_price && f_now_mx_price <= f_now_begin_price)
			return MX_CROSS_PRICE_FOOT;

	}
	else
	{
		if (f_now_mx_price >= f_now_close_price && f_now_mx_price <= f_now_begin_price)
			return MX_CROSS_PRICE_BODY;

		if (f_now_mx_price >= f_now_begin_price && f_now_mx_price <= f_now_high_price)
			return MX_CROSS_PRICE_HEAD;

		if (f_now_mx_price >= f_now_low_price && f_now_mx_price <= f_now_close_price)
			return MX_CROSS_PRICE_FOOT;
	}
	
	return -1;
}

//获取MX线 在 股价最大最小值的位置 百分比
double GetMXPositionPer(KLineFilterData2* pKLineFilterData, int mxtype)
{

	int mxpos = GetMXPosition(pKLineFilterData, mxtype);
	if (mxpos < 0 || (mxpos == MX_LOW_PRICE_ALL) || (mxpos == MX_HIGH_PRICE_ALL))
		return 0.0;

	double f_now_high_price = pKLineFilterData->f_high_price;
	double f_now_low_price = pKLineFilterData->f_low_price;
	double f_now_mx_price;
	if (mxtype == MX_TYPE_M5)
		f_now_mx_price = pKLineFilterData->f_m5_price;
	else if (mxtype == MX_TYPE_M10)
		f_now_mx_price = pKLineFilterData->f_m10_price;
	else if (mxtype == MX_TYPE_M20)
		f_now_mx_price = pKLineFilterData->f_m20_price;
	else
		f_now_mx_price = pKLineFilterData->f_m5_price;

	return (f_now_mx_price - f_now_low_price) * 100.0 / (f_now_high_price - f_now_low_price);
}


//是否K线趋势走坏

BOOL CKLineFilterAlg::IsKLineBadTrend(Vec_KLineFilterData2& vecKLineFilterData2)
{
	//先判断近 5个交易日内有没5日线跳空的长上影阴线

	int Size = vecKLineFilterData2.size();
	if (Size < 60)
		return FALSE;

#if 0
	KLineFilterData2* pKLineFilterData = NULL;
	for (int i = Size - 1; i >= Size - 3; i--)
	{
		pKLineFilterData= vecKLineFilterData2[i];


		if (pKLineFilterData->strStockCode == "SZ300151")
		{
			int a = 0;
			a++;
		}
		int mxpos = GetMXPosition(pKLineFilterData, MX_TYPE_M5);
		//飘在M5上同时是上影阴线false
		if (mxpos == MX_LOW_PRICE_ALL)
		{
			if (IsUpShadowNegativeLine(pKLineFilterData))
				return TRUE;
		}

	}
	
	
	pKLineFilterData = vecKLineFilterData2[Size - 4];
	int mxpos = GetMXPosition(pKLineFilterData, MX_TYPE_M5);

	if (mxpos == MX_LOW_PRICE_ALL)
	{
		double f_now_close_price = pKLineFilterData->f_close_price;
		double f_now_begin_price = pKLineFilterData->f_begin_price;
		double f_per = (f_now_close_price - f_now_begin_price) * 100.0 / f_now_begin_price;
		if (f_now_close_price < f_now_begin_price  && (f_per<-1.5))
		{
			if (pKLineFilterData->f_up_per_b > 40.0  && pKLineFilterData->f_total_per>5.0)
			{
				return TRUE;
			}
		}
	}



	//非今日的5日内最高值那天，还是飘在5日线上，并且是上吊阴线 ，则false
	double f_high_value = 0.0;
	int m_high_index = -1;
	for (int i = Size - 2; i >= Size - 5; i--)
	{
		pKLineFilterData = vecKLineFilterData2[i];

		if (pKLineFilterData->f_high_price > f_high_value)
		{
			f_high_value = pKLineFilterData->f_high_price;
			m_high_index = i;
		}

	}

	if (m_high_index > 0)
	{
		pKLineFilterData = vecKLineFilterData2[m_high_index];
		mxpos = GetMXPosition(pKLineFilterData, MX_TYPE_M5);
		if (mxpos == MX_LOW_PRICE_ALL)
		{
			if (IsUpShadowNegativeLine(pKLineFilterData))
			{
				return TRUE;
			}
		}
	}


	
	KLineFilterData2*  pNowKLineFilterData = vecKLineFilterData2[Size - 1];

	KLineFilterData2* pP1KLineFilterData = vecKLineFilterData2[Size - 2];

	KLineFilterData2* pP2KLineFilterData = vecKLineFilterData2[Size - 3];

	KLineFilterData2* pP3KLineFilterData = vecKLineFilterData2[Size - 4];

	//当日下跌大于2%，前两日至少一日下跌，并且前三日都飘于M5之上，同时其中至少两日振幅大于5%(三日加起来>12)
	double f_now_price_per = (pNowKLineFilterData->f_close_price - pNowKLineFilterData->f_begin_price) * 100.0 / pNowKLineFilterData->f_begin_price;
	double f_p1_price_per = (pP1KLineFilterData->f_close_price - pP1KLineFilterData->f_begin_price) * 100.0 / pP1KLineFilterData->f_begin_price;
	double f_p2_price_per = (pP2KLineFilterData->f_close_price - pP2KLineFilterData->f_begin_price) * 100.0 / pP2KLineFilterData->f_begin_price;
	if (f_now_price_per < -2.0 && (f_p1_price_per<0.0 || f_p2_price_per<0.0))
	{
		int mpos_p1 = GetMXPosition(pP1KLineFilterData, MX_TYPE_M5);
		int mpos_p2 = GetMXPosition(pP2KLineFilterData, MX_TYPE_M5);
		int mpos_p3 = GetMXPosition(pP3KLineFilterData, MX_TYPE_M5);
		if (mpos_p1 == MX_LOW_PRICE_ALL  && mpos_p1 == MX_LOW_PRICE_ALL && mpos_p3 == MX_LOW_PRICE_ALL)
		{
			double f_p1_total_per = pP1KLineFilterData->f_total_per;
			double f_p2_total_per = pP2KLineFilterData->f_total_per;
			double f_p3_total_per = pP3KLineFilterData->f_total_per;
			if((f_p1_total_per+ f_p2_total_per+ f_p3_total_per)>12.0)
				return TRUE;
		}
	}
#endif

#if 0
	KLineFilterData2* pNowKLineFilterData = vecKLineFilterData2[Size - 1];

	KLineFilterData2* pP1KLineFilterData = vecKLineFilterData2[Size - 2];

	KLineFilterData2* pP2KLineFilterData = vecKLineFilterData2[Size - 3];

	int mpos_now = GetMXPosition(pNowKLineFilterData, MX_TYPE_M5);

	int mpos_p1 = GetMXPosition(pP1KLineFilterData, MX_TYPE_M5);

	int mpos_p2 = GetMXPosition(pP2KLineFilterData, MX_TYPE_M5);
	
	if (pNowKLineFilterData->strStockCode == "SZ300203")
	{
		int a = 0;
		a++;
	}

	int m_per_b_ok_nums = 0;
	int m_increase_ok_nums = 0;
	int m_rang_ok_nums = 0;
	int m_pos_ok_nums = 0;
	KLineFilterData2* pKLineFilterData = NULL;
	for (int i = Size - 1; i >= Size - 3; i--)
	{
		pKLineFilterData= vecKLineFilterData2[i];
		double f_per_b = pKLineFilterData->f_body_per_b + pKLineFilterData->f_bottom_per_b;
		if (f_per_b > 60.0)
			m_per_b_ok_nums++;
		if (pKLineFilterData->f_close_price > pKLineFilterData->f_begin_price)
			m_increase_ok_nums++;
		int mpos = GetMXPosition(pKLineFilterData, MX_TYPE_M5);
		if (mpos > MX_LOW_PRICE_ALL)
			m_pos_ok_nums++;
		//if (pKLineFilterData->f_total_per < 8.0)
		//	m_rang_ok_nums++;
	}
	
	if (m_per_b_ok_nums >= 2 && m_increase_ok_nums >= 3 && m_pos_ok_nums >= 2)//&& m_rang_ok_nums >= 3
		return FALSE;

#endif


#if 0
	KLineFilterData2* pNowKLineFilterData = vecKLineFilterData2[Size - 1];

	KLineFilterData2* pP1KLineFilterData = vecKLineFilterData2[Size - 2];

	KLineFilterData2* pP2KLineFilterData = vecKLineFilterData2[Size - 3];

	KLineFilterData2* pP3KLineFilterData = vecKLineFilterData2[Size - 4];

	KLineFilterData2* pP4KLineFilterData = vecKLineFilterData2[Size - 5];



	double f_now_close = pNowKLineFilterData->f_close_price;

	double f_now_begin = pNowKLineFilterData->f_begin_price;

	double f_p4_close = pP4KLineFilterData->f_close_price;

	double f_p1_close = pP3KLineFilterData->f_close_price;

	double f_per = (f_now_close - f_p4_close) * 100.0 / f_p4_close;

	double f_now_per = (f_now_close - f_now_begin) * 100.0 / f_now_begin;
	
	double f_now_rsi3 = pNowKLineFilterData->f_rsi_3;

	double f_now_volume = pNowKLineFilterData->f_now_volume;
	double f_m5_volume = pNowKLineFilterData->f_m5_volume;
	double f_m10_volume = pNowKLineFilterData->f_m10_volume;

	double f_now_vol_per = (f_now_volume / f_m10_volume) * 100.0;


	if (f_per < -7.0)
	{
		

		if (pNowKLineFilterData->f_total_per < 6.0)
		{
			if (f_now_per>-3.0 && f_now_per<3.0)
			{
				if (pNowKLineFilterData->f_body_per_b < 35.0)
				{
					if (pNowKLineFilterData->f_bottom_per_b > 35.0)
					{
						printf(" %s %s  %.2f   rsi3=%.2f  vol_per=%.2f\n", (LPCSTR)pNowKLineFilterData->strStockCode, (LPCSTR)pNowKLineFilterData->strStockName,f_per, f_now_rsi3, f_now_vol_per);
						return FALSE;
					}
						
				}

			}
		}
	}


	return TRUE;
#else
	Size = vecKLineFilterData2.size();
	if (Size < 120)
		return TRUE;

	KLineFilterData2* pNowKLineFilterData = vecKLineFilterData2[Size - 1];

	KLineFilterData2* pP1KLineFilterData = vecKLineFilterData2[Size - 2];

	KLineFilterData2* pP2KLineFilterData = vecKLineFilterData2[Size - 3];

	double f_now_max = pNowKLineFilterData->f_high_price;
	double f_p1_max = pP1KLineFilterData->f_high_price;
	double f_p2_max = pP2KLineFilterData->f_high_price;

	double f_max = f_now_max;
	if (f_p1_max > f_max)
		f_max = f_p1_max;
	if (f_p2_max > f_max)
		f_max = f_p2_max;

	KLineFilterData2* pKLineFilterData = NULL;
	bool bMax = true;
	for (int i = 0; i < Size - 3; i++)
	{
		pKLineFilterData = vecKLineFilterData2[i];
		if (pKLineFilterData->f_high_price > f_max)
		{
			bMax = false;
			break;
		}

	}

	if (bMax)
		return FALSE;
	return TRUE;
#endif
}

//K线行业
BOOL CKLineFilterAlg::IsKLineIndustry(Vec_KLineFilterData2& vecKLineFilterData2)
{
	int Size = vecKLineFilterData2.size();
	if (Size < 60)
		return FALSE;

	KLineFilterData2* pNowKLineFilterData = vecKLineFilterData2[Size - 1];

	KLineFilterData2* pP1KLineFilterData = vecKLineFilterData2[Size - 2];

	KLineFilterData2* pP2KLineFilterData = vecKLineFilterData2[Size - 3];

	KLineFilterData2* pP3KLineFilterData = vecKLineFilterData2[Size - 4];

	KLineFilterData2* pP4KLineFilterData = vecKLineFilterData2[Size - 5];



	double f_now_close = pNowKLineFilterData->f_close_price;

	double f_now_begin = pNowKLineFilterData->f_begin_price;

	double f_p4_close = pP4KLineFilterData->f_close_price;

	double f_p1_close = pP3KLineFilterData->f_close_price;

	double f_per = (f_now_close - f_p4_close) * 100.0 / f_p4_close;

	double f_now_per = (f_now_close - f_now_begin) * 100.0 / f_now_begin;

	double f_now_rsi3 = pNowKLineFilterData->f_rsi_3;

	double f_now_volume = pNowKLineFilterData->f_now_volume;
	double f_m5_volume = pNowKLineFilterData->f_m5_volume;
	double f_m10_volume = pNowKLineFilterData->f_m10_volume;


	double f_p1_volume = pP1KLineFilterData->f_now_volume;
	double f_p1_m5_volume = pP1KLineFilterData->f_m5_volume;
	double f_p1_m10_volume = pP1KLineFilterData->f_m10_volume;



	double f_now_vol_per = (f_now_volume / f_m10_volume) * 100.0;

	double f_p1_vol_per = (f_p1_volume / f_p1_m10_volume) * 100.0;

	
	if (f_per < -4.0)
	{


		if (pNowKLineFilterData->f_total_per < 12.0)
		{
			if (f_now_per < 3.0)
			{
				if ( (pNowKLineFilterData->f_body_per_b + pNowKLineFilterData->f_bottom_per_b)>40.0)
				{
					printf(" %s %s  %.2f   rsi3=%.2f  vol_per=%.2f\n", (LPCSTR)pNowKLineFilterData->strStockCode, (LPCSTR)pNowKLineFilterData->strStockName, f_per, f_now_rsi3, f_now_vol_per);
					return TRUE;
					
				}

			}
		}
	}


	return FALSE;

}

//分析个股K线趋势
CString CKLineFilterAlg::AnalyzeSingleKLineTrend(Vec_KLineFilterData2& vecKLineFilterData2)
{
	int Size = vecKLineFilterData2.size();
	if (Size < 60)
		return "";

	if (vecKLineFilterData2[Size-1]->strStockCode == "SH600770")
	{
		int a = 0;
		a++;
	}

	KLineFilterData2* pKLineFilterData = NULL;
	for (int i = Size - 1; i >= Size - 5; i--)
	{
		pKLineFilterData = vecKLineFilterData2[i];
		BOOL bIs = IsDownShadowNegativeLine(pKLineFilterData);

		BOOL bIs2 = IsDownShadowPositiveLine(pKLineFilterData);
	}

	return "";
}


//神奇九转down
BOOL CKLineFilterAlg::IsKLineNineTurn(Vec_KLineFilterData2& vecKLineFilterData2)
{
	int Size = vecKLineFilterData2.size();
	if (Size < 60)
		return FALSE;
	
#if 1
	bool bOk1 = false;
	double f_min_price = vecKLineFilterData2[Size - 1]->f_low_price;
	double f_p1_min_price = vecKLineFilterData2[Size - 2]->f_low_price;
	double f_p2_min_price = vecKLineFilterData2[Size - 3]->f_low_price;

	if (f_p2_min_price < f_p1_min_price)
	{
		if (f_p1_min_price < f_min_price)
			bOk1 = true;
	}


	bool bOk2 = false;
	
	double f_max_price = vecKLineFilterData2[Size - 1]->f_high_price;
	double f_m5_price = vecKLineFilterData2[Size - 1]->f_m5_price;
	double f_m10_price = vecKLineFilterData2[Size - 1]->f_m10_price;
	double f_m20_price = vecKLineFilterData2[Size - 1]->f_m20_price;

	

	if (f_min_price < f_m5_price && f_max_price>f_m5_price)
		bOk2 = true;
	else if (f_min_price < f_m10_price && f_max_price>f_m10_price)
		bOk2 = true;
	else if (f_min_price < f_m20_price && f_max_price>f_m20_price)
		bOk2 = true;


	bool bOk3 = false;
	double f_p1_max_price = vecKLineFilterData2[Size - 2]->f_high_price;
	double f_p1_m5_price = vecKLineFilterData2[Size - 2]->f_m5_price;
	double f_p1_m10_price = vecKLineFilterData2[Size - 2]->f_m10_price;
	double f_p1_m20_price = vecKLineFilterData2[Size - 2]->f_m20_price;

	if (f_p1_min_price < f_p1_m5_price && f_p1_max_price>f_p1_m5_price)
		bOk3 = true;
	else if (f_p1_min_price < f_p1_m10_price && f_p1_max_price>f_p1_m10_price)
		bOk3 = true;
	else if (f_p1_min_price < f_p1_m20_price && f_p1_max_price>f_p1_m20_price)
		bOk3 = true;



	bool bOk4 = false;
	double f_p2_max_price = vecKLineFilterData2[Size - 3]->f_high_price;
	double f_p2_m5_price = vecKLineFilterData2[Size - 3]->f_m5_price;
	double f_p2_m10_price = vecKLineFilterData2[Size - 3]->f_m10_price;
	double f_p2_m20_price = vecKLineFilterData2[Size - 3]->f_m20_price;

	if (f_p2_min_price < f_p2_m5_price && f_p2_max_price>f_p2_m5_price)
		bOk4 = true;
	else if (f_p2_min_price < f_p2_m10_price && f_p2_max_price>f_p2_m10_price)
		bOk4 = true;
	else if (f_p2_min_price < f_p2_m20_price && f_p2_max_price>f_p2_m20_price)
		bOk4 = true;

	if (bOk1 && bOk2 && bOk3 && bOk4)
		return TRUE;
	return FALSE;
	

#else
#if 1
	KLineFilterData2* pNowKLineFilterData = NULL;
	KLineFilterData2* pP4KLineFilterData = NULL;

	bool bFail = false;
	for (int i = Size - 9; i < Size; i++)
	{
		pNowKLineFilterData = vecKLineFilterData2[i];
		pP4KLineFilterData = vecKLineFilterData2[i-4];

		double f_now_close = pNowKLineFilterData->f_close_price;
		double f_p4_close = pP4KLineFilterData->f_close_price;
		if (f_now_close >= f_p4_close)
		{
			bFail = true;
			break;
		}
	}

	if(bFail)
		return FALSE;
	KLineFilterData2* p9KLineFilterData = vecKLineFilterData2[Size - 1];  //9
	KLineFilterData2* p8KLineFilterData = vecKLineFilterData2[Size - 2];  //8
	KLineFilterData2* p7KLineFilterData = vecKLineFilterData2[Size - 3];  //7
	KLineFilterData2* p6KLineFilterData = vecKLineFilterData2[Size - 4];  //6

	double f_9_min = p9KLineFilterData->f_low_price;
	double f_8_min = p8KLineFilterData->f_low_price;
	double f_7_min = p7KLineFilterData->f_low_price;
	double f_6_min = p6KLineFilterData->f_low_price;

	if ((f_9_min < f_7_min) && (f_8_min < f_6_min))
	{
		return TRUE;
	}

	return FALSE;
#else
	KLineFilterData2* pNowKLineFilterData = NULL;
	KLineFilterData2* pP4KLineFilterData = NULL;

	bool bFail = false;
	for (int i = Size - 13; i < Size; i++)
	{
		pNowKLineFilterData = vecKLineFilterData2[i];
		pP4KLineFilterData = vecKLineFilterData2[i - 4];

		double f_now_close = pNowKLineFilterData->f_close_price;
		double f_p4_close = pP4KLineFilterData->f_close_price;
		if (f_now_close >= f_p4_close)
		{
			bFail = true;
			break;
		}
	}

	if (bFail)
		return FALSE;
	KLineFilterData2* p9KLineFilterData = vecKLineFilterData2[Size - 1];  //9
	KLineFilterData2* p8KLineFilterData = vecKLineFilterData2[Size - 2];  //8
	KLineFilterData2* p7KLineFilterData = vecKLineFilterData2[Size - 3];  //7
	KLineFilterData2* p6KLineFilterData = vecKLineFilterData2[Size - 4];  //6

	double f_9_min = p9KLineFilterData->f_low_price;
	double f_8_min = p8KLineFilterData->f_low_price;
	double f_7_min = p7KLineFilterData->f_low_price;
	double f_6_min = p6KLineFilterData->f_low_price;

	if ((f_9_min < f_7_min) && (f_8_min < f_6_min))
	{
		return TRUE;
	}

	return FALSE;

#endif
#endif
}

BOOL  CKLineFilterAlg::IsKLineNineTurnUp(Vec_KLineFilterData2& vecKLineFilterData2)
{

	int Size = vecKLineFilterData2.size();
	if (Size < 60)
		return FALSE;
	KLineFilterData2* pNowKLineFilterData = NULL;
	KLineFilterData2* pP4KLineFilterData = NULL;

	bool bFail = false;
	for (int i = Size - 6; i < Size; i++)
	{
		pNowKLineFilterData = vecKLineFilterData2[i];
		pP4KLineFilterData = vecKLineFilterData2[i - 4];

		double f_now_close = pNowKLineFilterData->f_close_price;
		double f_p4_close = pP4KLineFilterData->f_close_price;
		if (f_now_close <= f_p4_close)
		{
			bFail = true;
			break;
		}
	}

	if (bFail)
		return FALSE;
	

	return TRUE;
	
}

void CKLineFilterAlg::FreeVecKLineFilterData2(Vec_KLineFilterData2& vecKLineFilterData2)
{

	for (int i = 0; i < vecKLineFilterData2.size(); i++)
	{
		SAFE_DELETE(vecKLineFilterData2[i]);
	}

	vecKLineFilterData2.clear();

}