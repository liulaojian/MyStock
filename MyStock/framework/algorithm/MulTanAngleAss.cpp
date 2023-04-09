#include "stdafx.h"
#include "MulTanAngleAss.h"
#include "TanAngleAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
CMulTanAngleAss::CMulTanAngleAss()
{


}


CMulTanAngleAss::~CMulTanAngleAss()
{


}

Vec_TanAngleData  CMulTanAngleAss::doFilter(Vec_TanAngleData vecTanAngleData,CTime mDropOffTime)
{
	Vec_TanAngleData vecResult;
	TanAngleData *pTanAngleData=NULL;
	CStockDayTable*pExpStockDayTable=NULL;
	CStockDayTable *pStockDayTable=NULL;
	pExpStockDayTable=StockDataMgr()->GetStockDayTable("SH000001");

	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];
		pStockDayTable=StockDataMgr()->GetStockDayTable(pTanAngleData->strStockCode);
		CString strNowDate=pStockDayTable->GetNearestStockDayDate(mDropOffTime);

		

		CStockRSIData* pStockRSIData=NULL;
		pStockRSIData=CStockRSIArithmetic::CalcRSIData(pTanAngleData->strStockCode,strNowDate,125,K_LINE_DAY,6,12,24); 
		if(!pStockRSIData)
			continue;

		int rsi_size=pStockRSIData->vec_rsi_1_value.size();
		int size=pStockRSIData->vec_close_price.size();
		double f_pre_3_close_price=pStockRSIData->vec_close_price[size-3];
		double f_now_close_proce=pStockRSIData->vec_close_price[size-1];

		double f_now_3_per=(f_now_close_proce-f_pre_3_close_price)*100.0/f_pre_3_close_price;

		printf("%s  %f\n",pTanAngleData->strStockCode,f_now_3_per);
		BOOL bOk=FALSE;
		if(f_now_3_per<=-12.0)
			bOk=TRUE;

		/*if(!bOk)
		{
			double f_pre_2_close_price=pStockRSIData->vec_close_price[size-2];

			double f_now_2_per=(f_now_close_proce-f_pre_2_close_price)*100.0/f_pre_2_close_price;
			if(f_now_2_per<=-9.0)
				bOk=TRUE;

		}*/

		if(!bOk)
		{

			double f_rsi1=pStockRSIData->vec_rsi_1_value[rsi_size-1];
			if(f_rsi1<20.0)
				bOk=TRUE;

		}

		if(!bOk)
			continue;

		vecResult.push_back(pTanAngleData);
	}


	return vecResult;

}
