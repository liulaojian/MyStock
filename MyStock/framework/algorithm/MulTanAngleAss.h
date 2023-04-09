#pragma once

#include "StockDataMgr.h"
#include "afxwin.h"
#include "afxdtctl.h"


#include "Algorithm.h"

class CMulTanAngleAss
{

public:
	CMulTanAngleAss();
	virtual ~CMulTanAngleAss();

	Vec_TanAngleData  doFilter(Vec_TanAngleData vecTanAngleData,CTime mDropOffTime);

};