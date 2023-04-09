#include "stdafx.h"
#include <stdio.h>
#include "LimitUpAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include <math.h> 
#include "CommonMacro.h"
#include "StockBOLLArithmetic.h"
#include "StockMACDArithmetic.h"

CLimitUpAlg::CLimitUpAlg()
{


}

CLimitUpAlg::~CLimitUpAlg()
{

}

#if 0
Vec_LimitUpData  CLimitUpAlg::doFilter(CTime mDropOffTime)
{
	Vec_LimitUpData vecLimitUpData;

	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	Vec_StockCodeList vecStockCodeList=StockDataMgr()->GetStockCodeList();
	CStockKDJData *pStockKDJData=NULL;
	CStockBOLLData *pStockBOLLData=NULL;

	int mPreSize=2;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		pStockCode=vecStockCodeList[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
		strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		if(pStockKDJData)
		{
			SAFE_DELETE(pStockKDJData);
		}
		pStockKDJData=NULL;

		pStockKDJData=CStockKDJArithmetic::CalcKDJData(pStockCode->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
		if(pStockKDJData==NULL)
			continue;

		std::vector<double> vec_price_ma5,vec_price_ma10,vec_price_ma20,vec_price_ma60,vec_price_ma120;
		vec_price_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
		vec_price_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
		vec_price_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
		vec_price_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);
		vec_price_ma120=CStockKDJArithmetic::CalcMA(120,pStockKDJData->vec_close_price);

		int mSize=pStockKDJData->vec_close_price.size();


		double f_pre_price=pStockKDJData->vec_close_price[mSize-2];

		double f_now_price=pStockKDJData->vec_close_price[mSize-1];

		double f_limitup_price=pStockKDJData->vec_close_price[mSize-mPreSize-1];
		
		double f_p_limitup_price=pStockKDJData->vec_close_price[mSize-mPreSize-2];

		double f_p_p_limitup_price=pStockKDJData->vec_close_price[mSize-mPreSize-3];
		double f_p_p_p_limitup_price=pStockKDJData->vec_close_price[mSize-mPreSize-4];

		double f_limitup_per=(f_limitup_price-f_p_limitup_price)*100.0/f_p_limitup_price;
		double f_p_limitup_per=(f_p_limitup_price-f_p_p_limitup_price)*100.0/f_p_p_limitup_price;
		double f_p_p_limitup_per=(f_p_p_limitup_price-f_p_p_p_limitup_price)*100.0/f_p_p_p_limitup_price;


		double f_now_per=(f_now_price-f_limitup_price)*100.0/f_limitup_price;

		if(pStockCode->strStockCode=="SZ002109")
		{
			int a=0;
			a++;

		}

		if(f_limitup_per<9.8)
			continue;

		BOOL bLargeDown=FALSE;
		if(f_now_per<-8.0)
			bLargeDown=TRUE;

		BOOL bMiddleDown=FALSE;
		if(f_now_per<-4.5)
			bMiddleDown=TRUE;

		BOOL bPreDown=FALSE;

		if(f_p_p_limitup_per<2.0)
		{
			double f_per=f_p_limitup_per+f_p_p_limitup_per;
			if(f_per<-3.0)
				bPreDown=TRUE;
		}

		if((f_p_limitup_per+f_p_p_limitup_per)>10.0)
			continue;


		double f_now_close_price=pStockKDJData->vec_close_price[mSize-1];

		double f_now_begin_price=pStockKDJData->vec_open_price[mSize-1];

		double f_now_high_price=pStockKDJData->vec_high_price[mSize-1];

		double f_now_low_price=pStockKDJData->vec_low_price[mSize-1];

	

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

		

		double f_up_per_b=f_up_per*100.0/f_total_per;
		double f_bottom_per_b=f_bottom_per*100.0/f_total_per;
		double f_body_per_b=f_body_per*100.0/f_total_per;

		printf("%s   %.2f %.2f %.2f\n",pStockCode->strStockCode,f_up_per_b,f_bottom_per_b,f_body_per_b);


		BOOL bOk=FALSE;

		if(f_body_per_b<16.0)
			bOk=TRUE;
		else if(f_bottom_per_b>70.0)
			bOk=TRUE;
		else if(bLargeDown)
			bOk=TRUE;

		if(bOk&&bMiddleDown)
		{
			LimitUpData *pLimitUpData=new LimitUpData();
			pLimitUpData->strStockCode=pStockCode->strStockCode;
			pLimitUpData->strStockName=pStockCode->strStockName;

			pLimitUpData->strDateTime=strNowDate;
			pLimitUpData->mPara1=0;
			pLimitUpData->bPreDown=bPreDown;
			vecLimitUpData.push_back(pLimitUpData);
		}


	}

	return vecLimitUpData;
}


