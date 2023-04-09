#include "stdafx.h"
#include "StockMin5Table.h"
#include "NetStock.h"
#include "Convert.h"
#include "Log.h"
CStockMin5Table::CStockMin5Table(CString strCode)
{
	strStockCode=strCode;
	pNetStock=NULL;
	::InitializeCriticalSection(&dataLock);
}

CStockMin5Table::~CStockMin5Table()
{
	::DeleteCriticalSection(&dataLock);
}

typedef struct Tdxlc_tag
{
	uint16_t datetime;
	uint16_t mins;
	float beginprice;
	float highprice;
	float lowprice;
	float endprice;
	float totalprice;
	uint32_t volume;
	uint32_t reserve;
}Tdxlc;

typedef union Tdxlc_union_tag
{
	Tdxlc tdxlc;
	uint8_t data[32];
}Tdxlc_union;

BOOL CStockMin5Table:: LoadFromMin5File(CString strDataFilePath)
{
	/*CStdioFile min5File;

	CStockMin5Data *pStockMin5Data=NULL;
	if(min5File.Open(strDataFilePath,CFile::modeRead))
	{
		CString strTemp;
		int mLine=0;
		while(min5File.ReadString(strTemp))
		{
			mLine++;
			if(strTemp.Find("数据来源")>=0)
				continue;
			if(mLine>2)
			{
				CStringArray arryVal;
				StringSplit(strTemp,arryVal,'\t');
				int mNums=arryVal.GetSize();
				if(mNums==8)
				{
					CString strDate=arryVal.GetAt(0);
					CString strTime=arryVal.GetAt(1);
					float  fBeginPrice=atof((LPCSTR)arryVal.GetAt(2));
					float  fMaxPrice=atof((LPCSTR)arryVal.GetAt(3));
					float  fMinPrice=atof((LPCSTR)arryVal.GetAt(4));
					float  fEndPrice=atof((LPCSTR)arryVal.GetAt(5));
					long   mTotalVolume=atoi((LPCSTR)arryVal.GetAt(6));
					float  fTotalPrice=atof((LPCSTR)arryVal.GetAt(7));

					pStockMin5Data=new CStockMin5Data();
					pStockMin5Data->SetDate(strDate);
					pStockMin5Data->SetTime(strTime);
					pStockMin5Data->SetBeginPrice(fBeginPrice);
					pStockMin5Data->SetMaxPrice(fMaxPrice);
					pStockMin5Data->SetMinPrice(fMinPrice);
					pStockMin5Data->SetEndPrice(fEndPrice);
					pStockMin5Data->SetTotalVolume(mTotalVolume);
					pStockMin5Data->SetTotalPrice(fTotalPrice);
					vecStockMin5Data.push_back(pStockMin5Data);


				}
				else
				{
					AfxMessageBox("error");
				}

			}
		}
		min5File.Close();

	}
	*/
	FILE* fp = fopen(strDataFilePath, "rb");
	if (fp == NULL)
		return FALSE;
	CStockMin5Data* pStockMin5Data = NULL;
	Tdxlc_union tdxlc_union;
	while (!feof(fp))
	{
		int retsize = fread(tdxlc_union.data, sizeof(Tdxlc_union), 1, fp);
		if (retsize != 1)
			break;
		int   year = floor(tdxlc_union.tdxlc.datetime / 2048) + 2004;
		int   month = floor((tdxlc_union.tdxlc.datetime % 2048) / 100);
		int day = (tdxlc_union.tdxlc.datetime % 2048) % 100;
		int hour = tdxlc_union.tdxlc.mins / 60;
		int min = tdxlc_union.tdxlc.mins % 60;
		CString strDate;
		strDate.Format("%d/%02d/%02d", year, month, day);
		CString strTime;
		strTime.Format("%02d:%02d", hour, min);

		float fBeginPrice = tdxlc_union.tdxlc.beginprice;
		float fMaxPrice = tdxlc_union.tdxlc.highprice;
		float fMinPrice = tdxlc_union.tdxlc.lowprice;
		float fEndPrice = tdxlc_union.tdxlc.endprice;
		float fTotalPrice = tdxlc_union.tdxlc.totalprice;
		uint32_t mTotalVolume = tdxlc_union.tdxlc.volume;

		pStockMin5Data = new CStockMin5Data();
		pStockMin5Data->SetDate(strDate);
		pStockMin5Data->SetTime(strTime);
		pStockMin5Data->SetBeginPrice(fBeginPrice);
		pStockMin5Data->SetMaxPrice(fMaxPrice);
		pStockMin5Data->SetMinPrice(fMinPrice);
		pStockMin5Data->SetEndPrice(fEndPrice);
		pStockMin5Data->SetTotalVolume(mTotalVolume);
		pStockMin5Data->SetTotalPrice(fTotalPrice);
		vecStockMin5Data.push_back(pStockMin5Data);
		
	}

	fclose(fp);

	return TRUE;
}

