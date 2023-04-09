#include "stdafx.h"
#include "StockPowerArithmetic.h"
#include "StockDataMgr.h"
#include "Convert.h"

CStockPowerArithmetic::CStockPowerArithmetic(CString strCode)
{
	strStockCode=strCode;
	pStockMin5Table=NULL;
	pStockDayTable=NULL;

}


CStockPowerArithmetic::~CStockPowerArithmetic()
{

}



BOOL  CStockPowerArithmetic::Init(void)
{
	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);
	pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);

	if(!pStockDayTable || !pStockMin5Table)
		return FALSE;

	return TRUE;
}

StockPowerArithmeticInfo * CStockPowerArithmetic::CalcStockPowerArithmeticInfo(CString strBeginDate,CString strEndDate)
{
	StockPowerArithmeticInfo *pStockPowerArithmeticInfo=NULL;

	int mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDate);
	int mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1 || mEndPos==-1)
		return pStockPowerArithmeticInfo;

	if(mBeginPos>=mEndPos)
		return pStockPowerArithmeticInfo;

	Vec_StockDayData vecStockDayData;

	vecStockDayData=pStockDayTable->GetStockDayDataListBwIndex(mBeginPos,mEndPos);

	if(vecStockDayData.size()==0)
		return pStockPowerArithmeticInfo;

	float f_min_val=999999999999999.0;
	float f_max_val=-1.0;
	int mMinValPos=-1;
	int mMaxValPos=-1;
	CStockDayData * pStockDayData=NULL;
	
	for(int i=0;i<vecStockDayData.size();i++)
	{
		pStockDayData=vecStockDayData[i];

		if(pStockDayData->GetMaxPrice()>f_max_val)
		{
			f_max_val=pStockDayData->GetMaxPrice();
			mMaxValPos=i;
		}
	}

	if(mMaxValPos==-1)
		return pStockPowerArithmeticInfo;

	for(int i=0;i<mMaxValPos;i++)
	{
		pStockDayData=vecStockDayData[i];

		if(pStockDayData->GetMinPrice()<f_min_val)
		{
			f_min_val=pStockDayData->GetMinPrice();
			mMinValPos=i;
		}
	}

	float f_min_max_power=0.0;
	float f_max_end_power=0.0;
	if(mMinValPos>=0  && (mMaxValPos>mMinValPos))
	{
		float f_power=0.0;
		for(int i=mMinValPos+1;i<=mMaxValPos;i++)
		{
			pStockDayData=vecStockDayData[i];

			float f_percent=(pStockDayData->GetEndPrice()-vecStockDayData[i-1]->GetEndPrice())/vecStockDayData[i-1]->GetEndPrice();

			f_percent=f_percent/2.0;

			f_power=f_percent*pStockDayData->GetTotalPrice();

			f_min_max_power+=f_power;

		}
		

		int mValEndPos=vecStockDayData.size()-1;
		
		for(int i=mMaxValPos+1;i<=mValEndPos;i++)
		{
			pStockDayData=vecStockDayData[i];

			float f_percent=(pStockDayData->GetEndPrice()-vecStockDayData[i-1]->GetEndPrice())/vecStockDayData[i-1]->GetEndPrice();
			f_percent=f_percent/2.0;
			f_power=f_percent*pStockDayData->GetTotalPrice();
			f_max_end_power+=f_power;
		}



	}

	if(f_min_max_power!=0.0 && f_max_end_power!=0.0)
	{
		CString strMinPriceDate,strMaxPriceDate;
		strMinPriceDate=vecStockDayData[mMinValPos]->GetDate();
		strMaxPriceDate=vecStockDayData[mMaxValPos]->GetDate();
		pStockPowerArithmeticInfo=new StockPowerArithmeticInfo();
		pStockPowerArithmeticInfo->strStockCode=strStockCode;
		pStockPowerArithmeticInfo->strBeginDate=strBeginDate;
		pStockPowerArithmeticInfo->strEndDate=strEndDate;
		pStockPowerArithmeticInfo->strMinPriceDate=strMinPriceDate;
		pStockPowerArithmeticInfo->strMaxPriceDate=strMaxPriceDate;
		pStockPowerArithmeticInfo->f_min_max_power=f_min_max_power;
		pStockPowerArithmeticInfo->f_max_end_power=f_max_end_power;

		float    f_power_percent;
		f_power_percent=(f_min_max_power+f_max_end_power)*100.0/f_min_max_power;
		pStockPowerArithmeticInfo->f_power_percent=f_power_percent;
	}

	return pStockPowerArithmeticInfo;
}

