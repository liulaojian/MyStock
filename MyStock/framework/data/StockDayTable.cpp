#include "stdafx.h"
#include "StockDayTable.h"
#include "zbTypeDef.h"
#include "Convert.h"

CStockDayTable::CStockDayTable(CString strCode)
{
	strStockCode=strCode;
	::InitializeCriticalSection(&dataLock);
}


CStockDayTable::~CStockDayTable()
{
	::DeleteCriticalSection(&dataLock);
}


typedef struct Tdxld_tag
{
	uint32_t dateday;
	uint32_t beginprice;
	uint32_t highprice;
	uint32_t lowprice;
	uint32_t endprice;
	float totalprice;
	uint32_t volume;
	uint32_t reserve;
}Tdxld;

typedef union Tdxld_union_tag
{
	Tdxld tdxld;
	uint8_t data[32];
}Tdxld_union;


BOOL  CStockDayTable::LoadFromDayFile(CString strDatFilePath)
{
	/*
	CStdioFile dayFile;

	CStockDayData *pStockDayData=NULL;
	if(dayFile.Open(strDatFilePath,CFile::modeRead))
	{
		CString strTemp;
		int mLine=0;
		while(dayFile.ReadString(strTemp))
		{
			mLine++;
			if(strTemp.Find("数据来源")>=0)
				continue;
			if(mLine>2)
			{
				CStringArray arryVal;
				StringSplit(strTemp,arryVal,'\t');
				int mNums=arryVal.GetSize();
				if(mNums==7)
				{
					CString strDate=arryVal.GetAt(0);
					float  fBeginPrice=atof((LPCSTR)arryVal.GetAt(1));
					float  fMaxPrice=atof((LPCSTR)arryVal.GetAt(2));
					float  fMinPrice=atof((LPCSTR)arryVal.GetAt(3));
					float  fEndPrice=atof((LPCSTR)arryVal.GetAt(4));
					long   mTotalVolume=atoi((LPCSTR)arryVal.GetAt(5));
					float  fTotalPrice=atof((LPCSTR)arryVal.GetAt(6));
					
					pStockDayData=new CStockDayData();
					pStockDayData->SetDate(strDate);
					pStockDayData->SetBeginPrice(fBeginPrice);
					pStockDayData->SetMaxPrice(fMaxPrice);
					pStockDayData->SetMinPrice(fMinPrice);
					pStockDayData->SetEndPrice(fEndPrice);
					pStockDayData->SetTotalVolume(mTotalVolume);
					pStockDayData->SetTotalPrice(fTotalPrice);
					vecStockDayData.push_back(pStockDayData);
						

				}
				else
				{
					AfxMessageBox("error");
				}

			}
		}
		dayFile.Close();

	}

	*/
	FILE* fp = fopen(strDatFilePath, "rb");
	if (fp == NULL)
		return FALSE;
	CStockDayData* pStockDayData = NULL;
	Tdxld_union tdxld_union;
	while (!feof(fp))
	{
		int retsize = fread(tdxld_union.data, sizeof(Tdxld_union), 1, fp);
		if (retsize != 1)
			break;
		int32_t dateday = tdxld_union.tdxld.dateday;
		int   year = dateday / 10000;
		int   month = (dateday % 10000) / 100;
		int   day = (dateday % 10000) % 100;

		CString strDate;
		strDate.Format("%d/%02d/%02d", year, month, day);

		float fBeginPrice = tdxld_union.tdxld.beginprice / 100.0;
		float fMaxPrice = tdxld_union.tdxld.highprice / 100.0;
		float fMinPrice = tdxld_union.tdxld.lowprice / 100.0;
		float fEndPrice = tdxld_union.tdxld.endprice / 100.0;
		float fTotalPrice = tdxld_union.tdxld.totalprice;
		uint32_t mTotalVolume = tdxld_union.tdxld.volume;

		//printf("year=%d month=%d day=%d beginprice=%f highprice=%f lowprice=%f endprice=%f totalprice=%f volume=%d \n", year, month, day,
		//	beginprice, highprice, lowprice, endprice, totalprice, volume);

		pStockDayData = new CStockDayData();
		pStockDayData->SetDate(strDate);
		pStockDayData->SetBeginPrice(fBeginPrice);
		pStockDayData->SetMaxPrice(fMaxPrice);
		pStockDayData->SetMinPrice(fMinPrice);
		pStockDayData->SetEndPrice(fEndPrice);
		pStockDayData->SetTotalVolume(mTotalVolume);
		pStockDayData->SetTotalPrice(fTotalPrice);
		vecStockDayData.push_back(pStockDayData);

	}

	fclose(fp);
	return TRUE;
}


