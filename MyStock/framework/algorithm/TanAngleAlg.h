#pragma once
#include "StockDataMgr.h"
#include "afxwin.h"
#include "afxdtctl.h"

#include "StockProfitLossArithmetic.h"

#include "Algorithm.h"
#include <vector>
class CTanAngleAlg
{

public:
	CTanAngleAlg();
	virtual ~CTanAngleAlg();

	int CalcPriceVolumeContiDown(std::vector<double> vecPriceVolume);
	int CalcVolPriceContiDown(std::vector<double> vecVolPrice,std::vector<double> vecClosePrice);
	BOOL IsM5CrossM10(std::vector<double> vecPriceM5,std::vector<double> vecPriceM10);
	int GetVolM5M10StepIndex(std::vector<double> vecVolM5,std::vector<double> vecVolM10, int mBackDays);


	int CalcLowPriceContiDown(std::vector<double> vecLowPrice);
	int CalcBigPriceIncreaseNums(std::vector<double> vecClosePrice,int mPreSize,double f_max_ins_thes);
	int CalcMNPriceContiUp(std::vector<double> vecPriceMN);
	int CalcRsiPeakNums(std::vector<double> vecRsi1,int mPreSize);		
	int CalcVolM5ContiUp(std::vector<double> vecVolM5);
	int CalcVolM10ContiUp(std::vector<double> vecVolM10);

	int CalcPriceM5ContiUp(std::vector<double> vecPriceM5);
	int CalcPriceM10ContiUp(std::vector<double> vecPriceM10);
	int CalcPriceM20ContiUp(std::vector<double> vecPriceM20);

	void SetKLineType(int type) { mKLineType = type; }

	Vec_TanAngleData  doFilter(CTime mDropOffTime,int mBackDays,int mMaxAngle,double f_max_volume_multiple,bool bIgnoreM5,bool bUseM120,bool bUseAllUp,int mMaxInsBack,double f_max_ins_thes);

private:

	Vec_TanAngleData  vecTanAngleData;
	int mKLineType = 0;

};
