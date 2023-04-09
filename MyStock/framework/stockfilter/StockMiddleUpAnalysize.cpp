#include "stdafx.h"
#include "StockMiddleUpAnalysize.h"

#include "StockMACDArithmetic.h"

#include "T_FreeVector.h"

CStockMiddleUpAnalysize::CStockMiddleUpAnalysize(CString strCode)
{
	strStockCode=strCode;
}

CStockMiddleUpAnalysize::~CStockMiddleUpAnalysize()
{

}


BOOL CStockMiddleUpAnalysize::IsMinStockProfitLossData(CStockProfitLossData* pStockProfitLossData)
{
	double f_duty_up_0_2,f_duty_up_2_4,f_duty_up_4_6,f_duty_up_6_8,f_duty_up_8_10,f_duty_up_10;
	double f_duty_down_0_2,f_duty_down_2_4,f_duty_down_4_6,f_duty_down_6_8,f_duty_down_8_10,f_duty_down_10;

	f_duty_up_0_2=pStockProfitLossData->vec_up_range[0]+pStockProfitLossData->vec_up_range[1];
	f_duty_up_2_4=pStockProfitLossData->vec_up_range[2]+pStockProfitLossData->vec_up_range[3];
	f_duty_up_4_6=pStockProfitLossData->vec_up_range[4]+pStockProfitLossData->vec_up_range[5];
	f_duty_up_6_8=pStockProfitLossData->vec_up_range[6]+pStockProfitLossData->vec_up_range[7];
	f_duty_up_8_10=pStockProfitLossData->vec_up_range[8]+pStockProfitLossData->vec_up_range[9];

	f_duty_up_10=0.0;
	for(int j=10;j<=49;j++)
	{
		f_duty_up_10+=pStockProfitLossData->vec_up_range[j];
	}


	f_duty_down_0_2=pStockProfitLossData->vec_down_range[0]+pStockProfitLossData->vec_down_range[1];
	f_duty_down_2_4=pStockProfitLossData->vec_down_range[2]+pStockProfitLossData->vec_down_range[3];
	f_duty_down_4_6=pStockProfitLossData->vec_down_range[4]+pStockProfitLossData->vec_down_range[5];
	f_duty_down_6_8=pStockProfitLossData->vec_down_range[6]+pStockProfitLossData->vec_down_range[7];
	f_duty_down_8_10=pStockProfitLossData->vec_down_range[8]+pStockProfitLossData->vec_down_range[9];

	f_duty_down_10=0.0;

	for(int j=10;j<=49;j++)
	{
		f_duty_down_10+=pStockProfitLossData->vec_down_range[j];
	}

	double f_duty_down_0_10=f_duty_down_0_2+f_duty_down_2_4+f_duty_down_4_6+f_duty_down_6_8+f_duty_down_8_10;

	double f_duty_down_total=f_duty_down_0_10+f_duty_down_10;

	if(f_duty_down_total<10.0 )
	{
		return TRUE;
	}

	return FALSE;

}

