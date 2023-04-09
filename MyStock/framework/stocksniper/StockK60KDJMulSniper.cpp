#include "stdafx.h"
#include "StockK60KDJMulSniper.h"
#include "StockDataMgr.h"
#include "StockKDJArithmetic.h"
#include "StockMACDArithmetic.h"
#include "CommonMacro.h"
#include "StockLoopBackDataMgr.h"
#include "Log.h"


CStockK60KDJMulSniper::CStockK60KDJMulSniper(CString strStockCode):CStockSniper(strStockCode)
{
	strResultInfo="";
}

CStockK60KDJMulSniper::~CStockK60KDJMulSniper()
{

}

BOOL CStockK60KDJMulSniper::SniperAnalyze(BOOL bLoopBackMode)
{
	CStockMin5Table *pStockMin5Table=NULL;
	
	
	if(bLoopBackMode)
		pStockMin5Table=StockLoopBackDataMgr()->GetStockMin5Table(strStockCode);
	else
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);

	if(!pStockMin5Table)
		return FALSE;

	CString strDateTime=pStockMin5Table->GetLastStockMin5DataDateTime();

	CStockKDJData *pStockKDJData=NULL;

	pStockKDJData=CStockKDJArithmetic::CalcKDJData(strStockCode,strDateTime,125,K_LINE_60MIN,9,3,3);
	
	if(pStockKDJData==NULL)
		return FALSE;

	int mLength=pStockKDJData->m_length;

	double f_last_k,f_last_d,f_last_j;
	f_last_k=pStockKDJData->vec_k[mLength-1];
	f_last_d=pStockKDJData->vec_d[mLength-1];
	f_last_j=pStockKDJData->vec_j[mLength-1];

	double f_k_per=abs(f_last_k-f_last_d)*100.0/f_last_d;
	double f_j_per=abs(f_last_j-f_last_d)*100.0/f_last_d;

	double f_l_last_k,f_l_last_d,f_l_last_j;
	f_l_last_k=pStockKDJData->vec_k[mLength-2];
	f_l_last_d=pStockKDJData->vec_d[mLength-2];
	f_l_last_j=pStockKDJData->vec_j[mLength-2];

	if((f_l_last_j<f_l_last_k) && (f_l_last_k<f_l_last_d))
	{
		if((f_last_d<f_last_k) && (f_last_k<f_last_j))
		{
			KDJMulSniperInfo mKDJMulSniperInfo;

			int mKDJMulSniperWidth=40;

			mKDJMulSniperInfo=AnalyzeKDJ(pStockKDJData->vec_k,pStockKDJData->vec_d,pStockKDJData->vec_j,mKDJMulSniperWidth);

			double f_first_hight_value=mKDJMulSniperInfo.f_first_hight_value;
			int    m_first_hight_pos=mKDJMulSniperInfo.m_first_hight_pos;
			double f_second_hight_value=mKDJMulSniperInfo.f_second_hight_value;
			int    m_second_hight_pos=mKDJMulSniperInfo.m_second_hight_pos;

			double f_first_low_value=mKDJMulSniperInfo.f_first_low_value;
			int    m_first_low_pos=mKDJMulSniperInfo.m_first_low_pos;
			double f_second_low_value=mKDJMulSniperInfo.f_second_low_value;
			int    m_second_low_pos=mKDJMulSniperInfo.m_second_low_pos;

			if(m_first_hight_pos<0 || m_second_hight_pos<0 || m_first_low_pos<0 || m_second_low_pos<0)
				return FALSE;

			if(m_second_low_pos>m_second_hight_pos && m_second_hight_pos>m_first_low_pos && m_first_low_pos>m_first_hight_pos)
			{

				if((m_first_low_pos-m_first_hight_pos)<=13  && (m_second_hight_pos-m_first_low_pos) <=10  )
				{
					if(f_first_low_value<0.0  && f_first_hight_value>90.0 && f_second_hight_value>60.0)
					{
						if((f_second_low_value-f_first_low_value)>2.0 && (f_first_hight_value-f_second_hight_value)>5.0)		 //&& f_second_low_value<20.0
						{
							PrintfDebug(" %s f_first_hight_value=%f,f_first_low_value=%f,f_second_hight_value=%f,f_second_low_value=%f\n",strStockCode,f_first_hight_value,f_first_low_value,f_second_hight_value,f_second_low_value);
							CString strStockName;
							strStockName=StockDataMgr()->GetStockName(pStockKDJData->strStockCode);
							strResultInfo.Format("%s  %s 60分钟K线 KDJ 多底来临",pStockKDJData->strStockCode,strStockName);
							SAFE_DELETE(pStockKDJData);
							return TRUE;
							
						}
						
					}

					
				}

				
			}


		}
	}
	strResultInfo="";
	SAFE_DELETE(pStockKDJData);
	return FALSE;
	
}

