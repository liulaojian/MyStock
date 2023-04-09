#include "stdafx.h"
#include "MulTanAngleAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include <math.h> 
#include "CommonMacro.h"
#define PI 3.14159265
CMulTanAngleAlg::CMulTanAngleAlg()
{

}

CMulTanAngleAlg::~CMulTanAngleAlg()
{


}


Vec_TanAngleData  CMulTanAngleAlg::doFilter(CTime mDropOffTime,int mMulDays,int mBackDays,int mMaxAngle,double f_max_volume_multiple,bool bIgnoreM5,int mMaxInsBack,double f_max_ins_thes)
{
	Vec_TanAngleData vecTanAngleDataNow;
	Vec_TanAngleData vecTanAngleDataResult;
	Vec_TanAngleData vecTanAngleData;

	CStockDayTable*pExpStockDayTable=NULL;

	pExpStockDayTable=StockDataMgr()->GetStockDayTable("SH000001");

	CString strNowDate=pExpStockDayTable->GetNearestStockDayDate(mDropOffTime);
	vecTanAngleDataNow.clear();
	vecTanAngleDataNow=doSubFilter(strNowDate,0,mBackDays,mMaxAngle,f_max_volume_multiple,bIgnoreM5,true,mMaxInsBack,f_max_ins_thes);


	for(int i=1;i<mMulDays;i++)
	{
		vecTanAngleData.clear();
		vecTanAngleData=doSubFilter(strNowDate,i,mBackDays,mMaxAngle,f_max_volume_multiple,bIgnoreM5,false,mMaxInsBack,f_max_ins_thes);
		for(int j=0;j<vecTanAngleDataNow.size();j++)
		{
			CString strNowStockCode=vecTanAngleDataNow[j]->strStockCode;

			BOOL bFound=FALSE;

			for(int n=0;n<vecTanAngleData.size();n++)
			{
				CString strPreStockCode=vecTanAngleData[n]->strStockCode;
				if(strNowStockCode==strPreStockCode)
				{
					bFound=TRUE;
					vecTanAngleDataNow[j]->mTemp++;
					break;
				}

			}

		}

		for(int j=0;j<vecTanAngleData.size();j++)
		{
			SAFE_DELETE(vecTanAngleData[j]);
		}
		
		

	}

	for(int i=0;i<vecTanAngleDataNow.size();i++)
	{
		if(vecTanAngleDataNow[i]->mTemp>=(mMulDays-2))
		{
			TanAngleData *pTanAngleData=new TanAngleData();
			pTanAngleData->strStockCode=vecTanAngleDataNow[i]->strStockCode;
			pTanAngleData->strStockName=vecTanAngleDataNow[i]->strStockName;
			pTanAngleData->fPara0=vecTanAngleDataNow[i]->fPara0;
			pTanAngleData->fPara1= vecTanAngleDataNow[i]->fPara1;
			pTanAngleData->fPara2= vecTanAngleDataNow[i]->fPara2;
			pTanAngleData->fPara3=vecTanAngleDataNow[i]->fPara3;
			pTanAngleData->fPara4=vecTanAngleDataNow[i]->fPara4;
			pTanAngleData->fPara5=vecTanAngleDataNow[i]->fPara5;
			pTanAngleData->fPara6=vecTanAngleDataNow[i]->fPara6;
			pTanAngleData->mPara6=vecTanAngleDataNow[i]->mPara6;
			pTanAngleData->mPara7=vecTanAngleDataNow[i]->mPara7;
			pTanAngleData->mMaxDis=vecTanAngleDataNow[i]->mMaxDis;
			pTanAngleData->fRsi1=vecTanAngleDataNow[i]->fRsi1;
			
			pTanAngleData->mPara8=vecTanAngleDataNow[i]->mPara8;
			pTanAngleData->mPara9=vecTanAngleDataNow[i]->mPara9;
			pTanAngleData->mPara10=vecTanAngleDataNow[i]->mPara10;
			pTanAngleData->fPara7=vecTanAngleDataNow[i]->fPara7;
			pTanAngleData->fPara8=vecTanAngleDataNow[i]->fPara8;
			pTanAngleData->mContiDownNums=vecTanAngleDataNow[i]->mContiDownNums;

			pTanAngleData->strDateTime=vecTanAngleDataNow[i]->strDateTime;
			pTanAngleData->mTemp=0;



			vecTanAngleDataResult.push_back(pTanAngleData);
			//vecTanAngleDataResult.push_back(vecTanAngleDataNow[i]);
		}

	}

	for(int i=0;i<vecTanAngleDataNow.size();i++)
	{
		SAFE_DELETE(vecTanAngleDataNow[i]);
	}
	vecTanAngleDataNow.clear();

	

	return vecTanAngleDataResult;//vecTanAngleDataTotal;
}