BOOL CStockMiddleUpAnalysize::IsMaxStockProfitLossData(CStockProfitLossData* pStockProfitLossData)
{
	double f_duty_up_0_2,f_duty_up_2_4,f_duty_up_4_6,f_duty_up_6_8,f_duty_up_8_10,f_duty_up_10;
	double f_duty_down_0_2,f_duty_down_2_4,f_duty_down_4_6,f_duty_down_6_8,f_duty_down_8_10,f_duty_down_10;

	f_duty_up_0_2=pStockProfitLossData->vec_up_range[0]+pStockProfitLossData->vec_up_range[1];
	f_duty_up_2_4=pStockProfitLossData->vec_up_range[2]+pStockProfitLossData->vec_up_range[3];
	f_duty_up_4_6=pStockProfitLossData->vec_up_range[4]+pStockProfitLossData->vec_up_range[5];
	f_duty_up_6_8=pStockProfitLossData->vec_up_range[6]+pStockProfitLossData->vec_up_range[7];
	f_duty_up_8_10=pStockProfitLossData->vec_up_range[8]+pStockProfitLossData->vec_up_range[9];

	f_duty_up_10=0.0;
	for(int j=10;j<=49;j++)
	{
		f_duty_up_10+=pStockProfitLossData->vec_up_range[j];
	}


	f_duty_down_0_2=pStockProfitLossData->vec_down_range[0]+pStockProfitLossData->vec_down_range[1];
	f_duty_down_2_4=pStockProfitLossData->vec_down_range[2]+pStockProfitLossData->vec_down_range[3];
	f_duty_down_4_6=pStockProfitLossData->vec_down_range[4]+pStockProfitLossData->vec_down_range[5];
	f_duty_down_6_8=pStockProfitLossData->vec_down_range[6]+pStockProfitLossData->vec_down_range[7];
	f_duty_down_8_10=pStockProfitLossData->vec_down_range[8]+pStockProfitLossData->vec_down_range[9];

	f_duty_down_10=0.0;

	for(int j=10;j<=49;j++)
	{
		f_duty_down_10+=pStockProfitLossData->vec_down_range[j];
	}

	double f_duty_down_0_10=f_duty_down_0_2+f_duty_down_2_4+f_duty_down_4_6+f_duty_down_6_8+f_duty_down_8_10;

	double f_duty_down_total=f_duty_down_0_10+f_duty_down_10;

	if(f_duty_down_total>96.0 )
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CStockMiddleUpAnalysize::IsMiddleStockProfitLossData(CStockProfitLossData* pStockProfitLossData)
{
	double f_duty_up_0_2,f_duty_up_2_4,f_duty_up_4_6,f_duty_up_6_8,f_duty_up_8_10,f_duty_up_10;
	double f_duty_down_0_2,f_duty_down_2_4,f_duty_down_4_6,f_duty_down_6_8,f_duty_down_8_10,f_duty_down_10;

	f_duty_up_0_2=pStockProfitLossData->vec_up_range[0]+pStockProfitLossData->vec_up_range[1];
	f_duty_up_2_4=pStockProfitLossData->vec_up_range[2]+pStockProfitLossData->vec_up_range[3];
	f_duty_up_4_6=pStockProfitLossData->vec_up_range[4]+pStockProfitLossData->vec_up_range[5];
	f_duty_up_6_8=pStockProfitLossData->vec_up_range[6]+pStockProfitLossData->vec_up_range[7];
	f_duty_up_8_10=pStockProfitLossData->vec_up_range[8]+pStockProfitLossData->vec_up_range[9];

	f_duty_up_10=0.0;
	for(int j=10;j<=49;j++)
	{
		f_duty_up_10+=pStockProfitLossData->vec_up_range[j];
	}


	f_duty_down_0_2=pStockProfitLossData->vec_down_range[0]+pStockProfitLossData->vec_down_range[1];
	f_duty_down_2_4=pStockProfitLossData->vec_down_range[2]+pStockProfitLossData->vec_down_range[3];
	f_duty_down_4_6=pStockProfitLossData->vec_down_range[4]+pStockProfitLossData->vec_down_range[5];
	f_duty_down_6_8=pStockProfitLossData->vec_down_range[6]+pStockProfitLossData->vec_down_range[7];
	f_duty_down_8_10=pStockProfitLossData->vec_down_range[8]+pStockProfitLossData->vec_down_range[9];

	f_duty_down_10=0.0;

	for(int j=10;j<=49;j++)
	{
		f_duty_down_10+=pStockProfitLossData->vec_down_range[j];
	}

	double f_duty_down_0_10=f_duty_down_0_2+f_duty_down_2_4+f_duty_down_4_6+f_duty_down_6_8+f_duty_down_8_10;

	double f_duty_down_total=f_duty_down_0_10+f_duty_down_10;

	if(f_duty_down_total>15.0 &&  f_duty_down_total<30.0 )			//35
	{
		return TRUE;
	}

	return FALSE;
}

double CStockMiddleUpAnalysize::CalcStockProfitLossDataDownPer(CStockProfitLossData* pStockProfitLossData)
{
	double f_duty_up_0_2,f_duty_up_2_4,f_duty_up_4_6,f_duty_up_6_8,f_duty_up_8_10,f_duty_up_10;
	double f_duty_down_0_2,f_duty_down_2_4,f_duty_down_4_6,f_duty_down_6_8,f_duty_down_8_10,f_duty_down_10;

	f_duty_up_0_2=pStockProfitLossData->vec_up_range[0]+pStockProfitLossData->vec_up_range[1];
	f_duty_up_2_4=pStockProfitLossData->vec_up_range[2]+pStockProfitLossData->vec_up_range[3];
	f_duty_up_4_6=pStockProfitLossData->vec_up_range[4]+pStockProfitLossData->vec_up_range[5];
	f_duty_up_6_8=pStockProfitLossData->vec_up_range[6]+pStockProfitLossData->vec_up_range[7];
	f_duty_up_8_10=pStockProfitLossData->vec_up_range[8]+pStockProfitLossData->vec_up_range[9];

	f_duty_up_10=0.0;
	for(int j=10;j<=49;j++)
	{
		f_duty_up_10+=pStockProfitLossData->vec_up_range[j];
	}


	f_duty_down_0_2=pStockProfitLossData->vec_down_range[0]+pStockProfitLossData->vec_down_range[1];
	f_duty_down_2_4=pStockProfitLossData->vec_down_range[2]+pStockProfitLossData->vec_down_range[3];
	f_duty_down_4_6=pStockProfitLossData->vec_down_range[4]+pStockProfitLossData->vec_down_range[5];
	f_duty_down_6_8=pStockProfitLossData->vec_down_range[6]+pStockProfitLossData->vec_down_range[7];
	f_duty_down_8_10=pStockProfitLossData->vec_down_range[8]+pStockProfitLossData->vec_down_range[9];

	f_duty_down_10=0.0;

	for(int j=10;j<=49;j++)
	{
		f_duty_down_10+=pStockProfitLossData->vec_down_range[j];
	}

	double f_duty_down_0_10=f_duty_down_0_2+f_duty_down_2_4+f_duty_down_4_6+f_duty_down_6_8+f_duty_down_8_10;

	double f_duty_down_total=f_duty_down_0_10+f_duty_down_10;


	return f_duty_down_total;

}


//估算庄家筹码
//假设  在 全部筹码 基本 都赚钱 >97 % 的情况下，庄家 剩下的筹码 只有 总筹码的 5%
//然后  假设 涨停 10%  的情况下 70% 的 筹码 是 庄家抛出去的 ， 1 % 的情况下  7% 是庄家抛出去的 ，2 % 14% 。。。。
//假设 跌停 10% 的情况下 70% 的 筹码 是 庄家收回去， 1 % 的情况下  7% 是庄家收回去的 ，2 % 14% 。。。

double CStockMiddleUpAnalysize:: CalcBankerChip(CStockDayTable *pStockDayTable,int mMaxPos,int mNowPos,long long mTotalStockVolume)
{
	Vec_StockDayData vecStockDayData;
	pStockDayTable->LockData();
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	pStockDayTable->UnlockData();



	long long mNowBanderChip=mTotalStockVolume/20;

	for(int i=mMaxPos+1;i<=mNowPos;i++)
	{
		double f_range;
		double f_pre_price=vecStockDayData[i-1]->GetEndPrice();
		double f_now_price=vecStockDayData[i]->GetEndPrice();
		f_range=(f_now_price-f_pre_price)*100.0/f_pre_price;

		int m_rang=(int)f_range;
		if(f_range>=0.0)
			m_rang++;
		else
			m_rang--;

		f_range=(double)m_rang;

		double f_banderchip_range;
		
		if(f_range>=0.0)
			f_banderchip_range=f_range*(-0.02);
		else
			f_banderchip_range=f_range*(-0.18);
		
		long mVolume=vecStockDayData[i]->GetTotalVolume();

		long mBanderVolume=f_banderchip_range*mVolume;
		mNowBanderChip+=mBanderVolume;
	}

	double f_now_binder_chip=(mNowBanderChip*100.0)/mTotalStockVolume;
	
	return f_now_binder_chip;
}


BOOL  CStockMiddleUpAnalysize::AnalysisStock(CString strEndDate,double & f_bander_chip_per)
{

	CStockDayTable *pStockDayTable=NULL;
	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);

	if(!pStockDayTable)
		return FALSE;

	if(StockDataMgr()->IsExpStock(strStockCode))
		return FALSE;


	int mPos=pStockDayTable->GetStockDayIndex(strEndDate);
	if(mPos<=330)
		return FALSE;
	Vec_StockProfitLossData  vecStockProfitLossData;
	int mNowPos=mPos-90;
	for(int i=0;i<=90;i++)
	{
		
		CString strNowDate=pStockDayTable->GetStockDayDateByIndex(mNowPos+i);
		if(strNowDate=="")
			continue;
		CStockProfitLossData* pStockProfitLossData=NULL;
		pStockProfitLossData=CStockProfitLossArithmetic::CalcProfitLossData(strStockCode,strNowDate,240,50);
		if(pStockProfitLossData)
		{
			pStockProfitLossData->CalcVolumeSectionRange();
			vecStockProfitLossData.push_back(pStockProfitLossData);
		}
	}

	CStockProfitLossData* pNowStockProfitLossData=NULL;

	pNowStockProfitLossData=vecStockProfitLossData[vecStockProfitLossData.size()-1];

	if(!IsMiddleStockProfitLossData(pNowStockProfitLossData))		//目前只做10--30 middle 筹码的判断，其他的退出
	{
		CStockProfitLossData *pStockProfitLossData=NULL;
		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
				continue;
			CFreeVector<Vec_ProfitLossInfoList>::freeVector(pStockProfitLossData->vec_profitloss);
		}
		CFreeVector<Vec_StockProfitLossData>::freeVector(vecStockProfitLossData);

		return FALSE;
	}


	//PrintfDebug("Now %s \n",pNowStockProfitLossData->strStockCode);

	Vec_StockProfitLossData  vecMinStockProfitLossData;
	Vec_StockProfitLossData  vecMaxStockProfitLossData;
	Vec_StockProfitLossData  vecLatestStockProfitLossData;

	for(int i=vecStockProfitLossData.size()-8;i<vecStockProfitLossData.size();i++)
	{
		CStockProfitLossData* pStockProfitLossData=NULL;
		pStockProfitLossData=vecStockProfitLossData[i];
		if(!pStockProfitLossData)
			continue;
		vecLatestStockProfitLossData.push_back(pStockProfitLossData);
	}

	for(int i=0;i<vecStockProfitLossData.size();i++)
	{
		CStockProfitLossData* pStockProfitLossData=NULL;
		pStockProfitLossData=vecStockProfitLossData[i];
		if(!pStockProfitLossData)
			continue;
		
		if(IsMinStockProfitLossData(pStockProfitLossData))
		{
			vecMinStockProfitLossData.push_back(pStockProfitLossData);
		}
		else if(IsMaxStockProfitLossData(pStockProfitLossData))
		{
			vecMaxStockProfitLossData.push_back(pStockProfitLossData);
		}
		
	}

	
	if(vecMinStockProfitLossData.size()==0)			//没有最小筹码点，放弃
	{
		//PrintfDebug("%s Not Min \n",pNowStockProfitLossData->strStockCode);
		CStockProfitLossData *pStockProfitLossData=NULL;
		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
				continue;
			CFreeVector<Vec_ProfitLossInfoList>::freeVector(pStockProfitLossData->vec_profitloss);
		}
		CFreeVector<Vec_StockProfitLossData>::freeVector(vecStockProfitLossData);

		return FALSE;
	}
	

	int  mMaxPricePos=-1;
	if(vecMaxStockProfitLossData.size()==0)		//没有最高筹码点，放弃
	{
		int mBeginPos=mPos-90;
		double f_max_price=-99999.0;
		

		Vec_StockDayData vecStockDayData;
		pStockDayTable->LockData();
		vecStockDayData=pStockDayTable->GetStockDayDataList();
		pStockDayTable->UnlockData();

		mMaxPricePos=-1;
		for(int i=mBeginPos;i<=mPos;i++)
		{
			double f_end_price=vecStockDayData[i]->GetEndPrice();
			if(f_end_price>f_max_price)
			{
				f_max_price=f_end_price;
				mMaxPricePos=i;
			}

		}
		if(mMaxPricePos<0)
		{
			//PrintfDebug("%s Not Max \n",pNowStockProfitLossData->strStockCode);
			CStockProfitLossData *pStockProfitLossData=NULL;
			for(int i=0;i<vecStockProfitLossData.size();i++)
			{
				pStockProfitLossData=vecStockProfitLossData[i];
				if(!pStockProfitLossData)
					continue;
				CFreeVector<Vec_ProfitLossInfoList>::freeVector(pStockProfitLossData->vec_profitloss);
			}
			CFreeVector<Vec_StockProfitLossData>::freeVector(vecStockProfitLossData);

			return FALSE;
		}
		
	}


	CStockProfitLossData* pMinStockProfitLossData=NULL;
	CStockProfitLossData* pMaxStockProfitLossData=NULL;

	
	pMinStockProfitLossData=vecMinStockProfitLossData[vecMinStockProfitLossData.size()-1];

	if(vecMaxStockProfitLossData.size()==0)
	{
		Vec_StockDayData vecStockDayData;
		pStockDayTable->LockData();
		vecStockDayData=pStockDayTable->GetStockDayDataList();
		pStockDayTable->UnlockData();

		CString strMaxDate=vecStockDayData[mMaxPricePos]->GetDate();

		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			CStockProfitLossData* pStockProfitLossData=NULL;
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
				continue;

			if(strMaxDate==pStockProfitLossData->strEndDate)
			{
				pMaxStockProfitLossData=pStockProfitLossData;
				break;

			}

		}

		if(!pMaxStockProfitLossData)
		{
			//PrintfDebug("%s Not Max \n",pMaxStockProfitLossData->strStockCode);
			CStockProfitLossData *pStockProfitLossData=NULL;
			for(int i=0;i<vecStockProfitLossData.size();i++)
			{
				pStockProfitLossData=vecStockProfitLossData[i];
				if(!pStockProfitLossData)
					continue;
				CFreeVector<Vec_ProfitLossInfoList>::freeVector(pStockProfitLossData->vec_profitloss);
			}
			CFreeVector<Vec_StockProfitLossData>::freeVector(vecStockProfitLossData);

			return FALSE;
		}

	}
	else
		pMaxStockProfitLossData=vecMaxStockProfitLossData[vecMaxStockProfitLossData.size()-1];


	Vec_StockDayData vecStockDayData;
	pStockDayTable->LockData();
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	pStockDayTable->UnlockData();

	int mFirstPos=mPos-10;

	CStockDayData *pFirstStockDayData=NULL;
	CStockDayData *pLastStockDayData=NULL;

	pFirstStockDayData=vecStockDayData[mFirstPos];
	pLastStockDayData=vecStockDayData[mPos];


	int mMinPos=pStockDayTable->GetStockDayIndex(pMinStockProfitLossData->strEndDate);
	CStockDayData *pStockDayData=pStockDayTable->GetStockDayDataByIndex(mMinPos);
	double f_min_price=pStockDayData->GetEndPrice();
	double f_min_down_per=CalcStockProfitLossDataDownPer(pMinStockProfitLossData);


	if(f_min_down_per>15.0)		//15
	{
		double f_first_close=pFirstStockDayData->GetEndPrice();
		double f_last_close=pLastStockDayData->GetEndPrice();

		double f_close_per=(f_last_close-f_first_close)*100.0/f_first_close;
		if(f_close_per>-10.0)
		{
			CStockProfitLossData *pStockProfitLossData=NULL;
			for(int i=0;i<vecStockProfitLossData.size();i++)
			{
				pStockProfitLossData=vecStockProfitLossData[i];
				if(!pStockProfitLossData)
					continue;
				CFreeVector<Vec_ProfitLossInfoList>::freeVector(pStockProfitLossData->vec_profitloss);
			}
			CFreeVector<Vec_StockProfitLossData>::freeVector(vecStockProfitLossData);
			return FALSE;
		}
	}

	mNowPos=pStockDayTable->GetStockDayIndex(pNowStockProfitLossData->strEndDate);
	double f_now_down_per=CalcStockProfitLossDataDownPer(pNowStockProfitLossData);
	pStockDayData=pStockDayTable->GetStockDayDataByIndex(mNowPos);
	double f_now_price=pStockDayData->GetEndPrice();




	int mLess3Nums=0;
	int mLess2Nums=0;

	double f_max_last_down_per=-9999.0;
	double f_min_last_down_per=99999.0;
	for(int i=0;i<vecLatestStockProfitLossData.size();i++)
	{
		CStockProfitLossData* pStockProfitLossData=NULL;
		pStockProfitLossData=vecLatestStockProfitLossData[i];
		if(!pStockProfitLossData)
			continue;
		
		double f_now_last_down_per=CalcStockProfitLossDataDownPer(pStockProfitLossData);
		if(f_now_last_down_per<(f_min_down_per+25.0))		//4.0
		{
			mLess3Nums++;
		}

		if(f_now_last_down_per<10.0)		//4.0
		{
			mLess2Nums++;
		}


		if(f_now_last_down_per>f_max_last_down_per)
		{
			f_max_last_down_per=f_now_last_down_per;
		}

		if(f_now_last_down_per<f_min_last_down_per)
		{
			f_min_last_down_per=f_now_last_down_per;
		}
	}
    
	
	
	{
		if(mLess3Nums<3||f_max_last_down_per>(f_min_down_per+45.0))		//35
		{

			CStockProfitLossData *pStockProfitLossData=NULL;
			for(int i=0;i<vecStockProfitLossData.size();i++)
			{
				pStockProfitLossData=vecStockProfitLossData[i];
				if(!pStockProfitLossData)
					continue;
				CFreeVector<Vec_ProfitLossInfoList>::freeVector(pStockProfitLossData->vec_profitloss);
			}
			CFreeVector<Vec_StockProfitLossData>::freeVector(vecStockProfitLossData);
			return FALSE;
		}
	}
	
	


	
	//CStockDayData *pStockDayData=NULL;

	int mMaxPos=pStockDayTable->GetStockDayIndex(pMaxStockProfitLossData->strEndDate);
	double f_max_down_per=CalcStockProfitLossDataDownPer(pMaxStockProfitLossData);
	pStockDayData=pStockDayTable->GetStockDayDataByIndex(mMaxPos);
	double f_max_price=pStockDayData->GetEndPrice();