//加载文件股票数据，利用指数数据进行修补（主要是停牌时修补)
BOOL  CStockDayTable::LoadFromDayFileRepairDate(CString strDatFilePath,CStockDayTable *pExpStockDayTable)
{
	if(pExpStockDayTable==NULL)
		return FALSE;

	Vec_StockDayData vecTempStockDayData;
	
	/*CStdioFile dayFile;

	CStockDayData *pStockDayData=NULL;
	if(dayFile.Open(strDatFilePath,CFile::modeRead))
	{
		CString strTemp;
		int mLine=0;
		while(dayFile.ReadString(strTemp))
		{
			mLine++;
			if(strTemp.Find("数据来源")>=0)
				continue;
			if(mLine>2)
			{
				CStringArray arryVal;
				StringSplit(strTemp,arryVal,'\t');
				int mNums=arryVal.GetSize();
				if(mNums==7)
				{
					CString strDate=arryVal.GetAt(0);
					float  fBeginPrice=atof((LPCSTR)arryVal.GetAt(1));
					float  fMaxPrice=atof((LPCSTR)arryVal.GetAt(2));
					float  fMinPrice=atof((LPCSTR)arryVal.GetAt(3));
					float  fEndPrice=atof((LPCSTR)arryVal.GetAt(4));
					long   mTotalVolume=atoi((LPCSTR)arryVal.GetAt(5));
					float  fTotalPrice=atof((LPCSTR)arryVal.GetAt(6));

					pStockDayData=new CStockDayData();
					pStockDayData->SetDate(strDate);
					pStockDayData->SetBeginPrice(fBeginPrice);
					pStockDayData->SetMaxPrice(fMaxPrice);
					pStockDayData->SetMinPrice(fMinPrice);
					pStockDayData->SetEndPrice(fEndPrice);
					pStockDayData->SetTotalVolume(mTotalVolume);
					pStockDayData->SetTotalPrice(fTotalPrice);
					vecTempStockDayData.push_back(pStockDayData);


				}
				else
				{
					AfxMessageBox("error");
				}

			}
		}
		dayFile.Close();

	}
	*/

	FILE* fp = fopen(strDatFilePath, "rb");
	if (fp == NULL)
		return FALSE;
	CStockDayData* pStockDayData = NULL;
	Tdxld_union tdxld_union;
	while (!feof(fp))
	{
		int retsize = fread(tdxld_union.data, sizeof(Tdxld_union), 1, fp);
		if (retsize != 1)
			break;
		int32_t dateday = tdxld_union.tdxld.dateday;
		int   year = dateday / 10000;
		int   month = (dateday % 10000) / 100;
		int   day = (dateday % 10000) % 100;

		CString strDate;
		strDate.Format("%d/%02d/%02d", year, month, day);

		float fBeginPrice = tdxld_union.tdxld.beginprice / 100.0;
		float fMaxPrice = tdxld_union.tdxld.highprice / 100.0;
		float fMinPrice = tdxld_union.tdxld.lowprice / 100.0;
		float fEndPrice = tdxld_union.tdxld.endprice / 100.0;
		float fTotalPrice = tdxld_union.tdxld.totalprice;
		uint32_t mTotalVolume = tdxld_union.tdxld.volume;

		//printf("year=%d month=%d day=%d beginprice=%f highprice=%f lowprice=%f endprice=%f totalprice=%f volume=%d \n", year, month, day,
		//	beginprice, highprice, lowprice, endprice, totalprice, volume);

		pStockDayData = new CStockDayData();
		pStockDayData->SetDate(strDate);
		pStockDayData->SetBeginPrice(fBeginPrice);
		pStockDayData->SetMaxPrice(fMaxPrice);
		pStockDayData->SetMinPrice(fMinPrice);
		pStockDayData->SetEndPrice(fEndPrice);
		pStockDayData->SetTotalVolume(mTotalVolume);
		pStockDayData->SetTotalPrice(fTotalPrice);
		vecTempStockDayData.push_back(pStockDayData);

	}

	fclose(fp);

	if(vecTempStockDayData.size()==0)
		return FALSE;

	Vec_StockDayData vecExpStockDayData;

	vecExpStockDayData=pExpStockDayTable->GetStockDayDataList();

	pStockDayData=vecTempStockDayData[0];
	CString strBeginDate=pStockDayData->GetDate();

	int mExpBeginPos=pExpStockDayTable->GetStockDayIndex(strBeginDate);

	if(mExpBeginPos==-1)
		return FALSE;
		
	CStockDayData *pExpStockDayData;
	int pos=0;
	int i=0;
	for(i=mExpBeginPos;i<vecExpStockDayData.size();i++)
	{
		pExpStockDayData=vecExpStockDayData[i];
		if(!pExpStockDayData)
			continue;
		pStockDayData=vecTempStockDayData[pos];
		if(!pStockDayData)
			continue;

		if(pStockDayData->GetDate()==pExpStockDayData->GetDate())
		{
			vecStockDayData.push_back(pStockDayData);
			pos++;
			if(pos>=vecTempStockDayData.size())
			{
				break;
			}
		}
		else
		{
			CStockDayData *pData=new CStockDayData();
			if(pos>0)
			{
				CStockDayData *pPreStockDayData=vecTempStockDayData[pos-1];
				pData->SetDate(pExpStockDayData->GetDate());
				pData->SetBeginPrice(pPreStockDayData->GetEndPrice());
				pData->SetMaxPrice(pPreStockDayData->GetEndPrice());
				pData->SetMinPrice(pPreStockDayData->GetEndPrice());
				pData->SetEndPrice(pPreStockDayData->GetEndPrice());
				pData->SetTotalVolume(0);
				pData->SetTotalPrice(0.0);
				vecStockDayData.push_back(pData);
			}
			
		}
	}

	if(i<vecExpStockDayData.size()-1)
	{
		for(int j=i+1;j<vecExpStockDayData.size();j++)
		{
			pExpStockDayData=vecExpStockDayData[j];
			if(!pExpStockDayData)
				continue;
			CStockDayData *pData=new CStockDayData();
			CStockDayData *pPreStockDayData=vecTempStockDayData[vecTempStockDayData.size()-1];
			pData->SetDate(pExpStockDayData->GetDate());
			pData->SetBeginPrice(pPreStockDayData->GetEndPrice());
			pData->SetMaxPrice(pPreStockDayData->GetEndPrice());
			pData->SetMinPrice(pPreStockDayData->GetEndPrice());
			pData->SetEndPrice(pPreStockDayData->GetEndPrice());
			pData->SetTotalVolume(0);
			pData->SetTotalPrice(0.0);
			vecStockDayData.push_back(pData);
		}
		
	}

	return TRUE;

}


