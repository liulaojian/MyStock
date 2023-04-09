//����Sin�� �Ƚ�   


#pragma once
#include <vector>
#include "HistoryCmpMethod.h"

class CCurveSinCmpMethod :public CHistoryCmpMethod
{
public:
	CCurveSinCmpMethod();
	virtual ~CCurveSinCmpMethod();

public:
	virtual BOOL Init(void);
	virtual BOOL TraverseData(void);


private:
	BOOL CreateAimSinValVec(void);
	BOOL CreateAimStockDayDataVec(void);
	Vec_StockDayData CreateHistoryStockDayVec(CString strBegin,CString strEnd);
	std::vector<double> CreateHistoryStockSinValVec(Vec_StockDayData vecStockDayData);

	BOOL JudgeSinVal(std::vector<double> vecSinVal);


	BOOL  ParseCmpMethodParas(void);

private:
	double  f_x_scale;			//X  ��λ����
	double  f_gate_percent;			//���Ƚ�ʱ�İٷֱȷ�ֵ
	int     mEquGateNums;

	std::vector<double> vecAimSinVal;
	Vec_StockDayData vecAimStockDayData;

	
};