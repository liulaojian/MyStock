#include "stdafx.h"
#include "TriAngleAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
CTriAngleAlg::CTriAngleAlg()
{

}

CTriAngleAlg::~CTriAngleAlg()
{


}

#if 0
Vec_TriAngleData  CTriAngleAlg::doFilter(CTime mDropOffTime)
{
	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	Vec_StockCodeList vecStockCodeList=StockDataMgr()->GetStockCodeList();

	int mPreSize=10;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		pStockCode=vecStockCodeList[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
		strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);

		CStockKDJData *pStockKDJData=NULL;

		pStockKDJData=CStockKDJArithmetic::CalcKDJData(pStockCode->strStockCode,strNowDate,160,K_LINE_DAY,9,3,3);
		if(pStockKDJData==NULL)
			continue;
		std::vector<double> vec_price_ma5,vec_price_ma10,vec_price_ma20,vec_price_ma60;
		vec_price_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
		vec_price_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
		vec_price_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
		vec_price_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);
		int size=pStockKDJData->vec_volume_price.size();

		int m5_cross_m10_index=-1;
		for(int j=size-mPreSize;j<size;j++)
		{
			double f_pre_m5=vec_price_ma5[j-1];
			double f_now_m5=vec_price_ma5[j];

			double f_pre_m10=vec_price_ma10[j-1];
			double f_now_m10=vec_price_ma10[j];
			if(f_pre_m5<f_now_m5)
			{
				if(f_pre_m5<f_pre_m10)
				{
					if(f_now_m5>=f_now_m10)
					{
						m5_cross_m10_index=j;
						break;
					}
				}

			}
			
		}


		if(m5_cross_m10_index<0)
			continue;

		int m5_cross_m20_index=-1;
		for(int j=size-mPreSize;j<size;j++)
		{
			double f_pre_m5=vec_price_ma5[j-1];
			double f_now_m5=vec_price_ma5[j];

			double f_pre_m20=vec_price_ma20[j-1];
			double f_now_m20=vec_price_ma20[j];

			if(f_pre_m5<f_now_m5)
			{
				if(f_pre_m5<f_pre_m20)
				{
					if(f_now_m5>=f_now_m20)
					{
						m5_cross_m20_index=j;
						break;
					}
				}

			}
			
		}

		if(m5_cross_m20_index<0)
			continue;

		if(m5_cross_m20_index<=m5_cross_m10_index)
			continue;
		BOOL bOK=TRUE;
		for(int j=m5_cross_m10_index;j<=m5_cross_m20_index;j++)
		{
			double f_pre_m5=vec_price_ma5[j-1];
			double f_now_m5=vec_price_ma5[j];

			if(f_pre_m5>f_now_m5)
			{

				bOK=FALSE;
				break;
			}

		}

		if(!bOK)
			continue;

		int m10_cross_m20_index=-1;
		for(int j=size-mPreSize;j<size;j++)
		{
			double f_pre_m10=vec_price_ma10[j-1];
			double f_now_m10=vec_price_ma10[j];

			double f_pre_m20=vec_price_ma20[j-1];
			double f_now_m20=vec_price_ma20[j];

			if(f_pre_m10<f_pre_m20)
			{
				if(f_pre_m10>=f_now_m20)
				{
					m10_cross_m20_index=j;
					break;
				}
			}

		}

		if(m10_cross_m20_index<0)
			continue;

		if(m10_cross_m20_index<m5_cross_m20_index)
			continue;
		bOK=TRUE;
		for(int j=m5_cross_m20_index;j<=m10_cross_m20_index;j++)
		{
			double f_pre_m10=vec_price_ma10[j-1];
			double f_now_m10=vec_price_ma10[j];

			if(f_pre_m10>f_now_m10)
			{

				bOK=FALSE;
				break;
			}

		}

		if(!bOK)
			continue;


		//printf("%s %d  %d  %d\n",pStockCode->strStockCode,m5_cross_m10_index,m5_cross_m20_index,m10_cross_m20_index);

		
		
		if(m5_cross_m10_index<m5_cross_m20_index)
		{
			if(m5_cross_m20_index<m10_cross_m20_index)
			{

			

				TriAngleData *pTriAngleData=new TriAngleData();
				pTriAngleData->strStockCode=pStockCode->strStockCode;
				pTriAngleData->strStockName=pStockCode->strStockName;
				pTriAngleData->mPara1=size-m10_cross_m20_index;
				pTriAngleData->strDateTime=strNowDate;
				vecTriAngleData.push_back(pTriAngleData);
			
			}

		}

	}

	return vecTriAngleData;
}
#else
Vec_TriAngleData  CTriAngleAlg::doFilter(CTime mDropOffTime)
{
	StockCode * pStockCode=NULL;
	CStockDayTable*pStockDayTable=NULL;
	CString strNowDate;
	Vec_StockCodeList vecStockCodeList=StockDataMgr()->GetStockCodeList();

	int mPreSize=12;
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		pStockCode=vecStockCodeList[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(pStockCode->strStockCode);
		strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);

		
		CStockRSIData* pStockRSIData=NULL;
		pStockRSIData=CStockRSIArithmetic::CalcRSIData(pStockCode->strStockCode,strNowDate,125,K_LINE_DAY,6,12,24); 
		if(!pStockRSIData)
			continue;


		std::vector<double> vec_price_ma5,vec_price_ma10,vec_price_ma20,vec_price_ma60;
		vec_price_ma5=CStockKDJArithmetic::CalcMA(5,pStockRSIData->vec_close_price);
		vec_price_ma10=CStockKDJArithmetic::CalcMA(10,pStockRSIData->vec_close_price);
		vec_price_ma20=CStockKDJArithmetic::CalcMA(20,pStockRSIData->vec_close_price);
		vec_price_ma60=CStockKDJArithmetic::CalcMA(60,pStockRSIData->vec_close_price);
		int size=pStockRSIData->vec_volume_price.size();
#if 0
		int m_ma10_increase_nums=0;

		for(int j=size-mPreSize;j<size;j++)
		{

			double f_pre_ma10=vec_price_ma10[j-1];
			double f_now_ma10=vec_price_ma10[j];
			if(f_now_ma10>=f_pre_ma10)
				m_ma10_increase_nums++;

		}

		if(m_ma10_increase_nums<(mPreSize-2))
			continue;

		BOOL bOk=TRUE;


		for(int j=size-mPreSize;j<size;j++)
		{

			double f_pre_ma20=vec_price_ma20[j-1];
			double f_now_ma20=vec_price_ma20[j];
			if(f_now_ma20<f_pre_ma20)
			{
				bOk=FALSE;
				break;

			}

		}

		if(!bOk)
			continue;
		int m_rsi1_big_80_nums=0;
		for(int j=size-mPreSize;j<size;j++)
		{
			double f_rsi_1=pStockRSIData->vec_rsi_1_value[j];
			if(f_rsi_1>=80.0)
			{
				m_rsi1_big_80_nums++;
			}
		}

		BOOL bRsi1Big85=FALSE;
		for(int j=size-3;j<size;j++)
		{
			double f_rsi_1=pStockRSIData->vec_rsi_1_value[j];
			if(f_rsi_1>=85.0)
			{
				bRsi1Big85=TRUE;
			}
		}

		BOOL bRsi1NowBig80=FALSE;
		if(pStockRSIData->vec_rsi_1_value[size-1]>=80.0)
			bRsi1NowBig80=TRUE;
#else

		int m_rsi1_less_70_nums=0;
		for(int j=size-mPreSize;j<size;j++)
		{
			double f_rsi_1=pStockRSIData->vec_rsi_1_value[j];
			if(f_rsi_1<=70.0)
			{
				m_rsi1_less_70_nums++;
			}
		}

		if(m_rsi1_less_70_nums<(mPreSize-2))
			continue;
#endif

		TriAngleData *pTriAngleData=new TriAngleData();
		pTriAngleData->strStockCode=pStockCode->strStockCode;
		pTriAngleData->strStockName=pStockCode->strStockName;
#if 0
		pTriAngleData->mPara1=mPreSize-m_ma10_increase_nums;
		pTriAngleData->mPara2=m_rsi1_big_80_nums;
		if(bRsi1Big85)
			pTriAngleData->mPara3=44;
		else
			pTriAngleData->mPara3=0;
		if(bRsi1NowBig80)
			pTriAngleData->mPara3+55;
#else
		pTriAngleData->mPara1=m_rsi1_less_70_nums;
		pTriAngleData->mPara2=0;
		pTriAngleData->mPara3=0;
#endif

		pTriAngleData->strDateTime=strNowDate;
		vecTriAngleData.push_back(pTriAngleData);
	}

	return vecTriAngleData;
}


#endif