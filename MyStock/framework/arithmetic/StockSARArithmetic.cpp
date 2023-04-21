#include "stdafx.h"
#include "StockSARArithmetic.h"

#include "StockDataMgr.h"
#include "CommonMacro.h"

CStockSARArithmetic::CStockSARArithmetic()
{

}

CStockSARArithmetic::~CStockSARArithmetic()
{

}

/*
CStockSARData* CStockSARArithmetic::CalcSARData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN)
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


	int n=mN;

	if(n > pKLineBaseData->m_length || n < 3)
		return NULL;

	std::vector<double> sar;
	std::vector<double> sign;
	sar.assign(pKLineBaseData->m_length,0.0);
	sign.assign(pKLineBaseData->m_length,0.0);
	double xs = 0.02f;
	
	
	if(pKLineBaseData->vec_close_price[n - 1] < pKLineBaseData->vec_close_price[n - 2]) 
	{
		if(pKLineBaseData->vec_close_price[n - 2] <= pKLineBaseData->vec_close_price[n - 3])
			sign[n - 1] = 1.0f;
		else
			sign[n - 1] = 17.0f;	//17.0f;
	} 
	else
	{
		if(pKLineBaseData->vec_close_price[n - 1] > pKLineBaseData->vec_close_price[n - 2]) 
		{
			if(pKLineBaseData->vec_close_price[n - 2] >= pKLineBaseData->vec_close_price[n - 3])
				sign[n - 1] = 0.0f;
			else
				sign[n - 1] = 16.0f;	//16.0f;
		} 
		else
		{
			if(pKLineBaseData->vec_close_price[n - 2] < pKLineBaseData->vec_close_price[n - 3])
				sign[n - 1] = 1.0f;
			else
			{
				if(pKLineBaseData->vec_close_price[n - 2] > pKLineBaseData->vec_close_price[n - 3])
					sign[n - 1] = 0.0f;
				else
					sign[n - 1] = 20.0f;	//16.0f;
			}
		}
	}

	if(sign[n - 1] == 1.0f || sign[n - 1] == 17.0f)		//17.0f
	{
		sar[n - 1] = -1E+036F;
		for(int j = n - 1; j >= 0; j--) 
			sar[n - 1] = max(sar[n - 1], pKLineBaseData->vec_high_price[j]);

	} 
	else 
	{
		sar[n - 1] = 1E+036F;
		for(int j = n - 1; j >= 0; j--) 
			sar[n - 1] = min(sar[n - 1], pKLineBaseData->vec_low_price[j]);
	}

	
	for(int i = n; i < pKLineBaseData->m_length; i++)
	{
		if(sign[i - 1] == 0.0F || sign[i - 1] == 16.0f)		//16.0f
		{
			if(pKLineBaseData->vec_close_price[i] < sar[i - 1]) 
			{
				sar[i] = -1E+036F;
				for(int j = i; j > i - n; j--)
					sar[i] = max(sar[i], pKLineBaseData->vec_high_price[j]);

				sign[i] = 17.0f;
				xs = 0.02F;
			} 
			else 
			{
				sar[i] = sar[i - 1] + xs * (pKLineBaseData->vec_high_price[i - 1] - sar[i - 1]);
				xs = xs >= 0.2f ? xs : xs + 0.02F;
				sign[i] = 0.0f;
			}
		} 
		else
		{
			if(pKLineBaseData->vec_close_price[i] > sar[i - 1]) 
			{
				sar[i] = 1E+036F;
				for(int j = i; j > i - n; j--)
					sar[i] = min(sar[i], pKLineBaseData->vec_low_price[j]);

				sign[i] = 16.0f;
				xs = 0.02f;
			} 
			else 
			{
				sar[i] = sar[i - 1] + xs * (pKLineBaseData->vec_low_price[i - 1] - sar[i - 1]);
				xs = xs >= 0.2f ? xs : xs + 0.02f;
				sign[i] = 1.0f;
			}
		}
	}


	int length=sar.size();
	sar[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,sar);
	
	CStockSARData *pStockSARData=new CStockSARData();
	pStockSARData->strStockCode=strStockCode;
	pStockSARData->mN=mN;
	pStockSARData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin()+mN-1,pKLineBaseData->vec_avg_price.end());
	pStockSARData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin()+mN-1,pKLineBaseData->vec_open_price.end());
	pStockSARData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin()+mN-1,pKLineBaseData->vec_high_price.end());
	pStockSARData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin()+mN-1,pKLineBaseData->vec_low_price.end());
	pStockSARData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin()+mN-1,pKLineBaseData->vec_close_price.end());
	pStockSARData->vec_time.assign(pKLineBaseData->vec_time.begin()+mN-1,pKLineBaseData->vec_time.end());
	pStockSARData->vec_volume.assign(pKLineBaseData->vec_volume.begin()+mN-1,pKLineBaseData->vec_volume.end());
	pStockSARData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin()+mN-1,pKLineBaseData->vec_volume_price.end());
	pStockSARData->m_length=pStockSARData->vec_time.size();
	pStockSARData->m_type=mType;
	pStockSARData->vec_sar.assign(sar.begin()+mN-1,sar.end());

	SAFE_DELETE(pKLineBaseData);

	return pStockSARData;
}*/

