#include "stdafx.h"
#include "StockWRArithmetic.h"

#include "StockDataMgr.h"
#include "CommonMacro.h"
#include "Log.h"
#include "Convert.h"

CStockWRArithmetic::CStockWRArithmetic()
{

}

CStockWRArithmetic::~CStockWRArithmetic()
{

}


CStocWRData * CStockWRArithmetic::CalcWRData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN1,int mN2)
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

	std::vector<double> vec_wr1;
	std::vector<double> vec_wr2;

	int n1 =mN1;
	int n2 = mN2;

	for(int i = 0; i < pKLineBaseData->m_length; i++) 
	{
		vec_wr1.push_back(0.0);
		vec_wr2.push_back(0.0);
	}


	for(int i = n1 - 1; i < pKLineBaseData->m_length; i++) 
	{
		float maxhigh = pKLineBaseData->vec_high_price[i];
		float minlow = pKLineBaseData->vec_low_price[i];
		for(int j = i - 1; j > i - n1; j--) 
		{
			maxhigh = max(maxhigh, pKLineBaseData->vec_high_price[j]);
			minlow = min(minlow, pKLineBaseData->vec_low_price[j]);
		}

		if( (maxhigh - minlow) == 0.0) {
			if( (i - 1) == 0)
				vec_wr1[i] = -50.0;
			else
				vec_wr1[i] = vec_wr1[i - 1];
		} else {
			vec_wr1[i] = ((maxhigh - pKLineBaseData->vec_close_price[i]) / (maxhigh - minlow)) * 100.0;
		}
	}

	for(int i = n2 - 1; i < pKLineBaseData->m_length; i++) 
	{
		float maxhigh = pKLineBaseData->vec_high_price[i];
		float minlow = pKLineBaseData->vec_low_price[i];
		for(int j = i - 1; j > i - n2; j--) 
		{
			maxhigh = max(maxhigh, pKLineBaseData->vec_high_price[j]);
			minlow = min(minlow, pKLineBaseData->vec_low_price[j]);
		}

		if( (maxhigh - minlow) == 0.0) {
			if( (i - 1) == 0)
				vec_wr2[i] = -50.0;
			else
				vec_wr2[i] = vec_wr2[i - 1];
		} else {
			vec_wr2[i] = ((maxhigh - pKLineBaseData->vec_close_price[i]) / (maxhigh - minlow)) * 100.0;
		}
	}

	int length=pKLineBaseData->m_length;
	vec_wr1[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_wr1);
	vec_wr2[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_wr2);
	
	CStocWRData*  pStocWRData;
	pStocWRData=new CStocWRData();
	pStocWRData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin()+mN1,pKLineBaseData->vec_open_price.end());
	pStocWRData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin()+mN1,pKLineBaseData->vec_high_price.end());
	pStocWRData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin()+mN1,pKLineBaseData->vec_low_price.end());
	pStocWRData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin()+mN1,pKLineBaseData->vec_close_price.end());
	pStocWRData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin()+mN1,pKLineBaseData->vec_avg_price.end());
	pStocWRData->vec_time.assign(pKLineBaseData->vec_time.begin()+mN1,pKLineBaseData->vec_time.end());
	pStocWRData->vec_volume.assign(pKLineBaseData->vec_volume.begin()+mN1,pKLineBaseData->vec_volume.end());
	pStocWRData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin()+mN1,pKLineBaseData->vec_volume_price.end());
	pStocWRData->m_length=pStocWRData->vec_open_price.size();
	pStocWRData->m_type=mType;
	pStocWRData->n1=mN1;
	pStocWRData->n2=mN2;
	pStocWRData->vec_wr1.assign(vec_wr1.begin()+mN1,vec_wr1.end());
	pStocWRData->vec_wr2.assign(vec_wr2.begin()+mN1,vec_wr2.end());
	pStocWRData->strStockCode=strStockCode;
	SAFE_DELETE(pKLineBaseData);
	return pStocWRData;

}