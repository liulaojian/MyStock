#include "stdafx.h"
#include "StockK60CCISniper.h"
#include "StockDataMgr.h"
#include "StockKDJArithmetic.h"
#include "StockCCIArithmetic.h"
#include "StockMACDArithmetic.h"
#include "CommonMacro.h"
#include "StockLoopBackDataMgr.h"
#include "Log.h"

CStockK60CCISniper::CStockK60CCISniper(CString strStockCode):CStockSniper(strStockCode)
{

	strResultInfo="";
}


CStockK60CCISniper::~CStockK60CCISniper()
{

}

BOOL CStockK60CCISniper::SniperAnalyze(BOOL bLoopBackMode)
{
	CStockMin5Table *pStockMin5Table=NULL;

	if(bLoopBackMode)
		pStockMin5Table=StockLoopBackDataMgr()->GetStockMin5Table(strStockCode);
	else
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);

	if(!pStockMin5Table)
		return FALSE;

	CString strDateTime=pStockMin5Table->GetLastStockMin5DataDateTime();


	CStockCCIData* pStockCCIData=NULL;
	pStockCCIData=CStockCCIArithmetic::CalcCCIData(strStockCode,strDateTime,255,K_LINE_60MIN,14);

	if(pStockCCIData==NULL)
		return FALSE;


	

	int mLength=pStockCCIData->vec_cci_value.size();

	
	double f_now_cci_val=pStockCCIData->vec_cci_value[mLength-1];
	double f_last_cci_val=pStockCCIData->vec_cci_value[mLength-2];
	
	BOOL bOK2=FALSE;

	BOOL  bCCIF100Triger=FALSE;
	BOOL  bCCIF150Triger=FALSE;

	if(f_last_cci_val<-100.0 && f_now_cci_val>-100.0)
	{
		bOK2=TRUE;
		bCCIF100Triger=TRUE;

	}
	else if(f_last_cci_val<-150.0 && f_now_cci_val>-150.0)
	{
		bOK2=TRUE;
		bCCIF150Triger=TRUE;
	}
	if(!bOK2)
	{
		SAFE_DELETE(pStockCCIData);
		return FALSE;
	}

	

	f_min_cci_val=99999.0;
	int   m_min_cci_pos=-1;
	for(int i=mLength-7;i<mLength-1;i++)			//7 表示 很小范围内就要到最小CCI
	{
		if(pStockCCIData->vec_cci_value[i]<f_min_cci_val)
		{
			f_min_cci_val=pStockCCIData->vec_cci_value[i];
			m_min_cci_pos=i;
		}
	}

	if(m_min_cci_pos<0)
	{
		SAFE_DELETE(pStockCCIData);
		return FALSE;
	}

	
	BOOL bOK3=FALSE;
	
	bOK3=FALSE;
	if(f_min_cci_val<-200.0 )
		bOK3=TRUE;
	else if(f_min_cci_val<=-150.0)
	{
		if(bCCIF100Triger)
		{
				bOK3=TRUE;
		}
	}

	if(!bOK3)
	{
		SAFE_DELETE(pStockCCIData);
		return FALSE;
	}
	
	
	
	if(bLoopBackMode)
	{
		double f_range=0.0;
		int mPeriodNums=8;
		CalcNext4PeridRange(strDateTime,K_LINE_60MIN,mPeriodNums,f_range);
		strResultInfo.Format("%s rang %.2f   ",pStockCCIData->strStockCode,f_range);
		PrintfDebug("%s\n",strResultInfo);
	}

	CString strStockName;
	strStockName=StockDataMgr()->GetStockName(pStockCCIData->strStockCode);
	if(bLoopBackMode)
	{
		double f_range=0.0;
		int mPeriodNums=8;

		CalcNext4PeridRange(strDateTime,K_LINE_60MIN,mPeriodNums,f_range);
		strResultInfo.Format("%s  %s 回测%d涨幅 %.2f  mincci=%.2f",pStockCCIData->strStockCode,strStockName,mPeriodNums,f_range,f_min_cci_val);
	}
	else
	{
		if(bCCIF150Triger)
			strResultInfo.Format("%s  %s 60分钟K线 CCI过-150线 最小CCI %.2f ",pStockCCIData->strStockCode,strStockName,f_min_cci_val);
		else
			strResultInfo.Format("%s  %s 60分钟K线 CCI过-100线 最小CCI %.2f ",pStockCCIData->strStockCode,strStockName,f_min_cci_val);
	}
	SAFE_DELETE(pStockCCIData);
	return TRUE;
}


