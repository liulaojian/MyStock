#pragma once
#include "Algorithm.h"
class CStepStepAlg
{

public:
	CStepStepAlg();
	virtual ~CStepStepAlg();

	Vec_StepStepAlgData  doFilter(CTime mDropOffTime);
	int CalcMNPriceContiUp(std::vector<double> vecPriceMN);
private:



};
