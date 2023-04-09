#include "stdafx.h"
#include "StockKDJSniper.h"
#include "StockDataMgr.h"
#include "StockKDJArithmetic.h"
#include "CommonMacro.h"
#include "StockLoopBackDataMgr.h"
#include "Log.h"
CStockKDJSniper::CStockKDJSniper(CString strStockCode):CStockSniper(strStockCode)
{
	bKDJDetected=FALSE;
	bKDJValueZero=FALSE;
	strResultInfo="";
	
}


CStockKDJSniper::~CStockKDJSniper()
{

}



BOOL CStockKDJSniper::SniperAnalyze(BOOL bLoopBackMode)
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
		//if( ( (f_last_j>0) && (f_l_last_j<0)  )||  ( (f_last_j>5) && (f_l_last_j<5) ) ||  ( (f_last_j>10) && (f_l_last_j<10) ))
		{
			
			std::vector<double> vec_ma5,vec_ma10,vec_ma20,vec_ma60;
			vec_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
			vec_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
			vec_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
			vec_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);

			//找到前一个 KDJ 交叉点，这个点应该是 下交叉点
			int m_down_kdj_cross_pos=-1;
			for(int i=mLength-2;i>(mLength-15);i-- )
			{
				double f_next_k,f_next_d,f_next_j;
				f_next_k=pStockKDJData->vec_k[i+1];
				f_next_d=pStockKDJData->vec_d[i+1];
				f_next_j=pStockKDJData->vec_j[i+1];

				double f_pre_k,f_pre_d,f_pre_j;

				f_pre_k=pStockKDJData->vec_k[i];
				f_pre_d=pStockKDJData->vec_d[i];
				f_pre_j=pStockKDJData->vec_j[i];

				if((f_pre_j>f_next_j) &&  (f_pre_k>f_next_k))
				{
					if(f_pre_j > f_pre_k && f_pre_k>f_pre_d)
					{
						if(f_next_d > f_next_k && f_next_k > f_next_j)
						{
							m_down_kdj_cross_pos=i;
							break;
						}
					}
				}

			}

			if(m_down_kdj_cross_pos<0)
				return FALSE;
			

			// 找更之前的上升KDJ交叉点
			int m_up_kdj_cross_pos=-1;
			for(int i=m_down_kdj_cross_pos-2;i>(m_down_kdj_cross_pos-15);i-- )
			{
				double f_next_k,f_next_d,f_next_j;
				f_next_k=pStockKDJData->vec_k[i+1];
				f_next_d=pStockKDJData->vec_d[i+1];
				f_next_j=pStockKDJData->vec_j[i+1];

				double f_pre_k,f_pre_d,f_pre_j;

				f_pre_k=pStockKDJData->vec_k[i];
				f_pre_d=pStockKDJData->vec_d[i];
				f_pre_j=pStockKDJData->vec_j[i];

				if((f_pre_j<f_next_j) && (f_pre_k<f_next_k))
				{

					if(f_pre_j < f_pre_k && f_pre_k<f_pre_d)
					{

						if(f_next_j > f_next_k && f_next_k > f_next_d)
						{
							m_up_kdj_cross_pos=i;
							break;
						}


					}


				}


			}

			if(m_up_kdj_cross_pos<0)
				return FALSE;

			//在m_down_kdj_cross_pos --mLength 间 找 最低值点
			int m_min_low_pos=-1;
			double  f_min_low_value=999999.0;
			for(int i=m_down_kdj_cross_pos;i<mLength;i++)
			{
				if(pStockKDJData->vec_j[i]<f_min_low_value)
				{
					f_min_low_value=pStockKDJData->vec_j[i];
					m_min_low_pos=i;
				}
			}

			if(m_min_low_pos<0)
				return FALSE;


			//在 m_up_kdj_cross_pos  -- m_down_kdj_cross_pos 间 找 最高点

			int m_max_high_pos=-1;
			double f_max_high_value=-999999.0;

			for(int i=m_up_kdj_cross_pos;i<m_down_kdj_cross_pos;i++)
			{
				if(pStockKDJData->vec_j[i]>f_max_high_value)
				{
					f_max_high_value=pStockKDJData->vec_j[i];
					m_max_high_pos=i;
				}
			}

			if(m_max_high_pos<0)
				return FALSE;

			//最高点 最低点 差 符合条件
			if((f_max_high_value-f_min_low_value)>95.0)
			{
				double f_max_ma5_val=vec_ma5[m_max_high_pos];
				double f_now_ma5_val=vec_ma5[mLength-1];
				double f_ma5_diff=f_now_ma5_val-f_max_ma5_val;


				double f_max_ma10_val=vec_ma10[m_max_high_pos];
				double f_now_ma10_val=vec_ma10[mLength-1];
				double f_ma10_diff=f_now_ma10_val-f_max_ma10_val;

				double f_max_ma20_val=vec_ma20[m_max_high_pos];
				double f_now_ma20_val=vec_ma20[mLength-1];
				double f_ma20_diff=f_now_ma20_val-f_max_ma20_val;

				double f_max_ma60_val=vec_ma60[m_max_high_pos];
				double f_now_ma60_val=vec_ma60[mLength-1];
				double f_ma60_diff=f_now_ma60_val-f_max_ma60_val;

				double f_now_val=pStockKDJData->vec_close_price[mLength-1];

				double  f_ma60_per=(f_now_val-f_now_ma60_val)*100.0/f_now_ma60_val;
				double  f_ma20_per=(f_now_val-f_now_ma20_val)*100.0/f_now_ma20_val;


				double f_high_val=pStockKDJData->vec_close_price[m_max_high_pos];
				
			
				if( f_ma20_per>0.0 && f_ma60_per>=7.0  )  	//|| f_ma60_diff>0  f_ma5_diff>0&&f_ma10_diff>0 && 
				{
					CString strStockName;
					strStockName=StockDataMgr()->GetStockName(pStockKDJData->strStockCode);
					strResultInfo.Format("%s  %s 30分钟K线  KDJ 过零线，并站上20,60日均线",pStockKDJData->strStockCode,strStockName);
					SAFE_DELETE(pStockKDJData);
					return TRUE;
				}
				
			}

		}
	}


	strResultInfo="";
	SAFE_DELETE(pStockKDJData);
	return FALSE;
}