BOOL CStockDayTable:: LoadFromVec(Vec_StockDayData vecData)
{
	CStockDayData *pStockDayData=NULL;
	vecStockDayData.clear();
	for(int i=0;i<vecData.size();i++)
	{
		pStockDayData=vecData[i];
		if(!pStockDayData)
			continue;
		vecStockDayData.push_back(pStockDayData);
	}
	return TRUE;
}



CString CStockDayTable::GetStockBeginDate(void)
{
	
	if(vecStockDayData.size()==0)
		return "";
	LockData();
	CString strResult=vecStockDayData[0]->GetDate();
	UnlockData();
	return strResult;

}


CString CStockDayTable::GetStockEndDate(void)
{
	if(vecStockDayData.size()==0)
		return "";
	LockData();
	CString strResult=vecStockDayData[vecStockDayData.size()-1]->GetDate();
	UnlockData();
	return strResult;
}


CString  CStockDayTable::GetStockDayDateReverseIndex(int index)
{
	if(vecStockDayData.size()==0)
		return "";

	if(index>=vecStockDayData.size())
		return "";

	int pos=vecStockDayData.size()-index-1;
	
	LockData();
	CString strResult= vecStockDayData[pos]->GetDate();
	UnlockData();
	return strResult;

}

CString CStockDayTable::GetStockDayDateByIndex(int index)
{
	if(vecStockDayData.size()==0)
		return "";

	if(index>=vecStockDayData.size())
		return "";
	LockData();
	CString strResult= vecStockDayData[index]->GetDate();
	UnlockData();
	return strResult;
}


