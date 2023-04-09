#include "stdafx.h"
#include "HistoryStrategy.h"
#include "Log.h"
CHistoryStrategy::CHistoryStrategy()
{
	vecAimStockDayData.clear();
}

CHistoryStrategy::~CHistoryStrategy()
{

}

//根据开始结束时间生成目标天表
BOOL CHistoryStrategy::CreateAimStockDayVec(void)
{
	if(pStockDayTable==NULL)
		return FALSE;
	if(strBeginDayDate=="" || strEndDayDate=="")
		return FALSE;

	int mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDayDate);
	int mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDayDate);

	if(mBeginPos==-1 || mEndPos==-1 )
		return FALSE;

	if(mBeginPos>mEndPos)
		return FALSE;
	vecAimStockDayData.clear();
	Vec_StockDayData vecStockDayData;
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	CStockDayData *pStockDayData=NULL;

	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		vecAimStockDayData.push_back(pStockDayData);

	}
	return TRUE;
}

//根据开始结束时间生成天表数据
Vec_StockDayData CHistoryStrategy::CreateHistoryStockDayVec(CString strBegin,CString strEnd)
{

	Vec_StockDayData vecOutStockDayData;

	if(pStockDayTable==NULL)
		return vecOutStockDayData;
	if(strBeginDayDate=="" || strEndDayDate=="")
		return vecOutStockDayData;

	int mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBegin);
	int mEndPos=pStockDayTable->GetNearestStockDayIndex(strEnd);

	if(mBeginPos==-1 || mEndPos==-1 )
		return vecOutStockDayData;

	if(mBeginPos>mEndPos)
		return vecOutStockDayData;

	vecOutStockDayData.clear();

	Vec_StockDayData vecStockDayData;
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	CStockDayData *pStockDayData=NULL;

	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		vecOutStockDayData.push_back(pStockDayData);

	}
	return vecOutStockDayData;
}
//创建价格波动的集合
BOOL  CHistoryStrategy::CreateAimStockPriceRangeVec(void)
{
	if(vecAimStockDayData.size()<=1)
		return FALSE;
	vecAimPriceRange.clear();

	for(int i=1;i<vecAimStockDayData.size();i++)
	{
		double fVal=vecAimStockDayData[i]->GetEndPrice()-vecAimStockDayData[i-1]->GetEndPrice();
		double fPercent=(fVal/vecAimStockDayData[i]->GetEndPrice())*100.0;
		vecAimPriceRange.push_back(fPercent);
	}


	return TRUE;
}

std::vector<double> CHistoryStrategy:: CreateHistoryStockPriceRangeVec(Vec_StockDayData vecStockDayData)
{
	std::vector<double> vecPriceRange;
	if(vecStockDayData.size()<=1)
		return vecPriceRange;
	vecPriceRange.clear();

	for(int i=1;i<vecStockDayData.size();i++)
	{
		double fVal=vecStockDayData[i]->GetEndPrice()-vecStockDayData[i-1]->GetEndPrice();
		double fPercent=(fVal/vecStockDayData[i]->GetEndPrice())*100.0;
		vecPriceRange.push_back(fPercent);
	}

	return vecPriceRange;
}

//创建交易量波动的集合
BOOL CHistoryStrategy::CreateAimStockVolumeRangeVec(void)	
{
	if(vecAimStockDayData.size()<=1)
		return FALSE;
	vecAimVolumeRange.clear();

	for(int i=1;i<vecAimStockDayData.size();i++)
	{
		double fVal=vecAimStockDayData[i]->GetTotalPrice()-vecAimStockDayData[i-1]->GetTotalPrice();
		double fPercent=(fVal/vecAimStockDayData[i]->GetTotalPrice())*100.0;
		vecAimVolumeRange.push_back(fPercent);
	}
	return TRUE;
}

std::vector<double> CHistoryStrategy:: CreateHistoryStockVolumeRangeVec(Vec_StockDayData vecStockDayData)
{
	std::vector<double> vecVolumeRange;
	if(vecStockDayData.size()<=1)
		return vecVolumeRange;
	vecVolumeRange.clear();

	for(int i=1;i<vecStockDayData.size();i++)
	{
		double fVal=vecStockDayData[i]->GetTotalPrice()-vecStockDayData[i-1]->GetTotalPrice();
		double fPercent=(fVal/vecStockDayData[i]->GetTotalPrice())*100.0;
		vecVolumeRange.push_back(fPercent);
	}
	return vecVolumeRange;
}

BOOL CHistoryStrategy::Init(void)
{
	CreateAimStockDayVec();
	CreateAimStockPriceRangeVec();
	CreateAimStockVolumeRangeVec();
	return TRUE;
}

