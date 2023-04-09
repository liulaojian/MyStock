#pragma once
#include "StockDataMgr.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "Algorithm.h"
#include <vector>


class CTimePriceMapAlg
{

public:
	CTimePriceMapAlg();
	virtual ~CTimePriceMapAlg();

public:
	Vec_TimePriceMapData  doFilter(CTime mDropOffTime);



};