#include "stdafx.h"
#include <stdio.h>
#include "StockDataMgr.h"
#include "GeneralAnalyze.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include <math.h> 
#include "CommonMacro.h"
#include "Convert.h"



CGeneralAnalyze::CGeneralAnalyze()
{

}


CGeneralAnalyze::~CGeneralAnalyze()
{

}

#define  MAX_SIZE  90

CString  CGeneralAnalyze::doAnalyze(CTime mDropOffTime,CString strStockCode)
{
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	CStockKDJData *pStockKDJData=NULL;
	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);
	strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);
	pStockKDJData=CStockKDJArithmetic::CalcKDJData(strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
	if(pStockKDJData==NULL)
		return "";

	if(strStockCode=="SZ002338")
	{
		int a=0;
		a++;

	}
	

	int mSize=pStockKDJData->vec_close_price.size();

	std::vector<double> vec_volume_ma5,vec_volume_ma10;
	vec_volume_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_volume_price);
	vec_volume_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_volume_price);

	double f_total_volume=0.0;
	int m_total_nums=0;
	for(int i=3;i<mSize;i++)
	{
		if(pStockKDJData->vec_volume_price[i]>1000.0)
		{
			f_total_volume+=pStockKDJData->vec_volume_price[i];
			m_total_nums++;
		}
	}

	double f_ave_volume=f_total_volume/m_total_nums;

	Vec_GeneraAnalyzeData  vecGeneraAnalyzeData;
	CString strInfo="";
	CString strTotalInfo="";
	GeneraAnalyzeData *pGeneraAnalyzeData=NULL;
	for(int i=mSize-MAX_SIZE;i<mSize;i++)
	{
		double f_m5_m10_per=vec_volume_ma5[i]/vec_volume_ma10[i];
		double f_now_m5_per=pStockKDJData->vec_volume_price[i]/vec_volume_ma5[i];
		double f_now_m10_per=pStockKDJData->vec_volume_price[i]/vec_volume_ma10[i];
		double f_now_ave_per=pStockKDJData->vec_volume_price[i]/f_ave_volume;

		long m_5_m10_time=pStockKDJData->vec_time[i];
		CTime time(m_5_m10_time);
		CString strDateTime=ConverCTimeToString(time);

		printf("%s  %s  n_ave:%.2f  m5_m10:%.2f  n_m5:%.2f  n_m10:%.2f\n",strStockCode,strDateTime,f_now_ave_per,f_m5_m10_per,f_now_m5_per,f_now_m10_per);
		strInfo.Format("%s  %s  n_ave:%.2f  m5_m10:%.2f  n_m5:%.2f  n_m10:%.2f\n",strStockCode,strDateTime,f_now_ave_per,f_m5_m10_per,f_now_m5_per,f_now_m10_per);
		strTotalInfo+=strInfo;
		pGeneraAnalyzeData=new GeneraAnalyzeData();
		pGeneraAnalyzeData->strStockCode=strStockCode;
		pGeneraAnalyzeData->strDateTime=strDateTime;
		pGeneraAnalyzeData->f_m5_m10_per=f_m5_m10_per;
		pGeneraAnalyzeData->f_now_ave_per=f_now_ave_per;
		pGeneraAnalyzeData->f_now_m10_per=f_now_m10_per;
		pGeneraAnalyzeData->f_now_m5_per=f_now_m5_per;
		vecGeneraAnalyzeData.push_back(pGeneraAnalyzeData);
	}
	
	
	if( OpenClipboard(NULL) )
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, strTotalInfo.GetLength()+1);
		buffer = (char*)GlobalLock(clipbuffer);
		strcpy(buffer, LPCSTR(strTotalInfo));
		GlobalUnlock(clipbuffer);
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();
	}

	int mDataSize=MAX_SIZE;

	BOOL bNowAvePerLow=FALSE;
	int mNowAvePerLowNums=0;
	int mNowAvePerHighNums=0;
	int mBeginDivid=-1;
	int mEndDivid=-1;
	
	vecGeneraDataDivid.clear();

	for(int i=mDataSize-1;i>0;i--)
	{
		pGeneraAnalyzeData=vecGeneraAnalyzeData[i];

		double f_now_ave_per=pGeneraAnalyzeData->f_now_ave_per;

		if(f_now_ave_per<1.0)
		{
			if(!bNowAvePerLow)
			{
				bNowAvePerLow=TRUE;
				mBeginDivid=i;
			}
		
			mNowAvePerLowNums++;
			mNowAvePerHighNums=0;
		}
		else
		{
			mNowAvePerHighNums++;
			if(mNowAvePerHighNums>=2)
			{
				bNowAvePerLow=FALSE;
				if(mNowAvePerLowNums>=8)
				{
					mEndDivid=i;
					GeneraDataDivid* pGeneraDataDivid=new GeneraDataDivid();
					pGeneraDataDivid->mDividBegin=mBeginDivid;
					pGeneraDataDivid->mDividEnd=mEndDivid;
					vecGeneraDataDivid.push_back(pGeneraDataDivid);
				}
				mBeginDivid=-1;
				mEndDivid=-1;
				mNowAvePerLowNums=0;
			}
		}

		if(i==1)
		{
			if(mNowAvePerLowNums>=8)
			{
				mEndDivid=i;
				GeneraDataDivid* pGeneraDataDivid=new GeneraDataDivid();
				pGeneraDataDivid->mDividBegin=mBeginDivid;
				pGeneraDataDivid->mDividEnd=mEndDivid;
				vecGeneraDataDivid.push_back(pGeneraDataDivid);
			}

		}

	}
	
	GeneraDataDivid* pGeneraDataDivid=NULL;
	CString strResult="";
	
	for(int i=0;i<vecGeneraDataDivid.size();i++)
	{
		pGeneraDataDivid=vecGeneraDataDivid[i];
		CString strBeginDate=vecGeneraAnalyzeData[pGeneraDataDivid->mDividBegin]->strDateTime;
		CString strEndDate=vecGeneraAnalyzeData[pGeneraDataDivid->mDividEnd]->strDateTime;
		int mNums=pGeneraDataDivid->mDividBegin-pGeneraDataDivid->mDividEnd+1;//pGeneraDataDivid->mDividEnd-pGeneraDataDivid->mDividBegin+1;
		int mNowNums=mDataSize-pGeneraDataDivid->mDividBegin;
		strInfo.Format("%s 开始 %s   结束 %s  持续 %d  距今 %d\n ",strStockCode,strEndDate,strBeginDate,mNums,mNowNums);
		strResult+=strInfo;
	}


	return strResult;
}


Vec_GeneraDataDivid CGeneralAnalyze::doAnalyzeVec(CTime mDropOffTime,CString strStockCode)
{
	doAnalyze(mDropOffTime,strStockCode);

	return vecGeneraDataDivid;

}