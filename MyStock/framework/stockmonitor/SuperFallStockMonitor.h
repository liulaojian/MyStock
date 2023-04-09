#pragma once
#include "StockMonitor.h"
#include "MyTimer.h"

class CSuperFallStockMonitor:public CStockMonitor
{
public:
	CSuperFallStockMonitor(CString strCode,CString strExpCode);
	virtual ~CSuperFallStockMonitor();


	virtual BOOL Init(void);

	virtual BOOL beginMonitor(void);

	virtual BOOL Process(void);

public:

	BOOL doMonitor(void);

private:
	CMyTimerMS stRrocessTimer;

};