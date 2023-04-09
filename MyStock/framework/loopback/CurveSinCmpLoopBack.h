#pragma once

#include "HistoryLoopBack.h"
#include "CurveSinCmpMethod.h"
#include "StockDayTable.h"
enum
{
	X_SCALE_AVE_1_20=0,
	X_SCALE_AVE_1_30=1,
	X_SCALE_AVE_1_40=2,
};

class CCurveSinCmpLoopBack:public CHistoryLoopBack
{
public:
	CCurveSinCmpLoopBack();
	virtual ~CCurveSinCmpLoopBack();


public:
	virtual BOOL Init(void);

	virtual BOOL doLoopBack(void);

public:
	BOOL ParseCmpMethodParas(void);

	BOOL doSingleCurveSinCmp(void);


private:
	int		mXScaleMode;
	double  f_gate_percent;			//最后比较时的百分比阀值
	int     mEquGateNums;
	CCurveSinCmpMethod *pCurveSinCmpMethod;

	CStockDayTable *pStockDayTable;
	CStockDayTable *pStockExpDayTable;

private:
	float CalcXScaleAveValue(int mBeginPos,int mEndPos,int mXScaleMode,CStockDayTable *pTable);		//计算X轴平均值

	CmpMethodParas BuildCurveSinCmpMethodParas(float f_x_scale);

	Vec_HistoryResultList CalcExpCurveSinCmpMethod(int mBeginPos,int mEndPos);

	BOOL  doHandleExpHistoryResultList(Vec_HistoryResultList vecHistoryResultList);

	
	float CalcNextInCrease(CString strDate);		//计算下一日的涨幅

	BOOL BuyDestStock(CString strDate);			//购买股票

	BOOL SaleDestStock(CString strDate);			//卖出股票


private:
	int mLoopBackStockBeginPos;
	int mLoopBackStockEndPos;

	int mLoopBackExpBeginPos;
	int mLoopBackExpEndPos;

	int mLoopBackStockPos;
	int mLoopBackExpPos;

	CString strLoopBackingBeginDate;
	CString strLoopBackingEndDate;

};