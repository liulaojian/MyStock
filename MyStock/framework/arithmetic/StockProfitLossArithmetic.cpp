#include "stdafx.h"
#include "StockProfitLossArithmetic.h"
#include "StockDataMgr.h"
#include "CommonMacro.h"
#include "T_FreeVector.h"
#include <algorithm>  
CStockProfitLossArithmetic::CStockProfitLossArithmetic()
{

}

CStockProfitLossArithmetic::~CStockProfitLossArithmetic()
{


}





CStockProfitLossData* CStockProfitLossArithmetic::CalcProfitLossData(CString strStockCode,CString strDate,int mNums,int mPeridDays)
{
	CStockDayTable *pStockDayTable=NULL;

	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);

	if(!pStockDayTable)
		return NULL;

	int mPos=pStockDayTable->GetStockDayIndex(strDate);

	if(mPos<0)
		return NULL;

	if((mPos-240)<0)
		return NULL;

	Vec_StockDayData vecStockDayData;
	pStockDayTable->LockData();
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	pStockDayTable->UnlockData();

	CStockDayData *pStockDayData=NULL;

	int mValidNums=0;
	for(int i=0;i<mPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;

		if(pStockDayData->GetTotalVolume()>0)
		{
			mValidNums++;
		}

	}

	if(mValidNums<240)
		return NULL;

	long long mStockTotalVolume=0;
	mValidNums=0;
	int mRealBeginPos=0;
	for(int i=mPos;i>=0;i--)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;

		if(pStockDayData->GetTotalVolume()>0)
		{
			mStockTotalVolume+=pStockDayData->GetTotalVolume();
			mValidNums++;
			if(mValidNums>=240)
			{
				mRealBeginPos=i;
				break;
			}
		}
	}

	if(mStockTotalVolume==0)
		return NULL;

	double fCalcStockTotalVolume=mStockTotalVolume;
	double f_per=240.0/mPeridDays;
	fCalcStockTotalVolume=fCalcStockTotalVolume/f_per;
	mStockTotalVolume=(long long)fCalcStockTotalVolume;

	CString strBeginDate=vecStockDayData[mRealBeginPos]->GetDate();

	Vec_ProfitLossInfoList vecProfitLossInfoList;

	int mEndPos=mPos;
	ProfitLossInfo *pProfitLostInfo=NULL;
	for(int i=mRealBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		if(pStockDayData->GetTotalVolume()>0)
		{
			pProfitLostInfo=new ProfitLossInfo();
			pProfitLostInfo->mVolume=pStockDayData->GetTotalVolume();
			pProfitLostInfo->fMinPrice=pStockDayData->GetMinPrice();
			pProfitLostInfo->fMaxPrice=pStockDayData->GetMaxPrice();
			pProfitLostInfo->fEndPrice=pStockDayData->GetEndPrice();
			pProfitLostInfo->strDate=pStockDayData->GetDate();
			vecProfitLossInfoList.push_back(pProfitLostInfo);
		}
	}

	for(int i=0;i<vecProfitLossInfoList.size();i++)
	{
		double fNowVolume=(double)vecProfitLossInfoList[i]->mVolume;

		for(int j=i+1;j<vecProfitLossInfoList.size();j++)
		{
			double fNextVolume=(double)vecProfitLossInfoList[j]->mVolume;

			double f_volue_per=1.0-(fNextVolume/(double)mStockTotalVolume);

			fNowVolume=fNowVolume*f_volue_per;

		}
		vecProfitLossInfoList[i]->mVolume=(long)fNowVolume;
	}


	CStockProfitLossData *pStockProfitLossData=new CStockProfitLossData();

	pStockProfitLossData->strStockCode=strStockCode;
	pStockProfitLossData->strBeginDate=strBeginDate;
	pStockProfitLossData->strEndDate=strDate;
	pStockProfitLossData->mTotalStockVolume=mStockTotalVolume;
	pStockProfitLossData->vec_profitloss.assign(vecProfitLossInfoList.begin(),vecProfitLossInfoList.end());

	return pStockProfitLossData;
}




