#include "stdafx.h"
#include "StockKDJArithmetic.h"

#include "StockDataMgr.h"
#include "CommonMacro.h"
#include "Log.h"
#include "Convert.h"

CStockKDJArithmetic::CStockKDJArithmetic()
{

}

CStockKDJArithmetic::~CStockKDJArithmetic()
{

}

CStockKDJData* CStockKDJArithmetic::CalcKDJData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN1,int mN2,int mN3)
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

	std::vector<double> vec_k;
	std::vector<double> vec_d;
	std::vector<double> vec_j;

	int n1 =mN1;
	int n2 = mN2;
	int n3 = mN3;

	for(int i = 0; i < pKLineBaseData->m_length; i++) 
	{
		vec_k.push_back(0.0);
		vec_d.push_back(0.0);
		vec_j.push_back(0.0);
	}
	
	double maxhigh = pKLineBaseData->vec_high_price[n1 - 1];
	double minlow = pKLineBaseData->vec_low_price[n1 - 1];
	for(int j = n1 - 1; j >= 0; j--) {
		if(maxhigh < pKLineBaseData->vec_high_price[j])
			maxhigh = pKLineBaseData->vec_high_price[j];
		if(minlow < pKLineBaseData->vec_low_price[j])
			minlow = pKLineBaseData->vec_low_price[j];
	}
	
	double rsv;
	if(maxhigh <= minlow)
		rsv = 50.0;
	else
		rsv = ((pKLineBaseData->vec_close_price[n1 - 1] - minlow) / (maxhigh - minlow)) * 100.0;




	double prersv;
	vec_k[n1 - 1] = vec_d[n1 - 1] = vec_j[n1 - 1] = prersv = rsv;
	for(int i = 0; i < n1; i++) {
		vec_k[i] = 0.0;
		vec_d[i] = 0.0;
		vec_j[i] = 0.0;
	}

	for(int i = n1; i < pKLineBaseData->m_length; i++) 
	{
		maxhigh = pKLineBaseData->vec_high_price[i];
		minlow = pKLineBaseData->vec_low_price[i];
		for(int j = i - 1; j > i - n1; j--) 
		{
			if(maxhigh < pKLineBaseData->vec_high_price[j])
				maxhigh = pKLineBaseData->vec_high_price[j];
			if(minlow > pKLineBaseData->vec_low_price[j])
				minlow = pKLineBaseData->vec_low_price[j];
		}
		
		if(maxhigh <= minlow) 
		{
			rsv = prersv;
		} else 
		{
			prersv = rsv;
			rsv = ((pKLineBaseData->vec_close_price[i] - minlow) / (maxhigh - minlow)) * 100.0;
		}
		
		vec_k[i] = (vec_k[i - 1] * (double)(n2 - 1)) / (double)n2 + rsv / (double)n2;
		vec_d[i] = vec_k[i] / (double)n3 + (vec_d[i - 1] * (double)(n3 - 1)) / (double)n3;
		vec_j[i] = 3.0 * vec_k[i] - 2.0 * vec_d[i];
	}

	int length=pKLineBaseData->m_length;
	vec_k[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_k);
	vec_d[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_d);
	vec_j[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_j);

	CStockKDJData*  pStockKDJData;
	pStockKDJData=new CStockKDJData();
	pStockKDJData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin()+mN1,pKLineBaseData->vec_open_price.end());
	pStockKDJData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin()+mN1,pKLineBaseData->vec_high_price.end());
	pStockKDJData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin()+mN1,pKLineBaseData->vec_low_price.end());
	pStockKDJData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin()+mN1,pKLineBaseData->vec_close_price.end());
	pStockKDJData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin()+mN1,pKLineBaseData->vec_avg_price.end());
	pStockKDJData->vec_time.assign(pKLineBaseData->vec_time.begin()+mN1,pKLineBaseData->vec_time.end());
	pStockKDJData->vec_volume.assign(pKLineBaseData->vec_volume.begin()+mN1,pKLineBaseData->vec_volume.end());
	pStockKDJData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin()+mN1,pKLineBaseData->vec_volume_price.end());
	pStockKDJData->m_length=pStockKDJData->vec_open_price.size();
	pStockKDJData->m_type=mType;
	pStockKDJData->n1=mN1;
	pStockKDJData->n2=mN2;
	pStockKDJData->n3=mN3;
	pStockKDJData->vec_k.assign(vec_k.begin()+mN1,vec_k.end());
	pStockKDJData->vec_d.assign(vec_d.begin()+mN1,vec_d.end());
	pStockKDJData->vec_j.assign(vec_j.begin()+mN1,vec_j.end());
	pStockKDJData->strStockCode=strStockCode;
	SAFE_DELETE(pKLineBaseData);
	return pStockKDJData;


}


std::vector<double> CStockKDJArithmetic::CalcMA(int n,std::vector<double> vec_value)
{
	std::vector<double> vecma_value;
	double ma;  
	double closeSum = 0.0;  
	int period;  
	for (int i = 0; i < vec_value.size(); i++) {  
		closeSum += vec_value[i];  
		if (i >= (n - 1)) {  
			period = i - n;  
			if (period >= 0) {  
				closeSum -= vec_value[period];  
			}  
			ma = (double) closeSum / n;  
			vecma_value.push_back(ma);
		}  
		else
		{
			vecma_value.push_back(0.0);
		}
	}  

	return vecma_value;
}



