#pragma once
#include "TanAngleAlg.h"

class CSingleTanAngleAlg
{

public:
	CSingleTanAngleAlg();
	virtual ~CSingleTanAngleAlg();

#if 1
	int CalcPriceVolumeContiDown(std::vector<double> vecPriceVolume);
	int CalcLowPriceContiDown(std::vector<double> vecLowPrice);
	Vec_TanAngleData  doSubFilter(CString strDate,int mPreDays,int mBackDays,int mMaxAngle,double f_max_volume_multiple,bool bIgnoreM5,bool bCalcLow);
#endif
	Vec_TanAngleData  doFilter(CTime mDropOffTime,int mMulDays,int mBackDays,int mMaxAngle,double f_max_volume_multiple,bool bIgnoreM5);
	
#if 0
	//计算MN 均线 连续上升天数 （连续2天下降才算上升中断)

	int CalcMNPriceContiUp(std::vector<double> vecPriceMN);

	//获取MN 均线 连续上升天数开始的index
	int GetMNPriceContiUpBeginIndex(std::vector<double> vecPriceMN);
#endif

private:



};