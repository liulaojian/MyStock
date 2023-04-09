#include "stdafx.h"
#include "StockNewK60KDJMulSniper.h"
#include "StockDataMgr.h"
#include "StockKDJArithmetic.h"
#include "StockMACDArithmetic.h"
#include "CommonMacro.h"
#include "StockLoopBackDataMgr.h"
#include "Log.h"
#include "T_FreeVector.h"

CStockNewK60KDJMulSniper::CStockNewK60KDJMulSniper(CString strStockCode):CStockSniper(strStockCode)
{
	strResultInfo="";
}

CStockNewK60KDJMulSniper::~CStockNewK60KDJMulSniper()
{

}

BOOL CStockNewK60KDJMulSniper::SniperAnalyze(BOOL bLoopBackMode)
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
	//	if( ((f_last_j>0) && (f_l_last_j<0)  )||  ( (f_last_j>5) && (f_l_last_j<5) ) ||  ((f_last_j>10.0) && (f_l_last_j<10.0)) )		
		{
			Vec_KDJCrossInfo vecKDJCrossInfo=AnalyzeKDJCross(pStockKDJData->vec_k,pStockKDJData->vec_d,pStockKDJData->vec_j);
			
			KDJCrossInfo *pKDJCrossInfo=NULL;
			std::vector<int> vec_high_pos;

			for(int i=0;i<vecKDJCrossInfo.size();i++)
			{
				pKDJCrossInfo=vecKDJCrossInfo[i];
				if(!pKDJCrossInfo)
					continue;
				if(pKDJCrossInfo->m_role_type==KDJ_ROLE_TYPE_HIGH)
				{
					if(pKDJCrossInfo->f_role_value>=80.0)
					{
						vec_high_pos.push_back(pKDJCrossInfo->m_role_pos);
					}
				}
			}


			std::vector<int> vec_low_pos;
			
			for(int i=0;i<vecKDJCrossInfo.size();i++)
			{
				pKDJCrossInfo=vecKDJCrossInfo[i];
				if(!pKDJCrossInfo)
					continue;
				if(pKDJCrossInfo->m_role_type==KDJ_ROLE_TYPE_LOW)
				{
					if(pKDJCrossInfo->f_role_value<20.0)
					{
						vec_low_pos.push_back(pKDJCrossInfo->m_role_pos);
					}
				}
			}

			std::vector<double> vec_cross_now_val;
			std::vector<double> vec_cross_pre_val;


			for(int i=0;i<vecKDJCrossInfo.size();i++)
			{
				pKDJCrossInfo=vecKDJCrossInfo[i];
				if(!pKDJCrossInfo)
					continue;
				if(pKDJCrossInfo->m_role_type==KDJ_ROLE_TYPE_LOW)
				{
					double f_now_val=pStockKDJData->vec_close_price[pKDJCrossInfo->m_up_cross_pos];
					double f_pre_val=pStockKDJData->vec_close_price[pKDJCrossInfo->m_up_cross_pos-1];
					
					vec_cross_now_val.push_back(f_now_val);	
					vec_cross_pre_val.push_back(f_pre_val);	
				}
			}

			if(vec_low_pos.size()>=3 && vec_high_pos.size()>=3 && vec_cross_now_val.size()>=3)
			{
				int mDif=pStockKDJData->vec_j.size()-vec_low_pos[0]-1;
				if(mDif<=7)
				{

					std::vector<double> vec_ma5,vec_ma10,vec_ma20,vec_ma60;
					vec_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
					vec_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
					vec_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
					vec_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);

					double f_max_ma20_val=vec_ma20[vec_high_pos[0]];
					double f_now_ma20_val=vec_ma20[mLength-1];
					double f_ma20_diff=f_now_ma20_val-f_max_ma20_val;

					double f_max_ma60_val=vec_ma60[vec_high_pos[0]];
					double f_now_ma60_val=vec_ma60[mLength-1];
					double f_ma60_diff=f_now_ma60_val-f_max_ma60_val;
			
					double f_now_val=pStockKDJData->vec_close_price[mLength-1];

					double  f_ma60_per=(f_now_val-f_now_ma60_val)*100.0/f_now_ma60_val;
					double  f_ma20_per=(f_now_val-f_now_ma20_val)*100.0/f_now_ma20_val;

					double f_first_low_value=pStockKDJData->vec_j[vec_low_pos[2]];
					double f_second_low_value=pStockKDJData->vec_j[vec_low_pos[1]];
					double f_three_low_value=pStockKDJData->vec_j[vec_low_pos[0]];

					
					double f_first_high_value=pStockKDJData->vec_j[vec_high_pos[2]];
					double f_second_high_value=pStockKDJData->vec_j[vec_high_pos[1]];
					double f_three_high_value=pStockKDJData->vec_j[vec_high_pos[0]];

					double f_first_up_cross_now_value=vec_cross_now_val[2];
					double f_second_up_cross_now_value=vec_cross_now_val[1];
					double f_three_up_cross_now_value=vec_cross_now_val[0];
					
					double f_first_up_cross_pre_value=vec_cross_pre_val[2];
					double f_second_up_cross_pre_value=vec_cross_pre_val[1];
					double f_three_up_cross_pre_value=vec_cross_pre_val[0];


					double f_first_dif=f_first_high_value-f_first_low_value;
					double f_second_dif=f_second_high_value-f_second_low_value;
					double f_three_dif=f_three_high_value-f_three_low_value;

					if(f_first_low_value<f_second_low_value && f_first_low_value<f_three_low_value)	
					{
						if(f_first_low_value<0.0 && (f_first_dif>90.0))
						{
							//if(f_three_up_cross_pre_value <25.0  && f_three_up_cross_now_value>25.0)
							{
								CString strStockName;
								strStockName=StockDataMgr()->GetStockName(pStockKDJData->strStockCode);
								strResultInfo.Format("%s  %s 60分钟K线  多底KDJ 上交叉  ",pStockKDJData->strStockCode,strStockName);
								SAFE_DELETE(pStockKDJData);
								CFreeVector<Vec_KDJCrossInfo>::freeVector(vecKDJCrossInfo);
								return TRUE;
							}

						}

						//&& f_first_low_value<0.0 && f_up_cross_dif<0.0 && f_second_up_cross_value<30.0
						
					}


				}

			}

			CFreeVector<Vec_KDJCrossInfo>::freeVector(vecKDJCrossInfo);
			strResultInfo="";
		}
	}
	strResultInfo="";
	SAFE_DELETE(pStockKDJData);
	return FALSE;
}


