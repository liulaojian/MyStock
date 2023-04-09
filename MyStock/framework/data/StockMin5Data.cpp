#include "stdafx.h"
#include "StockMin5Data.h"

CStockMin5Data::CStockMin5Data()
{


}

CStockMin5Data::~CStockMin5Data()
{

}


CString CStockMin5Data::GetDateTime(void)
{
	CString strDateTime;
	strDateTime=strDate;
	strDateTime+=" ";
	strDateTime+=strTime;
	return strDateTime;
}