CStockDayData* CStockDayTable::GetNextStockDayDataByDate(CString strDate)
{
	CStockDayData *pStockDayData=NULL;
	if(vecStockDayData.size()==0)
		return NULL;
	int index=-1;
	LockData();
	for(int i=0;i<vecStockDayData.size();i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetDate()==strDate)
		{
			index=i;
			break;
		}
	}

	if(index==-1)
	{
		UnlockData();
		return NULL;
	}
	index=index+1;
	if(index>=vecStockDayData.size())
	{
		UnlockData();
		return NULL;
	}
	pStockDayData=vecStockDayData[index];
	UnlockData();
	return pStockDayData;

}

CStockDayData* CStockDayTable::GetStockDayDataByDate(CString strDate)
{
	CStockDayData *pStockDayData=NULL;
	if(vecStockDayData.size()==0)
		return NULL;
	LockData();
	for(int i=0;i<vecStockDayData.size();i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetDate()==strDate)
		{
			UnlockData();
			return pStockDayData;
		}
	}
	UnlockData();
	return NULL;
}

BOOL CStockDayTable::IsNextStockDayDataExist(CString strDate)
{
	if(vecStockDayData.size()==0)
		return FALSE;
	CStockDayData *pStockDayData=NULL;
	LockData();
	for(int i=0;i<vecStockDayData.size();i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetDate()==strDate)
		{
			UnlockData();
			return TRUE;
		}
	}
	UnlockData();
	return FALSE;
}

CString  CStockDayTable::GetNearestStockDayDate(CTime mDateTime)
{
	if(vecStockDayData.size()==0)
		return "";
	CStockDayData *pStockDayData=NULL;
	LockData();
	
	int mNearestDays=99999;
	int mNearestPos=-1;
	for(int i=0;i<vecStockDayData.size();i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		CString strCheckTime=vecStockDayData[i]->GetDate();
		CTime mCheckDateTime;
		try
		{
			mCheckDateTime=ConverStringToCTime(strCheckTime);
		}
		catch (...)
		{
			printf("222 catch\n");
			continue;
		}
		
		CTimeSpan span=mDateTime-mCheckDateTime;
		int iDay=span.GetDays();
		if(iDay==0)
		{
			UnlockData();
			return strCheckTime;
		}
		if((iDay<mNearestDays)&&(iDay>0))
		{
			mNearestDays=iDay;
			mNearestPos=i;
		}


	}

	if(mNearestPos>=0)
	{
		CString strReult=vecStockDayData[mNearestPos]->GetDate();
		UnlockData();
		return strReult;
	}
	
	UnlockData();
	return "";
}

int   CStockDayTable::GetStockDayIndexByDateReverse(CString strDate)
{
	if(vecStockDayData.size()==0)
		return -1;
	CStockDayData *pStockDayData=NULL;
	LockData();
	for(int i=vecStockDayData.size()-1;i>=0;i--)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetDate()==strDate)
		{
			UnlockData();
			return i;
		}
	}
	UnlockData();
	return -1;
}

CString CStockDayTable::GetStockDayDatePreOfIndexReverse(CString strDate,int prenums)
{
	int pos=GetStockDayIndexByDateReverse(strDate);
	if(pos==-1)
		return "";

	if(pos<prenums)
		return "";
	LockData();
	CString strResult=vecStockDayData[pos-prenums]->GetDate();
	return strResult;
	UnlockData();
}