BOOL  CStockK60CCISniper::CalcExpMa20Ma60(BOOL bLoopBackMode)
{
	CString strExpStockCode;

	CStockMin5Table *pStockMin5Table=NULL;

	strExpStockCode=StockDataMgr()->GetExpCodeByBoardType(StockDataMgr()->GetStockBoard(strStockCode));//"SH000001";

	if(bLoopBackMode)
		pStockMin5Table=StockLoopBackDataMgr()->GetStockMin5Table(strExpStockCode);
	else
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(strExpStockCode);

	if(!pStockMin5Table)
		return FALSE;

	CString strDateTime=pStockMin5Table->GetLastStockMin5DataDateTime();


	CStockKDJData *pStockKDJData=NULL;


	pStockKDJData=CStockKDJArithmetic::CalcKDJData(strExpStockCode,strDateTime,160,K_LINE_60MIN,9,3,3);


	if(pStockKDJData==NULL)
		return FALSE;


	std::vector<double> vec_ma5,vec_ma10,vec_ma20,vec_ma60;
	vec_ma5=CStockKDJArithmetic::CalcMA(5,pStockKDJData->vec_close_price);
	vec_ma10=CStockKDJArithmetic::CalcMA(10,pStockKDJData->vec_close_price);
	vec_ma20=CStockKDJArithmetic::CalcMA(20,pStockKDJData->vec_close_price);
	vec_ma60=CStockKDJArithmetic::CalcMA(60,pStockKDJData->vec_close_price);

	int mM5Length=vec_ma5.size();
	int mM10Length=vec_ma10.size();
	int mM20Length=vec_ma20.size();
	int mM60Length=vec_ma60.size();
	int mLength=pStockKDJData->vec_close_price.size();

	double f_now_ma5_val=vec_ma5[mM5Length-1];
	double f_now_ma10_val=vec_ma10[mM10Length-1];
	double f_now_ma20_val=vec_ma20[mM20Length-1];
	double f_now_ma60_val=vec_ma60[mM60Length-1];

	double f_now_val=pStockKDJData->vec_close_price[mLength-1];


	f_exp_ma60_per=(f_now_val-f_now_ma60_val)*100.0/f_now_ma60_val;
	f_exp_ma20_per=(f_now_val-f_now_ma20_val)*100.0/f_now_ma20_val;
	f_exp_ma10_per=(f_now_val-f_now_ma10_val)*100.0/f_now_ma10_val;
	f_exp_ma5_per=(f_now_val-f_now_ma5_val)*100.0/f_now_ma5_val;

	double f_toatl_val=0.0;
	for(int i=mLength-4;i<=mLength-1;i++)
	{
		double f_now_val,f_pre_val,f_rang;

		f_now_val=pStockKDJData->vec_close_price[i];
		f_pre_val=pStockKDJData->vec_close_price[i-1];
		f_rang=(f_now_val-f_pre_val)*100.0/f_pre_val;
		f_toatl_val+=f_rang;
	}

	f_exp_4_total_per=f_toatl_val;

	SAFE_DELETE(pStockKDJData);
	return TRUE;
}

BOOL CStockK60CCISniper:: CalcSamplePowerIsOk(double f_cci_sample,double f_10_sample,double f_20_sample,double f_40_sample,double f_60_sample,double f_120_sample,double f_240_sample,double f_range)
{
	BOOL bResult=FALSE;
	if(f_240_power>(f_240_sample-f_range) && f_240_power<(f_240_sample+f_range) )
	{
		if(f_120_power>(f_120_sample-f_range) && f_120_power<(f_120_sample+f_range) )
		{
			if(f_60_power>(f_60_sample-f_range) && f_60_power<(f_60_sample+f_range) )
			{
				if(f_40_power>(f_40_sample-f_range) && f_40_power<(f_40_sample+f_range) )
				{
					if(f_20_power>(f_20_sample-f_range) && f_20_power<(f_20_sample+f_range) )
					{
						if(f_10_power>(f_10_sample-f_range) && f_10_power<(f_10_sample+f_range) )
						{
							if(f_min_cci_val>(f_cci_sample-f_range) && f_min_cci_val<(f_cci_sample+f_range) )
							{
								bResult=TRUE;
							}
						}
					}
				}
			}
		}
	}

	return bResult;
}


CString CStockK60CCISniper::GetSniperAnalyzeResult(void)
{

	return strResultInfo;
}