//加载文件股票数据，利用指数数据进行修补（主要是停牌时修补)
BOOL  CStockMin5Table::LoadFromMin5FileRepairDate(CString strDatFilePath,CStockMin5Table *pExpStockMin5Table)
{

	Vec_StockMin5Data vecTempStockMin5Data;
	/*CStdioFile min5File;

	CStockMin5Data *pStockMin5Data=NULL;
	if(min5File.Open(strDatFilePath,CFile::modeRead))
	{
		CString strTemp;
		int mLine=0;
		while(min5File.ReadString(strTemp))
		{
			mLine++;
			if(strTemp.Find("数据来源")>=0)
				continue;
			if(mLine>2)
			{
				CStringArray arryVal;
				StringSplit(strTemp,arryVal,'\t');
				int mNums=arryVal.GetSize();
				if(mNums==8)
				{
					CString strDate=arryVal.GetAt(0);
					CString strTime=arryVal.GetAt(1);
					float  fBeginPrice=atof((LPCSTR)arryVal.GetAt(2));
					float  fMaxPrice=atof((LPCSTR)arryVal.GetAt(3));
					float  fMinPrice=atof((LPCSTR)arryVal.GetAt(4));
					float  fEndPrice=atof((LPCSTR)arryVal.GetAt(5));
					long   mTotalVolume=atoi((LPCSTR)arryVal.GetAt(6));
					float  fTotalPrice=atof((LPCSTR)arryVal.GetAt(7));

					pStockMin5Data=new CStockMin5Data();
					pStockMin5Data->SetDate(strDate);
					pStockMin5Data->SetTime(strTime);
					pStockMin5Data->SetBeginPrice(fBeginPrice);
					pStockMin5Data->SetMaxPrice(fMaxPrice);
					pStockMin5Data->SetMinPrice(fMinPrice);
					pStockMin5Data->SetEndPrice(fEndPrice);
					pStockMin5Data->SetTotalVolume(mTotalVolume);
					pStockMin5Data->SetTotalPrice(fTotalPrice);
					vecTempStockMin5Data.push_back(pStockMin5Data);


				}
				else
				{
					AfxMessageBox("error");
				}

			}
		}
		min5File.Close();

	}*/

	FILE* fp = fopen(strDatFilePath, "rb");
	if (fp == NULL)
		return FALSE;
	CStockMin5Data* pStockMin5Data = NULL;
	Tdxlc_union tdxlc_union;
	while (!feof(fp))
	{
		int retsize = fread(tdxlc_union.data, sizeof(Tdxlc_union), 1, fp);
		if (retsize != 1)
			break;
		int   year = floor(tdxlc_union.tdxlc.datetime / 2048) + 2004;
		int   month = floor((tdxlc_union.tdxlc.datetime % 2048) / 100);
		int day = (tdxlc_union.tdxlc.datetime % 2048) % 100;
		int hour = tdxlc_union.tdxlc.mins / 60;
		int min = tdxlc_union.tdxlc.mins % 60;
		CString strDate;
		strDate.Format("%d/%02d/%02d", year, month, day);
		CString strTime;
		strTime.Format("%02d:%02d", hour, min);

		float fBeginPrice = tdxlc_union.tdxlc.beginprice;
		float fMaxPrice = tdxlc_union.tdxlc.highprice;
		float fMinPrice = tdxlc_union.tdxlc.lowprice;
		float fEndPrice = tdxlc_union.tdxlc.endprice;
		float fTotalPrice = tdxlc_union.tdxlc.totalprice;
		uint32_t mTotalVolume = tdxlc_union.tdxlc.volume;

		pStockMin5Data = new CStockMin5Data();
		pStockMin5Data->SetDate(strDate);
		pStockMin5Data->SetTime(strTime);
		pStockMin5Data->SetBeginPrice(fBeginPrice);
		pStockMin5Data->SetMaxPrice(fMaxPrice);
		pStockMin5Data->SetMinPrice(fMinPrice);
		pStockMin5Data->SetEndPrice(fEndPrice);
		pStockMin5Data->SetTotalVolume(mTotalVolume);
		pStockMin5Data->SetTotalPrice(fTotalPrice);
		vecTempStockMin5Data.push_back(pStockMin5Data);

	}

	fclose(fp);


	if(vecTempStockMin5Data.size()==0)
		return FALSE;

	Vec_StockMin5Data vecExpStockMin5Data;
	vecExpStockMin5Data=pExpStockMin5Table->GetStockMin5DataList();

	pStockMin5Data=vecTempStockMin5Data[0];
	CString stDateTime=pStockMin5Data->GetDateTime();
	int mExpBeginPos=pExpStockMin5Table->GetStockMin5Index(stDateTime);
	if(mExpBeginPos==-1)
		return FALSE;
	CStockMin5Data *pExpStockMin5Data=NULL;
	int pos=0;
	int i=0;
	for(i=mExpBeginPos;i<vecExpStockMin5Data.size();i++)
	{
		pExpStockMin5Data=vecExpStockMin5Data[i];
		if(!pExpStockMin5Data)
			continue;

		pStockMin5Data=vecTempStockMin5Data[pos];
		if(!pStockMin5Data)
			continue;
		if(pStockMin5Data->GetDateTime()==pExpStockMin5Data->GetDateTime())
		{
			vecStockMin5Data.push_back(pStockMin5Data);
			pos++;
			if(pos>=vecTempStockMin5Data.size())
			{
				break;
			}
		}
		else
		{

			if(pos>0)
			{
				CStockMin5Data *pStockMin5Data=new CStockMin5Data();

				CStockMin5Data *pPreStockMin5Data=vecTempStockMin5Data[pos-1];
				pStockMin5Data->SetDate(pExpStockMin5Data->GetDate());
				pStockMin5Data->SetTime(pExpStockMin5Data->GetTime());
				pStockMin5Data->SetBeginPrice(pPreStockMin5Data->GetBeginPrice());
				pStockMin5Data->SetMaxPrice(pPreStockMin5Data->GetMaxPrice());
				pStockMin5Data->SetMinPrice(pPreStockMin5Data->GetMinPrice());
				pStockMin5Data->SetEndPrice(pPreStockMin5Data->GetEndPrice());
				pStockMin5Data->SetTotalPrice(0.0);
				pStockMin5Data->SetTotalVolume(0);
				vecStockMin5Data.push_back(pStockMin5Data);

			}
		}

	}

	if(i<vecExpStockMin5Data.size()-1)
	{
		for(int j=i+1;j<vecExpStockMin5Data.size();j++)
		{
			pExpStockMin5Data=vecExpStockMin5Data[j];
			if(!pExpStockMin5Data)
				continue;
			CStockMin5Data *pData=new CStockMin5Data();
			CStockMin5Data *pPreStockMin5Data=vecTempStockMin5Data[vecTempStockMin5Data.size()-1];
			pData->SetDate(pExpStockMin5Data->GetDate());
			pData->SetTime(pExpStockMin5Data->GetTime());
			pData->SetBeginPrice(pPreStockMin5Data->GetEndPrice());
			pData->SetMaxPrice(pPreStockMin5Data->GetEndPrice());
			pData->SetMinPrice(pPreStockMin5Data->GetEndPrice());
			pData->SetEndPrice(pPreStockMin5Data->GetEndPrice());
			pData->SetTotalVolume(0);
			pData->SetTotalPrice(0.0);
			vecStockMin5Data.push_back(pData);
		}

	}



	return TRUE;
}


