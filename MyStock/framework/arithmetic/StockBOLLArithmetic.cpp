#include "stdafx.h"
#include "StockBOLLArithmetic.h"

#include "StockDataMgr.h"
#include "CommonMacro.h"
#include "Log.h"


CStockBOLLArithmetic::CStockBOLLArithmetic()
{

}

CStockBOLLArithmetic::~CStockBOLLArithmetic()
{

}

#if 0
CStockBOLLData * CStockBOLLArithmetic::CalcBOLLData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN1)
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

	int n = mN1;

	std::vector<double> vec_average;
	std::vector<double> vec_up;
	std::vector<double> vec_down;

	for(int i=0;i<pKLineBaseData->m_length;i++)
	{
		vec_average.push_back(0.0);
		vec_up.push_back(0.0);
		vec_down.push_back(0.0);
	}
	double sum = 0.0;
	CalcCloseAverage(n,pKLineBaseData->vec_close_price, vec_average);
	for(int i = n - 1; i < (n + n) - 2; i++) 
	{
		double value = pKLineBaseData->vec_close_price[i] - vec_average[i];
		sum += value * value;
	}


	double prevalue = 0.0;
	for(int i = (n + n) - 2; i < pKLineBaseData->m_length; i++) 
	{
		sum -= prevalue;
		double value = pKLineBaseData->vec_close_price[i] - vec_average[i];
		sum += value * value;
		value = sqrt(sum / (double)n) *1.871;
		vec_up[i] = vec_average[i] + value;
		vec_down[i] = vec_average[i] - value;
		value = pKLineBaseData->vec_close_price[(i - n) + 1] - vec_average[(i - n) + 1];
		prevalue = value * value;
	}


	int length=vec_average.size();
	vec_average[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_average);
	vec_up[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_up);
	vec_down[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,vec_down);


	CStockBOLLData*  pStockBOLLData;
	pStockBOLLData=new CStockBOLLData();
	pStockBOLLData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin()+(mN1-1)*2,pKLineBaseData->vec_open_price.end());
	pStockBOLLData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin()+(mN1-1)*2,pKLineBaseData->vec_high_price.end());
	pStockBOLLData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin()+(mN1-1)*2,pKLineBaseData->vec_low_price.end());
	pStockBOLLData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin()+(mN1-1)*2,pKLineBaseData->vec_close_price.end());
	pStockBOLLData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin()+(mN1-1)*2,pKLineBaseData->vec_avg_price.end());
	pStockBOLLData->vec_time.assign(pKLineBaseData->vec_time.begin()+(mN1-1)*2,pKLineBaseData->vec_time.end());
	pStockBOLLData->vec_volume.assign(pKLineBaseData->vec_volume.begin()+(mN1-1)*2,pKLineBaseData->vec_volume.end());
	pStockBOLLData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin()+(mN1-1)*2,pKLineBaseData->vec_volume_price.end());
	pStockBOLLData->vec_boll.assign(vec_average.begin()+(mN1-1)*2,vec_average.end());
	pStockBOLLData->vec_up.assign(vec_up.begin()+(mN1-1)*2,vec_up.end());
	pStockBOLLData->vec_down.assign(vec_down.begin()+(mN1-1)*2,vec_down.end());
	pStockBOLLData->m_length=pStockBOLLData->vec_open_price.size();
	pStockBOLLData->m_type=mType;
	pStockBOLLData->mN=mN1;
	pStockBOLLData->strStockCode=strStockCode;
	SAFE_DELETE(pKLineBaseData);
	return pStockBOLLData;
}
#else


