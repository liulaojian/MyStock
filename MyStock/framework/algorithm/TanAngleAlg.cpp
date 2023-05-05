#include "stdafx.h"
#include <stdio.h>
#include "TanAngleAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include <math.h> 
#include "CommonMacro.h"
#include "StockBOLLArithmetic.h"
#define PI 3.14159265
CTanAngleAlg::CTanAngleAlg()
{


}

CTanAngleAlg::~CTanAngleAlg()
{


}


int CTanAngleAlg::CalcLowPriceContiDown(std::vector<double> vecLowPrice)
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

int CTanAngleAlg::CalcVolPriceContiDown(std::vector<double> vecVolPrice,std::vector<double> vecClosePrice)
{

	int size=vecVolPrice.size();
	double f_last_4_vol=vecVolPrice[size-5];
	double f_last_3_vol=vecVolPrice[size-4];
	double f_last_2_vol=vecVolPrice[size-3];
	double f_last_1_vol=vecVolPrice[size-2];
	double f_now_vol=vecVolPrice[size-1];

	double f_last_4_price=vecClosePrice[size-5];
	double f_last_4_per=(f_last_4_price-vecClosePrice[size-6])*100.0/vecClosePrice[size-6];


	double f_last_3_price=vecClosePrice[size-4];
	double f_last_3_per=(f_last_3_price-vecClosePrice[size-5])*100.0/vecClosePrice[size-5];

	double f_last_2_price=vecClosePrice[size-3];
	double f_last_2_per=(f_last_2_price-f_last_3_price)*100.0/f_last_3_price;


	double f_last_1_price=vecClosePrice[size-2];
	double f_last_1_per=(f_last_1_price-f_last_2_price)*100.0/f_last_2_price;

	double f_now_price=vecClosePrice[size-1];
	double f_now_per=(f_now_price-f_last_1_price)*100.0/f_last_1_price;


	/*if(f_last_4_vol>f_last_3_vol)
	{
		if(f_last_3_vol>f_last_2_vol)
		{
			if(f_last_2_vol>f_last_1_vol)
			{

				if(f_last_1_vol>f_now_vol)
				{

					if(f_last_4_per<6.0)
						return 5;
				}
			}
		}

	}*/

	if(f_last_3_vol>f_last_2_vol)
	{
		if(f_last_2_vol>f_last_1_vol)
		{
			if(f_last_1_vol>f_now_vol)
			{
				if(f_last_3_per<5.0)
				{
					if(f_last_3_per>0.0)
					{
						if(f_now_per<0.0&&f_last_1_per<0.0&&f_last_2_per<0.0)
						{
							return 4;

						}

					}
					else
					{
						int mNums=0;
						if(f_now_per<0.0)
							mNums++;
						if(f_last_1_per<0.0)
							mNums++;
						if(f_last_2_per<0.0)
							mNums++;
						if(f_now_per<3.0&&f_last_1_per<3.0&&f_last_2_per<3.0)
						{
							double f_per=f_now_per+f_last_1_per+f_last_2_per;
							if(f_per<-4.0)
								return 4;
							else if(mNums>=2)
								return 4;
						}

					}
					
				}
				else
				{
					double f_per=(f_now_price-f_last_3_price)*100.0/f_last_3_price;
					if(f_per<-12.0)
					{
						return 4;
					}
					else
						return 3;
				}
				
			}

		}

	}

	return 0;
}

BOOL CTanAngleAlg::IsM5CrossM10(std::vector<double> vecPriceM5,std::vector<double> vecPriceM10)
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