BOOL CStockMin5Table::LoadFromVec(Vec_StockMin5Data vecData)
{
	CStockMin5Data *pStockMin5Data=NULL;
	LockData();
	vecStockMin5Data.clear();
	for(int i=0;i<vecData.size();i++)
	{
		pStockMin5Data=vecData[i];
		if(!pStockMin5Data)
			continue;
		vecStockMin5Data.push_back(pStockMin5Data);
	}
	UnlockData();
	return TRUE;
}

CStockMin5Data * CStockMin5Table::GetLastStockMin5Data(void)
{
	if(vecStockMin5Data.size()==0)
		return NULL;
	LockData();
	CStockMin5Data *pResult=vecStockMin5Data[vecStockMin5Data.size()-1];
	UnlockData();
	return pResult;
}

CStockMin5Data * CStockMin5Table::GetStockMin5DataByIndex(int index)
{
	if(vecStockMin5Data.size()==0)
		return NULL;
	if(index<0)
		return NULL;
	if(index>=vecStockMin5Data.size())
		return NULL;
	LockData();
	CStockMin5Data *pResult=vecStockMin5Data[index];
	UnlockData();
	return pResult;
}


CString CStockMin5Table::GetLastStockMin5DataDate(void)
{
	if(vecStockMin5Data.size()==0)
		return "";
	LockData();
	CString strResult= vecStockMin5Data[vecStockMin5Data.size()-1]->GetDate();
	UnlockData();
	return strResult;
}

