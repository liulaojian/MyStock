#pragma once

//��ƱΣ��ֵ�㷨��

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

	CString strParaZeroDate;			//����0 ����
	CString strParaHundredDate;			//����100 �� ����

	CString strHighPointDate;			//�ߵ� ����
	CString strLowPointDate;			//�͵� ����

	CString strPrePointDate;			//ǰ�� ����

	float f_x_base;						//x�����

	float f_y_base;						//y�����
};