StockPowerArithmeticInfo *  CStockPowerArithmetic::CalcLastStockPowerArithmeticInfo(int mLastNums)
{
	CString strEndDate=pStockDayTable->GetStockDayDateReverseIndex(0);

	CString strBeginDate=pStockDayTable->GetStockDayDateReverseIndex(mLastNums);

	return CalcStockPowerArithmeticInfo(strBeginDate,strEndDate);

}


BOOL CStockPowerArithmetic::NewCalcStockPowerValue(CString strBeginDate,CString strEndDate,double &f_power_val)
{
	int mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDate);
	int mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDate);

	
	if(mBeginPos==-1 || mEndPos==-1)
		return FALSE;

	

	if(mBeginPos>=mEndPos)
		return FALSE;

	if((mBeginPos-1)<0)
		return FALSE;


	Vec_StockDayData vecStockDayData;
	pStockDayTable->LockData();
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	pStockDayTable->UnlockData();

	int mLength=mEndPos-mBeginPos+1;

	double f_total_sale_val=0.0;

	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		double f_range;
		double f_now_val=vecStockDayData[i]->GetEndPrice();
		double f_pre_val=vecStockDayData[i-1]->GetEndPrice();
		f_range=(f_now_val-f_pre_val)/f_pre_val;
		f_range=f_range/2.0;
		if(f_range<0.0)
		{
			double f_sale_val=vecStockDayData[i]->GetTotalPrice()*f_range;
			f_total_sale_val+=f_sale_val;
		}
	}

	double f_total_buy_val=0.0;

	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		double f_range;
		double f_now_val=vecStockDayData[i]->GetEndPrice();
		double f_pre_val=vecStockDayData[i-1]->GetEndPrice();
		f_range=(f_now_val-f_pre_val)/f_pre_val;
		f_range=f_range/2.0;
		if(f_range>=0.0)
		{
			double f_buy_val=vecStockDayData[i]->GetTotalPrice()*f_range;
			f_total_buy_val+=f_buy_val;
		}
	}

	if(f_total_buy_val>=abs(f_total_sale_val))
	{
		f_power_val=(f_total_buy_val+f_total_sale_val)*100.0/f_total_buy_val;
	}
	else
	{
		f_power_val=(f_total_sale_val+f_total_buy_val)*100.0/abs(f_total_sale_val);
	}
	return TRUE;

}

BOOL CStockPowerArithmetic::NewCalcStockPowerValue(int mBeginPos,int mEndPos,double &f_power_val)
{
	if(mBeginPos==-1 || mEndPos==-1)
		return FALSE;



	if(mBeginPos>=mEndPos)
		return FALSE;

	if((mBeginPos-1)<0)
		return FALSE;


	Vec_StockDayData vecStockDayData;
	pStockDayTable->LockData();
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	pStockDayTable->UnlockData();

	if(mBeginPos>=vecStockDayData.size() || mEndPos>vecStockDayData.size())
		return FALSE;

	double f_total_sale_val=0.0;

	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		double f_range;
		double f_now_val=vecStockDayData[i]->GetEndPrice();
		double f_pre_val=vecStockDayData[i-1]->GetEndPrice();
		f_range=(f_now_val-f_pre_val)/f_pre_val;
		f_range=f_range/2.0;
		if(f_range<0.0)
		{
			double f_sale_val=vecStockDayData[i]->GetTotalPrice()*f_range;
			f_total_sale_val+=f_sale_val;
		}
	}

	double f_total_buy_val=0.0;

	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		double f_range;
		double f_now_val=vecStockDayData[i]->GetEndPrice();
		double f_pre_val=vecStockDayData[i-1]->GetEndPrice();
		f_range=(f_now_val-f_pre_val)/f_pre_val;
		f_range=f_range/2.0;
		if(f_range>=0.0)
		{
			double f_buy_val=vecStockDayData[i]->GetTotalPrice()*f_range;
			f_total_buy_val+=f_buy_val;
		}
	}

	if(f_total_buy_val>=abs(f_total_sale_val))
	{
		f_power_val=(f_total_buy_val+f_total_sale_val)*100.0/f_total_buy_val;
	}
	else
	{
		f_power_val=(f_total_sale_val+f_total_buy_val)*100.0/abs(f_total_sale_val);
	}
	return TRUE;

}