CString CStockMin5Table::GetLastStockMin5DataDateTime(void)
{
	if(vecStockMin5Data.size()==0)
		return "";
	LockData();
	CString strDate= vecStockMin5Data[vecStockMin5Data.size()-1]->GetDate();
	CString strTime= vecStockMin5Data[vecStockMin5Data.size()-1]->GetTime();
	CString strResult;
	strResult=strDate;
	strResult+=" ";
	strResult+=strTime;
	UnlockData();
	return strResult;
}

CString  CStockMin5Table:: GetStockMin5BeginDateTime(void)
{
	if(vecStockMin5Data.size()==0)
		return "";

	CString strDateTime;
	LockData();
	strDateTime=vecStockMin5Data[0]->GetDate();
	strDateTime+=" ";
	strDateTime+=vecStockMin5Data[0]->GetTime();
	UnlockData();
	return strDateTime;

}

CString  CStockMin5Table::GetStockMin5EndDateTime(void)
{
	if(vecStockMin5Data.size()==0)
		return "";

	CString strDateTime;

	int pos=vecStockMin5Data.size()-1;
	LockData();
	strDateTime=vecStockMin5Data[pos]->GetDate();
	strDateTime+=" ";
	strDateTime+=vecStockMin5Data[pos]->GetTime();
	UnlockData();
	return strDateTime;
}


CString  CStockMin5Table::GetNearestStockDayDate(CTime mDateTime)
{
	if(vecStockMin5Data.size()==0)
		return "";
	CStockMin5Data *pStockMin5Data=NULL;
	LockData();

	int mNearestDays=99999;
	int mNearestPos=-1;
	for(int i=0;i<vecStockMin5Data.size();i++)
	{
		pStockMin5Data=vecStockMin5Data[i];
		if(!pStockMin5Data)
			continue;
		CString strCheckTime=vecStockMin5Data[i]->GetDate();
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
		CString strReult=vecStockMin5Data[mNearestPos]->GetDate();
		UnlockData();
		return strReult;
	}

	UnlockData();
	return "";
}


//从http（新浪)获取 最近的5分钟数据
Vec_StockMin5Data CStockMin5Table:: GetNearestStockDataFormHttp(int mNums)
{
	if(!pNetStock)
		pNetStock=new CNetStock();

	CString strHttpData=pNetStock->GetNearestStockMin5HttpData(strStockCode,mNums);

	Vec_StockMin5Data vecStockMin5Data;
	vecStockMin5Data=pNetStock->ParseNearestStockMin5HttpData(strHttpData,strStockCode);
	if(vecStockMin5Data.size()==0)
		PrintfDebug("% Get Form Http Error\n",strStockCode);

	return vecStockMin5Data;

}

float CStockMin5Table:: GetNearestEndPriceFormHttp(int mNums)
{
	if(!pNetStock)
		pNetStock=new CNetStock();
	CString strHttpData=pNetStock->GetNearestStockMin5HttpData(strStockCode,mNums);
	Vec_StockMin5Data vecStockMin5Data;
	vecStockMin5Data=pNetStock->ParseNearestStockMin5HttpData(strHttpData,strStockCode);
	if(vecStockMin5Data.size()>0)
	{
		return vecStockMin5Data[vecStockMin5Data.size()-1]->GetEndPrice();
	}
	else
	{
		PrintfDebug("% Get Form Http Error\n",strStockCode);
		return -1.0;
	}
}