int  CStockDayTable::GetStockDayIndex(CString strDate)
{
	if(vecStockDayData.size()==0)
		return -1;
	CStockDayData *pStockDayData=NULL;
	LockData();
	for(int i=0;i<vecStockDayData.size();i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetDate()==strDate)
		{
			UnlockData();
			return i;
		}
	}
	UnlockData();
	return -1;
}
int  CStockDayTable::GetNearestStockDayIndex(CString strDate)
{
	if(vecStockDayData.size()==0)
		return -1;
	CString strTempDate=strDate.Left(5);
	CStockDayData *pStockDayData=NULL;
	int mBeginPos=0;
	LockData();
	for(int i=0;i<vecStockDayData.size();i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		CString strTemp=pStockDayData->GetDate().Left(5);
		if(strTemp==strTempDate)
		{
			mBeginPos=i;
			break;
		}
	}

	CTime mDateTime=ConverStringToCTime(strDate);
	
	
	int mNearestDays=99999;
	int mNearestPos=-1;
	for(int i=mBeginPos;i<vecStockDayData.size();i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		CString strCheckTime=vecStockDayData[i]->GetDate();
		CTime mCheckDateTime=ConverStringToCTime(strCheckTime);

		CTimeSpan span=mDateTime-mCheckDateTime;
		int iDay=span.GetDays();
		if(iDay==0)
		{
			UnlockData();
			return i;
		}
		if((iDay<mNearestDays)&&(iDay>0))
		{
			mNearestDays=iDay;
			mNearestPos=i;
		}


	}

	if(mNearestPos>=0)
	{
		UnlockData();
		return mNearestPos;
	}
	UnlockData();
	return -1;
}



CString CStockDayTable::GetStockDayDatePreOfIndex(CString strDate,int prenums)
{
	if(vecStockDayData.size()==0)
		return "";
	if(prenums<0)
		return "";
	int Pos=GetNearestStockDayIndex(strDate);

	Pos=Pos-prenums;

	if(Pos<0)
		Pos=0;

	LockData();
	CString strResult=vecStockDayData[Pos]->GetDate();
	UnlockData();
	return strResult;
}

CString CStockDayTable::GetStockDayDateAftOfIndex(CString strDate,int aftnums)
{
	if(vecStockDayData.size()==0)
		return "";
	if(aftnums<0)
		return "";
	int Pos=GetNearestStockDayIndex(strDate);

	Pos=Pos+aftnums;

	if(Pos>=vecStockDayData.size())
		Pos=vecStockDayData.size()-1;
	LockData();
	CString strResult= vecStockDayData[Pos]->GetDate();
	UnlockData();
	return strResult;
}


float CStockDayTable::GetMinLowPriceBwDates(CString strBeginDate,CString strEndDate)
{
	if(vecStockDayData.size()==0)
		return 0.0;
	
	int mBeginPos=GetNearestStockDayIndex(strBeginDate);
	int mEndPos=GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1 || mEndPos==-1 )
		return 0.0;

	if(mBeginPos>mEndPos)
		return 0.0;
	
	float f_min_val=999999.0;
	CStockDayData *pStockDayData=NULL;
	LockData();
	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetMinPrice()<f_min_val)
			f_min_val=pStockDayData->GetMinPrice();
	}
	UnlockData();
	return f_min_val;
}


float CStockDayTable::GetMaxHighPriceBwDates(CString strBeginDate,CString strEndDate)
{
	if(vecStockDayData.size()==0)
		return 0.0;

	int mBeginPos=GetNearestStockDayIndex(strBeginDate);
	int mEndPos=GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1 || mEndPos==-1 )
		return 0.0;

	if(mBeginPos>mEndPos)
		return 0.0;
	LockData();
	float f_max_val=0.0;
	CStockDayData *pStockDayData=NULL;
	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetMaxPrice()>f_max_val)
			f_max_val=pStockDayData->GetMaxPrice();
	}
	UnlockData();
	return f_max_val;
}

float CStockDayTable::GetMinVolumeBwDates(CString strBeginDate,CString strEndDate)
{
	if(vecStockDayData.size()==0)
		return 0.0;

	int mBeginPos=GetNearestStockDayIndex(strBeginDate);
	int mEndPos=GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1 || mEndPos==-1 )
		return 0.0;

	if(mBeginPos>mEndPos)
		return 0.0;

	float f_min_volume=999999999999999.0;
	CStockDayData *pStockDayData=NULL;
	LockData();
	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetTotalPrice()<f_min_volume)
			f_min_volume=pStockDayData->GetTotalPrice();
	}
	UnlockData();
	return f_min_volume;

}

