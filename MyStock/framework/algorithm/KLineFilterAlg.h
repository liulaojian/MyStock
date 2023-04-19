#pragma once
#include "StockDataMgr.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "Algorithm.h"
#include <vector>
#include "DataType.h"


class CKLineFilterAlg
{

public:
	CKLineFilterAlg();
	virtual ~CKLineFilterAlg();

public:
	Vec_KLineFilterData  doFilter(CTime mDropOffTime,Vec_DropOffData & vecDropOffData);
	Vec_KLineFilterData2  doFilter2(CString strStockCode, CString strStockName, CTime mNowTime);

	KLineContinusMNData  doCalcMNPriceContiUp(CString strStockCode, CString strStockName, CTime mNowTime);


	int CalcBollType(double f_boll_up,double f_boll_middle,double f_boll_bottom,double f_close,double f_begin,double f_high,double f_low);

	//K线 4连跌 反转
	static BOOL IsKLineFourDownFilter(Vec_KLineFilterData2& vecKLineFilterData2);
	
	//十字星反转
	//阴十字星 第二日阳线包含整个阴十字星
	static BOOL  IsCrossStartRevertFilter(Vec_KLineFilterData2& vecKLineFilterData2, KLineContinusMNData & mKLineContinusMNData);
	
	//是否K线趋势走坏
	static BOOL IsKLineBadTrend(Vec_KLineFilterData2& vecKLineFilterData2);

	//K线行业
	static BOOL IsKLineIndustry(Vec_KLineFilterData2& vecKLineFilterData2);

	//神奇九转Down
	static BOOL IsKLineNineTurn(Vec_KLineFilterData2& vecKLineFilterData2);
	//神奇九转Up
	static BOOL IsKLineNineTurnUp(Vec_KLineFilterData2& vecKLineFilterData2);


	//是否K线均线Ok
	static BOOL IsKLineAveLineOk(Vec_KLineFilterData2& vecKLineFilterData2);


	//分析个股K线趋势
	static CString AnalyzeSingleKLineTrend(Vec_KLineFilterData2& vecKLineFilterData2);

	static void FreeVecKLineFilterData2(Vec_KLineFilterData2& vecKLineFilterData2);


	//倒并行K线
	static BOOL IsKLineReverse(CString strStockCode, CString strStockName,CTime mNowTime);

};