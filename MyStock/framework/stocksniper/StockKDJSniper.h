#pragma once
#include <vector>
#include "StockSniper.h"

class CStockKDJSniper:public CStockSniper
{
public:
	CStockKDJSniper(CString strStockCode);
	virtual ~CStockKDJSniper();

	virtual BOOL SniperAnalyze(BOOL bLoopBackMode);

	virtual CString GetSniperAnalyzeResult(void);

	BOOL SniperAnalyzeK60(BOOL bLoopBackMode);

	BOOL SniperAnalyzeKDJ(std::vector<double> vec_k,std::vector<double> vec_d,std::vector<double> vec_j,std::vector<long> vec_time);

	std::vector<double>  ExtendVecValue(std::vector<double> vec_val,int mMuls,int mSubMuls);
	std::vector<long>  ExtendVecLongValue(std::vector<long> vec_val,int mMuls,int mSubMuls);

	
	


private:
	BOOL  bKDJDetected;			//KDJ 是否检测到
	BOOL  bKDJValueZero;		//KDJ 是否在前几个周期内上穿或者接近0

	CString strResultInfo;
	CString strK60ResultInfo;

	
};