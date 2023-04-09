#pragma once

#include "HistoryCmpMethod.h"


typedef	std::vector<CHistoryCmpMethod * > Vec_HistoryCmpMethodList;

class CHistoryCmpMethodMgr
{
public:
	CHistoryCmpMethodMgr();
	virtual ~CHistoryCmpMethodMgr();

public:
	static CHistoryCmpMethodMgr* GetInstance();

	CHistoryCmpMethod * CreateHistoryCmpMethod(CString strName);


private:
	static CHistoryCmpMethodMgr* s_pIntance;
	Vec_HistoryCmpMethodList vecHistoryCmpMethodList;
};


#define HistoryCmpMethodMgr()	CHistoryCmpMethodMgr::GetInstance()