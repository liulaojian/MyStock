#pragma once

#include "CmpMethod.h"

#include "StockDayTable.h"

class CHistoryCmpMethod :public CCmpMethod
{
public:
	CHistoryCmpMethod(CString strName);
	virtual ~CHistoryCmpMethod();

	void SetStockDayTable(CStockDayTable *pTable) {pStockDayTable=pTable;}

	void SetBeginDate(CString strVal)  {strBeginDate=strVal;}

	void SetEndDate(CString strVal) {strEndDate=strVal;}

public:
	virtual BOOL Init(void)=0;
	virtual BOOL TraverseData(void)=0;


public:
	Vec_HistoryResultList  GetHistoryResultList(void)  {return vecHistoryResultList;}

protected:

	CStockDayTable *pStockDayTable;

	CString strBeginDate;
	CString strEndDate;

	Vec_HistoryResultList vecHistoryResultList;

};