BOOL CStockPowerArithmetic::NewCalcLastStockPowerValue(int mLastNums,double &f_power_val)
{
	CString strEndDate=pStockDayTable->GetStockDayDateReverseIndex(0);

	CString strBeginDate=pStockDayTable->GetStockDayDateReverseIndex(mLastNums);

	return NewCalcStockPowerValue(strBeginDate,strEndDate,f_power_val);
}

BOOL CStockPowerArithmetic::NewCalcLastStockPowerValue(CString strEndDate,int mN,double &f_power_val)
{
	int mLastNums=mN;
	int mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDate);

	CStockDayData *pStockDayData=NULL;
	pStockDayData=pStockDayTable->GetStockDayDataByIndex(mEndPos);

	if(!pStockDayData)
		return FALSE;

	CString strRealEndDate=pStockDayData->GetDate();

	int mBeginPos=mEndPos-mLastNums;

	if(mBeginPos<0)
		return FALSE;

	pStockDayData=pStockDayTable->GetStockDayDataByIndex(mBeginPos);

	if(!pStockDayData)
		return FALSE;
	CString strRealBeginDate=pStockDayData->GetDate();


	return NewCalcStockPowerValue(strRealBeginDate,strRealEndDate,f_power_val);

}

StockPowerPeriodInfo * CStockPowerArithmetic::NewCalcStockPeriodInfo(CString strBeginDate,CString strEndDate)
{
	StockPowerPeriodInfo * pStockPowerPeriodInfo=NULL;


	double f_5_power;
	if(!NewCalcLastStockPowerValue(strEndDate,5,f_5_power))
		f_5_power=-9999.0;

	double f_10_power;
	if(!NewCalcLastStockPowerValue(strEndDate,10,f_10_power))
		f_10_power=-9999.0;

	double f_20_power;
	if(!NewCalcLastStockPowerValue(strEndDate,20,f_20_power))
		f_20_power=-9999.0;

	double f_40_power;
	if(!NewCalcLastStockPowerValue(strEndDate,40,f_40_power))
		f_40_power=-9999.0;

	double f_60_power;
	if(!NewCalcLastStockPowerValue(strEndDate,60,f_60_power))
		f_60_power=-9999.0;

	double f_120_power;
	if(!NewCalcLastStockPowerValue(strEndDate,120,f_120_power))
		f_120_power=-9999.0;

	double f_240_power;
	if(!NewCalcLastStockPowerValue(strEndDate,240,f_240_power))
		f_240_power=-9999.0;


	double f_date_power;
	if(!NewCalcStockPowerValue(strBeginDate,strEndDate,f_date_power))
		f_date_power=-9999.0;

	pStockPowerPeriodInfo=new StockPowerPeriodInfo();

	pStockPowerPeriodInfo->strStockCode=strStockCode;
	pStockPowerPeriodInfo->strBeginDate=strBeginDate;
	pStockPowerPeriodInfo->strEndDate=strEndDate;
	pStockPowerPeriodInfo->f_5_power=f_5_power;
	pStockPowerPeriodInfo->f_10_power=f_10_power;
	pStockPowerPeriodInfo->f_20_power=f_20_power;
	pStockPowerPeriodInfo->f_40_power=f_40_power;
	pStockPowerPeriodInfo->f_60_power=f_60_power;
	pStockPowerPeriodInfo->f_120_power=f_120_power;
	pStockPowerPeriodInfo->f_240_power=f_240_power;
	pStockPowerPeriodInfo->f_date_power=f_date_power;
	return pStockPowerPeriodInfo;
}


