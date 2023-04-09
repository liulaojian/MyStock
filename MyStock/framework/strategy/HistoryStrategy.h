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
	BOOL CreateAimStockDayVec(void);			//���ݿ�ʼ����ʱ������Ŀ�����
	BOOL CreateAimStockPriceRangeVec(void);		//�����۸񲨶��ļ���
	BOOL CreateAimStockVolumeRangeVec(void);		//���������������ļ���

	BOOL Init(void);


	Vec_StockDayData CreateHistoryStockDayVec(CString strBegin,CString strEnd);
	std::vector<double> CreateHistoryStockPriceRangeVec(Vec_StockDayData vecStockDayData);
	std::vector<double> CreateHistoryStockVolumeRangeVec(Vec_StockDayData vecStockDayData);

	BOOL JudgePriceRange(std::vector<double> vecPriceRange);
	BOOL JudgeVolumeRange(std::vector<double> vecVolumeRange);


public:
	BOOL TraverseStockDayData(void);			//���������� 


private:

	Vec_StockDayData vecAimStockDayData;
	std::vector<double> vecAimPriceRange;				//�۸񲨶��ļ���
	std::vector<double> vecAimVolumeRange;				//�����������ļ���

	Vec_HistoryResultList vecHistoryResultList;
};