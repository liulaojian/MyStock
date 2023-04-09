#include "stdafx.h"
#include "LongAveGroupAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include <math.h> 
#include "CommonMacro.h"
#include "TanAngleAlg.h"
#include "Convert.h"

CLongAveGroupAlg::CLongAveGroupAlg()
{

}

CLongAveGroupAlg::~CLongAveGroupAlg()
{

}

BOOL CLongAveGroupAlg::IsVolM5M10Step(std::vector<double> vecVolM5,std::vector<double> vecVolM10)
{
	int size=vecVolM5.size();

	int mBegin=size-13;		

	int mEnd=size-2;

	BOOL bContiDown=TRUE;
	for(int i=mBegin;i<mEnd;i++)
	{
		bContiDown=TRUE;
		for(int j=i;j<i+10;j++)
		{
			double f_pre_m5=vecVolM5[j-1];
			double f_now_m5=vecVolM5[j];
			double f_pre_m10=vecVolM10[j-1];
			double f_now_m10=vecVolM10[j];

			if(f_now_m5>f_now_m10)
			{
				bContiDown=FALSE;
				break;
			}

			if(f_now_m5>f_pre_m5)
			{
				bContiDown=FALSE;
				break;
			}

			if(f_now_m10>f_pre_m10)
			{
				bContiDown=FALSE;
				break;
			}

		}

		if(bContiDown)
		{
			break;
		}

	}

	if(!bContiDown)
	{
		return FALSE;

	}

	double f_now_m5=vecVolM5[size-1];
	double f_now_m10=vecVolM10[size-1];

	double f_per=(f_now_m5*100.0)/f_now_m10;

	if(f_per<90.0)
		return FALSE;
	return TRUE;


}

Vec_LongAveGroupAlgData  CLongAveGroupAlg::doFilter(CTime mDropOffTime)
{

	Vec_LongAveGroupAlgData vecLongAveGroupAlgData;

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

		if(pStockCode->strStockCode=="SZ300722")
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


		std::vector<double> vec_price_ma5,vec_volume_ma5,vec_volume_ma10;
		vec_price_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
		vec_volume_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_volume_price);
		vec_volume_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_volume_price);
		int size=vec_volume_ma10.size();

		if(pStockKDJData->vec_volume_price[size-1]<1000.0)
			continue;

#if 0
		BOOL bPriceM5ContiUp=TRUE;
		for(int j=size-6;j<size;j++)
		{
			double f_pre_price_m5=vec_price_ma5[j-1];
			double f_now_price_m5=vec_price_ma5[j];
			if(f_now_price_m5<f_pre_price_m5)
			{
				bPriceM5ContiUp=FALSE;
				break;
			}
		}


		BOOL bVolumeM10ContiDown=TRUE;
		for(int j=size-6;j<size;j++)
		{
			double f_pre_volume_m10=vec_volume_ma10[j-1];
			double f_now_volume_m10=vec_volume_ma10[j];
			if(f_pre_volume_m10<f_now_volume_m10)
			{
				bVolumeM10ContiDown=FALSE;
				break;
			}
		}

		if(bPriceM5ContiUp&&bVolumeM10ContiDown)
		{
			LongAveGroupAlgData *pLongAveGroupAlgData=new LongAveGroupAlgData();
			pLongAveGroupAlgData->strStockCode=pStockCode->strStockCode;
			pLongAveGroupAlgData->strStockName=pStockCode->strStockName;
			pLongAveGroupAlgData->strDateTime=strNowDate;
			vecLongAveGroupAlgData.push_back(pLongAveGroupAlgData);
		}
#else

		double f_now_m5=vec_volume_ma5[size-1];
		double f_now_m10=vec_volume_ma10[size-1];

		if(f_now_m5<f_now_m10)		//当前要m5>m10
			continue;

		//发现m5 cross m10 处
		BOOL bCross=FALSE;
		int mCrossIndex=-1;
		for(int i=size-5;i<size;i++)
		{
			double f_n_m5=vec_volume_ma5[i];
			double f_n_m10=vec_volume_ma10[i];

			double f_p_m5=vec_volume_ma5[i-1];
			double f_p_m10=vec_volume_ma10[i-1];

			if(f_p_m5<f_p_m10)
			{
				if(f_n_m5>f_n_m10)
				{
					bCross=TRUE;
					mCrossIndex=i;
					break;
				}
			}
		}

		if(!bCross)
			continue;


		int mBegin=mCrossIndex-11;		

		int mEnd=mCrossIndex-1;

		BOOL bContiDown=TRUE;
		for(int i=mBegin;i<mEnd;i++)
		{
			bContiDown=TRUE;
			for(int j=i;j<i+10;j++)
			{
				double f_pre_m5=vec_volume_ma5[j-1];
				double f_now_m5=vec_volume_ma5[j];
				double f_pre_m10=vec_volume_ma10[j-1];
				double f_now_m10=vec_volume_ma10[j];

				if(f_now_m5>f_now_m10)
				{
					bContiDown=FALSE;
					break;
				}

				if(f_now_m5>f_pre_m5)
				{
					bContiDown=FALSE;
					break;
				}

				if(f_now_m10>f_pre_m10)
				{
					bContiDown=FALSE;
					break;
				}

			}

			if(bContiDown)
			{
				break;
			}

		}



		if(bContiDown)
		{

			LongAveGroupAlgData *pLongAveGroupAlgData=new LongAveGroupAlgData();
			pLongAveGroupAlgData->strStockCode=pStockCode->strStockCode;
			pLongAveGroupAlgData->strStockName=pStockCode->strStockName;
			pLongAveGroupAlgData->strDateTime=strNowDate;
			vecLongAveGroupAlgData.push_back(pLongAveGroupAlgData);
		}


#endif


	}


	return vecLongAveGroupAlgData;
}


