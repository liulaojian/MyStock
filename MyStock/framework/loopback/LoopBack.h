#pragma once

#include "CmpMethod.h"
#include "DlgLoopBackCallBack.h"





//�ز���
class CLoopBack
{
public:
	CLoopBack();
	virtual ~CLoopBack();

	void SetTotalFund(float f_val) {f_total_fund=f_val;}
	float GetTotalFund(void) {return f_total_fund;}

	void SetStockCode(CString strVal) {strStockCode=strVal;}
	CString GetStockCode(void) {return strStockCode;}

	void SetStockExp(CString strVal){strStockExp=strVal;}
	CString GetStockExp(void) {return strStockExp;}

	
	void SetCmpMethodNums(int mVal) {mCmpMethodNums=mVal;}
	int GetCmpMethodNums(void) {return mCmpMethodNums;}

	void SetBeginDate(CString strVal) {strBeginDate=strVal;}
	CString GetBeginDate(void) {return strBeginDate;}

	void SetEndDate(CString strVal) {strEndDate=strVal;}
	CString GetEndDate(void) {return strEndDate;}

	float  GetStampTax(void)  { return f_stamp_tax;}
	void   SetStampTax(float f_val) {f_stamp_tax=f_val;}

	float GetServiceCharge(void) {return f_service_charge;}
	void  SetServiceCharge(float f_val) {f_service_charge=f_val;}

	float GetMinServiceCharge(void) {return f_min_service_charge;}
	void  SetMinServiceCharge(float f_val) {f_min_service_charge=f_val;}

	void SetCmpMethodParas(CmpMethodParas Paras) {mapCmpMethodParas=Paras;}

	CString GetCmpMethodName(void) {return strCmpMethodName;}

	void SetCmpMethodName(CString strVal) {strCmpMethodName=strVal;}
	
	CDlgLoopBackCallBack * GetDlgLoopBackCallBack(void) {return pDlgLoopBackCallBack;}

	void SetDlgLoopBackCallBack(CDlgLoopBackCallBack * pDlg) {pDlgLoopBackCallBack=pDlg;}

	BOOL  doSendLogInfo(CString strInfo);

	BOOL  doSendLogTitle(CString strTitle);


public:
	virtual BOOL Init(void)=0;

	virtual BOOL doLoopBack(void)=0;

protected:
	float f_total_fund;		//���ʽ�

	float f_stamp_tax;		//ӡ��˰

	float f_service_charge;	//������

	float f_min_service_charge;		//��С������

	CString strStockCode;	//�ز��Ʊ����
	CString strStockExp;	// �ز����ݵĹ�Ʊָ��

	CString strBeginDate;	//�ز⿪ʼ����
	CString strEndDate;		//�ز��������

	CString strCmpMethodName;		//�ȽϷ�����

	int  mCmpMethodNums;			//�ز�ʹ�õıȽϷ����ıȽϴ���������)

	int mStockBuyedNums;			//�Ѿ������˶��ٹ�

	float  f_buy_space;				//�����λ

	CmpMethodParas   mapCmpMethodParas;

	CDlgLoopBackCallBack *pDlgLoopBackCallBack;

};