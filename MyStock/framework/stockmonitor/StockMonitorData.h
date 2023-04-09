#pragma once
#include <vector>


enum
{
	SAR_COLOR_GREEN=0,
	SAR_COLOR_RED,
};
typedef struct 
{
	CString  strDateTime;
	double   f_sar;
	double   f_close;
	int      mSarColor;
}StockSarData;
typedef std::vector<StockSarData *> Vec_StockSarData;


class CStockMonitorData
{
public:
	CStockMonitorData(CString strCode);
	virtual ~CStockMonitorData();

	BOOL  AddStockSarData(StockSarData *pStockSarData);

	StockSarData *GetLastStockSarData(void);
	StockSarData *GetStockSarDataByDateTime(CString  strDateTime);

	//是否 最后连续mContinue都是绿的
	BOOL  IsLastTwoContinueGreen(void);

	CString GetStockCode(void) {return strStockCode;}

private:
	Vec_StockSarData  vecStockSarData;
	CString strStockCode;

};

typedef std::vector<CStockMonitorData *> Vec_StockMonitorData;