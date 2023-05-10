#include "stdafx.h"
#include "StockPSYArithmetic.h"
#include "StockDataMgr.h"
#include "CommonMacro.h"

CStockPSYArithmetic::CStockPSYArithmetic()
{


}


CStockPSYArithmetic::~CStockPSYArithmetic()
{

}

CStockPSYData* CStockPSYArithmetic::CalcPSYData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN, int mN2)
{
	KLineBaseData* pKLineBaseData = NULL;

	int mRelNums = mNums + mN;
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

	

	std::vector<float> vecpsy;
	for (int i = mN; i < pKLineBaseData->m_length; i++)
	{
		int mUpNums = 0;
		for (int j = i - mN + 1; j <= i; j++)
		{
			float nowclose = pKLineBaseData->vec_close_price[j];
			float preclose = pKLineBaseData->vec_close_price[j-1];
			if (nowclose > preclose)
				mUpNums++;
		}

		float psy=(float)mUpNums / (float)mN * 100.0;
		vecpsy.push_back(psy);
	}
	std::vector<float> vecmpsy = CStockPSYArithmetic::CalcMA(mN2, vecpsy);

	
	CStockPSYData* pCStockPSYData;
	pCStockPSYData = new CStockPSYData();
	pCStockPSYData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin() + mN, pKLineBaseData->vec_open_price.end());
	pCStockPSYData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin() + mN, pKLineBaseData->vec_high_price.end());
	pCStockPSYData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin() + mN, pKLineBaseData->vec_low_price.end());
	pCStockPSYData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin() + mN, pKLineBaseData->vec_close_price.end());
	pCStockPSYData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin() + mN, pKLineBaseData->vec_avg_price.end());
	pCStockPSYData->vec_time.assign(pKLineBaseData->vec_time.begin() + mN, pKLineBaseData->vec_time.end());
	pCStockPSYData->vec_volume.assign(pKLineBaseData->vec_volume.begin() + mN, pKLineBaseData->vec_volume.end());
	pCStockPSYData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin() + mN, pKLineBaseData->vec_volume_price.end());
	pCStockPSYData->vec_psy = vecpsy;
	pCStockPSYData->vec_mpsy = vecmpsy;
	pCStockPSYData->m_length = vecpsy.size();
	pCStockPSYData->m_type = pKLineBaseData->m_type;
	pCStockPSYData->mN = mN;
	pCStockPSYData->mN2 = mN2;
	pCStockPSYData->strStockCode = strStockCode;
	SAFE_DELETE(pKLineBaseData);
	return pCStockPSYData;

}


std::vector<float> CStockPSYArithmetic::CalcMA(int n, std::vector<float> vecmfi)
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