std::vector<double>  CStockKDJSniper::ExtendVecValue(std::vector<double> vec_val,int mMuls,int mSubMuls)
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

std::vector<long>   CStockKDJSniper::ExtendVecLongValue(std::vector<long> vec_val,int mMuls,int mSubMuls)
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

BOOL CStockKDJSniper::SniperAnalyzeKDJ(std::vector<double> vec_k,std::vector<double> vec_d,std::vector<double> vec_j,std::vector<long> vec_time)
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


BOOL CStockKDJSniper::SniperAnalyzeK60(BOOL bLoopBackMode)
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



	if(f_j_per<4.0 && f_k_per<4.0)
	{
		if(f_last_d>f_last_k && f_last_d> f_last_j)
		{

			PrintfDebug("%s 60min k=%f,d=%f,j=%f,f_k_per=%f f_j_per=%f\n",pStockKDJData->strStockCode,f_last_k,f_last_d,f_last_j,f_k_per,f_j_per);

			bKDJValueZero=FALSE;

			int mJZeroPos=-1;
			double f_zero_j_val=-1.0;
			for(int i=0;i<15;i++)
			{
				double f_j=pStockKDJData->vec_j[mLength-15+i];
				if(f_j<=3.0)
				{
					mJZeroPos=mLength-15+i;
					f_zero_j_val=f_j;
				}

			}

			int mJMaxPos=-1;
			double f_max_j_val=-1.0;
			if(mJZeroPos>0)
				PrintfDebug("%s 60min mJZeroPos=%d\n",pStockKDJData->strStockCode,mLength-mJZeroPos-1);
			//J值在0点的位置 在 jdk 交汇处 前 6个 周期内

			if(mJZeroPos>=0  &&(mLength-mJZeroPos-1)<=6)
			{	
				CString strStockName;
				strStockName=StockDataMgr()->GetStockName(pStockKDJData->strStockCode);
				strK60ResultInfo.Format("%s  %s 60分钟K线 KDJ 接近上穿金叉,6个周期内J值接近0",pStockKDJData->strStockCode,strStockName);
				SAFE_DELETE(pStockKDJData);
				return TRUE;

			}
		}	
	}

	
	strK60ResultInfo="";
	SAFE_DELETE(pStockKDJData);

	return FALSE;
}

CString CStockKDJSniper::GetSniperAnalyzeResult(void)
{

	return strResultInfo;
}