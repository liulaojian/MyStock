#include "stdafx.h"
#include "HistoryCmpMethod.h"

CHistoryCmpMethod::CHistoryCmpMethod(CString strName): CCmpMethod(strName)
{
	pStockDayTable=NULL;
	strBeginDate="";
	strEndDate="";
}

CHistoryCmpMethod::~CHistoryCmpMethod()
{

}