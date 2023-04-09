#pragma once
#include <vector>
#include "StockSniper.h"

enum
{
	KDJ_ROLE_TYPE_HIGH=0,		//最高点角
	KDJ_ROLE_TYPE_LOW,		//最低点角
};

typedef struct 
{
	int  m_up_cross_pos;
	int  m_down_cross_pos;
	int  m_role_pos;	
	double f_role_value;
	int  m_role_type;
	int  m_role_index;
}KDJCrossInfo;

typedef std::vector<KDJCrossInfo *> Vec_KDJCrossInfo;


class CStockNewK60KDJMulSniper:public CStockSniper
{
public:
	CStockNewK60KDJMulSniper(CString strStockCode);
	virtual ~CStockNewK60KDJMulSniper();


	virtual BOOL SniperAnalyze(BOOL bLoopBackMode);

	virtual CString GetSniperAnalyzeResult(void);

public:

	Vec_KDJCrossInfo AnalyzeKDJCross(std::vector<double> vec_calc_k,std::vector<double> vec_calc_d,std::vector<double> vec_calc_j);

private:

	CString strResultInfo;

};