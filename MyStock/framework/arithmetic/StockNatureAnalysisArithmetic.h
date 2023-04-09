#pragma once

//股票股性分析算法类

#include "StockDayTable.h"
#include "StockMin5Table.h"
#include "zbTypeDef.h"

#include <vector>
#include "T_FreeVector.h"

// CDlgStockNatureAnalysis 对话框

typedef struct 
{
	CString  strStockCode;
	CString  strStockDate;
	float    f_stock_end_price;
	float    f_stock_increase;
	float    f_stock_pre3ave_increase;
	float    f_stock_volume_increase;
	float    f_stock_pre3ave_volume_increase;
	float    f_exp_end_price;
	float    f_exp_increase;
	float    f_exp_pre3ave_increase;
	float    f_exp_volume_increase;
	float    f_exp_pre3ave_volume_increase;
}StockAnalysisInfo;

typedef std::vector<StockAnalysisInfo *> Vec_StockAnalysisInfo;



enum
{
	EXP_FILTER_ALL=0,			//全部
	EXP_FILTER_BIG_RISE,		//指数大涨  >=3%
	EXP_FILTER_MIDDLE_RISE,		//指数中涨  >=1.5%  and  <3%
	EXP_FILTER_SMALL_RISE,		//指数小涨  >=0.5%  and <1.5%
	EXP_FILTER_MILL_RISE,		//指数毫涨  >=0.2%  and <0.5%
	EXP_FILTER_MIRO_RISE_FALL,	//指数微涨或微跌  >-0.2% and <0.2%
	EXP_FILTER_MILL_FALL,		//指数毫跌  >-0.5%  and <=-0.2%
	EXP_FILTER_SMALL_FALL,		//指数小跌  >-1.5%  and <=-0.5%
	EXP_FILTER_MIDDLE_FALL,		//指数中跌	>-3%  and <=-1.5%
	EXP_FILTER_BIG_FALL,		//指数大跌  <=-3.0%

};

class CStockNatureAnalysisArthmetic
{
public:
	CStockNatureAnalysisArthmetic(CString strCode);
	virtual ~CStockNatureAnalysisArthmetic();

	BOOL  Init(void);

	void SetBeginDate(CString strVal) {strBeginDate=strVal;}
	void SetEndDate(CString strVal)  {strEndDate=strVal;}

	Vec_StockAnalysisInfo BuildStockAnalysisInfoList(int mMode);

	BOOL JudgeExpIncrease(int mMode,float f_exp_increase);

	Vec_CString BuildAnalysisResultListString(void);

	CString BuildAnalysisResultString(Vec_StockAnalysisInfo vecStockAnalysisInfo);


protected:

	
	CString strStockCode;
	CString strExpStockCode;
	CStockMin5Table *pStockMin5Table;
	CStockDayTable *pStockDayTable;

	CStockDayTable *pExpStockDayTable;
	
	CString strBeginDate;
	CString strEndDate;

	int  mBeginPos;
	int  mEndPos;

	int  mExpBeginPos;
	int  mExpEndPos;

};