int  CTanAngleAlg::GetVolM5M10StepIndex(std::vector<double> vecVolM5,std::vector<double> vecVolM10, int mBackDays)
{

	int size=vecVolM5.size();

	int mBegin=size-(mBackDays+27);		//35

	int mEnd=size-(mBackDays+2); //10

	BOOL bContiDown=TRUE;
	int mStepIndex=-1;
	for(int i=mBegin;i<mEnd;i++)
	{
		bContiDown=TRUE;
		mStepIndex=i;
		for(int j=i;j<i+10;j++)	//10
		{
			if (j >= vecVolM5.size())
				break;
			if (j >= vecVolM10.size())
				break;
			double f_pre_m5=vecVolM5[j-1];
			double f_now_m5=vecVolM5[j];
			double f_pre_m10=vecVolM10[j-1];
			double f_now_m10=vecVolM10[j];

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

		if(bContiDown)
		{
			break;
		}

	}

	if(!bContiDown)
	{
		return 0;

	}
	mStepIndex+=10;

	mStepIndex=size-mStepIndex;

	/*bContiDown=TRUE;
	for(int i=mBegin;i<mEnd;i++)
	{
		bContiDown=TRUE;
		for(int j=i;j<i+10;j++)
		{
			double f_pre_m10=vecVolM10[j-1];
			double f_now_m10=vecVolM10[j];
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

	}*/


	return mStepIndex;
}

int  CTanAngleAlg::CalcBigPriceIncreaseNums(std::vector<double> vecClosePrice,int mPreSize,double f_max_ins_thes)
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

int CTanAngleAlg::CalcPriceVolumeContiDown(std::vector<double> vecPriceVolume)
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

int CTanAngleAlg::CalcRsiPeakNums(std::vector<double> vecRsi1,int mPreSize)
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

int  CTanAngleAlg::CalcMNPriceContiUp(std::vector<double> vecPriceMN)
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


int CTanAngleAlg::CalcVolM5ContiUp(std::vector<double> vecVolM5)
{
	int size = vecVolM5.size();
	
	int mContiUpNums = 0;
	for (int i = size - 1; i >= size - 75; i--)
	{
		double f_now_mn = vecVolM5[i];
		double f_pre_mn = vecVolM5[i-1];
		if (f_now_mn >= f_pre_mn)
		{
			mContiUpNums++;
		}
		else
		{
			break;
		}
	}


	return mContiUpNums;
}

int CTanAngleAlg::CalcVolM10ContiUp(std::vector<double> vecVolM10)
{
	int size = vecVolM10.size();

	int mContiUpNums = 0;
	for (int i = size - 1; i >= size - 75; i--)
	{
		double f_now_mn = vecVolM10[i];
		double f_pre_mn = vecVolM10[i - 1];
		if (f_now_mn >= f_pre_mn)
		{
			mContiUpNums++;
		}
		else
		{
			break;
		}
	}


	return mContiUpNums;
}

int CTanAngleAlg::CalcPriceM5ContiUp(std::vector<double> vecPriceM5)
{
	int size = vecPriceM5.size();

	int mContiUpNums = 0;
	for (int i = size - 1; i >= size - 75; i--)
	{
		double f_now_mn = vecPriceM5[i];
		double f_pre_mn = vecPriceM5[i - 1];
		if (f_now_mn >= f_pre_mn)
		{
			mContiUpNums++;
		}
		else
		{
			break;
		}
	}


	return mContiUpNums;
}
int CTanAngleAlg::CalcPriceM10ContiUp(std::vector<double> vecPriceM10)
{
	int size = vecPriceM10.size();

	int mContiUpNums = 0;
	for (int i = size - 1; i >= size - 75; i--)
	{
		double f_now_mn = vecPriceM10[i];
		double f_pre_mn = vecPriceM10[i - 1];
		if (f_now_mn >= f_pre_mn)
		{
			mContiUpNums++;
		}
		else
		{
			break;
		}
	}


	return mContiUpNums;
}

int CTanAngleAlg::CalcPriceM20ContiUp(std::vector<double> vecPriceM20)
{
	int size = vecPriceM20.size();

	int mContiUpNums = 0;
	for (int i = size - 1; i >= size - 75; i--)
	{
		double f_now_mn = vecPriceM20[i];
		double f_pre_mn = vecPriceM20[i - 1];
		if (f_now_mn >= f_pre_mn)
		{
			mContiUpNums++;
		}
		else
		{
			break;
		}
	}


	return mContiUpNums;
}


double CalcCustomToatlValue(CStockRSIData* pStockRSIData)
{
	double f_total_value = 0.0;
	double f_pre_value = 0.0;
	int mKdjNums = 10;
	int mKdjMuls = 3;
	std::vector<double> vec_ma5, vec_ma10;
	vec_ma5 = CStockKDJArithmetic::CalcMA(5, pStockRSIData->vec_volume_price);
	vec_ma10 = CStockKDJArithmetic::CalcMA(10, pStockRSIData->vec_volume_price);
	int size = vec_ma5.size();
	for (int j = size - mKdjNums; j < size; j++)
	{
		double begin = pStockRSIData->vec_open_price[j];
		double end = pStockRSIData->vec_close_price[j];
		double f = -((end - begin) * 100.0 / begin);

		double vol = pStockRSIData->vec_volume_price[j];
		double vol_m10 = vec_ma10[j];
		double vol_m5 = vec_ma5[j];
		if (vol <= 0.01)
		{
			f_total_value += f_pre_value;
			continue;
		}


		double g;

		if (f >= 0.0)
			g = vol_m10 / vol;
		else
			g = vol / vol_m10;

		double f_muls = g;
		if (vol < vol_m5)
		{
			for (int n = 1; n < mKdjMuls; n++)
			{
				f_muls = f_muls * g;
			}

		}

		double f_nums = 1.0;
		
		double value = f * f_muls * f_nums;
		f_pre_value = value;
		f_total_value += value;

	}
	
	return f_total_value;
}

Vec_TanAngleData  CTanAngleAlg::doFilter(CTime mDropOffTime,int mBackDays,int mMaxAngle,double f_max_volume_multiple,bool bIgnoreM5,bool bUseM120,bool bUseAllUp,int mMaxInsBack,double f_max_ins_thes)
{
	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	Vec_StockCodeList vecStockCodeList=StockDataMgr()->GetStockCodeList();

	int mPreSize=mBackDays;	//10;
	double fTanThold=30.0;
	CStockRSIData* pStockRSIData=NULL;
	CStockKDJData *pStockKDJData=NULL;
	CStockBOLLData *pStockBOLLData=NULL;
	int mTimeType = K_LINE_DAY;
	if (mKLineType==1)
		mTimeType = K_LINE_60MIN;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		pStockCode=vecStockCodeList[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
		
		strNowDate = pStockDayTable->GetNearestStockDayDate(mDropOffTime);

		if (mKLineType == 1)
			strNowDate += " 0935";
		
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
		
		if(pStockBOLLData)
		{
			SAFE_DELETE(pStockBOLLData);
		}
		pStockBOLLData=NULL;

		pStockBOLLData=CStockBOLLArithmetic::CalcBOLLData(pStockCode->strStockCode,strNowDate,125, mTimeType,20);//K_LINE_DAY
		if(!pStockBOLLData)
			continue;

		pStockRSIData=CStockRSIArithmetic::CalcRSIData(pStockCode->strStockCode,strNowDate,125, mTimeType,6,12,24); //K_LINE_DAY
		if(!pStockRSIData)
			continue;

	
		int rsi_size=pStockRSIData->vec_rsi_1_value.size();
		if(pStockCode->strStockCode=="SZ300654")
		{
			int a=0;
			a++;

		}
		int boll_size=pStockBOLLData->vec_boll.size();
	
		pStockKDJData=CStockKDJArithmetic::CalcKDJData(pStockCode->strStockCode,strNowDate,160, mTimeType,9,3,3);//K_LINE_DAY
		if(pStockKDJData==NULL)
			continue;

		std::vector<double> vec_price_ma5,vec_price_ma10,vec_price_ma20,vec_price_ma60,vec_price_ma120;
		vec_price_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
		vec_price_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
		vec_price_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
		vec_price_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);
		vec_price_ma120=CStockKDJArithmetic::CalcMA(120,pStockKDJData->vec_close_price);


		double f_custom_total_value = CalcCustomToatlValue(pStockRSIData);
		
		int mPriceM5ContiUpNums = CalcPriceM5ContiUp(vec_price_ma5);
		

		std::vector<double> vec_vol_ma5, vec_vol_ma10;
		std::vector<double> vec_volume_f;
		for (int n = 0; n < pStockKDJData->vec_volume.size(); n++)
		{
			vec_volume_f.push_back(pStockKDJData->vec_volume[n]);
		}
		vec_vol_ma5 = CStockKDJArithmetic::CalcMA(5, vec_volume_f);
		vec_vol_ma10 = CStockKDJArithmetic::CalcMA(10, vec_volume_f);

		int mVolM5ContiUpNums = CalcVolM5ContiUp(vec_vol_ma5);
		int mVolM10ContiUpNums = CalcVolM5ContiUp(vec_vol_ma10);




		int mContiDownNums=CalcLowPriceContiDown(pStockKDJData->vec_low_price);
		int mContiVolDownNums=CalcVolPriceContiDown(pStockKDJData->vec_volume_price,pStockKDJData->vec_close_price);
		int mBigIncreaseNums=CalcBigPriceIncreaseNums(pStockKDJData->vec_close_price,mMaxInsBack,f_max_ins_thes);
		int mRsi1BigNums=CalcRsiPeakNums(pStockRSIData->vec_rsi_1_value,mPreSize);
		int size=pStockKDJData->vec_volume_price.size();

		if(pStockKDJData->vec_volume_price[size-1]<1000)
			continue;
	
		BOOL bM5CrossM10=IsM5CrossM10(vec_price_ma5,vec_price_ma10);
	

		int mNowIsMaxPriceNums=0;		//目前这个价位是，多少日的最高值

		double f_now_close_price=pStockKDJData->vec_close_price[size-1];
		double f_now_high_price = pStockKDJData->vec_high_price[size - 1];
		for(int j=size-2;j>size-130;j--) //mPreSize
		{
			double f_pre_high_price=pStockKDJData->vec_high_price[j];
			if(f_now_high_price > f_pre_high_price)
			{
				mNowIsMaxPriceNums++;
			}
			else
			{
				break;
			}
		}


		double f_pre_close_price=pStockKDJData->vec_close_price[size-2];
		double f_p3_close_price=pStockKDJData->vec_close_price[size-4];
		double fNowGrow=(f_now_close_price-f_pre_close_price)*100.0/f_pre_close_price;

		double f_now_max_price=pStockKDJData->vec_high_price[size-1];
		double fNowMaxGrow=(f_now_max_price-f_pre_close_price)*100.0/f_pre_close_price;


		double fLast3Grow=(f_now_close_price-f_p3_close_price)*100.0/f_p3_close_price;




		double f_60_day_increase=0.0;

		double f_now_60_day_close_value=vec_price_ma60[size-1];
		double f_presize_60_day_close_value=vec_price_ma60[size-mPreSize];

		if(f_presize_60_day_close_value>0.0)
			f_60_day_increase=(f_now_60_day_close_value-f_presize_60_day_close_value)*100.0/f_presize_60_day_close_value;
		else
			f_60_day_increase=0.0;

		BOOL bAllUp=FALSE;

		int mM5DayUpNums=0;

		for(int j=size-1;j>=size-mPreSize;j--)
		{
			double f_low_value=pStockKDJData->vec_low_price[j];
			double f_m5_value=vec_price_ma5[j];
		
			double f_per=(f_low_value*100.0)/f_m5_value;

			if(f_per>=97.0&&f_per<=103.0)
				mM5DayUpNums++;

		}


		/*BOOL  bSuperHight=FALSE;
		for(int j=size-1;j>=size-mPreSize/2;j--)
		{
			double f_now_low_price=pStockKDJData->vec_low_price[j];
			double f_now_m5_price=vec_price_ma5[j];

			double f_now_low_m5_per=f_now_low_price*100.0/f_now_m5_price;

			if(f_now_low_m5_per>102.5)
			{
				bSuperHight=TRUE;
			}
		}*/

		

	

		BOOL bAllM5Up=TRUE;
		for(int j=size-1;j>=size-mPreSize-1;j--)
		{
			double f_pre_m5=vec_price_ma5[j-1];
			double f_now_m5=vec_price_ma5[j];
			if(f_now_m5<f_pre_m5)
			{
				bAllM5Up=FALSE;
				break;
			}
		}

		BOOL bBig2M20Down=FALSE;
		int mBig2M20DownNums=0;
		for(int j=size-1;j>=size-mPreSize-1;j--)
		{
			double f_low_value=pStockKDJData->vec_low_price[j];
			double f_now_m20=vec_price_ma20[j];
			if(f_low_value<f_now_m20)
			{
				mBig2M20DownNums++;
				break;
			}
		}

		if(mBig2M20DownNums>=2)
			bBig2M20Down=TRUE;

		if(mM5DayUpNums>=(mPreSize-2))
		{
			if(bAllM5Up&&(!bBig2M20Down))
			{
				  bAllUp=TRUE;
			}
		}


		int m_continus_price_m10_up_nums=0;
		/*for(int j=size-1;j>=size-90;j--)
		{
			double f_pre_val=vec_price_ma10[j-1];
			double f_now_val=vec_price_ma10[j];

			if(f_now_val>=f_pre_val)
				m_continus_price_m10_up_nums++;
			else
				break;
		}*/
		m_continus_price_m10_up_nums=CalcMNPriceContiUp(vec_price_ma10);

		int m_continus_price_m20_up_nums=0;
		/*for(int j=size-1;j>=size-90;j--)
		{
			double f_pre_val=vec_price_ma20[j-1];
			double f_now_val=vec_price_ma20[j];

			if(f_now_val>=f_pre_val)
				m_continus_price_m20_up_nums++;
			else
				break;
		}*/
		m_continus_price_m20_up_nums=CalcMNPriceContiUp(vec_price_ma20);


		int m_continus_price_m60_up_nums=0;
		/*for(int j=size-1;j>=size-90;j--)
		{
			double f_pre_val=vec_price_ma60[j-1];
			double f_now_val=vec_price_ma60[j];

			if(f_now_val>=f_pre_val)
				m_continus_price_m60_up_nums++;
			else
				break;
		}*/
		m_continus_price_m60_up_nums=CalcMNPriceContiUp(vec_price_ma60);

		
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
		/*if (!bIgnoreM5)
		{
			if (!bOk)
				continue;
		}*/


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


		
		bOk=TRUE;
		for(int j=size-mPreSize*2;j<size;j++)
		{
			double f_pre_m120=vec_price_ma120[j-1];
			double f_now_m120=vec_price_ma120[j];
			if(f_now_m120<f_pre_m120)
			{
				bOk=FALSE;
				break;

			}

		}

		if(bUseM120)
		{
			if(!bOk)
				continue;
			double f_now_m120=vec_price_ma120[size-1];
			double f_now_m60=vec_price_ma60[size-1];
			if(f_now_m60<f_now_m120)
				continue;
			double f_pre_m120=vec_price_ma120[size-1-mPreSize];
			double f_pre_m60=vec_price_ma60[size-1-mPreSize];
			if(f_pre_m60<f_pre_m120)
				continue;
		}
		

		
		double f_now_m5_price=vec_price_ma5[size-1];
		double f_now_m10_price=vec_price_ma10[size-1];
		double f_now_m20_price=vec_price_ma20[size-1];

		if(f_now_m10_price>f_now_m5_price)
		{

			BOOL b_Ok=FALSE;
			if(mContiVolDownNums>=4||mContiDownNums>=5)
				b_Ok=TRUE;
			if(!b_Ok)
				continue;
		}
		if(f_now_m20_price>f_now_m10_price)
		{
			if(mContiDownNums<5)
				continue;
		}


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

	

		std::vector<double> vec_volume_ma5,vec_volume_ma10, vec_volume_ma20, vec_volume_ma30;
		vec_volume_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_volume_price);
		vec_volume_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_volume_price);
		vec_volume_ma20 = CStockKDJArithmetic::CalcMA(20, pStockKDJData->vec_volume_price);
		vec_volume_ma30 = CStockKDJArithmetic::CalcMA(30, pStockKDJData->vec_volume_price);

		double f_now_volume_value=pStockKDJData->vec_volume_price[size-1];
		double f_now_volume_ma10=vec_volume_ma10[size-1];
		double f_now_volume_ma5 = vec_volume_ma5[size - 1];
		double f_now_volume_ma20= vec_volume_ma20[size - 1];
		double f_now_volume_ma30 = vec_volume_ma30[size - 1];
		double f_volume_per=0.0;
		double f_volume_per_form5 = 0.0;
		double f_volume_per_form20 = 0.0;
		double f_volume_per_form30 = 0.0;
		if(f_now_volume_ma10>1.0)
			f_volume_per=f_now_volume_value/f_now_volume_ma10;
		if (f_now_volume_ma5 > 1.0)
			f_volume_per_form5 = f_now_volume_value / f_now_volume_ma5;
		if(f_now_volume_ma20>1.0)
			f_volume_per_form20 = f_now_volume_value / f_now_volume_ma20;
		if(f_now_volume_ma30>1.0)
			f_volume_per_form30 = f_now_volume_value / f_now_volume_ma30;

		int   mStepIndex=GetVolM5M10StepIndex(vec_volume_ma5,vec_volume_ma10, mBackDays);

		double f_max_volume=0.0;
		int  m_max_volume_index=-1;
		for(int j=size-mPreSize*2;j<size;j++)
		{
			if(pStockKDJData->vec_volume[j]>=f_max_volume)
			{
				f_max_volume=pStockKDJData->vec_volume[j];
				m_max_volume_index=j;
			}
		}
		int m_max_volume_distance=size-m_max_volume_index;

		f_max_volume=0.0;
		m_max_volume_index=-1;
		for(int j=size-mPreSize*2;j<size;j++)
		{
			if(pStockKDJData->vec_volume_price[j]>=f_max_volume)
			{
				f_max_volume=pStockKDJData->vec_volume_price[j];
				m_max_volume_index=j;
			}
		}



		double f_cur_volume=pStockKDJData->vec_volume_price[size-1];
		double f_cur_volume_m10=vec_volume_ma10[size-1];
		double f_cur_vol_m10_per=f_cur_volume/f_cur_volume_m10;
		double f_cur_rsi_1=pStockRSIData->vec_rsi_1_value[rsi_size-1];
		double f_cur_rsi_2= pStockRSIData->vec_rsi_2_value[rsi_size - 1];
		double f_cur_rsi_3 = pStockRSIData->vec_rsi_3_value[rsi_size - 1];

		double f_min_rsi_1 = 9999.0;
		for (int j = rsi_size - 45; j < rsi_size; j++)
		{
			if (pStockRSIData->vec_rsi_1_value[j] < f_min_rsi_1)
				f_min_rsi_1 = pStockRSIData->vec_rsi_1_value[j];
		}

		double f_min_rsi_2 = 9999.0;
		for (int j = rsi_size - 45; j < rsi_size; j++)
		{
			if (pStockRSIData->vec_rsi_2_value[j] < f_min_rsi_2)
				f_min_rsi_2 = pStockRSIData->vec_rsi_2_value[j];
		}

		double f_min_rsi_3 = 9999.0;
		int m_min_rsi_3_interval = -1;
		for (int j = rsi_size - 45; j < rsi_size; j++)
		{
			if (pStockRSIData->vec_rsi_3_value[j] < f_min_rsi_3)
			{
				m_min_rsi_3_interval = (rsi_size - j);
				f_min_rsi_3 = pStockRSIData->vec_rsi_3_value[j];
			}
				
		}


		int m_20_10_cross_index=-1;
		if (vec_price_ma20[size - 1] < vec_price_ma10[size - 1])
		{
			for (int j = size - 1; j > size - 90; j--)
			{
				double f_now_m20 = vec_price_ma20[j];
				double f_now_m10 = vec_price_ma10[j];
				if (f_now_m10 < f_now_m20)
				{
					m_20_10_cross_index = j;
					break;
				}
			}
		}
		
		int m_10_big_20_nums=-1;
		
		if(m_20_10_cross_index>0)
			m_10_big_20_nums=size-m_20_10_cross_index;
		else
			m_10_big_20_nums=-1;
		
		double f_max_high_price=0.0; //f_max_close_price

		for(int j=size-mPreSize-1;j<size;j++)
		{
			if(pStockKDJData->vec_high_price[j]> f_max_high_price)
				f_max_high_price =pStockKDJData->vec_high_price[j];
		}
		
		double f_20_10_cross_price_increase=0.0;

		if(m_20_10_cross_index>0)
		{
			double f_20_10_cross_close_pirce=pStockKDJData->vec_close_price[m_20_10_cross_index];
			double f_now_close_pirce=pStockKDJData->vec_close_price[size-1];
			f_20_10_cross_price_increase=(f_max_high_price -f_20_10_cross_close_pirce)*100.0/f_20_10_cross_close_pirce;
		}
		else
		{
			//double f_20_10_cross_close_pirce=pStockKDJData->vec_close_price[size-90];
			//double f_now_close_pirce=pStockKDJData->vec_close_price[size-1];
			//f_20_10_cross_price_increase=(f_max_high_price -f_20_10_cross_close_pirce)*100.0/f_20_10_cross_close_pirce;
			f_20_10_cross_price_increase=(vec_price_ma10[size - 1] - vec_price_ma20[size - 1]) * 100.0 / vec_price_ma20[size - 1];
		}



		int m_60_20_cross_index=-1;

		if (vec_price_ma60[size - 1] < vec_price_ma20[size - 1])
		{
			for (int j = size - 1; j > size - 90; j--)
			{
				double f_now_m60 = vec_price_ma60[j];
				double f_now_m20 = vec_price_ma20[j];
				if (f_now_m20 < f_now_m60)
				{
					m_60_20_cross_index = j;
					break;
				}
			}
		}
		

		int m_60_big_20_nums=-1;

		if(m_60_20_cross_index>0)
			m_60_big_20_nums=size-m_60_20_cross_index;
		else
			m_60_big_20_nums=-1;

		double f_60_20_cross_price_increase=0.0;
		if(m_60_20_cross_index>0)
		{
			double f_60_20_cross_close_pirce=pStockKDJData->vec_close_price[m_60_20_cross_index];
			double f_now_close_pirce=pStockKDJData->vec_close_price[size-1];
			f_60_20_cross_price_increase=(f_max_high_price -f_60_20_cross_close_pirce)*100.0/f_60_20_cross_close_pirce;
		}
		else
		{
			//double f_60_20_cross_close_pirce=pStockKDJData->vec_close_price[size-90];
			//double f_now_close_pirce=pStockKDJData->vec_close_price[size-1];
			//f_60_20_cross_price_increase=(f_max_high_price -f_60_20_cross_close_pirce)*100.0/f_60_20_cross_close_pirce;
			f_60_20_cross_price_increase=(vec_price_ma20[size - 1] - vec_price_ma60[size - 1]) * 100.0 / vec_price_ma60[size - 1];

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
		printf("%s f_max_volume_per %f \n",(LPCSTR)pStockCode->strStockCode,f_max_volume_per);
		if(f_max_volume_per>f_max_volume_multiple) //1.8
		{
			//if(f_ma5_angle>35.0||f_ma10_angle>35.0||f_ma20_angle>30.0)
			continue;
		}

		if(f_cur_vol_m10_per>f_max_volume_multiple)
		{
			continue;
		}
			
		bOk=TRUE;

		if(bUseAllUp)
			bOk=bAllUp;

		printf("%s m10 tan %f  m20  tan   %f \n", (LPCSTR)pStockCode->strStockCode,f_ma10_angle,f_ma20_angle);
		if(bOk)
		{
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
			pTanAngleData->mNextGrow=0;
			pTanAngleData->fNextGrow=0.0;
			pTanAngleData->fNowGrow=fNowGrow;
			pTanAngleData->fNowMaxGrow=fNowMaxGrow;
			pTanAngleData->fLast3Grow=fLast3Grow;
			pTanAngleData->fVolumePer=f_volume_per;
			pTanAngleData->fVolumePerForM5 = f_volume_per_form5;
			pTanAngleData->fVolumePerForM20 = f_volume_per_form20;
			pTanAngleData->fVolumePerForM30 = f_volume_per_form30;
			pTanAngleData->bM5CrossM10=bM5CrossM10;
			pTanAngleData->mStepIndex=mStepIndex;
			pTanAngleData->mCalcuSel=0;
			pTanAngleData->bCalcuOk=FALSE;
			pTanAngleData->bShow=FALSE;
			pTanAngleData->fRsi1=f_cur_rsi_1;
			pTanAngleData->fRsi2 = f_cur_rsi_2;
			pTanAngleData->fRsi3 = f_cur_rsi_3;

			pTanAngleData->fMinRsi1 = f_min_rsi_1;
			pTanAngleData->fMinRsi2 = f_min_rsi_2;
			pTanAngleData->fMinRsi3 = f_min_rsi_3;
			pTanAngleData->mMinRsi3Interval = m_min_rsi_3_interval;
			pTanAngleData->mPriceM5ContiUpNums = mPriceM5ContiUpNums;
			pTanAngleData->mVolM5ContiUpNums = mVolM5ContiUpNums;
			pTanAngleData->mVolM10ContiUpNums = mVolM10ContiUpNums;
			pTanAngleData->fcustomtotalvalue = f_custom_total_value;
			
			pTanAngleData->strDateTime=strNowDate;
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

			for (int j = size - 31; j < size; j++)
			{
				pTanAngleData->vec_price_m20.push_back(vec_price_ma20[j]);
			}


			for(int j=size-31;j<size;j++)
			{

				pTanAngleData->vec_volume_m5.push_back(vec_volume_ma5[j]);
			}
			

			for(int j=size-31;j<size;j++)
			{
				pTanAngleData->vec_volume_m10.push_back(vec_volume_ma10[j]);
			}

			for(int j=size-31;j<size;j++)
			{
				pTanAngleData->vec_volume_value.push_back(pStockKDJData->vec_volume_price[j]);
			}
			


			for(int j=boll_size-31;j<boll_size;j++)
			{
				pTanAngleData->vec_boll_up.push_back(pStockBOLLData->vec_up[j]);
			}


			for(int j=boll_size-31;j<boll_size;j++)
			{
				pTanAngleData->vec_boll_middle.push_back(pStockBOLLData->vec_boll[j]);
			}

			for(int j=boll_size-31;j<boll_size;j++)
			{
				pTanAngleData->vec_boll_bottom.push_back(pStockBOLLData->vec_down[j]);
			}

			vecTanAngleData.push_back(pTanAngleData);

		}
		
	}
	return vecTanAngleData;
}


