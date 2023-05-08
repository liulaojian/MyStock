#pragma once
#include <vector>

#include "DataType.h"

class CCIVRAngle
{
public:
	CCIVRAngle();
	virtual ~CCIVRAngle();


	static CCIVRAngleData CalcCCIVRAngle(CString strStockCode, CString strDate, std::vector<float> & vec_vr,int m_prenum);
};