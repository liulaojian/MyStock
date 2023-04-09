#pragma once


class CStockMin5Data
{
public:
	CStockMin5Data();
	virtual ~CStockMin5Data();
		 

	CString GetDate(void) {return strDate;}
	void SetDate(CString strVal) {strDate=strVal;}

	CString GetTime(void) {return strTime;}
	void SetTime(CString strVal) {strTime=strVal;}

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

	CString GetDateTime(void);

private:
	CString strDate;		//����
	CString strTime;		//ʱ��
	float  fBeginPrice;		//���̼۸�
	float  fMaxPrice;		//��߼۸�
	float  fMinPrice;		//��ͼ۸�
	float  fEndPrice;		//���̼۸�
	long   mTotalVolume;		//�ɽ���
	float  fTotalPrice;		//�ɽ����

};