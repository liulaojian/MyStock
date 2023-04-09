#pragma once


class CStockDayData
{
public:
	CStockDayData();
	virtual ~CStockDayData();
	
	CString GetDate(void) {return strDate;}
	void SetDate(CString strVal) {strDate=strVal;}

	void SetBeginPrice(float fVal) {fBeginPrice=fVal;}
	float GetBeginPrice(void) {return fBeginPrice;}

	void SetMaxPrice(float fVal) {fMaxPrice=fVal;}
	float GetMaxPrice(void) {return fMaxPrice;}

	void SetMinPrice(float fVal) {fMinPrice=fVal;}
	float GetMinPrice(void) {return fMinPrice;}

	void SetEndPrice(float fVal) {fEndPrice=fVal;}
	float GetEndPrice(void) {return fEndPrice;}

	void SetTotalVolume(long mVal) {mTotalVolume=mVal;}
	long GetTotalVolume(void) {return mTotalVolume;}

	void SetTotalPrice(float fVal) {fTotalPrice=fVal;}
	float GetTotalPrice(void) {return fTotalPrice;}

private:
	CString strDate;		//����
	float  fBeginPrice;		//���̼۸�
	float  fMaxPrice;		//��߼۸�
	float  fMinPrice;		//��ͼ۸�
	float  fEndPrice;		//���̼۸�
	long   mTotalVolume;		//�ɽ���
	float  fTotalPrice;		//�ɽ����
};