#include "stdafx.h"
#include "StockCRAtithmetic.h"
#include "StockDataMgr.h"
#include "CommonMacro.h"
#include "T_Queue.h"
CStockCRArithmetic::CStockCRArithmetic()
{


}


CStockCRArithmetic::~CStockCRArithmetic()
{

}


CStockCRData* CStockCRArithmetic::CalcCRData(CString strStockCode, CString strDateTime, int mNums, int mType, int mCrNum)
{
	KLineBaseData* pKLineBaseData = NULL;

	int mRelNums = mNums + 1;
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


	float highSubPreMidSum = 0.0;
	float preMidSubLowSum = 0.0;

	CQueue<float> vec_riseList;
	CQueue<float> vec_fallList;

	std::vector<float> vec_cr_value;

	for (int i = 1; i < pKLineBaseData->m_length; i++)
	{
		double preMid = (pKLineBaseData->vec_high_price[i - 1] + pKLineBaseData->vec_low_price[i - 1]) / 2.0;
		double highSubPreMid = pKLineBaseData->vec_high_price[i] - preMid > 0.0 ? pKLineBaseData->vec_high_price[i] - preMid : 0.0;
		vec_riseList.push(highSubPreMid);
		highSubPreMidSum += highSubPreMid;
		double preMidSubLow = preMid - pKLineBaseData->vec_low_price[i] > 0.0 ? preMid - pKLineBaseData->vec_low_price[i] : 0.0;
		vec_fallList.push(preMidSubLow);
		preMidSubLowSum += preMidSubLow;

		if (preMidSubLowSum !=0.0) {
			float cr = highSubPreMidSum / preMidSubLowSum * 100;
			vec_cr_value.push_back(cr);
		}

		if (vec_riseList.size() == mCrNum) {
			float t= vec_riseList.pop();
			highSubPreMidSum = highSubPreMidSum - t;
		}

		if (vec_fallList.size() == mCrNum) {
			float t = vec_fallList.pop();
			preMidSubLowSum = preMidSubLowSum - t;
		}
	}

	CStockCRData* pCStockCRData;
	pCStockCRData = new CStockCRData();
	pCStockCRData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin() + 1, pKLineBaseData->vec_open_price.end());
	pCStockCRData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin() + 1, pKLineBaseData->vec_high_price.end());
	pCStockCRData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin() + 1, pKLineBaseData->vec_low_price.end());
	pCStockCRData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin() + 1, pKLineBaseData->vec_close_price.end());
	pCStockCRData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin() + 1, pKLineBaseData->vec_avg_price.end());
	pCStockCRData->vec_time.assign(pKLineBaseData->vec_time.begin() + 1, pKLineBaseData->vec_time.end());
	pCStockCRData->vec_volume.assign(pKLineBaseData->vec_volume.begin() + 1, pKLineBaseData->vec_volume.end());
	pCStockCRData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin() + 1, pKLineBaseData->vec_volume_price.end());
	pCStockCRData->vec_cr = vec_cr_value;
	pCStockCRData->m_length = vec_cr_value.size();
	pCStockCRData->m_type = pKLineBaseData->m_type;
	pCStockCRData->mCRNum = mCrNum;
	pCStockCRData->strStockCode = strStockCode;
	SAFE_DELETE(pKLineBaseData);
	return pCStockCRData;

}


std::vector<float> CStockCRArithmetic::CalcMA(int n, std::vector<float> veccr)
{
	std::vector<float> vecma_value;
	double ma;
	double closeSum = 0.0;
	int period;
	for (int i = 0; i < veccr.size(); i++) {
		closeSum += veccr[i];
		if (i >= (n - 1)) {
			period = i - n;
			if (period >= 0) {
				closeSum -= veccr[period];
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