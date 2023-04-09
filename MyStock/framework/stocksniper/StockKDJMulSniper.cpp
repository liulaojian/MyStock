#include "stdafx.h"
#include "StockKDJMulSniper.h"
#include "StockDataMgr.h"
#include "StockKDJArithmetic.h"
#include "StockMACDArithmetic.h"
#include "CommonMacro.h"
#include "StockLoopBackDataMgr.h"
#include "Log.h"


CStockKDJMulSniper::CStockKDJMulSniper(CString strStockCode):CStockSniper(strStockCode)
{
	strResultInfo="";
}

CStockKDJMulSniper::~CStockKDJMulSniper()
{

}


BOOL CStockKDJMulSniper::SniperAnalyze(BOOL bLoopBackMode)
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

	pStockKDJData=CStockKDJArithmetic::CalcKDJData(strStockCode,strDateTime,125,K_LINE_30IN,9,3,3);
	
	if(pStockKDJData==NULL)
		return FALSE;

	/*CStockMACDData *pStockMACDData=NULL;
	pStockMACDData=CStockMACDArithmetic::CalcMACDData(strStockCode,strDateTime,125,K_LINE_30IN,12,26,9);

	if(pStockMACDData==NULL)
		return FALSE;
		*/
	//SniperAnalyzeKDJ(pStockKDJData->vec_k,pStockKDJData->vec_d,pStockKDJData->vec_j,pStockKDJData->vec_time);

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

				if((m_first_low_pos-m_first_hight_pos)<=11  && (m_second_hight_pos-m_first_low_pos) <=9)
				{
					if(f_first_low_value<0.0  && f_first_hight_value>90.0 && f_second_hight_value>60.0)
					{
						if((f_second_low_value-f_first_low_value)>4.0 && (f_first_hight_value-f_second_hight_value)>8.0)		 //&& f_second_low_value<20.0
						{

							/*int mMacdLength=pStockMACDData->vec_dif.size();
							double f_last_dif=pStockMACDData->vec_dif[mMacdLength-1];
							double f_last_dea=pStockMACDData->vec_dea[mMacdLength-1];
							double f_last_macd=pStockMACDData->vec_macd[mMacdLength-1];

							if((f_last_dif>0 && f_last_dea>0) ||f_last_macd>=0.0)*/
							//if((m_second_hight_pos-m_first_hight_pos)<(mKDJMulSniperWidth-m_second_hight_pos))
							{
								PrintfDebug(" %s f_first_hight_value=%f,f_first_low_value=%f,f_second_hight_value=%f,f_second_low_value=%f\n",strStockCode,f_first_hight_value,f_first_low_value,f_second_hight_value,f_second_low_value);
								CString strStockName;
								strStockName=StockDataMgr()->GetStockName(pStockKDJData->strStockCode);
								strResultInfo.Format("%s  %s 30分钟K线 KDJ 多底来临",pStockKDJData->strStockCode,strStockName);
								SAFE_DELETE(pStockKDJData);
								//SAFE_DELETE(pStockMACDData);
								return TRUE;
							}

							
						}
						
					}

					
				}

				
			}


		}
	}
	strResultInfo="";
	SAFE_DELETE(pStockKDJData);
	//SAFE_DELETE(pStockMACDData);
	return FALSE;
	
}

KDJMulSniperInfo CStockKDJMulSniper::AnalyzeKDJ(std::vector<double> vec_calc_k,std::vector<double> vec_calc_d,std::vector<double> vec_calc_j,int mWidth)
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

std::vector<double>  CStockKDJMulSniper::ExtendVecValue(std::vector<double> vec_val,int mMuls,int mSubMuls)
{
	std::vector<double>  vec_result;

	int length=vec_val.size();

	if(mSubMuls>0)
		length=length-1;

	for(int i=0;i<length-1;i++)
	{
		double f_pre_val,f_val;
		f_pre_val=vec_val[i];
		f_val=vec_val[i+1];
		for(int j=0;j<mMuls;j++)
		{
			double f_result;
			double f_muls;

			if(j==0)
				f_result=f_pre_val;
			else
			{
				f_muls=(double)j/(double)mMuls;
				f_result=(f_val-f_pre_val)*f_muls+f_pre_val;
			}

			vec_result.push_back(f_result);
		}
	}

	if(mSubMuls==0)
	{
		vec_result.push_back(vec_val[length-1]);
	}
	else
	{
		length=vec_val.size();
		double f_pre_val,f_val;
		f_pre_val=vec_val[length-2];
		f_val=vec_val[length-1];

		for(int j=0;j<mSubMuls;j++)
		{
			double f_result;
			double f_muls;

			if(j==0)
				f_result=f_pre_val;
			else
			{
				f_muls=(double)j/(double)mSubMuls;
				f_result=(f_val-f_pre_val)*f_muls+f_pre_val;
			}

			vec_result.push_back(f_result);
		}

		vec_result.push_back(vec_val[length-1]);
	}

	return vec_result;

}

