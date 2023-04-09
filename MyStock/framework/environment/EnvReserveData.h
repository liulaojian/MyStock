#pragma once


class CEnvReserveData
{
public:
	CEnvReserveData();
	virtual ~CEnvReserveData();

	CString GetDate(void) {return strDate;}
	void SetDate(CString strVal) {strDate=strVal;}

	float GetBigAfter(void) {return f_big_after;}
	void SetBigAfter(float f_val) {f_big_after=f_val;}

	float GetBigRange(void) {return f_big_range;}
	void SetBigRange(float f_val)  {f_big_range=f_val;}

	float GetSmallAfter(void) {return f_small_after;}
	void  SetSmallAfter(float f_val) {f_small_after=f_val;}

	float GetSmallRange(void) {return f_small_range;}
	void  SetSmallRange(float f_val) {f_small_range=f_val;}
private:
	CString strDate;
	float f_big_after;
	float f_big_range;
	float f_small_after;
	float f_small_range;
};