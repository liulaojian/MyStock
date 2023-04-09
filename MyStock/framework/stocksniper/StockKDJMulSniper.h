#pragma once
#include <vector>
#include "StockSniper.h"


typedef struct 
{
	double f_first_hight_value;
	int    m_first_hight_pos;
	double f_second_hight_value;
	int    m_second_hight_pos;

	double f_first_low_value;
	int    m_first_low_pos;
	double f_second_low_value;
	int    m_second_low_pos;

}KDJMulSniperInfo;

class CStockKDJMulSniper:public CStockSniper
{
public:
	CStockKDJMulSniper(CString strStockCode);
	virtual ~CStockKDJMulSniper();


	virtual BOOL SniperAnalyze(BOOL bLoopBackMode);

	virtual CString GetSniperAnalyzeResult(void);

public:

	BOOL SniperAnalyzeKDJ(std::vector<double> vec_k,std::vector<double> vec_d,std::vector<double> vec_j,std::vector<long> vec_time);

	KDJMulSniperInfo AnalyzeKDJ(std::vector<double> vec_calc_k,std::vector<double> vec_calc_d,std::vector<double> vec_calc_j,int mWidth);


	std::vector<double>  ExtendVecValue(std::vector<double> vec_val,int mMuls,int mSubMuls);
	std::vector<long>  ExtendVecLongValue(std::vector<long> vec_val,int mMuls,int mSubMuls);

	

private:

	CString strResultInfo;

};