long long CStockProfitLossData::GetStockVolumeBwPrice(double f_low_price,double f_high_price,int mLastDayNums)
{
	
	if(f_low_price>=f_high_price)
		return 0;
	ProfitLossInfo *pProfitLossInfo=NULL;

	int mBeginPos;
	if(mLastDayNums==0)
		mBeginPos=0;
	else
		mBeginPos=vec_profitloss.size()-mLastDayNums;
	if(mBeginPos<0)
		return 0;

	long long mTotalVolume=0;
	for(int i=mBeginPos;i<vec_profitloss.size();i++)
	{
		pProfitLossInfo=vec_profitloss[i];
		if(!pProfitLossInfo)
			continue;
		//pProfitLossInfo完全在f_low_price f_high_price间

		

		if(pProfitLossInfo->fMinPrice>=f_low_price && pProfitLossInfo->fMaxPrice<f_high_price)	
		{
			mTotalVolume+=pProfitLossInfo->mVolume;
		}
		else		
		{
			//pProfitLossInfo完全在f_low_price f_high_price外
			if(pProfitLossInfo->fMinPrice>f_high_price|| pProfitLossInfo->fMaxPrice<f_low_price)	
			{

			}
			else
			{
				double f_info_ave_price=(pProfitLossInfo->fEndPrice+pProfitLossInfo->fMaxPrice+pProfitLossInfo->fMinPrice)/3.0;

				double f_info_up_dif=pProfitLossInfo->fMaxPrice-f_info_ave_price;
				double f_info_down_dif=f_info_ave_price-pProfitLossInfo->fMinPrice;

				double f_info_up_per=f_info_up_dif/50.0;
				double f_info_down_per=f_info_down_dif/50.0;

				long long m_per_volume=pProfitLossInfo->mVolume/100;

				long long m_sub_volume=0;
				for(int j=0;j<50;j++)
				{
					double f_info_low_value,f_info_high_value;

					f_info_low_value=pProfitLossInfo->fMinPrice+(j*f_info_down_per);

					f_info_high_value=pProfitLossInfo->fMinPrice+((j+1)*f_info_down_per);

					if(f_info_low_value>f_low_price && f_info_high_value<f_high_price)
					{
						m_sub_volume+=m_per_volume;
					}
					/*else
					{
						if(f_info_low_value>f_high_price || f_info_high_value<f_low_price)
						{

						}
						else
						{
							m_sub_volume+=m_per_volume;
						}
					}*/
				}


				for(int j=0;j<50;j++)
				{
					double f_info_low_value,f_info_high_value;

					f_info_low_value=f_info_ave_price+(j*f_info_up_per);

					f_info_high_value=f_info_ave_price+((j+1)*f_info_up_per);

					if(f_info_low_value>f_low_price && f_info_high_value<f_high_price)
					{
						m_sub_volume+=m_per_volume;
					}
				/*	else
					{
						if(f_info_low_value>f_high_price || f_info_high_value<f_low_price)
						{

						}
						else
						{
							m_sub_volume+=m_per_volume;
						}
					}*/
					
				}

				mTotalVolume+=m_sub_volume;
			}

		}
	}

	return mTotalVolume;
}



//计算出目前股价上方的百分比波段，vector 为 50 大小 表示 1%的涨幅波段内，股票数在总额的百分比
BOOL CStockProfitLossData::CalcVolumeSectionRange(int mLastDayNums)
{
	
	CStockDayTable *pStockDayTable=NULL;

	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);

	if(!pStockDayTable)
		return FALSE;

	int mPos=pStockDayTable->GetStockDayIndex(strEndDate);
	if(mPos<0)
		return FALSE;
	
	vec_up_range.clear();
	vec_down_range.clear();

	Vec_StockDayData vecStockDayData;
	pStockDayTable->LockData();
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	pStockDayTable->UnlockData();


	CStockDayData *pStockDayData=NULL;

	pStockDayData=vecStockDayData[mPos];

	double f_now_price=pStockDayData->GetEndPrice();

	double f_min_price=99999999.0;

	double f_max_price=-99999999.0;

	for(int i=0;i<vec_profitloss.size();i++)
	{
		if(f_min_price>vec_profitloss[i]->fMinPrice)
			f_min_price=vec_profitloss[i]->fMinPrice;

		if(f_max_price<vec_profitloss[i]->fMaxPrice)
			f_max_price=vec_profitloss[i]->fMaxPrice;

	}

	double f_up_range=f_max_price-f_now_price;
	double f_down_rang=f_now_price-f_min_price;

	double f_up_per_range=f_up_range/50.0;

	double f_down_per_range=f_down_rang/50.0;

	//up
	
	long long mUpTotalVolume=0;
	for(int i=0;i<50;i++)
	{

		double f_low_price,f_high_price;
		f_low_price=f_now_price+(i*f_up_per_range);
		f_high_price=f_now_price+((i+1)*f_up_per_range);

		long long mVolume=GetStockVolumeBwPrice(f_low_price,f_high_price,mLastDayNums);
		mUpTotalVolume+=mVolume;
		double f_volume_range=((double)mVolume*100.0)/(double)mTotalStockVolume;
		
		vec_up_range.push_back(f_volume_range);
		
	}

	//down
	for(int i=0;i<50;i++)
	{
		double f_low_price,f_high_price;
		f_high_price=f_now_price-(i*f_down_per_range);
		f_low_price=f_now_price-((i+1)*f_down_per_range);

		long long mVolume=GetStockVolumeBwPrice(f_low_price,f_high_price,mLastDayNums);
		double f_volume_range=((double)mVolume*100.0)/(double)mTotalStockVolume;

		vec_down_range.push_back(f_volume_range);
	}
	return TRUE;
}


