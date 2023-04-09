#pragma once
#include "afxdtctl.h"
#include "afxwin.h"

#include "StockDayTable.h"
// CDlgLoopBackSetting 对话框

class CDlgLoopBackSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLoopBackSetting)

public:
	CDlgLoopBackSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLoopBackSetting();

// 对话框数据
	enum { IDD = IDD_DLG_LOOPBACK };

	CString GetBeginDate(void) {return strBeginDate;}
	CString GetEndDate(void) {return strEndDate;}
	CString GetCmpMethodDes(void) {return strCmpMethodDes;}
	int GetCmpMethodNums(void) {return mCmpMethodNums;}

	void SetStockDayTable(CStockDayTable *pTable) {pStockDayTable=pTable;}


	float GetTotalFund(void) {return f_total_fund;}
	float GetStampTax(void) {return f_stamp_tax;}
	float GetServiceCharge(void) {return f_service_charge;}
	float GetMinServiceCharge(void) {return f_min_service_charge;}

	CString GetStockExpName(void) {return strStockExpName;}
private:

	float f_total_fund;		//总资金

	float f_stamp_tax;		//印花税

	float f_service_charge;	//手续费

	float f_min_service_charge;		//最小手续费

	CString strBeginDate;
	CString strEndDate;
	CString strCmpMethodDes;
	int  mCmpMethodNums;

	CString strStockExpName;

	CStockDayTable *pStockDayTable;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl mDateTimeBegin;
	CDateTimeCtrl mDateTimeEnd;
	CComboBox mCmbCmpMethod;
	CComboBox mCmbMethodNums;
	virtual BOOL OnInitDialog();
	CComboBox mCmbToatlFund;
	CComboBox mCmbStampTax;
	CComboBox mCmbServiceCharge;
	CComboBox mCmbMinServiceCharge;
	afx_msg void OnBnClickedOk();
	CComboBox mCmbStockExp;
};