/*	if(mMaxPos>mMinPos)		//最大值在最小值后面，暂时没算法
	{
		CStockProfitLossData *pStockProfitLossData=NULL;
		for(int i=0;i<vecStockProfitLossData.size();i++)
		{
			pStockProfitLossData=vecStockProfitLossData[i];
			if(!pStockProfitLossData)
				continue;
			CFreeVector<Vec_ProfitLossInfoList>::freeVector(pStockProfitLossData->vec_profitloss);
		}
		CFreeVector<Vec_StockProfitLossData>::freeVector(vecStockProfitLossData);
		return FALSE;
	}*/

	
	long long mTotalVolume=(pMaxStockProfitLossData->mTotalStockVolume+pNowStockProfitLossData->mTotalStockVolume)/2;


	double f_max_min_bander_chip_per=CalcBankerChip(pStockDayTable,mMaxPos,mMinPos,mTotalVolume);

	f_bander_chip_per=CalcBankerChip(pStockDayTable,mMaxPos,mNowPos,mTotalVolume);

	

	
	CStockProfitLossData *pStockProfitLossData=NULL;
	for(int i=0;i<vecStockProfitLossData.size();i++)
	{
		pStockProfitLossData=vecStockProfitLossData[i];
		if(!pStockProfitLossData)
			continue;
		CFreeVector<Vec_ProfitLossInfoList>::freeVector(pStockProfitLossData->vec_profitloss);
	}
	CFreeVector<Vec_StockProfitLossData>::freeVector(vecStockProfitLossData);
	
	
	return TRUE;
	
}