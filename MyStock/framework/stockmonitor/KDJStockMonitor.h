#pragma once
#include "StockMonitor.h"
#include "MyTimer.h"
#include "StockDataMgr.h"
#include <vector>


enum
{
	STOCK_SNIPER_K60MIN_KDJ_ZERO_CCI_ZERO=0,
	STOCK_SNIPER_K60MIN_CCI_MINUS_50,
	STOCK_SNIPER_K60MIN_SAR,
};


class CKDJStockMonitor:public CStockMonitor
{
public:
	CKDJStockMonitor(Vec_CString vecStockList);
	virtual ~CKDJStockMonitor();


	virtual BOOL Init(void);

	virtual BOOL beginMonitor(void);

	virtual BOOL Process(void);

public:

	BOOL doMonitor(void);

	void SetStockSniperType(int mSinperType) {mStockSniperType=mSinperType;}
	int  GetStockSniperType(void) {return mStockSniperType;}


	long mMonitorLogNums;
private:
	CMyTimerMS stRrocessTimer;

	int mPos;

	int  mMin5LoopBackNowPos;

	int mStockSniperType;

	CStockMin5Data *pCurLoopBackStockMin5Data;

	
};
typedef std::vector<CKDJStockMonitor *> Vec_KDJStockMonitor;
