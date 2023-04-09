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
	//����MN ���� ������������ ������2���½����������ж�)

	int CalcMNPriceContiUp(std::vector<double> vecPriceMN);

	//��ȡMN ���� ��������������ʼ��index
	int GetMNPriceContiUpBeginIndex(std::vector<double> vecPriceMN);
#endif

private:



};