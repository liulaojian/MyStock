#include "stdafx.h"
#include "StockMonitorData.h"

CStockMonitorData::CStockMonitorData(CString strCode)
{
	strStockCode=strCode;
}

CStockMonitorData::~CStockMonitorData()
{

}

BOOL  CStockMonitorData::AddStockSarData(StockSarData *pStockSarData)
{
	if(pStockSarData==NULL)
		return FALSE;

	
	for(int i=0;i<vecStockSarData.size();i++)
	{
		if(!vecStockSarData[i])
			continue;
		if(vecStockSarData[i]->strDateTime==pStockSarData->strDateTime)
		{
			return FALSE;
		}
	}

	vecStockSarData.push_back(pStockSarData);

	return TRUE;
}

StockSarData *CStockMonitorData::GetLastStockSarData(void)
{
	if(vecStockSarData.size()==0)
		return NULL;
	return vecStockSarData[vecStockSarData.size()-1];
}

//是否 最后连续2个都是绿的
BOOL  CStockMonitorData::IsLastTwoContinueGreen()
{
	if(vecStockSarData.size()<2)
		return TRUE;

	if( (vecStockSarData[vecStockSarData.size()-2]->mSarColor==SAR_COLOR_GREEN) && (vecStockSarData[vecStockSarData.size()-1]->mSarColor==SAR_COLOR_GREEN) )
		return TRUE;

	return FALSE;
}

StockSarData *CStockMonitorData::GetStockSarDataByDateTime(CString  strDateTime)
{
	StockSarData *pStockSarData=NULL;

	for(int i=0;i<vecStockSarData.size();i++)
	{
		pStockSarData=vecStockSarData[i];
		if(!pStockSarData)
			continue;
		if(pStockSarData->strDateTime==strDateTime)
			return pStockSarData;
	}
	return NULL;
}