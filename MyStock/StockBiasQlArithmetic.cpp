#include "stdafx.h"
#include "StockBiasQlArithmetic.h"
#include "StockDataMgr.h"
#include "CommonMacro.h"

CStockBIASQLArithmetic::CStockBIASQLArithmetic()
{


}


CStockBIASQLArithmetic::~CStockBIASQLArithmetic()
{

}

CStocBIASQLData* CStockBIASQLArithmetic::CalcBiasQlData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN1, int mN2)
{
	KLineBaseData* pKLineBaseData = NULL;

	int mRelNums = mNums + mN1;
	if (mType == K_LINE_DAY)
	{
		CStockDayTable* pStockDayTable;
		pStockDayTable = StockDataMgr()->GetStockDayTable(strStockCode);
		if (!pStockDayTable)
			return NULL;

		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseData(pStockDayTable, strDateTime, mRelNums);

	}
	else if (mType == K_LINE_5IN)
	{
		CStockMin5Table* pStockMin5Table;
		pStockMin5Table = StockDataMgr()->GetStockMin5Table(strStockCode);
		if (!pStockMin5Table)
			return NULL;
		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin5(pStockMin5Table, strDateTime, mRelNums);

	}
	else if (mType == K_LINE_15IN)
	{
		CStockMin5Table* pStockMin5Table;
		pStockMin5Table = StockDataMgr()->GetStockMin5Table(strStockCode);
		if (!pStockMin5Table)
			return NULL;
		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin15(pStockMin5Table, strDateTime, mRelNums);
	}
	else if (mType == K_LINE_30IN)
	{
		CStockMin5Table* pStockMin5Table;
		pStockMin5Table = StockDataMgr()->GetStockMin5Table(strStockCode);
		if (!pStockMin5Table)
			return NULL;
		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin30(pStockMin5Table, strDateTime, mRelNums);
	}
	else if (mType == K_LINE_60MIN)
	{
		CStockMin5Table* pStockMin5Table;
		pStockMin5Table = StockDataMgr()->GetStockMin5Table(strStockCode);
		if (!pStockMin5Table)
			return NULL;
		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin60(pStockMin5Table, strDateTime, mRelNums);
	}

	if (!pKLineBaseData)
		return NULL;

	std::vector<float> vec_price_ma_Temp;
	vec_price_ma_Temp = CStockBIASQLArithmetic::CalcMA(mN1, pKLineBaseData->vec_close_price);

	std::vector<float> vec_price_maN;
	if (vec_price_ma_Temp.size() > mN1)
	{
		vec_price_maN.assign(vec_price_ma_Temp.begin()+mN1, vec_price_ma_Temp.end() );
	}

	int mCloseNums = pKLineBaseData->vec_close_price.size();
	
	std::vector<float> vec_bias;
	for (int i = mN1; i < mCloseNums; i++)
	{
		float bias = (pKLineBaseData->vec_close_price[i] - vec_price_maN[i- mN1]) / vec_price_maN[i- mN1] * 100.0;
		vec_bias.push_back(bias);
	}

	std::vector<float> vec_ql;

	std::vector < double > vec_bias_temp;
	for (int i = 0; i < vec_bias.size(); i++)
		vec_bias_temp.push_back(vec_bias[i]);

	vec_ql=CStockBIASQLArithmetic::CalcMA(mN2, vec_bias_temp);


	CStocBIASQLData* pCStocBIASQLData;
	pCStocBIASQLData = new CStocBIASQLData();
	pCStocBIASQLData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin() + mN1, pKLineBaseData->vec_open_price.end());
	pCStocBIASQLData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin() + mN1, pKLineBaseData->vec_high_price.end());
	pCStocBIASQLData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin() + mN1, pKLineBaseData->vec_low_price.end());
	pCStocBIASQLData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin() + mN1, pKLineBaseData->vec_close_price.end());
	pCStocBIASQLData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin() + mN1, pKLineBaseData->vec_avg_price.end());
	pCStocBIASQLData->vec_time.assign(pKLineBaseData->vec_time.begin() + mN1, pKLineBaseData->vec_time.end());
	pCStocBIASQLData->vec_volume.assign(pKLineBaseData->vec_volume.begin() + mN1, pKLineBaseData->vec_volume.end());
	pCStocBIASQLData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin() + mN1, pKLineBaseData->vec_volume_price.end());
	pCStocBIASQLData->vec_bias = vec_bias;
	pCStocBIASQLData->m_length = vec_bias.size();
	pCStocBIASQLData->vec_ql = vec_ql;
	pCStocBIASQLData->m_type = pKLineBaseData->m_type;
	pCStocBIASQLData->mN1 = mN1;
	pCStocBIASQLData->mN2 = mN2;
	pCStocBIASQLData->strStockCode = strStockCode;
	SAFE_DELETE(pKLineBaseData);
	return pCStocBIASQLData;
}


std::vector<float> CStockBIASQLArithmetic::CalcMA(int n, std::vector<double> vecmfi)
{
	std::vector<float> vecma_value;
	double ma;
	double closeSum = 0.0;
	int period;
	for (int i = 0; i < vecmfi.size(); i++) {
		closeSum += vecmfi[i];
		if (i >= (n - 1)) {
			period = i - n;
			if (period >= 0) {
				closeSum -= vecmfi[period];
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