StockPowerPeriodInfo * CStockPowerArithmetic::NewCalcStockPeriodInfo(int mLastNums)
{
	CString strEndDate=pStockDayTable->GetStockDayDateReverseIndex(0);

	CString strBeginDate=pStockDayTable->GetStockDayDateReverseIndex(mLastNums);

	if(strBeginDate=="")
		return NULL;

	return NewCalcStockPeriodInfo(strBeginDate,strEndDate);
}

BOOL IsStockPowerValueInRange(double f_power,double f_cmp_power,double f_allow_range)
{
	double f_range;

	f_range=(f_power-f_cmp_power)*100.0/f_cmp_power;
	
	f_range=abs(f_range);
	if( f_range >=0.0 && f_range<f_allow_range)
	{
		
		return TRUE;
		

	}

	return FALSE;
}

Vec_CString CStockPowerArithmetic::FindSimilarStockPowerPeriodInfo(StockPowerPeriodInfo *pStockPowerPeriodInfo)
{
	Vec_CString vecResult;

	Vec_StockDayData vecStockDayData;
	pStockDayTable->LockData();
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	pStockDayTable->UnlockData();


	if(vecStockDayData.size()<251)
		return vecResult;

	

	for(int i=250;i<(vecStockDayData.size()-1);i++)
	{
		int mEndPos=i;
		CString strDate=vecStockDayData[i]->GetDate();

		int mBeginPos=mEndPos-5;
		double f_5_power=-99999.0;
		NewCalcStockPowerValue(mBeginPos,mEndPos,f_5_power);

		mBeginPos=mEndPos-10;
		double f_10_power=-99999.0;
		NewCalcStockPowerValue(mBeginPos,mEndPos,f_10_power);

		mBeginPos=mEndPos-20;
		double f_20_power=-99999.0;
		NewCalcStockPowerValue(mBeginPos,mEndPos,f_20_power);

		mBeginPos=mEndPos-40;
		double f_40_power=-99999.0;
		NewCalcStockPowerValue(mBeginPos,mEndPos,f_40_power);

		mBeginPos=mEndPos-60;
		double f_60_power=-99999.0;
		NewCalcStockPowerValue(mBeginPos,mEndPos,f_60_power);


		mBeginPos=mEndPos-120;
		double f_120_power=-99999.0;
		NewCalcStockPowerValue(mBeginPos,mEndPos,f_120_power);

		mBeginPos=mEndPos-240;
		double f_240_power=-99999.0;
		NewCalcStockPowerValue(mBeginPos,mEndPos,f_240_power);

		if(IsStockPowerValueInRange(f_10_power,pStockPowerPeriodInfo->f_10_power,30.0))
		{
			if(IsStockPowerValueInRange(f_20_power,pStockPowerPeriodInfo->f_20_power,30.0))
			{

				if(IsStockPowerValueInRange(f_40_power,pStockPowerPeriodInfo->f_40_power,30.0))
				{
					if(IsStockPowerValueInRange(f_60_power,pStockPowerPeriodInfo->f_60_power,30.0))
					{
						if(IsStockPowerValueInRange(f_120_power,pStockPowerPeriodInfo->f_120_power,30.0))
						{
							if(IsStockPowerValueInRange(f_240_power,pStockPowerPeriodInfo->f_240_power,30.0))
							{
								//if(IsStockPowerValueInRange(f_5_power,pStockPowerPeriodInfo->f_5_power,30.0))
								{
									CString strInfo;
									strInfo=strStockCode;
									strInfo+="|";
									strInfo+=vecStockDayData[i]->GetDate();
									vecResult.push_back(strInfo);
								}
								
							}
						}
					}
				}
			}
		}
		


		
	}

	return  vecResult;


}