float CStockDayTable::GetMaxVolumeBwDates(CString strBeginDate,CString strEndDate)
{
	if(vecStockDayData.size()==0)
		return 0.0;

	int mBeginPos=GetNearestStockDayIndex(strBeginDate);
	int mEndPos=GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1 || mEndPos==-1 )
		return 0.0;

	if(mBeginPos>mEndPos)
		return 0.0;

	float f_max_volume=0.0;
	CStockDayData *pStockDayData=NULL;
	LockData();
	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetTotalPrice()>f_max_volume)
			f_max_volume=pStockDayData->GetTotalPrice();
	}
	UnlockData();
	return f_max_volume;
}

Vec_StockDayData CStockDayTable::GetStockDayDataListBwDates(CString strBeginDate,CString strEndDate)
{
	Vec_StockDayData vecData;

	if(vecStockDayData.size()==0)
		return vecData;

	int mBeginPos=GetNearestStockDayIndex(strBeginDate);
	int mEndPos=GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1 || mEndPos==-1 )
		return vecData;

	if(mBeginPos>mEndPos)
		return vecData;

	CStockDayData *pStockDayData=NULL;
	LockData();
	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		vecData.push_back(pStockDayData);
	}
	UnlockData();
	return vecData;
}

Vec_StockDayData CStockDayTable::GetStockDayDataListBwIndex(int mBeginPos,int  mEndPos)
{
	Vec_StockDayData vecData;

	if(vecStockDayData.size()==0)
		return vecData;

	if(mBeginPos==-1 || mEndPos==-1 )
		return vecData;

	if(mBeginPos>mEndPos)
		return vecData;

	CStockDayData *pStockDayData=NULL;
	LockData();
	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		vecData.push_back(pStockDayData);
	}
	UnlockData();
	return vecData;

}

CStockDayData * CStockDayTable::GetStockDayDataByIndex(int index)
{
	CStockDayData *pStockDayData=NULL;

	if(vecStockDayData.size()==0)
		return NULL;

	if(index>=vecStockDayData.size() || index<0)
		return NULL;
	LockData();
	CStockDayData *pResult= vecStockDayData[index];
	UnlockData();
	return pResult;

}



BOOL  CStockDayTable::AddOrUpdateStockDayData(CStockDayData *pAddStockDayData)
{
	if(!pAddStockDayData)
		return FALSE;
	CStockDayData *pStockDayData=NULL;
	LockData();
	for(int i=0;i<vecStockDayData.size();i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetDate()==pAddStockDayData->GetDate())
		{
			pStockDayData->SetBeginPrice(pAddStockDayData->GetBeginPrice());
			pStockDayData->SetEndPrice(pAddStockDayData->GetEndPrice());
			pStockDayData->SetMaxPrice(pAddStockDayData->GetMaxPrice());
			pStockDayData->SetMinPrice(pAddStockDayData->GetMinPrice());
			pStockDayData->SetTotalVolume(pAddStockDayData->GetTotalVolume());
			pStockDayData->SetTotalPrice(pAddStockDayData->GetTotalPrice());
			UnlockData();
			return TRUE;
		}
	}
	vecStockDayData.push_back(pAddStockDayData);
	UnlockData();
	return TRUE;

}
//获取最后的股票日期
CString CStockDayTable::GetLastStockDate(void)
{
	if(vecStockDayData.size()==0)
		return "";
	LockData();
	CString strResult= vecStockDayData[vecStockDayData.size()-1]->GetDate();
	UnlockData();
	return strResult;
}

CString CStockDayTable::GetLastStockDateByReverse(int index)
{
	if(vecStockDayData.size()==0)
		return "";

	if(index>=vecStockDayData.size())
		return "";

	LockData();
	CString strResult= vecStockDayData[vecStockDayData.size()-1-index]->GetDate();
	UnlockData();
	return strResult;
}

//获取最后的股票End Price
float CStockDayTable::GetLastStockEndPrice(void)
{
	if(vecStockDayData.size()==0)
		return -1.0;
	LockData();
	float f_result= vecStockDayData[vecStockDayData.size()-1]->GetEndPrice();
	UnlockData();
	return f_result;
}