//是否 StockData已经存在于列表中
BOOL  CStockMin5Table::IsStockDataExist(CStockMin5Data *pStockMin5Data)
{
	LockData();
	for(int i=0;i<vecStockMin5Data.size();i++)
	{
		if( pStockMin5Data->GetDate()==vecStockMin5Data[i]->GetDate() && pStockMin5Data->GetTime() ==vecStockMin5Data[i]->GetTime() )
		{
			UnlockData();
			 return TRUE;
		}
	}
	UnlockData();
	return FALSE;

}

//将从http（新浪)获取 最近的5分钟数据加入到Table List里面
BOOL CStockMin5Table:: AddNearestStockData(Vec_StockMin5Data vecNearestStockData)
{
	
	if(vecNearestStockData.size()==0)
		return FALSE;
	LockData();
	for(int i=0;i<vecNearestStockData.size();i++)
	{
		if(!IsStockDataExist(vecNearestStockData[i]))		//不在List内
		{
			vecStockMin5Data.push_back(vecNearestStockData[i]);
		}
	}
	UnlockData();
	return  TRUE;
}


CStockDayData* CStockMin5Table::BuildStockDayData(CString strStockDate)
{
	CStockDayData* pStockDayData=NULL;

	Vec_StockMin5Data vecFilterMin5Data;
	CStockMin5Data *pStockMin5Data=NULL;
	LockData();
	for(int i=0;i<vecStockMin5Data.size();i++)
	{
		pStockMin5Data=vecStockMin5Data[i];
		if(!pStockMin5Data)
			continue;
		if(pStockMin5Data->GetDate()==strStockDate)
		{
			vecFilterMin5Data.push_back(pStockMin5Data);
		}

	}

	if(vecFilterMin5Data.size()>0)
	{
		pStockMin5Data=vecFilterMin5Data[vecFilterMin5Data.size()-1];
		//CString strTime=pStockMin5Data->GetTime();

		/*int mTime=atoi((LPCSTR)strTime);
		if(mTime<1430)
		{
			return NULL;
		}*/
	}
	else
	{
		UnlockData();
		return NULL;
	}

	float f_min_val=99999999.0;
	float f_max_val=-1.0;
	long m_total_volume=0;
	float f_total_price=0;
	float f_begin_price=0;
	float f_end_price=0;
	for(int i=0;i<vecFilterMin5Data.size();i++)
	{
		pStockMin5Data=vecFilterMin5Data[i];
		if(!pStockMin5Data)
			continue;

		if(i==0)
		{
			f_begin_price=pStockMin5Data->GetBeginPrice();
		}

		if(i==(vecFilterMin5Data.size()-1))
		{
			f_end_price=pStockMin5Data->GetEndPrice();
		}

		if(pStockMin5Data->GetMinPrice()<f_min_val)
		{
			f_min_val=pStockMin5Data->GetMinPrice();
		}

		if(pStockMin5Data->GetMaxPrice()>f_max_val)
		{
			f_max_val=pStockMin5Data->GetMaxPrice();
		}
		m_total_volume+=pStockMin5Data->GetTotalVolume();
		f_total_price+=pStockMin5Data->GetTotalPrice();
	}

	pStockDayData=new CStockDayData();


	pStockDayData->SetDate(strStockDate);
	pStockDayData->SetBeginPrice(f_begin_price);
	pStockDayData->SetMaxPrice(f_max_val);
	pStockDayData->SetMinPrice(f_min_val);
	pStockDayData->SetEndPrice(f_end_price);
	pStockDayData->SetTotalVolume(m_total_volume);
	pStockDayData->SetTotalPrice(f_total_price);
	UnlockData();
	return pStockDayData;
}


int  CStockMin5Table::GetStockMin5Index(CString strDateTime)
{
	if(vecStockMin5Data.size()==0)
		return -1;

	CStockMin5Data * pStockMin5Data=NULL;
	LockData();
	for(int i=0;i<vecStockMin5Data.size();i++)
	{
		pStockMin5Data=vecStockMin5Data[i];
		if(!pStockMin5Data)
			continue;
		CString strTempDateTime=pStockMin5Data->GetDate();
		strTempDateTime+=" ";
		strTempDateTime+=pStockMin5Data->GetTime();

		if(strTempDateTime==strDateTime)
		{
			UnlockData();
			return i;
		}
	}
	UnlockData();
	return -1;
}