int CMulTanAngleAlg::CalcLowPriceContiDown(std::vector<double> vecLowPrice)
{
	int size=vecLowPrice.size();

	double f_pre_6_low_price=vecLowPrice[size-6];
	double f_pre_5_low_price=vecLowPrice[size-5];
	double f_pre_4_low_price=vecLowPrice[size-4];
	double f_pre_3_low_price=vecLowPrice[size-3];
	double f_pre_2_low_price=vecLowPrice[size-2];
	double f_pre_1_low_price=vecLowPrice[size-1];

	BOOL bConti4DayDown=FALSE;
	BOOL bConti5DayDown=FALSE;
	BOOL bConti6DayDown=FALSE;


	if(f_pre_1_low_price<f_pre_2_low_price)
	{
		if(f_pre_2_low_price<f_pre_3_low_price)
		{

			if(f_pre_3_low_price<f_pre_4_low_price)
			{
				bConti4DayDown=TRUE;

				if(f_pre_4_low_price<f_pre_5_low_price)
				{
					bConti5DayDown=TRUE;
					if(f_pre_5_low_price<f_pre_6_low_price)
					{
						bConti6DayDown=TRUE;
					}
				}

			}
		}
	}

	if(bConti6DayDown)
		return 6;

	if(bConti5DayDown)
		return 5;

	if(bConti4DayDown)
		return 4;
	return 0;
}

int CMulTanAngleAlg::CalcVolPriceContiDown(std::vector<double> vecVolPrice)
{

	int size=vecVolPrice.size();

	double f_last_3_vol=vecVolPrice[size-4];
	double f_last_2_vol=vecVolPrice[size-3];
	double f_last_1_vol=vecVolPrice[size-2];
	double f_now_vol=vecVolPrice[size-1];

	if(f_last_3_vol>f_last_2_vol)
	{
		if(f_last_2_vol>f_last_1_vol)
		{
			if(f_last_1_vol>f_now_vol)
			{

				return 4;
			}

		}

	}

	return 0;
}

BOOL CMulTanAngleAlg::IsM5CrossM10(std::vector<double> vecPriceM5,std::vector<double> vecPriceM10)
{
	int size=vecPriceM5.size();

	double f_pre_m5=vecPriceM5[size-2];
	double f_now_m5=vecPriceM5[size-1];

	double f_pre_m10=vecPriceM10[size-2];
	double f_now_m10=vecPriceM10[size-1];

	if(f_pre_m5<f_pre_m10)
	{
		if(f_now_m5>f_now_m10)
		{

			return TRUE;
		}
	}
	return FALSE;
}

int CMulTanAngleAlg::CalcRsiPeakNums(std::vector<double> vecRsi1,int mPreSize)
{
	int size=vecRsi1.size();
	int mIndex=size-mPreSize*2-1;
	double f_rsi1=0.0;
	int mPeakNums=0;
	BOOL bRsiBig=FALSE;
	while(TRUE)
	{
		f_rsi1=vecRsi1[mIndex];
		if(f_rsi1>=85.0)
		{
			if(!bRsiBig)
			{
				mPeakNums++;
				bRsiBig=TRUE;
			}
			mIndex++;
		}
		else
		{
			bRsiBig=FALSE;
			mIndex++;
		}
		if(mIndex>=size)
			break;
	}


	return mPeakNums;

}

