#pragma once

#include "StockMin5Table.h"
#include "StockDayTable.h"
#include "MyTimer.h"
class CNewStockMonitor
{
public:
	CNewStockMonitor(CString stockCode);
	virtual ~CNewStockMonitor();

public:
	BOOL Init(void);

	BOOL Run(void);
private:
	CString strStockCode;
	CStockMin5Table *pStockMin5Table;
	CStockDayTable *pStockDayTable;
	BOOL bRun;
	BOOL bInited;
	CMyTimerMS st5MinTimer;
};