#pragma once

#include "CmpMethod.h"
#include "HistoryCmpMethod.h"
#include "CurveSinCmpMethod.h"


typedef struct 
{
	CString  strCmpMethodName;
	CString  strCmpMethodDes;
}CmpMethodInfo;

typedef std::vector<CmpMethodInfo *> Vec_CmpMethodInfoList;

class CStrategyMgr
{
public:
	CStrategyMgr();
	virtual ~CStrategyMgr();

public:
	static CStrategyMgr* GetInstance();

	CCmpMethod *NewCmpMethod(CString strCmpMethodName);

	CString GetCmpMethodNameByDes(CString strCmpMethodDes);

	BOOL Init(void);

private:
	static CStrategyMgr* s_pIntance;

	Vec_CmpMethodInfoList vecCmpMethodInfoList;
};


#define StrategyMgr()	CStrategyMgr::GetInstance()