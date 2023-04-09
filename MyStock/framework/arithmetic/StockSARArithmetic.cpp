#include "stdafx.h"
#include "StockSARArithmetic.h"

#include "StockDataMgr.h"
#include "CommonMacro.h"

CStockSARArithmetic::CStockSARArithmetic()
{

}

CStockSARArithmetic::~CStockSARArithmetic()
{

}


CStockSARData* CStockSARArithmetic::CalcSARData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN)
{
	KLineBaseData *pKLineBaseData=NULL;
	if(mType==K_LINE_DAY)
	{
		CStockDayTable *pStockDayTable;
		pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);
		if(!pStockDayTable)
			return NULL;

		pKLineBaseData=CKLineDataBean::ConvStockDayDataToArithmeticBaseData(pStockDayTable,strDateTime,mNums);		

	}
	else if(mType==K_LINE_5IN)
	{
		CStockMin5Table *pStockMin5Table;
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);
		if(!pStockMin5Table)
			return NULL;
		pKLineBaseData=CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin5(pStockMin5Table,strDateTime,mNums);

	}
	else if(mType==K_LINE_15IN)
	{
		CStockMin5Table *pStockMin5Table;
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);
		if(!pStockMin5Table)
			return NULL;
		pKLineBaseData=CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin15(pStockMin5Table,strDateTime,mNums);
	}
	else if(mType==K_LINE_30IN)
	{
		CStockMin5Table *pStockMin5Table;
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);
		if(!pStockMin5Table)
			return NULL;
		pKLineBaseData=CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin30(pStockMin5Table,strDateTime,mNums);
	}
	else if(mType==K_LINE_60MIN)
	{
		CStockMin5Table *pStockMin5Table;
		pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);
		if(!pStockMin5Table)
			return NULL;
		pKLineBaseData=CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin60(pStockMin5Table,strDateTime,mNums);
	}

	if(!pKLineBaseData)
		return NULL;


	int n=mN;

	if(n > pKLineBaseData->m_length || n < 3)
		return NULL;

	std::vector<double> sar;
	std::vector<double> sign;
	sar.assign(pKLineBaseData->m_length,0.0);
	sign.assign(pKLineBaseData->m_length,0.0);
	double xs = 0.02f;
	
	
	if(pKLineBaseData->vec_close_price[n - 1] < pKLineBaseData->vec_close_price[n - 2]) 
	{
		if(pKLineBaseData->vec_close_price[n - 2] <= pKLineBaseData->vec_close_price[n - 3])
			sign[n - 1] = 1.0f;
		else
			sign[n - 1] = 17.0f;	//17.0f;
	} 
	else
	{
		if(pKLineBaseData->vec_close_price[n - 1] > pKLineBaseData->vec_close_price[n - 2]) 
		{
			if(pKLineBaseData->vec_close_price[n - 2] >= pKLineBaseData->vec_close_price[n - 3])
				sign[n - 1] = 0.0f;
			else
				sign[n - 1] = 16.0f;	//16.0f;
		} 
		else
		{
			if(pKLineBaseData->vec_close_price[n - 2] < pKLineBaseData->vec_close_price[n - 3])
				sign[n - 1] = 1.0f;
			else
			{
				if(pKLineBaseData->vec_close_price[n - 2] > pKLineBaseData->vec_close_price[n - 3])
					sign[n - 1] = 0.0f;
				else
					sign[n - 1] = 20.0f;	//16.0f;
			}
		}
	}

	if(sign[n - 1] == 1.0f || sign[n - 1] == 17.0f)		//17.0f
	{
		sar[n - 1] = -1E+036F;
		for(int j = n - 1; j >= 0; j--) 
			sar[n - 1] = max(sar[n - 1], pKLineBaseData->vec_high_price[j]);

	} 
	else 
	{
		sar[n - 1] = 1E+036F;
		for(int j = n - 1; j >= 0; j--) 
			sar[n - 1] = min(sar[n - 1], pKLineBaseData->vec_low_price[j]);
	}

	
	for(int i = n; i < pKLineBaseData->m_length; i++)
	{
		if(sign[i - 1] == 0.0F || sign[i - 1] == 16.0f)		//16.0f
		{
			if(pKLineBaseData->vec_close_price[i] < sar[i - 1]) 
			{
				sar[i] = -1E+036F;
				for(int j = i; j > i - n; j--)
					sar[i] = max(sar[i], pKLineBaseData->vec_high_price[j]);

				sign[i] = 17.0f;
				xs = 0.02F;
			} 
			else 
			{
				sar[i] = sar[i - 1] + xs * (pKLineBaseData->vec_high_price[i - 1] - sar[i - 1]);
				xs = xs >= 0.2f ? xs : xs + 0.02F;
				sign[i] = 0.0f;
			}
		} 
		else
		{
			if(pKLineBaseData->vec_close_price[i] > sar[i - 1]) 
			{
				sar[i] = 1E+036F;
				for(int j = i; j > i - n; j--)
					sar[i] = min(sar[i], pKLineBaseData->vec_low_price[j]);

				sign[i] = 16.0f;
				xs = 0.02f;
			} 
			else 
			{
				sar[i] = sar[i - 1] + xs * (pKLineBaseData->vec_low_price[i - 1] - sar[i - 1]);
				xs = xs >= 0.2f ? xs : xs + 0.02f;
				sign[i] = 1.0f;
			}
		}
	}


	int length=sar.size();
	sar[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,sar);
	
	CStockSARData *pStockSARData=new CStockSARData();
	pStockSARData->strStockCode=strStockCode;
	pStockSARData->mN=mN;
	pStockSARData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin()+mN-1,pKLineBaseData->vec_avg_price.end());
	pStockSARData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin()+mN-1,pKLineBaseData->vec_open_price.end());
	pStockSARData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin()+mN-1,pKLineBaseData->vec_high_price.end());
	pStockSARData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin()+mN-1,pKLineBaseData->vec_low_price.end());
	pStockSARData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin()+mN-1,pKLineBaseData->vec_close_price.end());
	pStockSARData->vec_time.assign(pKLineBaseData->vec_time.begin()+mN-1,pKLineBaseData->vec_time.end());
	pStockSARData->vec_volume.assign(pKLineBaseData->vec_volume.begin()+mN-1,pKLineBaseData->vec_volume.end());
	pStockSARData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin()+mN-1,pKLineBaseData->vec_volume_price.end());
	pStockSARData->m_length=pStockSARData->vec_time.size();
	pStockSARData->m_type=mType;
	pStockSARData->vec_sar.assign(sar.begin()+mN-1,sar.end());

	SAFE_DELETE(pKLineBaseData);

	return pStockSARData;
}