#else

#if 0
Vec_LimitUpData  CLimitUpAlg::doFilter(CTime mDropOffTime)
{
	Vec_LimitUpData vecLimitUpData;

	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	Vec_StockCodeList vecStockCodeList=StockDataMgr()->GetStockCodeList();
	CStockKDJData *pStockKDJData=NULL;
	CStockBOLLData *pStockBOLLData=NULL;

	for(int i=0;i<vecStockCodeList.size();i++)
	{
		pStockCode=vecStockCodeList[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
		strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		if(pStockKDJData)
		{
			SAFE_DELETE(pStockKDJData);
		}
		pStockKDJData=NULL;

		if(pStockBOLLData)
		{
			SAFE_DELETE(pStockBOLLData);
		}
		pStockBOLLData=NULL;

		pStockBOLLData=CStockBOLLArithmetic::CalcBOLLData(pStockCode->strStockCode,strNowDate,125,K_LINE_DAY,20);
		if(!pStockBOLLData)
			continue;

		pStockKDJData=CStockKDJArithmetic::CalcKDJData(pStockCode->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
		if(pStockKDJData==NULL)
			continue;

		std::vector<double> vec_price_ma5,vec_price_ma10,vec_price_ma20,vec_price_ma60,vec_price_ma120;
		vec_price_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
		vec_price_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
		vec_price_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
		vec_price_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);
		vec_price_ma120=CStockKDJArithmetic::CalcMA(120,pStockKDJData->vec_close_price);

		std::vector<double>  vec_volume_ma5, vec_volume_ma10;
		vec_volume_ma5= CStockKDJArithmetic::CalcMA(5, pStockKDJData->vec_volume_price);
		vec_volume_ma10 = CStockKDJArithmetic::CalcMA(5, pStockKDJData->vec_volume_price);

		int mSize = pStockKDJData->vec_close_price.size();

		double f_now_volume= pStockKDJData->vec_volume_price[mSize - 1];

		double f_p1_volume= pStockKDJData->vec_volume_price[mSize - 2];

		double f_p1_volume_ma10= vec_volume_ma10[mSize - 2];
		
		double f_per = f_now_volume / f_p1_volume;

		double f_ma10_per = f_now_volume / f_p1_volume_ma10;

		if(f_per>3.0 && f_ma10_per>3.0)
		{
			LimitUpData *pLimitUpData=new LimitUpData();
			pLimitUpData->strStockCode=pStockCode->strStockCode;
			pLimitUpData->strStockName=pStockCode->strStockName;

			pLimitUpData->strDateTime=strNowDate;
			pLimitUpData->mPara1=0;
			pLimitUpData->bPreDown=TRUE;
			vecLimitUpData.push_back(pLimitUpData);

		}

		
	}

	return vecLimitUpData;

}
#else
Vec_LimitUpData   CLimitUpAlg::CLimitUpAlg::doFilter(CTime mDropOffTime)
{
	Vec_LimitUpData vecLimitUpData;

	StockCode* pStockCode = NULL;
	CStockDayTable* pStockDayTable = NULL;
	CString strNowDate;
	Vec_StockCodeList vecStockCodeList = StockDataMgr()->GetStockCodeList();
	
	CStockMACDData* pStockMACDData = NULL;
	
	for (int i = 0; i < vecStockCodeList.size(); i++)
	{
		pStockCode = vecStockCodeList[i];
		pStockDayTable = StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
		strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);
		
		if (pStockMACDData)
		{
			SAFE_DELETE(pStockMACDData);
		}
		pStockMACDData = NULL;

		

		
		pStockMACDData = CStockMACDArithmetic::CalcMACDData(pStockCode->strStockCode, strNowDate, 220, K_LINE_DAY, 12, 26, 9);
		if (pStockMACDData == NULL)
			continue;
#if 1
		int Size = pStockMACDData->vec_macd.size();
		if(Size<200)
			continue;
		int Size_close = pStockMACDData->vec_close_price.size();
		double f_total_macd = 0.0;
		double f_now_close = pStockMACDData->vec_close_price[Size_close - 1];

		if (pStockCode->strStockCode == "SH600403")
		{
			f_total_macd = 0.1;
			f_total_macd = 0.0;
		}
		for (int i = Size -200; i < Size; i++)
		{
			f_total_macd += pStockMACDData->vec_macd[i];
		}

		double f_macd_per = f_total_macd  / f_now_close;
		
		if (f_macd_per < -1.0)
		{
			printf("%s  %s  f_macd_per=%.2f\n", (LPCSTR)pStockCode->strStockCode, (LPCSTR)pStockCode->strStockName, f_macd_per);
			LimitUpData* pLimitUpData = new LimitUpData();
			pLimitUpData->strStockCode = pStockCode->strStockCode;
			pLimitUpData->strStockName = pStockCode->strStockName;

			pLimitUpData->strDateTime = strNowDate;
			pLimitUpData->mPara1 = 0;
			pLimitUpData->bPreDown = TRUE;
			vecLimitUpData.push_back(pLimitUpData);
		}
#else
		int mMatchNums = 0;
		int Size = pStockMACDData->vec_close_price.size();

		double macd_now = pStockMACDData->vec_macd[Size-1];
		double close_price_now = pStockMACDData->vec_close_price[Size-1];
		double f_now_macd_per = (macd_now * 100.0) / close_price_now;
		int okNums = 0;
		if (f_now_macd_per > -5.0 && f_now_macd_per < 2.0)
		{

			for (int i = Size - 5; i < Size; i++)
			{
				double macd_pre = pStockMACDData->vec_macd[i-1];
				double macd = pStockMACDData->vec_macd[i];
				if (macd >= macd_pre)
					okNums++;
			}

		}

		bool bOk = false;
		double f_min_macd = 999.0;
		double f_min_macd_per = 0.0;
		int m_negative_nums = 0;

		for (int i = Size - 40; i < Size; i++)
		{
			double macd = pStockMACDData->vec_macd[i];
			double close_price = pStockMACDData->vec_close_price[i];
			double f_macd_per = (macd * 100.0) / close_price;
			if (f_macd_per < 2.0)
			{
				m_negative_nums++;
			}
		}

		for (int i = Size - 25; i < Size; i++)
		{
			double macd = pStockMACDData->vec_macd[i];
			
			if (macd < 0.0)
			{
				double close_price = pStockMACDData->vec_close_price[i];
				if (f_min_macd > macd)
				{
					f_min_macd = macd;
					f_min_macd_per = abs(f_min_macd)*100.0 / close_price;
				}
					
				
				macd = abs(macd);
				if (macd >= close_price / 20.0)
				{
					bOk = true;
					
				}

				

			}

		}
		if (okNums >= 4 && bOk )
		{
			printf("%s  %s  m_negative_nums=%d  f_min_macd_per=%.2f\n", (LPCSTR)pStockCode->strStockCode, (LPCSTR)pStockCode->strStockName, m_negative_nums,f_min_macd_per);
			LimitUpData* pLimitUpData = new LimitUpData();
			pLimitUpData->strStockCode = pStockCode->strStockCode;
			pLimitUpData->strStockName = pStockCode->strStockName;

			pLimitUpData->strDateTime = strNowDate;
			pLimitUpData->mPara1 = 0;
			pLimitUpData->bPreDown = TRUE;
			vecLimitUpData.push_back(pLimitUpData);
		}

#endif

	}
	return vecLimitUpData;
}

#endif

#endif