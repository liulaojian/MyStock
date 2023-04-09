#pragma once

#include "LoopBack.h"

class CLoopBackMgr
{
public:
	CLoopBackMgr();
	virtual ~CLoopBackMgr();

public:
	static CLoopBackMgr* GetInstance();

	BOOL  doRunLoopBack(CLoopBack *pLoopBack);

private:
	static CLoopBackMgr* s_pIntance;

};

#define LoopBackMgr()	CLoopBackMgr::GetInstance()