CStockBOLLData* CStockBOLLArithmetic::CalcBOLLData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN1)
{
	KLineBaseData* pKLineBaseData = NULL;
	int mRealNums = mNums + mN1;
	if (mType == K_LINE_DAY)
	{
		CStockDayTable* pStockDayTable;
		pStockDayTable = StockDataMgr()->GetStockDayTable(strStockCode);
		if (!pStockDayTable)
			return NULL;

		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseData(pStockDayTable, strDateTime, mRealNums);

	}
	else if (mType == K_LINE_5IN)
	{
		CStockMin5Table* pStockMin5Table;
		pStockMin5Table = StockDataMgr()->GetStockMin5Table(strStockCode);
		if (!pStockMin5Table)
			return NULL;
		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin5(pStockMin5Table, strDateTime, mRealNums);

	}
	else if (mType == K_LINE_15IN)
	{
		CStockMin5Table* pStockMin5Table;
		pStockMin5Table = StockDataMgr()->GetStockMin5Table(strStockCode);
		if (!pStockMin5Table)
			return NULL;
		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin15(pStockMin5Table, strDateTime, mRealNums);
	}
	else if (mType == K_LINE_30IN)
	{
		CStockMin5Table* pStockMin5Table;
		pStockMin5Table = StockDataMgr()->GetStockMin5Table(strStockCode);
		if (!pStockMin5Table)
			return NULL;
		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin30(pStockMin5Table, strDateTime, mRealNums);
	}
	else if (mType == K_LINE_60MIN)
	{
		CStockMin5Table* pStockMin5Table;
		pStockMin5Table = StockDataMgr()->GetStockMin5Table(strStockCode);
		if (!pStockMin5Table)
			return NULL;
		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin60(pStockMin5Table, strDateTime, mRealNums);
	}

	if (!pKLineBaseData)
		return NULL;

	int length = pKLineBaseData->vec_close_price.size();
	
	std::vector<double> vecMa = CStockBOLLArithmetic::CalcMA(mN1, pKLineBaseData->vec_close_price);

	
	std::vector<double> vecMaCor;

	for (int i = mN1; i < vecMa.size(); i++)
		vecMaCor.push_back(vecMa[i]);

	std::vector<double> vecClose;
	for (int i = mN1; i < pKLineBaseData->vec_close_price.size(); i++)
		vecClose.push_back(pKLineBaseData->vec_close_price[i]);

	std::vector<double> vecStd;
	for (int i = 0; i < mN1; i++)
		vecStd.push_back(0.0);

	for (int i = mN1; i < vecClose.size(); i++)
	{
		double sum = 0.0;
		for (int j = i - mN1 + 1; j <= i; j++)
		{
			sum += (vecClose[j] - vecMaCor[j]) * (vecClose[j] - vecMaCor[j]);
		}
		double std = sqrt(sum /mN1);
		vecStd.push_back(std);
	}

	
	std::vector<double> vecUb_t;
	for (int i = 0; i < mN1; i++)
		vecUb_t.push_back(0.0);

	for (int i = mN1; i < vecClose.size(); i++)
	{
		double ub = vecMaCor[i] + 2.0 * vecStd[i];
		vecUb_t.push_back(ub);
	}


	std::vector<double> vecLb_t;
	for (int i = 0; i < mN1; i++)
		vecLb_t.push_back(0.0);

	for (int i = mN1; i < vecClose.size(); i++)
	{
		double lb = vecMaCor[i] - 2.0 * vecStd[i];
		vecLb_t.push_back(lb);
	}

	std::vector<double> vecBoll;
	vecBoll.push_back(0.0);
	for (int i = 0; i < vecMaCor.size() - 1; i++)
		vecBoll.push_back(vecMaCor[i]);

	std::vector<double> vecUb;
	vecUb.push_back(0.0);
	for (int i = 0; i < vecUb_t.size() - 1; i++)
		vecUb.push_back(vecUb_t[i]);

	std::vector<double> vecLb;
	vecLb.push_back(0.0);
	for (int i = 0; i < vecLb_t.size() - 1; i++)
		vecLb.push_back(vecLb_t[i]);



	CStockBOLLData* pCStockBOLLData;
	pCStockBOLLData = new CStockBOLLData();
	pCStockBOLLData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin() + mN1, pKLineBaseData->vec_open_price.end());
	pCStockBOLLData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin() + mN1, pKLineBaseData->vec_high_price.end());
	pCStockBOLLData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin() + mN1, pKLineBaseData->vec_low_price.end());
	pCStockBOLLData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin() + mN1, pKLineBaseData->vec_close_price.end());
	pCStockBOLLData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin() + mN1, pKLineBaseData->vec_avg_price.end());
	pCStockBOLLData->vec_time.assign(pKLineBaseData->vec_time.begin() + mN1, pKLineBaseData->vec_time.end());
	pCStockBOLLData->vec_volume.assign(pKLineBaseData->vec_volume.begin() + mN1, pKLineBaseData->vec_volume.end());
	pCStockBOLLData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin() + mN1, pKLineBaseData->vec_volume_price.end());
	pCStockBOLLData->vec_boll = vecBoll;
	pCStockBOLLData->vec_up = vecUb;
	pCStockBOLLData->vec_down = vecLb;
	pCStockBOLLData->m_length = vecBoll.size();
	pCStockBOLLData->m_type = pKLineBaseData->m_type;
	pCStockBOLLData->mN = mN1;
	pCStockBOLLData->strStockCode = strStockCode;
	SAFE_DELETE(pKLineBaseData);
	return pCStockBOLLData;

}
#endif


std::vector<double> CStockBOLLArithmetic::CalcMA(int n, std::vector<double> vec_value)
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
			ma = (double)closeSum / n;
			vecma_value.push_back(ma);
		}
		else
		{
			vecma_value.push_back(0.0);
		}
	}

	return vecma_value;
}

void CStockBOLLArithmetic::CalcCloseAverage(int n,std::vector<double> closePrice,std::vector<double> &data)
{
	double preClose = 0.0;
	double sum = 0.0;
	for(int i = 0; i < n - 1; i++)
		sum += closePrice[i];

	for(int i = n - 1; i < closePrice.size(); i++) {
		sum -= preClose;
		sum += closePrice[i];
		data[i] = (double)(sum / (double)n);
		preClose = closePrice[(i - n) + 1]; 
	}
}