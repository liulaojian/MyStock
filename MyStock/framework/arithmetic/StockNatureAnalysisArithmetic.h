#pragma once

//��Ʊ���Է����㷨��

#include "StockDayTable.h"
#include "StockMin5Table.h"
#include "zbTypeDef.h"

#include <vector>
#include "T_FreeVector.h"

// CDlgStockNatureAnalysis �Ի���

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
	EXP_FILTER_ALL=0,			//ȫ��
	EXP_FILTER_BIG_RISE,		//ָ������  >=3%
	EXP_FILTER_MIDDLE_RISE,		//ָ������  >=1.5%  and  <3%
	EXP_FILTER_SMALL_RISE,		//ָ��С��  >=0.5%  and <1.5%
	EXP_FILTER_MILL_RISE,		//ָ������  >=0.2%  and <0.5%
	EXP_FILTER_MIRO_RISE_FALL,	//ָ��΢�ǻ�΢��  >-0.2% and <0.2%
	EXP_FILTER_MILL_FALL,		//ָ������  >-0.5%  and <=-0.2%
	EXP_FILTER_SMALL_FALL,		//ָ��С��  >-1.5%  and <=-0.5%
	EXP_FILTER_MIDDLE_FALL,		//ָ���е�	>-3%  and <=-1.5%
	EXP_FILTER_BIG_FALL,		//ָ�����  <=-3.0%

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