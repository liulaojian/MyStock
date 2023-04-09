#pragma once

#include "Strategy.h"

typedef struct 
{
	CString  strBeginDate;
	CString  strEndDate;
}HistoryResult;
typedef std::vector<HistoryResult *> Vec_HistoryResultList;


class CHistoryStrategy:public CStrategy
{
public:
	CHistoryStrategy();
	virtual ~CHistoryStrategy();


public:
	BOOL CreateAimStockDayVec(void);			//根据开始结束时间生成目标天表
	BOOL CreateAimStockPriceRangeVec(void);		//创建价格波动的集合
	BOOL CreateAimStockVolumeRangeVec(void);		//创建交易量波动的集合

	BOOL Init(void);


	Vec_StockDayData CreateHistoryStockDayVec(CString strBegin,CString strEnd);
	std::vector<double> CreateHistoryStockPriceRangeVec(Vec_StockDayData vecStockDayData);
	std::vector<double> CreateHistoryStockVolumeRangeVec(Vec_StockDayData vecStockDayData);

	BOOL JudgePriceRange(std::vector<double> vecPriceRange);
	BOOL JudgeVolumeRange(std::vector<double> vecVolumeRange);


public:
	BOOL TraverseStockDayData(void);			//遍历天数据 


private:

	Vec_StockDayData vecAimStockDayData;
	std::vector<double> vecAimPriceRange;				//价格波动的集合
	std::vector<double> vecAimVolumeRange;				//交易量波动的集合

	Vec_HistoryResultList vecHistoryResultList;
};