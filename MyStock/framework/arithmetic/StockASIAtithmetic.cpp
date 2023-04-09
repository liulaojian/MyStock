#include "stdafx.h"
#include "StockASIArithmetic.h"

#include "StockDataMgr.h"
#include "CommonMacro.h"

CStockASIArithmetic::CStockASIArithmetic()
{

}
CStockASIArithmetic::~CStockASIArithmetic()
{

}


CStockASIData* CStockASIArithmetic::CalcASIData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN)
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

	std::vector<double> asi;
	asi.assign(pKLineBaseData->m_length,0.0);

	double si = 0.0f;
	std::vector<double> vec_si;
	for(int i = 1; i < pKLineBaseData->m_length; i++) 
	{
		
		double a = abs(pKLineBaseData->vec_high_price[i] - pKLineBaseData->vec_close_price[i - 1]);
		double b = abs(pKLineBaseData->vec_low_price[i] - pKLineBaseData->vec_close_price[i - 1]);
		double c = abs(pKLineBaseData->vec_high_price[i] - pKLineBaseData->vec_low_price[i - 1]);
		double d = abs(pKLineBaseData->vec_close_price[i - 1] - pKLineBaseData->vec_open_price[i - 1]);
		double e = pKLineBaseData->vec_close_price[i] - pKLineBaseData->vec_close_price[i - 1];
		double f = pKLineBaseData->vec_close_price[i] - pKLineBaseData->vec_open_price[i];
		double g = pKLineBaseData->vec_close_price[i - 1] - pKLineBaseData->vec_open_price[i - 1];
		double x = e + 0.5*f  + g;
		double r = 0.0;
		
		if( a > b && a > c )
		{
			r = a + b / 2.0 + d / 4.0;
		}
		else if(b > a && b > c)
		{
			r = b + a / 2.0+ d / 4.0;
		}
		else
			r = c + d / 4.0;
		double k = max(a, b);  
		si = (((50.0 * x) / r) * k) / 3.0;
		asi[i] = asi[i - 1] + si;
		
	}


	std::vector<double> maasi;
	
	maasi=CalcMA(mN,asi);

	int length=maasi.size();
	maasi[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,maasi);
	
	return NULL;
}


std::vector<double> CStockASIArithmetic::CalcMA(int n,std::vector<double> vecrsi)
{
	std::vector<double> vecmarsi;
	double ma;  
	double closeSum = 0.0;  
	int period;  
	for (int i = 0; i < vecrsi.size(); i++) {  
		closeSum += vecrsi[i];  
		if (i >= (n - 1)) {  
			period = i - n;  
			if (period >= 0) {  
				closeSum -= vecrsi[period];  
			}  
			ma = (double) closeSum / n;  
			vecmarsi.push_back(ma);
		}  
	}  

	return vecmarsi;
}