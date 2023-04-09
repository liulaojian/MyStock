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
	double  f_gate_percent;			//���Ƚ�ʱ�İٷֱȷ�ֵ
	int     mEquGateNums;
	CCurveSinCmpMethod *pCurveSinCmpMethod;

	CStockDayTable *pStockDayTable;
	CStockDayTable *pStockExpDayTable;

private:
	float CalcXScaleAveValue(int mBeginPos,int mEndPos,int mXScaleMode,CStockDayTable *pTable);		//����X��ƽ��ֵ

	CmpMethodParas BuildCurveSinCmpMethodParas(float f_x_scale);

	Vec_HistoryResultList CalcExpCurveSinCmpMethod(int mBeginPos,int mEndPos);

	BOOL  doHandleExpHistoryResultList(Vec_HistoryResultList vecHistoryResultList);

	
	float CalcNextInCrease(CString strDate);		//������һ�յ��Ƿ�

	BOOL BuyDestStock(CString strDate);			//�����Ʊ

	BOOL SaleDestStock(CString strDate);			//������Ʊ


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