int  CMulTanAngleAlg::CalcBigPriceIncreaseNums(std::vector<double> vecClosePrice,int mPreSize,double f_max_ins_thes)
{
	int size=vecClosePrice.size();
	int mNums=0;
	for(int i=size-mPreSize;i<size;i++)
	{
		double f_pre_close_value=vecClosePrice[i-1];
		double f_now_close_value=vecClosePrice[i];
		double f_per=(f_now_close_value-f_pre_close_value)*100.0/f_pre_close_value;
		if(f_per>f_max_ins_thes) //6.0
			mNums++;
	}

	return mNums;
}

int CMulTanAngleAlg::CalcPriceVolumeContiDown(std::vector<double> vecPriceVolume)
{

	//3个连续下降
	int size=vecPriceVolume.size();
	BOOL bConti4DayDown=FALSE;
	BOOL bConti3DayDown=FALSE;
	BOOL bConti2DayDown=FALSE;
	double f_pre_4_vol=vecPriceVolume[size-4];
	double f_pre_3_vol=vecPriceVolume[size-3];
	double f_pre_2_vol=vecPriceVolume[size-2];
	double f_pre_1_vol=vecPriceVolume[size-1];

	if(f_pre_4_vol>f_pre_3_vol)
	{
		if(f_pre_3_vol>f_pre_2_vol)
		{
			if(f_pre_2_vol>f_pre_1_vol)
			{
				bConti4DayDown=TRUE;
			}

		}
	}

	if(bConti4DayDown)
		return 8;

	if(f_pre_3_vol>f_pre_2_vol)
	{
		if(f_pre_2_vol>f_pre_1_vol)
		{

			bConti3DayDown=TRUE;
		}

	}

	if(f_pre_2_vol>f_pre_1_vol)
	{
		bConti2DayDown=TRUE;
	}




	int pre_size=0;

	if(bConti3DayDown)
		pre_size=3;
	else if(bConti2DayDown)
		pre_size=2;
	else
		return 0;

	BOOL bPrePreConti3DayDown=FALSE;
	BOOL bPrePreConti2DayDown=FALSE;
	double f_pre_pre_3_vol=vecPriceVolume[size-pre_size-3];
	double f_pre_pre_2_vol=vecPriceVolume[size-pre_size-2];
	double f_pre_pre_1_vol=vecPriceVolume[size-pre_size-1];

	if(f_pre_pre_3_vol>f_pre_pre_2_vol)
	{
		if(f_pre_pre_2_vol>f_pre_pre_1_vol)
		{

			bPrePreConti3DayDown=TRUE;
		}

	}

	if(f_pre_pre_2_vol>f_pre_pre_1_vol)
	{

		bPrePreConti2DayDown=TRUE;
	}


	if(bConti3DayDown&&bPrePreConti3DayDown)
		return 6;

	if(bConti2DayDown&&bPrePreConti3DayDown)
		return 5;

	if(bConti3DayDown&&bPrePreConti2DayDown)
		return 5;

	if(bConti2DayDown&&bPrePreConti2DayDown)
		return 4;

	return 0;
}

