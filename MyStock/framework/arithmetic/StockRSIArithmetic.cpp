#include "stdafx.h"
#include "StockRSIArithmetic.h"
#include "StockDataMgr.h"
#include "CommonMacro.h"
#include<algorithm>
CStockRSIArithmetic::CStockRSIArithmetic()
{

}

CStockRSIArithmetic::~CStockRSIArithmetic()
{

}


 CStockRSIData* CStockRSIArithmetic::CalcRSIData(CString strStockCode,CString strDateTime,int mNums,int mType,int mN1,int mN2,int mN3)
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

	 CStockRSIData *pStockRSIData=NULL;

	  std::vector<double> rsi1=CalcRSI(mN1,pKLineBaseData);
	   std::vector<double> rsi2=CalcRSI(mN2,pKLineBaseData);
	    std::vector<double> rsi3=CalcRSI(mN3,pKLineBaseData);

		int length=rsi1.size();
		rsi1[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,rsi1);
		rsi2[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,rsi2);
		rsi3[length-1]=CKLineDataBean::CalcDateTimeCorrect(strDateTime,mType,rsi3);

		int maxN=max(mN1,mN2);
		maxN=max(maxN,mN3);
		pStockRSIData=new CStockRSIData();
		pStockRSIData->mN1=mN1;
		pStockRSIData->mN2=mN2;
		pStockRSIData->mN3=mN3;
		pStockRSIData->vec_rsi_1_value.assign(rsi1.begin()+maxN-1,rsi1.end());
		pStockRSIData->vec_rsi_2_value.assign(rsi2.begin()+maxN-1,rsi2.end());
		pStockRSIData->vec_rsi_3_value.assign(rsi3.begin()+maxN-1,rsi3.end());

		pStockRSIData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin()+maxN-1,pKLineBaseData->vec_avg_price.end());
		pStockRSIData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin()+maxN-1,pKLineBaseData->vec_open_price.end());
		pStockRSIData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin()+maxN-1,pKLineBaseData->vec_high_price.end());
		pStockRSIData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin()+maxN-1,pKLineBaseData->vec_low_price.end());
		pStockRSIData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin()+maxN-1,pKLineBaseData->vec_close_price.end());
		pStockRSIData->vec_time.assign(pKLineBaseData->vec_time.begin()+maxN-1,pKLineBaseData->vec_time.end());
		pStockRSIData->vec_volume.assign(pKLineBaseData->vec_volume.begin()+maxN-1,pKLineBaseData->vec_volume.end());
		pStockRSIData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin()+maxN-1,pKLineBaseData->vec_volume_price.end());

		pStockRSIData->m_length=pStockRSIData->vec_rsi_3_value.size();
		pStockRSIData->m_type=mType;
		pStockRSIData->strStockCode=strStockCode;

		SAFE_DELETE(pKLineBaseData);

	 return pStockRSIData;
 }

 std::vector<double> CStockRSIArithmetic::CalcRSI(int n,KLineBaseData *pKLineBaseData)
 {
	 std::vector<double> rsi;
	 

	 if(pKLineBaseData==NULL)
		 return rsi;

	 if(n > pKLineBaseData->m_length || n < 1)
		 return rsi;
 

	 double lastClosePx =pKLineBaseData->vec_close_price[0];
	 double lastSm=0.0;
	 double lastSa=0.0;

	 for(int i=1;i<pKLineBaseData->m_length; i++) 
	 {
		 double c=pKLineBaseData->vec_close_price[i];
		 double m=max(c-lastClosePx,0);
		 double a=fabs(c-lastClosePx);
		 
		 int d=n;

		 lastSm = (m + (d - 1) * lastSm)/ d;
		 lastSa = (a + (d - 1) * lastSa) / d;
		 if (lastSa!= 0) {
			 rsi.push_back(lastSm/lastSa * 100);
		 } else {
			  rsi.push_back(0);
		 }
		 lastClosePx = c;
	 }
	 return rsi;


 }