KDJMulSniperInfo CStockK60KDJMulSniper::AnalyzeKDJ(std::vector<double> vec_calc_k,std::vector<double> vec_calc_d,std::vector<double> vec_calc_j,int mWidth)
{
	KDJMulSniperInfo mKDJMulSniperInfo;
	mKDJMulSniperInfo.f_first_hight_value=0.0;
	mKDJMulSniperInfo.f_first_low_value=0.0;
	mKDJMulSniperInfo.f_second_hight_value=0.0;
	mKDJMulSniperInfo.f_second_low_value=0.0;

	mKDJMulSniperInfo.m_first_hight_pos=-1;
	mKDJMulSniperInfo.m_first_low_pos=-1;
	mKDJMulSniperInfo.m_second_hight_pos=-1;
	mKDJMulSniperInfo.m_second_low_pos=-1;


	if(vec_calc_k.size()<mWidth)
		return mKDJMulSniperInfo;
	int m_calc_length=vec_calc_k.size();
	std::vector<double> vec_k,vec_d,vec_j;

	for(int i=0;i<mWidth;i++)
	{
		vec_k.push_back(vec_calc_k[m_calc_length-mWidth+i]);
		vec_d.push_back(vec_calc_d[m_calc_length-mWidth+i]);
		vec_j.push_back(vec_calc_j[m_calc_length-mWidth+i]);
	}

	//查找最低点

	int mLength=vec_k.size();
	double  f_first_low_val=9999999.0;
	int  m_first_low_pos=-1;

	for(int i=0;i<mLength;i++)
	{
		if(vec_j[i]<f_first_low_val)
		{
			f_first_low_val=vec_j[i];
			m_first_low_pos=i;
		}
	}

	if(m_first_low_pos<0)
		return mKDJMulSniperInfo;

	mKDJMulSniperInfo.f_first_low_value=f_first_low_val;
	mKDJMulSniperInfo.m_first_low_pos=m_first_low_pos;

	double  f_first_high_val=-9999999.0;
	int  m_first_high_pos=-1;

	//从0 到 最低点 间 查找第一高点
	for(int i=0;i<m_first_low_pos;i++)
	{
		if(vec_j[i]>f_first_high_val)
		{
			f_first_high_val=vec_j[i];
			m_first_high_pos=i;
		}
	}

	if(m_first_high_pos<0)
		return mKDJMulSniperInfo;
	mKDJMulSniperInfo.f_first_hight_value=f_first_high_val;
	mKDJMulSniperInfo.m_first_hight_pos=m_first_high_pos;


	//从最低点 开始找 第二高点

	double  f_second_high_val=-9999999.0;
	int  m_second_high_pos=-1;

	for(int i=m_first_low_pos+1;i<mLength;i++)
	{
		if(vec_j[i]>f_second_high_val)
		{
			f_second_high_val=vec_j[i];
			m_second_high_pos=i;
		}
	}

	if(m_second_high_pos<0)
		return mKDJMulSniperInfo;
	mKDJMulSniperInfo.f_second_hight_value=f_second_high_val;
	mKDJMulSniperInfo.m_second_hight_pos=m_second_high_pos;

	//从第二高点 开始找  第二低点
	double  f_second_low_val=9999999.0;
	int  m_second_low_pos=-1;
	for(int i=m_second_high_pos+1;i<mLength;i++)
	{
		if(vec_j[i]<f_second_low_val)
		{
			f_second_low_val=vec_j[i];
			m_second_low_pos=i;
		}
	}
	if(m_second_low_pos<0)
		return mKDJMulSniperInfo;
	mKDJMulSniperInfo.f_second_low_value=f_second_low_val;
	mKDJMulSniperInfo.m_second_low_pos=m_second_low_pos;

	return mKDJMulSniperInfo;
}



CString CStockK60KDJMulSniper::GetSniperAnalyzeResult(void)
{

	return strResultInfo;
}