BOOL CHistoryStrategy::JudgePriceRange(std::vector<double> vecPriceRange)
{
	if(vecPriceRange.size()!=vecAimPriceRange.size())
		return FALSE;

	/*double fAimVal;
	double fVal;
	int mOkNums=0;
	for(int i=0;i<vecAimPriceRange.size();i++)
	{
		fAimVal=vecAimPriceRange[i];
		fVal=vecPriceRange[i];

		if(fAimVal>=0.0 && fVal>=0.0)
		{
			double fTemp=abs(fVal-fAimVal);

			double fDif=(fTemp/fAimVal)*100.0;
			if(fDif<30.0)
				mOkNums++;
		}
		else if(fAimVal<0.0 && fVal<0.0)
		{
			double fTemp=abs(fVal-fAimVal);
			double fDif=(fTemp/abs(fAimVal))*100.0;
			if(fDif<30.0)
				mOkNums++;
		}
		else if(fAimVal>=0.0 && fVal<0.0)
		{
			double fTemp=abs(fVal-fAimVal);
			double fDif=(fTemp/fAimVal)*100.0;
			if(fDif<30.0)
				mOkNums++;

		}
		else if(fAimVal<0.0 && fVal>=0.0)
		{
			double fTemp=abs(fVal-fAimVal);
			double fDif=(fTemp/abs(fAimVal))*100.0;
			if(fDif<30.0)
				mOkNums++;
		}

	}
	if(mOkNums>5)
		PrintfDebug("mOkNums=%d\n",mOkNums);

	if(mOkNums==vecAimPriceRange.size())
		return TRUE;
	else
		return FALSE;*/

	double fAimVal;
	double fVal;
	int mOkNums=0;
	for(int i=0;i<vecAimPriceRange.size();i++)
	{
		fAimVal=vecAimPriceRange[i];
		fVal=vecPriceRange[i];

		if(fAimVal>=0.0 && fVal>=0.0)
		{
			mOkNums++;
		}
		else if(fAimVal<0.0 && fVal<0.0)
		{
			mOkNums++;
		}
	}

	if(mOkNums>11)
		PrintfDebug("mOkNums=%d\n",mOkNums);
	if(mOkNums==vecAimPriceRange.size())
		return TRUE;
	else
		return FALSE;

}

BOOL CHistoryStrategy::JudgeVolumeRange(std::vector<double> vecVolumeRange)
{
	if(vecVolumeRange.size()!=vecAimVolumeRange.size())
		return FALSE;

	double fAimVal;
	double fVal;
	int mOkNums=0;
	for(int i=0;i<vecVolumeRange.size();i++)
	{
		fAimVal=vecAimVolumeRange[i];
		fVal=vecVolumeRange[i];

		if(fAimVal>=0.0 && fVal>=0.0)
		{
			double fTemp=abs(fVal-fAimVal);

			double fDif=(fTemp/fAimVal)*100.0;
			if(fDif<30.0)
				mOkNums++;
		}
		else if(fAimVal<0.0 && fVal<0.0)
		{
			double fTemp=abs(fVal-fAimVal);
			double fDif=(fTemp/abs(fAimVal))*100.0;
			if(fDif<30.0)
				mOkNums++;
		}
		else if(fAimVal>=0.0 && fVal<0.0)
		{
			double fTemp=abs(fVal-fAimVal);
			double fDif=(fTemp/fAimVal)*100.0;
			if(fDif<30.0)
				mOkNums++;

		}
		else if(fAimVal<0.0 && fVal>=0.0)
		{
			double fTemp=abs(fVal-fAimVal);
			double fDif=(fTemp/abs(fAimVal))*100.0;
			if(fDif<30.0)
				mOkNums++;
		}

	}

	if(mOkNums>5)
		PrintfDebug("222 mOkNums=%d\n",mOkNums);


	if(mOkNums==vecAimVolumeRange.size())
		return TRUE;
	else
		return FALSE;

}


//遍历天数据 
BOOL CHistoryStrategy::TraverseStockDayData(void)
{
	if(pStockDayTable==NULL)
		return FALSE;
	if(strBeginDayDate=="" || strEndDayDate=="")
		return FALSE;

	int mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDayDate);
	int mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDayDate);

	if(mBeginPos==-1 || mEndPos==-1 )
		return FALSE;

	if(mBeginPos>mEndPos)
		return FALSE;

	vecHistoryResultList.clear();

	int mDataNums=(mEndPos-mBeginPos)+1;

	Vec_StockDayData vecStockDayData;
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	CStockDayData *pStockDayData=NULL;


	for(int i=0;i<vecStockDayData.size();i++)
	{
		if((i+mDataNums)<=vecStockDayData.size())
		{
			CString strBegin=vecStockDayData[i]->GetDate();
			CString strEnd=vecStockDayData[i+mDataNums-1]->GetDate();
			Vec_StockDayData vecHistoryStockDayData;

			vecHistoryStockDayData=CreateHistoryStockDayVec(strBegin,strEnd);

			std::vector<double> vecPriceRange;
			vecPriceRange=CreateHistoryStockPriceRangeVec(vecHistoryStockDayData);

			std::vector<double> vecVolumeRange;
			vecVolumeRange=CreateHistoryStockVolumeRangeVec(vecHistoryStockDayData);
			BOOL bOK1=JudgePriceRange(vecPriceRange);
			BOOL bOK2=JudgeVolumeRange(vecVolumeRange);
			if( bOK1)	//&& bOK2
			{
				i+=mDataNums;
				HistoryResult * pHistoryResult=new HistoryResult();
				pHistoryResult->strBeginDate=strBegin;
				pHistoryResult->strEndDate=strEnd;
				vecHistoryResultList.push_back(pHistoryResult);
			}
		}
	}

	return TRUE;
}