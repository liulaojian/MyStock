#pragma once
#include "StockDayTable.h"
class CStrategy
{
public:
	CStrategy();
	virtual ~CStrategy();

public:

	void  SetStockDayTable(CStockDayTable *pTable)  {pStockDayTable=pTable;}

	CStockDayTable * GetStockDayTable(void) {return pStockDayTable;}

	void  SetBeginDayDate(CString strVal)  {strBeginDayDate=strVal;}
	CString GetBeginDayDate(void) {return strBeginDayDate;}

	void SetEndDayDate(CString strVal) {strEndDayDate=strVal;}
	CString GetEndDayDate(void) {return strEndDayDate;}

protected:
	CStockDayTable *pStockDayTable;
	CString strBeginDayDate;
	CString strEndDayDate;
};