//获取股票最后n--m个交易日内，最低值  n>m,如果没有返回-1.0
float CStockDayTable::GetLastDayNumsStockMinPrice(int mDayNums,int mNoUseDayNums)
{
	if(vecStockDayData.size()==0)
		return -1.0;

	if(mNoUseDayNums>=mDayNums)
		return -1.0;

	float f_min_price=999999999999999.0;

	int mBeginPos=vecStockDayData.size()-mDayNums;
	int mEndPos=vecStockDayData.size()-mNoUseDayNums;
	if(mBeginPos<0||mEndPos<0)
		return -1.0;

	CStockDayData *pStockDayData=NULL;
	LockData();
	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetMinPrice()<f_min_price)
			f_min_price=pStockDayData->GetMinPrice();
	}
	UnlockData();
	return f_min_price;
}




//获取股票指定日期的涨幅(百分比格式)
float CStockDayTable::GetStockEndPriceIncrease(CString strDate)
{
	CStockDayData *pStockDayData=NULL;
	pStockDayData=GetStockDayDataByDate(strDate);
	if(pStockDayData==NULL)
		return INVALID_INCREASE;
	
	CString strPreDate=GetStockDayDatePreOfIndexReverse(strDate,1);	// GetStockDayDatePreOfIndex(strDate,1);
	if(strPreDate=="")
		return INVALID_INCREASE;
	CStockDayData *pPreStockDayData=NULL;

	pPreStockDayData=GetStockDayDataByDate(strPreDate);

	if(pPreStockDayData==NULL)
		return INVALID_INCREASE;

	float f_increase=(pStockDayData->GetEndPrice()-pPreStockDayData->GetEndPrice())*100.0/pPreStockDayData->GetEndPrice();

	return f_increase;

}
//获取股票指定日期的成交额涨幅(百分比格式)
float  CStockDayTable::GetStockVolumeIncrease(CString strDate)
{
	CStockDayData *pStockDayData=NULL;
	pStockDayData=GetStockDayDataByDate(strDate);
	if(pStockDayData==NULL)
		return INVALID_VOLUME;
	CString strPreDate=GetStockDayDatePreOfIndexReverse(strDate,1);//GetStockDayDatePreOfIndex(strDate,1);
	if(strPreDate=="")
		return INVALID_VOLUME;

	CStockDayData *pPreStockDayData=NULL;

	pPreStockDayData=GetStockDayDataByDate(strPreDate);

	if(pPreStockDayData==NULL)
		return INVALID_VOLUME;
	float f_volume_increase=(pStockDayData->GetTotalPrice()-pPreStockDayData->GetTotalPrice())*100.0/pPreStockDayData->GetTotalPrice();

	return f_volume_increase;
}



//获取股票指定日期前N日的平均涨幅(百分比格式) (不包含当前日期)
float CStockDayTable::GetStockEndPricePreAveIncrease(CString strDate,int mNums)
{
	if(mNums<=0)
		return INVALID_INCREASE;
	float f_total_increase=0.0;
	for(int i=mNums;i>0;i--)
	{
		CString strPreDate=GetStockDayDatePreOfIndexReverse(strDate,i);//GetStockDayDatePreOfIndex(strDate,i);
		if(strPreDate=="")
			return INVALID_INCREASE;
		float f_increase=GetStockEndPriceIncrease(strPreDate);
		f_total_increase+=f_increase;

	}

	float f_ave_increase=f_total_increase/mNums;

	return f_ave_increase;

}



//获取股票指定日期前N日的平均成交额涨幅(百分比格式)
float CStockDayTable::GetStockVolumePreAveIncrease(CString strDate,int mNums)
{
	if(mNums<=0)
		return INVALID_VOLUME;
	float f_total_volume_increase=0.0;
	for(int i=mNums;i>0;i--)
	{
		CString strPreDate=GetStockDayDatePreOfIndexReverse(strDate,i);//GetStockDayDatePreOfIndex(strDate,i);
		if(strPreDate=="")
			return INVALID_VOLUME;
		float f_volume_increase=GetStockVolumeIncrease(strPreDate);
		f_total_volume_increase+=f_volume_increase;

	}

	float f_ave_volume_increase=f_total_volume_increase/mNums;

	return f_ave_volume_increase;

}


CStockDayData * CStockDayTable::GetLastStockDayData(void)
{ 
	int mSize=vecStockDayData.size();
	return vecStockDayData[mSize-1];
}