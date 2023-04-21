#include "stdafx.h"
#include "StockVRArithmetic.h"
#include "StockDataMgr.h"
#include "CommonMacro.h"

CStockVRArithmetic::CStockVRArithmetic()
{


}


CStockVRArithmetic::~CStockVRArithmetic()
{

}

CStockVRData* CStockVRArithmetic::CalcVRData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN)
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

	
	std::vector<float> vecvr;
	for (int i = mN; i < pKLineBaseData->m_length; i++)
	{
		
		int uptoatlvolume = 0;
		int downtoatlvolume = 0;
		int middletoatlvolume = 0;

		for (int j = i - mN + 1; j <= i; j++)
		{
			float nowclose = pKLineBaseData->vec_close_price[j];
			float preclose = pKLineBaseData->vec_close_price[j - 1];

			if (nowclose > preclose)
			{
				int voulme = pKLineBaseData->vec_volume[j];
				uptoatlvolume += voulme;
			}
			else if (nowclose < preclose)
			{
				int voulme = pKLineBaseData->vec_volume[j];
				downtoatlvolume += voulme;
			}
			else
			{
				int voulme = pKLineBaseData->vec_volume[j];
				middletoatlvolume += voulme;
			}
		
		}

		float vr = (float)(uptoatlvolume+ middletoatlvolume/2.0) / (float)(downtoatlvolume+ middletoatlvolume/2.0) * 100.0;

		vecvr.push_back(vr);
	}


	CStockVRData* pCStockVRData;
	pCStockVRData = new CStockVRData();
	pCStockVRData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin() + mN, pKLineBaseData->vec_open_price.end());
	pCStockVRData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin() + mN, pKLineBaseData->vec_high_price.end());
	pCStockVRData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin() + mN, pKLineBaseData->vec_low_price.end());
	pCStockVRData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin() + mN, pKLineBaseData->vec_close_price.end());
	pCStockVRData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin() + mN, pKLineBaseData->vec_avg_price.end());
	pCStockVRData->vec_time.assign(pKLineBaseData->vec_time.begin() + mN, pKLineBaseData->vec_time.end());
	pCStockVRData->vec_volume.assign(pKLineBaseData->vec_volume.begin() + mN, pKLineBaseData->vec_volume.end());
	pCStockVRData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin() + mN, pKLineBaseData->vec_volume_price.end());
	pCStockVRData->vec_vr = vecvr;
	pCStockVRData->m_length = vecvr.size();
	pCStockVRData->m_type = pKLineBaseData->m_type;
	pCStockVRData->mN = mN;
	pCStockVRData->strStockCode = strStockCode;
	SAFE_DELETE(pKLineBaseData);
	return pCStockVRData;

}


std::vector<float> CStockVRArithmetic::CalcMA(int n, std::vector<float> vecmfi)
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