#pragma once
#include "zbTypeDef.h"
class CStockPriceFilter
{
public:
	CStockPriceFilter();
	virtual ~CStockPriceFilter();

	Vec_CString FilterStock(void);


	void SetStockCodeList(Vec_CString vecList) {vecStockCodeList=vecList;}

	void SetDayNums(int val) {mDayNums=val;}

	void SetUpPercent(float f_val) {f_up_percent=f_val;}

	void SetDownPercent(float f_val) {f_down_percent=f_val;}
private:
	Vec_CString vecStockCodeList;
	int mDayNums;
	float f_up_percent;
	float f_down_percent;
};