Vec_TanAngleData   CMulTanAngleAlg::doSubFilter(CString strDate,int mPreDays,int mBackDays,int mMaxAngle,double f_max_volume_multiple,bool bIgnoreM5,bool bCalcLow,int mMaxInsBack,double f_max_ins_thes)
{
	Vec_TanAngleData vecTanAngleData;
	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	Vec_StockCodeList vecStockCodeList=StockDataMgr()->GetStockCodeList();

	int mPreSize=mBackDays;	//10;
	double fTanThold=30.0;
	CString strNowDate;
	CStockRSIData* pStockRSIData=NULL;
	CStockKDJData *pStockKDJData=NULL;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		try
		{
			pStockCode=vecStockCodeList[i];
			pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);

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

			if(mPreDays>0)
				strNowDate=pStockDayTable->GetStockDayDatePreOfIndex(strDate,mPreDays);
			else
				strNowDate=strDate;
			pStockRSIData=CStockRSIArithmetic::CalcRSIData(pStockCode->strStockCode,strNowDate,125,K_LINE_DAY,6,12,24); 
			if(!pStockRSIData)
				continue;

			int rsi_size=pStockRSIData->vec_rsi_1_value.size();


			
			pStockKDJData=CStockKDJArithmetic::CalcKDJData(pStockCode->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
			if(pStockKDJData==NULL)
				continue;

			std::vector<double> vec_price_ma5,vec_price_ma10,vec_price_ma20,vec_price_ma60;
			vec_price_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
			vec_price_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
			vec_price_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
			vec_price_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);

		
			int mContiDownNums=0;
			if(bCalcLow)
			{
				if(pStockCode->strStockCode=="SH600291")
				{
					int b=0;
					b++;
					if(strNowDate == "2020/06/29")
					{
						int a=0;
						a++;
					}
				}
				mContiDownNums=CalcLowPriceContiDown(pStockKDJData->vec_low_price);
			}
			else
				mContiDownNums=-1;
			int mContiVolDownNums=CalcVolPriceContiDown(pStockKDJData->vec_volume_price);
			int mBigIncreaseNums=CalcBigPriceIncreaseNums(pStockKDJData->vec_close_price,mMaxInsBack,f_max_ins_thes);
			int mRsi1BigNums=CalcRsiPeakNums(pStockRSIData->vec_rsi_1_value,mPreSize);

			BOOL bM5CrossM10=IsM5CrossM10(vec_price_ma5,vec_price_ma10);
			

			int size=pStockKDJData->vec_volume_price.size();

			int mNowIsMaxPriceNums=0;		//目前这个价位是前PreSize日前，多少日的最高值

			double f_now_close_price=pStockKDJData->vec_close_price[size-1];
			for(int j=size-mPreSize-1;j>size-130;j--)
			{
				double f_pre_close_price=pStockKDJData->vec_close_price[j];
				if(f_now_close_price>f_pre_close_price)
				{
					mNowIsMaxPriceNums++;
				}
				else
				{
					break;
				}
			}

			double f_60_day_increase=0.0;

			double f_now_60_day_close_value=vec_price_ma60[size-1];
			double f_presize_60_day_close_value=vec_price_ma60[size-mPreSize];

			if(f_presize_60_day_close_value>0.0)
				f_60_day_increase=(f_now_60_day_close_value-f_presize_60_day_close_value)*100.0/f_presize_60_day_close_value;
			else
				f_60_day_increase=0.0;

			
			int m_continus_price_m10_up_nums=0;
			for(int j=size-1;j>=size-90;j--)
			{
				double f_pre_val=vec_price_ma10[j-1];
				double f_now_val=vec_price_ma10[j];

				if(f_now_val>=f_pre_val)
					m_continus_price_m10_up_nums++;
				else
					break;
			}

			int m_continus_price_m20_up_nums=0;
			for(int j=size-1;j>=size-90;j--)
			{
				double f_pre_val=vec_price_ma20[j-1];
				double f_now_val=vec_price_ma20[j];

				if(f_now_val>=f_pre_val)
					m_continus_price_m20_up_nums++;
				else
					break;
			}

			int m_continus_price_m60_up_nums=0;
			for(int j=size-1;j>=size-90;j--)
			{
				double f_pre_val=vec_price_ma60[j-1];
				double f_now_val=vec_price_ma60[j];

				if(f_now_val>=f_pre_val)
					m_continus_price_m60_up_nums++;
				else
					break;
			}


			BOOL bOk=TRUE;
			for(int j=size-mPreSize;j<size;j++)
			{
				double f_pre_m5=vec_price_ma5[j-1];
				double f_now_m5=vec_price_ma5[j];
				if(f_now_m5<f_pre_m5)
				{
					bOk=FALSE;
					break;

				}

			}

			if(!bIgnoreM5)
			{
				if(!bOk)
					continue;
			}


			bOk=TRUE;
			for(int j=size-mPreSize;j<size;j++)
			{
				double f_pre_m10=vec_price_ma10[j-1];
				double f_now_m10=vec_price_ma10[j];
				if(f_now_m10<f_pre_m10)
				{
					bOk=FALSE;
					break;

				}

			}
			if(!bOk)
				continue;

			bOk=TRUE;
			for(int j=size-mPreSize;j<size;j++)
			{
				double f_pre_m20=vec_price_ma20[j-1];
				double f_now_m20=vec_price_ma20[j];
				if(f_now_m20<f_pre_m20)
				{
					bOk=FALSE;
					break;

				}

			}
			if(!bOk)
				continue;

			bOk=TRUE;
			for(int j=size-mPreSize;j<size;j++)
			{
				double f_pre_m60=vec_price_ma60[j-1];
				double f_now_m60=vec_price_ma60[j];
				if(f_now_m60<f_pre_m60)
				{
					bOk=FALSE;
					break;

				}

			}
			if(!bOk)
				continue;


			double f_now_m5_price=vec_price_ma5[size-1];
			double f_now_m10_price=vec_price_ma10[size-1];
			double f_now_m20_price=vec_price_ma20[size-1];

			if(f_now_m10_price>f_now_m5_price)
				continue;
			if(f_now_m20_price>f_now_m10_price)
				continue;


			double f_preSize_m5=vec_price_ma5[size-mPreSize-1];
			double f_now_m5=vec_price_ma5[size-1];
			double f_m5_increase=(f_now_m5-f_preSize_m5)*100.0/f_preSize_m5;
			double f_m5_tan=f_m5_increase/(double)mPreSize;


			double f_preSize_m10=vec_price_ma10[size-mPreSize-1];
			double f_now_m10=vec_price_ma10[size-1];
			double f_m10_increase=(f_now_m10-f_preSize_m10)*100.0/f_preSize_m10;
			double f_m10_tan=f_m10_increase/(double)mPreSize;

			//double f_ma10_tan_angle=atan (f_m10_tan) * 180 / PI;

			//if(f_ma10_tan_angle<fTanThold)
			//	continue;

			double f_preSize_m20=vec_price_ma20[size-mPreSize-1];
			double f_now_m20=vec_price_ma20[size-1];
			double f_m20_increase=(f_now_m20-f_preSize_m20)*100.0/f_preSize_m20;
			double f_m20_tan=f_m20_increase/(double)mPreSize;

			//double f_ma20_tan_angle=atan (f_m20_tan) * 180 / PI;


			//if(f_ma20_tan_angle<fTanThold)
			//	continue;

			double f_preSize_m60=vec_price_ma60[size-mPreSize-1];
			double f_now_m60=vec_price_ma60[size-1];
			double f_m60_increase=(f_now_m60-f_preSize_m60)*100.0/f_preSize_m60;
			double f_m60_tan=f_m60_increase/(double)mPreSize;



			std::vector<double> vec_volume_ma5,vec_volume_ma10;
			vec_volume_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_volume_price);
			vec_volume_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_volume_price);

			double f_max_volume=0.0;
			int  m_max_volume_index=-1;
			for(int j=size-mPreSize;j<size;j++)
			{

				if(pStockKDJData->vec_volume_price[j]>f_max_volume)
				{
					f_max_volume=pStockKDJData->vec_volume_price[j];
					m_max_volume_index=j;
				}
			}
			int m_max_volume_distance=size-m_max_volume_index;

			double f_cur_volume=pStockKDJData->vec_volume_price[size-1];
			double f_cur_volume_m10=vec_volume_ma10[size-1];
			double f_cur_vol_m10_per=f_cur_volume/f_cur_volume_m10;
			double f_cur_rsi_1=pStockRSIData->vec_rsi_1_value[rsi_size-1];

			int m_20_10_cross_index=-1;
			for(int j=size-1;j>size-90;j--)
			{
				double f_now_m20=vec_price_ma20[j];
				double f_now_m10=vec_price_ma10[j];
				if(f_now_m10<f_now_m20)
				{
					m_20_10_cross_index=j;
					break;
				}
			}

			int m_10_big_20_nums=-1;

			if(m_20_10_cross_index>0)
				m_10_big_20_nums=size-m_20_10_cross_index;
			else
				m_10_big_20_nums=90;


			double f_20_10_cross_price_increase=0.0;

			if(m_20_10_cross_index>0)
			{
				double f_20_10_cross_close_pirce=pStockKDJData->vec_close_price[m_20_10_cross_index];
				double f_now_close_pirce=pStockKDJData->vec_close_price[size-1];
				f_20_10_cross_price_increase=(f_now_close_pirce-f_20_10_cross_close_pirce)*100.0/f_20_10_cross_close_pirce;
			}
			else
			{
				double f_20_10_cross_close_pirce=pStockKDJData->vec_close_price[size-90];
				double f_now_close_pirce=pStockKDJData->vec_close_price[size-1];
				f_20_10_cross_price_increase=(f_now_close_pirce-f_20_10_cross_close_pirce)*100.0/f_20_10_cross_close_pirce;
			}




			int m_60_20_cross_index=-1;
			for(int j=size-1;j>size-90;j--)
			{
				double f_now_m60=vec_price_ma60[j];
				double f_now_m20=vec_price_ma20[j];
				if(f_now_m20<f_now_m60)
				{
					m_60_20_cross_index=j;
					break;
				}
			}

			int m_60_big_20_nums=-1;

			if(m_60_20_cross_index>0)
				m_60_big_20_nums=size-m_60_20_cross_index;
			else
				m_60_big_20_nums=90;

			double f_60_20_cross_price_increase=0.0;
			if(m_60_20_cross_index>0)
			{
				double f_60_20_cross_close_pirce=pStockKDJData->vec_close_price[m_60_20_cross_index];
				double f_now_close_pirce=pStockKDJData->vec_close_price[size-1];
				f_60_20_cross_price_increase=(f_now_close_pirce-f_60_20_cross_close_pirce)*100.0/f_60_20_cross_close_pirce;
			}
			else
			{
				double f_60_20_cross_close_pirce=pStockKDJData->vec_close_price[size-90];
				double f_now_close_pirce=pStockKDJData->vec_close_price[size-1];
				f_60_20_cross_price_increase=(f_now_close_pirce-f_60_20_cross_close_pirce)*100.0/f_60_20_cross_close_pirce;
			}

			double f_total_price_volume=0.0;
			double f_ave_price_volume=0.0;
			double f_total_volume_ma10=0.0;
			double f_ave_volume_ma10=0.0;


			for(int j=size-5;j<size;j++)
			{
				f_total_price_volume+=pStockKDJData->vec_volume_price[j];
				f_total_volume_ma10+=vec_volume_ma10[j];

			}
			f_ave_price_volume=f_total_price_volume/5.0;
			f_ave_volume_ma10=f_total_volume_ma10/5.0;



			double f_ave_volume=0.0;
			double f_m10_ave_volume=0.0;
			double f_ave_toatl_volume=0.0;
			double f_m10_ave_toatl_volume=0.0;
			for(int j=size-mPreSize;j<size;j++)
			{
				f_ave_toatl_volume+=pStockKDJData->vec_volume_price[j];
			}

			for(int j=size-mPreSize*7;j<size-mPreSize;j++)
			{
				f_m10_ave_toatl_volume+=vec_volume_ma10[j];
			}

			f_ave_volume=f_ave_toatl_volume/(double)mPreSize;
			f_m10_ave_toatl_volume=f_m10_ave_toatl_volume/((double)mPreSize*6);
			double f_ave_volume_per=f_ave_volume/f_m10_ave_toatl_volume;


			double f_ma5_angle=atan (f_m5_tan) * 180 / PI;
			double f_ma10_angle=atan (f_m10_tan) * 180 / PI;
			double f_ma20_angle=atan (f_m20_tan) * 180 / PI; 
			double f_ma60_angle=atan (f_m60_tan) * 180 / PI; 

			if(f_ma5_angle>mMaxAngle)//70.0
				continue;
			if(f_ma10_angle>mMaxAngle)//70.0
				continue;
			if(f_ma20_angle>mMaxAngle)//70.0
				continue;

			//double f_max_volume_per=f_ave_price_volume/f_ave_volume_ma10;//f_max_volume/vec_volume_ma10[m_max_volume_index];
			double f_max_volume_per=f_max_volume/vec_volume_ma10[m_max_volume_index];
			printf("%s f_max_volume_per %f \n",pStockCode->strStockCode,f_max_volume_per);
			if(f_max_volume_per>f_max_volume_multiple) //1.8
			{
				//if(f_ma5_angle>35.0||f_ma10_angle>35.0||f_ma20_angle>30.0)
				continue;
			}

			if(f_cur_vol_m10_per>f_max_volume_multiple)
			{
				continue;
			}



			printf("%s m10 tan %f  m20  tan   %f \n",pStockCode->strStockCode,f_ma10_angle,f_ma20_angle);

			TanAngleData *pTanAngleData=new TanAngleData();
			pTanAngleData->strStockCode=pStockCode->strStockCode;
			pTanAngleData->strStockName=pStockCode->strStockName;
			pTanAngleData->fPara0=f_ma5_angle;
			pTanAngleData->fPara1= f_ma10_angle;
			pTanAngleData->fPara2= f_ma20_angle;
			pTanAngleData->fPara3=f_ma60_angle;
			pTanAngleData->fPara4=f_max_volume_per;
			pTanAngleData->fPara5=f_ave_volume_per;
			pTanAngleData->fPara6=f_60_20_cross_price_increase;
			pTanAngleData->fPara7=f_20_10_cross_price_increase;
			pTanAngleData->fPara8=f_60_day_increase;
			pTanAngleData->mPara6=m_10_big_20_nums;
			pTanAngleData->mPara7=m_60_big_20_nums;
			pTanAngleData->mPara8=m_continus_price_m10_up_nums;
			pTanAngleData->mPara9=m_continus_price_m20_up_nums;
			pTanAngleData->mPara10=m_continus_price_m60_up_nums;
			pTanAngleData->mMaxDis=m_max_volume_distance;
			pTanAngleData->mContiDownNums=mContiDownNums;
			pTanAngleData->mContiVolDownNums=mContiVolDownNums;
			pTanAngleData->mNowIsMaxPriceNums=mNowIsMaxPriceNums;
			pTanAngleData->mBigIncreaseNums=mBigIncreaseNums;
			pTanAngleData->mRsi1BigNums=mRsi1BigNums;
			pTanAngleData->fRsi1=f_cur_rsi_1;
			pTanAngleData->strDateTime=strNowDate;
			pTanAngleData->mNextGrow=0;
			pTanAngleData->fNextGrow=0.0;
			pTanAngleData->bM5CrossM10=bM5CrossM10;
			pTanAngleData->mTemp=0;
			pTanAngleData->mCalcuSel=0;
			pTanAngleData->bCalcuOk=FALSE;
			for(int j=rsi_size-31;j<rsi_size;j++)
			{
				pTanAngleData->vec_rsi_1.push_back(pStockRSIData->vec_rsi_1_value[j]);
			}
			for(int j=size-31;j<size;j++)
			{
				pTanAngleData->vec_close_value.push_back(pStockKDJData->vec_close_price[j]);
			}

			for(int j=size-31;j<size;j++)
			{
				pTanAngleData->vec_begin_value.push_back(pStockKDJData->vec_open_price[j]);
			}

			for(int j=size-31;j<size;j++)
			{
				pTanAngleData->vec_high_value.push_back(pStockKDJData->vec_high_price[j]);
			}
			for(int j=size-31;j<size;j++)
			{
				pTanAngleData->vec_low_value.push_back(pStockKDJData->vec_low_price[j]);
			}


			for(int j=size-31;j<size;j++)
			{
				pTanAngleData->vec_price_m5.push_back(vec_price_ma5[j]);
			}

			for(int j=size-31;j<size;j++)
			{
				pTanAngleData->vec_price_m10.push_back(vec_price_ma10[j]);
			}

			for(int j=size-31;j<size;j++)
			{

				pTanAngleData->vec_volume_m5.push_back(vec_volume_ma5[j]);
			}


			for(int j=size-31;j<size;j++)
			{
				pTanAngleData->vec_volume_m10.push_back(vec_volume_ma10[j]);
			}

			vecTanAngleData.push_back(pTanAngleData);
		}
		catch(...)
		{

			printf("MulTanAngleAlg catch\n");
		}
		


	}

	return vecTanAngleData;
}