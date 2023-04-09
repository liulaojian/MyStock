#include "stdafx.h"
#include "NetStock.h"
#include "Log.h"
//#include <json/json.h>
#include <regex>  
#include "Convert.h"

#include "StockDataMgr.h"

CNetStock::CNetStock()
{

}

CNetStock::~CNetStock()
{

}



CString CNetStock::GetNearestStockMin5HttpData(CString strStockCode,int mNums)
{

	CString strHttpInfo;

	strHttpInfo.Format("symbol=%s&scale=5&ma=no&datalen=%d",strStockCode,mNums);
	
	CString strResult=mHttp.post("http://money.finance.sina.com.cn/quotes_service/api/json_v2.php/CN_MarketData.getKLineData",strHttpInfo);
	return strResult;
}



Vec_StockMin5Data CNetStock::ParseNearestStockMin5HttpData(CString strHttpData,CString strStockCode)
{
	Vec_StockMin5Data vecStockMin5Data;
	/*Json::Value root_value;
	Json::Reader reader;
	
	int n = strHttpData.Replace("{", "{\"" );
	n = strHttpData.Replace(":\"", "\":\"" );
	n = strHttpData.Replace("\",", "\",\"" );

//	strHttpData="[{\"day\":\"2018-02-02 14:55:00\",\"open\":\"39.090\",\"high\":\"39.100\",\"low\":\"39.000\",\"close\":\"39.040\",\"volume\":\"20300\"},{\"day\":\"2018-02-02 15:00:00\",\"open\":\"39.090\",\"high\":\"39.140\",\"low\":\"39.000\",\"close\":\"39.140\",\"volume\":\"92909\"}]";
	
	//strHttpData="[{day:2018-02-02 14:55:00,open:39.090,high:39.100,low:39.000,close:39.040,volume:20300},{day:2018-02-02 15:00:00,open:39.090,high:39.140,low:39.000,close:39.140,volume:92909}]";
	if(reader.parse((LPCTSTR)strHttpData,root_value))
	{
		int size=root_value.size();
		for(int i=0;i<size;i++)
		{
			CString strDateTime=root_value[i]["day"].asString().c_str();
			CString strOpen=root_value[i]["open"].asString().c_str();
			CString strHigh=root_value[i]["high"].asString().c_str();
			CString strLow=root_value[i]["low"].asString().c_str();
			CString strClose=root_value[i]["close"].asString().c_str();
			CString strVolume=root_value[i]["volume"].asString().c_str();

			CStringArray arryTemp;
			StringSplit(strDateTime,arryTemp,' ');


			if(arryTemp.GetSize()==2)
			{
				CString strDate=arryTemp.GetAt(0);
				CString strTime=arryTemp.GetAt(1);

				strDate.Trim();
				strDate.Replace("-","/");

				strTime.Trim();
				strTime=strTime.Left(5);
				strTime.Replace(":","");

				float  fBeginPrice=atof((LPCSTR)strOpen);
				float  fMaxPrice=atof((LPCSTR)strHigh);
				float  fMinPrice=atof((LPCSTR)strLow);
				float  fEndPrice=atof((LPCSTR)strClose);
				long   mTotalVolume=atol((LPCSTR)strVolume);

				float  fTotalPrice;
				
				if(StockDataMgr()->IsExpStock(strStockCode))
				{
					fTotalPrice=12.0*mTotalVolume;
				}
				else
				{
					fTotalPrice=((fEndPrice+fMinPrice+fMaxPrice)/3.0)*mTotalVolume;
				}
				

				
				CStockMin5Data *pStockMin5Data=new CStockMin5Data();
				pStockMin5Data->SetDate(strDate);
				pStockMin5Data->SetTime(strTime);
				pStockMin5Data->SetBeginPrice(fBeginPrice);
				pStockMin5Data->SetMaxPrice(fMaxPrice);
				pStockMin5Data->SetMinPrice(fMinPrice);
				pStockMin5Data->SetEndPrice(fEndPrice);
				pStockMin5Data->SetTotalVolume(mTotalVolume);
				pStockMin5Data->SetTotalPrice(fTotalPrice);
				vecStockMin5Data.push_back(pStockMin5Data);
			}



		}

	}
	 */
	
	return vecStockMin5Data;
}