std::vector<long>   CStockKDJMulSniper::ExtendVecLongValue(std::vector<long> vec_val,int mMuls,int mSubMuls)
{
	std::vector<long>  vec_result;
	int length;
	length=vec_val.size();

	if(mSubMuls>0)
		length=length-1;

	for(int i=0;i<length-1;i++)
	{
		long f_pre_val,f_val;
		f_pre_val=vec_val[i];
		f_val=vec_val[i+1];
		for(int j=0;j<mMuls;j++)
		{
			long f_result;
			long f_muls;

			if(j==0)
				f_result=f_pre_val;
			else
			{
				f_muls=(long)j/(long)mMuls;
				f_result=(f_val-f_pre_val)*f_muls+f_pre_val;
			}

			vec_result.push_back(f_result);
		}
	}
	if(mSubMuls==0)
	{
		vec_result.push_back(vec_val[length-1]);
	}
	else
	{
		length=vec_val.size();
		long f_pre_val,f_val;
		f_pre_val=vec_val[length-2];
		f_val=vec_val[length-1];

		for(int j=0;j<mSubMuls;j++)
		{
			long f_result;
			long f_muls;

			if(j==0)
				f_result=f_pre_val;
			else
			{
				f_muls=(long)j/(long)mSubMuls;
				f_result=(f_val-f_pre_val)*f_muls+f_pre_val;
			}

			vec_result.push_back(f_result);
		}

		vec_result.push_back(vec_val[length-1]);
	}


	return vec_result;
}

BOOL CStockKDJMulSniper::SniperAnalyzeKDJ(std::vector<double> vec_k,std::vector<double> vec_d,std::vector<double> vec_j,std::vector<long> vec_time)
{
	std::vector<double> vec_min5_k,vec_min5_d,vec_min5_j;
	std::vector<long> vec_min5_time;


	int length=vec_time.size();

	long m_first_time=vec_time[0];
	long m_last_time=vec_time[length-1];

	int mMin5Nums=(m_last_time-m_first_time)/(60*5);

	int mSubMin5Nums=mMin5Nums%6;

	vec_min5_k=ExtendVecValue(vec_k,6,mSubMin5Nums);
	vec_min5_d=ExtendVecValue(vec_d,6,mSubMin5Nums);
	vec_min5_j=ExtendVecValue(vec_j,6,mSubMin5Nums);
	vec_min5_time=ExtendVecLongValue(vec_time,6,mSubMin5Nums);



	int mMin5Length=vec_min5_k.size();

	std::vector<double> vec_last_k,vec_last_d,vec_last_j;

	if(mSubMin5Nums==0)
	{
		for(int i=mMin5Length-6;i<mMin5Length;i++)
		{
			vec_last_k.push_back(vec_min5_k[i]);
			vec_last_d.push_back(vec_min5_d[i]);
			vec_last_j.push_back(vec_min5_j[i]);
		}

	}
	else
	{
		for(int i=mMin5Length-mSubMin5Nums;i<mMin5Length;i++)
		{
			vec_last_k.push_back(vec_min5_k[i]);
			vec_last_d.push_back(vec_min5_d[i]);
			vec_last_j.push_back(vec_min5_j[i]);
		}
	}

	int mLastLength=vec_last_k.size();

	BOOL  bCapture=FALSE;

	int n=0;
	for(n=0;n<mLastLength;n++)
	{
		double f_last_k,f_last_d,f_last_j;
		f_last_k=vec_last_k[n];
		f_last_d=vec_last_d[n];
		f_last_j=vec_last_j[n];

		double f_k_per=abs(f_last_k-f_last_d)*100.0/f_last_d;
		double f_j_per=abs(f_last_j-f_last_d)*100.0/f_last_d;

		if(f_j_per<4.0 && f_k_per<4.0)
		{


			if(f_last_d>f_last_k && f_last_d> f_last_j)
			{
				bCapture=TRUE;
				break;
			}
		}
	}

	if(bCapture)
	{

	}



	return TRUE;
}


CString CStockKDJMulSniper::GetSniperAnalyzeResult(void)
{

	return strResultInfo;
}