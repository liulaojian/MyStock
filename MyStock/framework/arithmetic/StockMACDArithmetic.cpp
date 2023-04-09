#include "stdafx.h"
#include "StockMACDArithmetic.h"
#include "StockDataMgr.h"
#include "CommonMacro.h"

CStockMACDArithmetic::CStockMACDArithmetic()
{

}

CStockMACDArithmetic::~CStockMACDArithmetic()
{


}



CStockMACDData* CStockMACDArithmetic::CalcMACDData(CString strStockCode,CString strDateTime,int mNums,int mType,int shortValue,int longValue,int mValue)
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

	//dou

	std::vector<double> vec_dif;
	std::vector<double> vec_dea;
	std::vector<double> vec_macd;

	double emaShort = 0.0;  
	double emaLong = 0.0;  
	double macd;  
	double dif;  
	double dea = 0.0;  
	for (int i = 0; i < pKLineBaseData->vec_close_price.size(); i++) 
	{  
		if (i == 0) 
		{  
			emaShort =pKLineBaseData->vec_close_price[i];  
			emaLong = pKLineBaseData->vec_close_price[i];  
			dif = 0;  
			dea = 0;  
			macd = 0;  
		} 
		else 
		{  
			emaShort = (emaShort * (shortValue - 1) + pKLineBaseData->vec_close_price[i] * 2) / (shortValue + 1);  
			emaLong = (emaLong * (longValue - 1) + pKLineBaseData->vec_close_price[i] * 2) / (longValue + 1);  
			dif = emaShort - emaLong;  
			dea = (dea * (mValue - 1) + dif * 2) / (mValue + 1);  
			macd = (dif - dea) * 2;  
			vec_dif.push_back(dif);
			vec_dea.push_back(dea);
			vec_macd.push_back(macd);
		}  
	}  

	int length=vec_dif.size();
	vec_dif[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_dif);
	vec_dea[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_dea);
	vec_macd[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_macd);

	CStockMACDData *pStockMACDData=new CStockMACDData();
	pStockMACDData->strStockCode=strStockCode;
	pStockMACDData->mLongValue=longValue;
	pStockMACDData->mShortValue=shortValue;
	pStockMACDData->mValue=mValue;
	pStockMACDData->m_length=vec_dif.size();
	pStockMACDData->m_type=pStockMACDData->m_type;

	pStockMACDData->vec_avg_price=pKLineBaseData->vec_avg_price;
	pStockMACDData->vec_close_price=pKLineBaseData->vec_close_price;
	pStockMACDData->vec_high_price=pKLineBaseData->vec_high_price;
	pStockMACDData->vec_low_price=pKLineBaseData->vec_low_price;
	pStockMACDData->vec_open_price=pKLineBaseData->vec_open_price;
	pStockMACDData->vec_time=pKLineBaseData->vec_time;
	pStockMACDData->vec_volume=pKLineBaseData->vec_volume;
	pStockMACDData->vec_volume_price=pKLineBaseData->vec_volume_price;

	pStockMACDData->vec_dea=vec_dea;
	pStockMACDData->vec_dif=vec_dif;
	pStockMACDData->vec_macd=vec_macd;

	SAFE_DELETE(pKLineBaseData);

	return pStockMACDData;
}


//Close 的 N 日 平均线
std::vector<double> CStockMACDArithmetic::CalcMA(int n,KLineBaseData *pKLineBaseData)
{
	std::vector<double> vecma;
	double ma;  
	double closeSum = 0.0;  
	int period;  
	for (int i = 0; i < pKLineBaseData->m_length; i++) {  
		closeSum += pKLineBaseData->vec_close_price[i];  
		if (i >= (n - 1)) {  
			period = i - n;  
			if (period >= 0) {  
				closeSum -= pKLineBaseData->vec_close_price[period];  
			}  
			ma = (double) closeSum / n;  
			vecma.push_back(ma);
		}  
	}  


	return vecma;
}