#define LONG	0
#define SHORT   1

static float MAX_(float a, float b)
{
	return a > b ? a : b;
}

static float MIN_(float a, float b)
{
	return a < b ? a : b;
}

CStockSARData* CStockSARArithmetic::CalcSARData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN)
{
	KLineBaseData* pKLineBaseData = NULL;
	
	int mRelNums = mNums + mN+1;


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


	std::vector<float> vec_sar;
	float preSip;
	float af = 0.02;
	int flag = LONG;
	float sar=0.0;
	float sip=0.0;
	float preSar=0.0;
	float bb;
	int i;
	for (int n = 1; n < pKLineBaseData->m_length; n++)
	{
		float node_low = pKLineBaseData->vec_low_price[n];
		float node_high = pKLineBaseData->vec_high_price[n];

		float preNode_low = pKLineBaseData->vec_low_price[n-1];
		float preNode_high = pKLineBaseData->vec_high_price[n-1];

		i = n - 1;
		if (i == 0)
		{
			sar = pKLineBaseData->vec_low_price[n];
			sip = pKLineBaseData->vec_high_price[n];
			bb = 0;
		}
		else if (i < (mN - 1))
		{
			sar = MIN_(sar, node_low);
			bb = 0;
		}
		else if (i == (mN - 1))
		{
			sar = MIN_(sar, node_low);
			bb = sar;
		}

		if (i >= mN)
		{
			preSip = sip;
			if (flag ==LONG) 
			{
				if (node_low < preSar) 
				{
					flag = SHORT;
					sip = node_low;
					af = 0.02;
					sar = MAX_(node_high, preNode_high);
					sar = MAX_(sar, preSip + af * (sip - preSip));
				}
				else 
				{
					flag = LONG;
					if (node_high > preSip) {
						sip = node_high;
						af = MIN_(af + 0.02, 0.2);
					
					}
					sar = MIN_(node_low, preNode_low);
					sar = MIN_(sar, preSar + af * (sip - preSar));
				}
			}
			else 
			{
				if (node_high > preSar) 
				{
					flag = LONG;
					sip = node_high;
					af = 0.02;
					sar = MIN_(node_low, preNode_low);
					sar = MIN_(sar, preSar + af * (sip - preSip));
				}
				else 
				{
					flag = SHORT;
					if (node_low < preSip) {
						sip = node_low;
						af = MIN_(af + 0.02, 0.2);
					}
					sar = MAX_(node_high, preNode_high);
					sar = MAX_(sar, preSar + af * (sip - preSar));
				}
			}
			bb = sar;
			vec_sar.push_back(bb);
		}

		preSar = sar;

	}


	CStockSARData* pCStockSARData;
	pCStockSARData = new CStockSARData();
	pCStockSARData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin() + mN+1, pKLineBaseData->vec_open_price.end());
	pCStockSARData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin() + mN + 1, pKLineBaseData->vec_high_price.end());
	pCStockSARData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin() + mN + 1, pKLineBaseData->vec_low_price.end());
	pCStockSARData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin() + mN + 1, pKLineBaseData->vec_close_price.end());
	pCStockSARData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin() + mN + 1, pKLineBaseData->vec_avg_price.end());
	pCStockSARData->vec_time.assign(pKLineBaseData->vec_time.begin() + mN + 1, pKLineBaseData->vec_time.end());
	pCStockSARData->vec_volume.assign(pKLineBaseData->vec_volume.begin() + mN + 1, pKLineBaseData->vec_volume.end());
	pCStockSARData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin() + mN + 1, pKLineBaseData->vec_volume_price.end());
	pCStockSARData->vec_sar = vec_sar;
	pCStockSARData->m_length = vec_sar.size();
	pCStockSARData->m_type = pKLineBaseData->m_type;
	pCStockSARData->mN = mN;
	pCStockSARData->strStockCode = strStockCode;
	SAFE_DELETE(pKLineBaseData);
	return pCStockSARData;

}