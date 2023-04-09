#include "stdafx.h"
#include "StockOBVArithmetic.h"

#include "StockDataMgr.h"
#include "CommonMacro.h"
#include "Log.h"
CStockOBVArithmetic::CStockOBVArithmetic()
{

}

CStockOBVArithmetic::~CStockOBVArithmetic()
{

}

CStockOBVData* CStockOBVArithmetic::CalcOBVData(CString strStockCode,CString strDateTime,int mNums,int mType,int mMaN)
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
	double obv;  
	double preObv = 0.0;  
	std::vector<double> vec_obv;
	for (int i = 0; i < pKLineBaseData->vec_close_price.size(); i++)
	{  
		if (i == 0) 
		{  
			obv = 0.0;  
		} 
		else 
		{  
			if (pKLineBaseData->vec_close_price[i] > pKLineBaseData->vec_close_price[i - 1]) 
			{  
				obv = (preObv + pKLineBaseData->vec_volume[i]/100);  
			} 
			else if (pKLineBaseData->vec_close_price[i] < pKLineBaseData->vec_close_price[i - 1]) 
			{  
				obv = (preObv - pKLineBaseData->vec_volume[i]/100);  
			} 
			else 
			{  
				obv = preObv;  
			}  
		}  

		vec_obv.push_back(obv);

		preObv = obv;  
	}  


	std::vector<double> vec_maobv;
	vec_maobv=CalcMA(mMaN,vec_obv);

	int length=vec_obv.size();
	vec_obv[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_obv);
	vec_maobv[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_maobv);
	

	CStockOBVData *pStockOBVData=new CStockOBVData();
	pStockOBVData->strStockCode=strStockCode;
	pStockOBVData->mMaN=mMaN;
	pStockOBVData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin()+mMaN-1,pKLineBaseData->vec_avg_price.end());
	pStockOBVData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin()+mMaN-1,pKLineBaseData->vec_open_price.end());
	pStockOBVData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin()+mMaN-1,pKLineBaseData->vec_high_price.end());
	pStockOBVData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin()+mMaN-1,pKLineBaseData->vec_low_price.end());
	pStockOBVData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin()+mMaN-1,pKLineBaseData->vec_close_price.end());
	pStockOBVData->vec_time.assign(pKLineBaseData->vec_time.begin()+mMaN-1,pKLineBaseData->vec_time.end());
	pStockOBVData->vec_volume.assign(pKLineBaseData->vec_volume.begin()+mMaN-1,pKLineBaseData->vec_volume.end());
	pStockOBVData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin()+mMaN-1,pKLineBaseData->vec_volume_price.end());
	pStockOBVData->vec_obv.assign(vec_obv.begin()+mMaN-1,vec_obv.end());
	pStockOBVData->vec_maobv.assign(vec_maobv.begin(),vec_maobv.end());
	pStockOBVData->m_length=pStockOBVData->vec_obv.size();
	pStockOBVData->m_type=mType;
	SAFE_DELETE(pKLineBaseData);

	
	return pStockOBVData;


}


std::vector<double> CStockOBVArithmetic::CalcMA(int n,std::vector<double> vecobv)
{
	std::vector<double> vecma;
	double ma;  
	double closeSum = 0.0;  
	int period;  
	for (int i = 0; i < vecobv.size(); i++) {  
		closeSum += vecobv[i];  
		if (i >= (n - 1)) {  
			period = i - n;  
			if (period >= 0) {  
				closeSum -= vecobv[period];  
			}  
			ma = (double) closeSum / n;  
			vecma.push_back(ma);
		}  
	}  


	return vecma;
}