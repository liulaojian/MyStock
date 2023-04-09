#pragma once
#include "TanAngleAlg.h"

class CMulTanAngleAlg
{

public:
	CMulTanAngleAlg();
	virtual ~CMulTanAngleAlg();
	int CalcPriceVolumeContiDown(std::vector<double> vecPriceVolume);
	int CalcVolPriceContiDown(std::vector<double> vecVolPrice);
	BOOL IsM5CrossM10(std::vector<double> vecPriceM5,std::vector<double> vecPriceM10);
	int CalcBigPriceIncreaseNums(std::vector<double> vecClosePrice,int mPreSize,double f_max_ins_thes);
	int CalcLowPriceContiDown(std::vector<double> vecLowPrice);
	int CalcRsiPeakNums(std::vector<double> vecRsi1,int mPreSize);	
	Vec_TanAngleData  doFilter(CTime mDropOffTime,int mMulDays,int mBackDays,int mMaxAngle,double f_max_volume_multiple,bool bIgnoreM5,int mMaxInsBack,double f_max_ins_thes);


	Vec_TanAngleData  doSubFilter(CString strDate,int mPreDays,int mBackDays,int mMaxAngle,double f_max_volume_multiple,bool bIgnoreM5,bool bCalcLow,int mMaxInsBack,double f_max_ins_thes);

private:



};