Vec_KDJCrossInfo CStockNewK60KDJMulSniper::AnalyzeKDJCross(std::vector<double> vec_calc_k,std::vector<double> vec_calc_d,std::vector<double> vec_calc_j)
{
	Vec_KDJCrossInfo vecKDJCrossInfo;

	int mCalcLength=80;

	if(vec_calc_j.size()<mCalcLength)
		return vecKDJCrossInfo;

	std::vector<int > vec_calc_up_cross_j_pos;

	std::vector<int > vec_calc_down_cross_j_pos;

	KDJCrossInfo *pKDJCrossInfo=NULL;
	int m_Hight_Index=0;
	int m_Low_Index=0;

	for(int i=vec_calc_j.size()-1;i>=vec_calc_j.size()-1-mCalcLength;i--)
	{
		double f_now_k,f_now_d,f_now_j;
		double f_pre_k,f_pre_d,f_pre_j;

		f_now_k=vec_calc_k[i];
		f_pre_k=vec_calc_k[i-1];

		f_now_d=vec_calc_d[i];
		f_pre_d=vec_calc_d[i-1];

		f_now_j=vec_calc_j[i];
		f_pre_j=vec_calc_j[i-1];


		//KDJ 上穿
		if(f_now_j>f_now_k  &&  f_now_k>f_now_d)
		{
			if(f_pre_d>f_pre_k && f_pre_k > f_pre_j)
			{
				if(pKDJCrossInfo)
				{
					if(pKDJCrossInfo->m_role_type==KDJ_ROLE_TYPE_HIGH)
					{
						pKDJCrossInfo->m_up_cross_pos=i;
						pKDJCrossInfo->m_role_index=m_Hight_Index;

						double f_max_val=-999999.0;
						int m_max_pos=-1;
						for(int i=pKDJCrossInfo->m_up_cross_pos;i<=pKDJCrossInfo->m_down_cross_pos;i++)
						{
							if(vec_calc_j[i]>f_max_val)
							{
								f_max_val=vec_calc_j[i];
								m_max_pos=i;
							}
						}
						pKDJCrossInfo->m_role_pos=m_max_pos;
						pKDJCrossInfo->f_role_value=f_max_val;
						vecKDJCrossInfo.push_back(pKDJCrossInfo);
						m_Hight_Index++;
					}
				}

				pKDJCrossInfo=new KDJCrossInfo();
				pKDJCrossInfo->m_role_type=KDJ_ROLE_TYPE_LOW;
				pKDJCrossInfo->m_up_cross_pos=i;
			}
		}

		//KDJ 下穿 
		if(f_now_d>f_now_k && f_now_k>f_now_j)
		{
			if(f_pre_j>f_pre_k && f_pre_k>f_pre_d)
			{
				if(pKDJCrossInfo)
				{
					if(pKDJCrossInfo->m_role_type==KDJ_ROLE_TYPE_LOW)
					{
						pKDJCrossInfo->m_down_cross_pos=i;
						pKDJCrossInfo->m_role_index=m_Low_Index;

						double f_min_val=999999.0;
						int m_min_pos=-1;
						for(int i=pKDJCrossInfo->m_down_cross_pos;i<=pKDJCrossInfo->m_up_cross_pos;i++)
						{
							if(vec_calc_j[i]<f_min_val)
							{
								f_min_val=vec_calc_j[i];
								m_min_pos=i;
							}
						}
						pKDJCrossInfo->m_role_pos=m_min_pos;
						pKDJCrossInfo->f_role_value=f_min_val;
						vecKDJCrossInfo.push_back(pKDJCrossInfo);
						m_Low_Index++;
					}
				}

				pKDJCrossInfo=new KDJCrossInfo();
				pKDJCrossInfo->m_role_type=KDJ_ROLE_TYPE_HIGH;
				pKDJCrossInfo->m_down_cross_pos=i;
			}
		}

	


	}

	

	return vecKDJCrossInfo;
}


CString CStockNewK60KDJMulSniper::GetSniperAnalyzeResult(void)
{

	return strResultInfo;
}