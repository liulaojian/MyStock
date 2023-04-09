#pragma once


#include "StockDataMgr.h"
#include "afxwin.h"
#include "afxdtctl.h"

#include "StockProfitLossArithmetic.h"

#include "Algorithm.h"

class CTriAngleAlg
{

public:
	CTriAngleAlg();
	virtual ~CTriAngleAlg();

	Vec_TriAngleData  doFilter(CTime mDropOffTime);

private:

	Vec_TriAngleData  vecTriAngleData;


};

