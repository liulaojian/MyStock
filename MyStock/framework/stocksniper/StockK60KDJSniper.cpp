#include "stdafx.h"
#include "StockK60KDJSniper.h"
#include "StockDataMgr.h"
#include "StockKDJArithmetic.h"
#include "StockCCIArithmetic.h"
#include "StockMACDArithmetic.h"
#include "CommonMacro.h"
#include "StockLoopBackDataMgr.h"
#include "Log.h"

CStockK60KDJSniper::CStockK60KDJSniper(CString strStockCode):CStockSniper(strStockCode)
{
	
	strResultInfo="";
}


CStockK60KDJSniper::~CStockK60KDJSniper()
{

}

BOOL CStockK60KDJSniper::SniperAnalyze(BOOL bLoopBackMode)
{
	CStockMin5Table *pStockMin5Table=NULL;
	
	//if(StockDataMgr()->IsExpStock(strStockCode))
	//	return FALSE;

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
	
	CStockCCIData* pStockCCIData=NULL;
	pStockCCIData=CStockCCIArithmetic::CalcCCIData(strStockCode,strDateTime,125,K_LINE_60MIN,14);

	if(pStockCCIData==NULL)
	{
		SAFE_DELETE(pStockKDJData);
		return FALSE;
	}

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

	BOOL bOK1=FALSE;

	int mStockBoard=StockDataMgr()->GetStockBoard(strStockCode);

	if(  (f_last_j>10.0) && (f_l_last_j<10.0)  )		
			bOK1=TRUE;
	
	//if((f_l_last_j<f_l_last_k) && (f_l_last_k<f_l_last_d))
	{
		//if((f_last_d<f_last_k) && (f_last_k<f_last_j))
		if(bOK1)		// ((f_last_j>0) && (f_l_last_j<0)  )||  ( (f_last_j>5) && (f_l_last_j<5) )||((f_last_j>10.0) && (f_l_last_j<10.0))
		{
			
			
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
			{
				SAFE_DELETE(pStockCCIData);
				SAFE_DELETE(pStockKDJData);
				
				
				return FALSE;
			}
			

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
			{
				SAFE_DELETE(pStockCCIData);
				SAFE_DELETE(pStockKDJData);
				//SAFE_DELETE(pStockDayCCIData);
				return FALSE;
			}

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
			{
				SAFE_DELETE(pStockCCIData);
				SAFE_DELETE(pStockKDJData);
				
				return FALSE;
			}

			



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
			{
				SAFE_DELETE(pStockCCIData);
				SAFE_DELETE(pStockKDJData);
				
				return FALSE;
			}
			
			int m_cci_min_low_pos=-1;
			double f_cci_min_low_value=999999.0;
			int mCCILength=pStockCCIData->m_length;
			for(int i=m_max_high_pos;i<mCCILength;i++)
			{
				if(pStockCCIData->vec_cci_value[i]<f_cci_min_low_value)
				{
					f_cci_min_low_value=pStockCCIData->vec_cci_value[i];
					m_cci_min_low_pos=i;
				}
			}

			if(m_cci_min_low_pos<0)
			{
				SAFE_DELETE(pStockCCIData);
				SAFE_DELETE(pStockKDJData);
				
				return FALSE;
			}


			/*if(!CalcExpMa20Ma60(bLoopBackMode))
			{
				SAFE_DELETE(pStockCCIData);
				SAFE_DELETE(pStockKDJData);
			
				return FALSE;
			}*/
			
			BOOL  bOK2=FALSE;
			
			

			//最高点 最低点 差 符合条件
			double f_max_high_mim_low_dif=f_max_high_value-f_min_low_value;

			if(f_cci_min_low_value<-120.0 )			//&& f_day_last_cci<-150.0
			{
				if(f_max_high_mim_low_dif>=100.0 && f_min_low_value<0.0)
					bOK2=TRUE;
			}
			
			
			if(bOK2)
			{
				
					
					CString strStockName;
					strStockName=StockDataMgr()->GetStockName(pStockKDJData->strStockCode);
						
					if(bLoopBackMode)
					{
						double f_range=0.0;
						int mPeriodNums=8;
						CalcNext4PeridRange(strDateTime,K_LINE_60MIN,mPeriodNums,f_range);
						strResultInfo.Format("%s  %s 60分钟K线  KDJ 过10线，CCI < -120,回测%d周期涨幅 %.2f",pStockKDJData->strStockCode,strStockName,mPeriodNums,f_range);
					}
					else
						strResultInfo.Format("%s  %s 60分钟K线  KDJ 过10线，CCI < -120",pStockKDJData->strStockCode,strStockName);
					SAFE_DELETE(pStockKDJData);
					SAFE_DELETE(pStockCCIData);

					return TRUE;
				
				
			}

		}
	}


	strResultInfo="";
	SAFE_DELETE(pStockKDJData);
	SAFE_DELETE(pStockCCIData);
	return FALSE;
}

/*
BOOL  CStockK60KDJSniper::CalcExpMa20Ma60(BOOL bLoopBackMode)
{
	CString strExpStockCode;

	CStockMin5Table *pStockMin5Table=NULL;

	strExpStockCode=StockDataMgr()->GetExpCodeByBoardType(StockDataMgr()->GetStockBoard(strStockCode));	//"SH000001";

	if(bLoopBackMode)
		pStockMin5Table=StockLoopBackDataMgr()->GetStockMin5Table(strExpStockCode);
	else
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(strExpStockCode);

	if(!pStockMin5Table)
		return FALSE;

	CString strDateTime=pStockMin5Table->GetLastStockMin5DataDateTime();


	CStockKDJData *pStockKDJData=NULL;


	pStockKDJData=CStockKDJArithmetic::CalcKDJData(strExpStockCode,strDateTime,125,K_LINE_60MIN,9,3,3);


	if(pStockKDJData==NULL)
		return FALSE;
	

	std::vector<double> vec_ma20,vec_ma60;
	vec_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
	vec_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);



	int mM20Length=vec_ma20.size();
	int mM60Length=vec_ma60.size();
	int mLength=pStockKDJData->m_length;

	
	double f_now_ma20_val=vec_ma20[mM20Length-2];
	double f_now_ma60_val=vec_ma60[mM60Length-2];

	double f_now_val=pStockKDJData->vec_close_price[mLength-2];


	f_exp_ma60_per=(f_now_val-f_now_ma60_val)*100.0/f_now_ma60_val;
	f_exp_ma20_per=(f_now_val-f_now_ma20_val)*100.0/f_now_ma20_val;
	


	SAFE_DELETE(pStockKDJData);
	return TRUE;
}
*/



CString CStockK60KDJSniper::GetSniperAnalyzeResult(void)
{

	

	return strResultInfo;
}
