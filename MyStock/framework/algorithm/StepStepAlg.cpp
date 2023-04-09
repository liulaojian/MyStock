#include "stdafx.h"
#include "StepStepAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include <math.h> 
#include "CommonMacro.h"
#include "TanAngleAlg.h"
#include "Convert.h"

CStepStepAlg::CStepStepAlg()
{

}

CStepStepAlg::~CStepStepAlg()
{

}

int  CStepStepAlg::CalcMNPriceContiUp(std::vector<double> vecPriceMN)
{
	int size=vecPriceMN.size();

	if(size<80)
		return 0;
	int mContiUpNums=0;
	int mContiDownNums=0;
	for(int i=size-1;i>=size-75;i--)
	{
		double f_now_mn=vecPriceMN[i];
		double f_pre_mn=vecPriceMN[i-1];
		if(f_now_mn>=f_pre_mn)
		{
			mContiUpNums++;
			mContiDownNums=0;
		}
		else
		{
			mContiDownNums++;
			if(mContiDownNums>=2)
				break;
		}
	}

	return mContiUpNums;
}

Vec_StepStepAlgData CStepStepAlg:: doFilter(CTime mDropOffTime)
{
	Vec_StepStepAlgData vecStepStepAlgData;

	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	Vec_StockCodeList vecStockCodeList=StockDataMgr()->GetStockCodeList();

	CStockRSIData* pStockRSIData=NULL;
	CStockKDJData *pStockKDJData=NULL;

	for(int i=0;i<vecStockCodeList.size();i++)
	{
		pStockCode=vecStockCodeList[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
		strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);

		if(pStockRSIData)
		{
			SAFE_DELETE(pStockRSIData);
		}
		pStockRSIData=NULL;

		if(pStockKDJData)
		{
			SAFE_DELETE(pStockKDJData);
		}
		pStockKDJData=NULL;

		if(pStockCode->strStockCode=="SZ000619")
		{
			int a=0;
			a++;
		}

		pStockRSIData=CStockRSIArithmetic::CalcRSIData(pStockCode->strStockCode,strNowDate,125,K_LINE_DAY,6,12,24); 
		if(!pStockRSIData)
			continue;

		int rsi_size=pStockRSIData->vec_rsi_1_value.size();

		pStockKDJData=CStockKDJArithmetic::CalcKDJData(pStockCode->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
		if(pStockKDJData==NULL)
			continue;


		std::vector<double> vec_volume_ma5,vec_volume_ma10;
		vec_volume_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_volume_price);
		vec_volume_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_volume_price);
		int size=vec_volume_ma10.size();
		

		std::vector<double> vec_price_ma20,vec_price_ma60,vec_price_ma120;
		vec_price_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
		vec_price_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);
		vec_price_ma120=CStockKDJArithmetic::CalcMA(120,pStockKDJData->vec_close_price);

		int m20ContiNums=CalcMNPriceContiUp(vec_price_ma20);

		int m60ContiNums=CalcMNPriceContiUp(vec_price_ma60);

		int m120ContiNums=CalcMNPriceContiUp(vec_price_ma120);

		if(pStockKDJData->vec_volume_price[size-1]<1000.0)
			continue;

		double f_p4_per;
		double f_p3_per;
		double f_p2_per;
		double f_p1_per;
		double f_now_per;

		double f_now_close_value=pStockKDJData->vec_close_price[size-1];
		double f_p1_close_value=pStockKDJData->vec_close_price[size-2];
		double f_p2_close_value=pStockKDJData->vec_close_price[size-3];
		double f_p3_close_value=pStockKDJData->vec_close_price[size-4];
		double f_p4_close_value=pStockKDJData->vec_close_price[size-5];
		double f_p5_close_value=pStockKDJData->vec_close_price[size-6];

		f_p4_per=(f_p4_close_value-f_p5_close_value)*100.0/f_p5_close_value;
		f_p3_per=(f_p3_close_value-f_p4_close_value)*100.0/f_p4_close_value;
		f_p2_per=(f_p2_close_value-f_p3_close_value)*100.0/f_p3_close_value;
		f_p1_per=(f_p1_close_value-f_p2_close_value)*100.0/f_p2_close_value;
		f_now_per=(f_now_close_value-f_p1_close_value)*100.0/f_p1_close_value;


		BOOL bContiDown=TRUE;
		int mBegin=size-10;
		int mEnd=size;
		for(int i=mBegin;i<mEnd;i++)
		{
			double f_pre_m5=vec_volume_ma5[i-1];
			double f_now_m5=vec_volume_ma5[i];
			double f_pre_m10=vec_volume_ma10[i-1];
			double f_now_m10=vec_volume_ma10[i];

			if(f_now_m5>f_now_m10)
			{
				bContiDown=FALSE;
				break;
			}

			//if(f_now_m5>f_pre_m5)
			//{
			//	bContiDown=FALSE;
			//	break;
			//}

			if(f_now_m10>f_pre_m10)
			{
				bContiDown=FALSE;
				break;
			}
		}


		if(!bContiDown)
		{
			continue;
		}

		mBegin=size-45;
		mEnd=size-1;
		int   mStepNums=0;
		int  mBeginIndex=-1;
		for(int i=mEnd;i>mBegin;i--)
		{
			double f_pre_m5=vec_volume_ma5[i-1];
			double f_now_m5=vec_volume_ma5[i];
			double f_pre_m10=vec_volume_ma10[i-1];
			double f_now_m10=vec_volume_ma10[i];

			if(f_pre_m5>f_pre_m10)
			{
				if(f_now_m5<f_now_m10)
				{
					mBeginIndex=i;
					break;
					
				}
			}

			mStepNums++;
		}

		if(mBeginIndex<0)
			continue;


		double fCurStepPer=0.0;


		double f_now_m5=vec_volume_ma5[size-1];
		double f_now_m10=vec_volume_ma10[size-1];

		fCurStepPer=f_now_m5/f_now_m10;

		double fTotalStepPer=0.0;

		for(int i=mBeginIndex;i<size;i++)
		{
			double f_now_m5=vec_volume_ma5[i];
			double f_now_m10=vec_volume_ma10[i];

			double f_per=1.0-f_now_m5/f_now_m10;

			fTotalStepPer+=f_per;
		}
		double fAveStepPer=fTotalStepPer/mStepNums;

		StepStepAlgData * pStepStepAlgData=new StepStepAlgData();
		pStepStepAlgData->strStockCode=pStockCode->strStockCode;
		pStepStepAlgData->strStockName=pStockCode->strStockName;
		pStepStepAlgData->strDateTime=strNowDate;
		pStepStepAlgData->mStepNums=mStepNums;
		pStepStepAlgData->fAveStepPer=fAveStepPer;
		pStepStepAlgData->fCurStepPer=fCurStepPer;
		pStepStepAlgData->fTotalStepPer=fTotalStepPer;
		pStepStepAlgData->f_now_per=f_now_per;
		pStepStepAlgData->f_p1_per=f_p1_per;
		pStepStepAlgData->f_p2_per=f_p2_per;
		pStepStepAlgData->f_p3_per=f_p3_per;
		pStepStepAlgData->f_p4_per=f_p4_per;
		pStepStepAlgData->m20ContiNums=m20ContiNums;
		pStepStepAlgData->m60ContiNums=m60ContiNums;
		pStepStepAlgData->m120ContiNums=m120ContiNums;

		vecStepStepAlgData.push_back(pStepStepAlgData);

	}

	return vecStepStepAlgData;

}