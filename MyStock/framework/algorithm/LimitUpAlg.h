#pragma once
#include "StockDataMgr.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "Algorithm.h"
#include <vector>


class CLimitUpAlg
{

public:
	CLimitUpAlg();
	virtual ~CLimitUpAlg();

public:
	Vec_LimitUpData  doFilter(CTime mDropOffTime);

	

};