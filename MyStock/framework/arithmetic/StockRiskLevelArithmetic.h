#pragma once

//股票危险值算法类

#include "StockDayTable.h"
#include "StockMin5Table.h"
#include "zbTypeDef.h"


class CStockRiskLevelArithmetic
{
public:
	CStockRiskLevelArithmetic(CString strCode);
	virtual ~CStockRiskLevelArithmetic();

	BOOL  Init(void);
	
protected:
	CString strStockCode;
	CStockMin5Table *pStockMin5Table;
	CStockDayTable *pStockDayTable;

	CString strParaZeroDate;			//参数0 日期
	CString strParaHundredDate;			//参数100 的 日期

	CString strHighPointDate;			//高点 日期
	CString strLowPointDate;			//低点 日期

	CString strPrePointDate;			//前点 日期

	float f_x_base;						//x轴基数

	float f_y_base;						//y轴基数
};