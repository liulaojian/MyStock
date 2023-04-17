#include "stdafx.h"
#include "StockMFIArithmetic.h"
#include "StockDataMgr.h"
#include "CommonMacro.h"
#include "T_Queue.h"
CStockMFIArithmetic::CStockMFIArithmetic()
{


}


CStockMFIArithmetic::~CStockMFIArithmetic()
{

}

CStockMFIData* CStockMFIArithmetic::CalcMFIData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN)
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

	std::vector<float> typValues;

	for (int i = 0; i < pKLineBaseData->m_length; i++)
	{
		float typ = (pKLineBaseData->vec_high_price[i] + pKLineBaseData->vec_low_price[i] + pKLineBaseData->vec_close_price[i]) / 3.0;
		typValues.push_back(typ);
	}

	std::vector<float> vecmfi;
	for (int i = mN; i < pKLineBaseData->m_length; i++)
	{
		float pstValueN = 0.0;
		float ntvValueN = 0.0;
		for (int j = i - mN + 1; j <= i; j++)
		{
			float nowtyp = typValues[j];
			float pretyp = typValues[j - 1];
			int voulme = pKLineBaseData->vec_volume[j];
			float pstValue = nowtyp > pretyp ? nowtyp * voulme : 0.0;
			float ntvValue = nowtyp < pretyp ? nowtyp * voulme : 0.0;
			pstValueN += pstValue;
			ntvValueN += ntvValue;
		}

		float v1Value = pstValueN / ntvValueN;
		float mfi = 100.0 - (100.0 / (1.0 + v1Value));
		vecmfi.push_back(mfi);
	}


	CStockMFIData* pCStockMFIData;
	pCStockMFIData = new CStockMFIData();
	pCStockMFIData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin() + mN , pKLineBaseData->vec_open_price.end());
	pCStockMFIData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin() + mN , pKLineBaseData->vec_high_price.end());
	pCStockMFIData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin() + mN , pKLineBaseData->vec_low_price.end());
	pCStockMFIData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin() + mN , pKLineBaseData->vec_close_price.end());
	pCStockMFIData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin() + mN , pKLineBaseData->vec_avg_price.end());
	pCStockMFIData->vec_time.assign(pKLineBaseData->vec_time.begin() + mN , pKLineBaseData->vec_time.end());
	pCStockMFIData->vec_volume.assign(pKLineBaseData->vec_volume.begin() + mN , pKLineBaseData->vec_volume.end());
	pCStockMFIData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin() + mN, pKLineBaseData->vec_volume_price.end());
	pCStockMFIData->vec_mfi = vecmfi;
	pCStockMFIData->m_length = vecmfi.size();
	pCStockMFIData->m_type = pKLineBaseData->m_type;
	pCStockMFIData->mN = mN;
	pCStockMFIData->strStockCode = strStockCode;
	SAFE_DELETE(pKLineBaseData);
	return pCStockMFIData;

}


std::vector<float> CStockMFIArithmetic::CalcMA(int n, std::vector<float> vecmfi)
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