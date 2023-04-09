#pragma once
#include <vector>

#include "StockMonitorData.h"
// ��Ʊ�ѻ���
class CStockSniper
{

public:
	CStockSniper(CString strCode);
	virtual ~CStockSniper();

	virtual BOOL SniperAnalyze(BOOL bLoopBackMode)=0;

	virtual CString GetSniperAnalyzeResult(void)=0;

public:
	//���������ں���Ƿ������ڻز�
	BOOL CalcNext4PeridRange(CString strDateTime,int mKLineType,int mPeriodNums,double & fNextRange);
	void SetStockMonitorData(CStockMonitorData *pMonitorData) {pStockMonitorData=pMonitorData;}
protected:
	CString strStockCode;

	CStockMonitorData *pStockMonitorData;
};