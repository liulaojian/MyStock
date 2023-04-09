#pragma once


class CEnvInterestData
{
public:
	CEnvInterestData();
	virtual ~CEnvInterestData();

	CString GetDate(void) {return strDate;}
	void SetDate(CString strVal) {strDate=strVal;}

	float GetDepositAfter(void) {return f_deposit_after;}
	void  SetDepositAfter(float f_val) {f_deposit_after=f_val;}

	float GetDepositRange(void) {return f_deposit_range;}
	void SetDepositRange(float f_val) {f_deposit_range=f_val;}

	float GetLoansAfter(void) {return f_loans_after;}
	void  SetLoansAfter(float f_val) {f_loans_after=f_val;}

	float GetLoansRange(void) {return f_loans_range;}
	void  SetLoansRange(float f_val) {f_loans_range=f_val;}
private:
	CString strDate;
	float f_deposit_after;
	float f_deposit_range;
	float f_loans_after;
	float f_loans_range;
};