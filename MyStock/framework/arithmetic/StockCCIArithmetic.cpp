#include "stdafx.h"
#include "StockCCIArithmetic.h"
#include "StockDataMgr.h"
#include "CommonMacro.h"
CStockCCIArithmetic::CStockCCIArithmetic()
{


}


CStockCCIArithmetic::~CStockCCIArithmetic()
{

}

//计算出CCI的数据 
//strStockCode 股票代码
//strDateTime  日期
//mNums  共多少交易日 包含日期
//mN CCI算法内的N
//得到的 std::vector<double>  数量 是 mNums+mN-1
CStockCCIData*  CStockCCIArithmetic::CalcCCIData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN)
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

	std::vector<double> vec_cci_value;

	double typSum = 0;  
	double cciValue;  
	double typMa;  
	double typDiff;  
	double typDiffSum;  
	double typDEV;  

	int n=mN;

	int period;  
	for (int i = 0;i<pKLineBaseData->m_length;i++)
	{  
		typSum += pKLineBaseData->vec_avg_price[i];
		if (i >= (n - 1)) 
		{

			period = i - n;  
			if (period >= 0) {  
				typSum -= pKLineBaseData->vec_avg_price[period]; 
			}  
			typMa = typSum/n;  
			typDiffSum = 0;  

			for (int j = period+1;j<=i;j++){  
				typDiff = abs(pKLineBaseData->vec_avg_price[j]-typMa);  
				typDiffSum+=typDiff;  
			}  
			typDEV = typDiffSum/n;  
			cciValue = (pKLineBaseData->vec_avg_price[i]-typMa)/(typDEV*0.015);  
			vec_cci_value.push_back(cciValue);
		}
	}


	int length=vec_cci_value.size();
	vec_cci_value[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_cci_value);
	
	CStockCCIData*  pCStockCCIData;
	pCStockCCIData=new CStockCCIData();
	pCStockCCIData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin()+mN-1,pKLineBaseData->vec_open_price.end());
	pCStockCCIData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin()+mN-1,pKLineBaseData->vec_high_price.end());
	pCStockCCIData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin()+mN-1,pKLineBaseData->vec_low_price.end());
	pCStockCCIData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin()+mN-1,pKLineBaseData->vec_close_price.end());
	pCStockCCIData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin()+mN-1,pKLineBaseData->vec_avg_price.end());
	pCStockCCIData->vec_time.assign(pKLineBaseData->vec_time.begin()+mN-1,pKLineBaseData->vec_time.end());
	pCStockCCIData->vec_volume.assign(pKLineBaseData->vec_volume.begin()+mN-1,pKLineBaseData->vec_volume.end());
	pCStockCCIData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin()+mN-1,pKLineBaseData->vec_volume_price.end());
	pCStockCCIData->vec_cci_value=vec_cci_value;
	pCStockCCIData->m_length=vec_cci_value.size();
	pCStockCCIData->m_type=pKLineBaseData->m_type;
	pCStockCCIData->mN=mN;
	pCStockCCIData->strStockCode=strStockCode;
	SAFE_DELETE(pKLineBaseData);
	return pCStockCCIData;
}