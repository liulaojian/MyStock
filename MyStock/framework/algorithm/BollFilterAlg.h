#pragma once
#include "StockDataMgr.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "Algorithm.h"
#include <vector>
#include "DataType.h"


class CBollFilterAlg
{

public:
	CBollFilterAlg();
	virtual ~CBollFilterAlg();

public:
	Vec_BOLLFilterData  doFilter(CTime mDropOffTime,Vec_DropOffData & vecDropOffData);

};