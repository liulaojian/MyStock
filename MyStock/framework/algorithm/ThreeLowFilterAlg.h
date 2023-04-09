#pragma once
#include "StockDataMgr.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "Algorithm.h"
#include <vector>
#include "DataType.h"


class CThreeLowFilterAlg
{

public:
	CThreeLowFilterAlg();
	virtual ~CThreeLowFilterAlg();

public:
	Vec_ThreeLowData  doFilter(CTime mDropOffTime,Vec_DropOffData & vecDropOffData);

};