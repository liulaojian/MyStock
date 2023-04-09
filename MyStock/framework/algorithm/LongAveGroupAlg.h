#pragma once
#include "Algorithm.h"
class CLongAveGroupAlg
{

public:
	CLongAveGroupAlg();
	virtual ~CLongAveGroupAlg();

	Vec_LongAveGroupAlgData  doFilter(CTime mDropOffTime);
	BOOL IsVolM5M10Step(std::vector<double> vecVolM5,std::vector<double> vecVolM10);
private:



};
