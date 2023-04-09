#pragma once

#include "StockDayTable.h"
#include "afxdtctl.h"
#include "afxwin.h"
#include "afxcmn.h"

class CDlgCalcRiskLevel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCalcRiskLevel)

public:
	CDlgCalcRiskLevel(CString strCode,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCalcRiskLevel();

// 对话框数据
	enum { IDD = IDD_DLG_CALC_RISK_LEVEL };

	BOOL  doCalcResult(void);
	
	//计算前点日期
	CString CalcPrePointDate(void);



private:
	CString strStockCode;
	CStockDayTable *pStockDayTable;

	CString strRef0Date;		//参考点0 日期
	CString strRef100Date;		//参考点100 日期

	CString strHighDate;		//高点 日期
	CString strLowDate;		//低点 日期

	float f_x_axis_base;		//x轴基数

	float f_y_axis_base;		//y轴基数

	CString strCalcDate;		//计算日期

	float  f_axis_para;			//轴的计算参数

	float  f_sh_exp_axis_para;		//上证的轴计算参数

	BOOL bAutoCalcPrePoint;

	CString strPrePointDate;

	double  f_role_adjust_rate;		//角度调整率

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CDateTimeCtrl mRef0DateTimeCtrl;
	CDateTimeCtrl mRef100DateTimeCtrl;
	CDateTimeCtrl mHighDateTimeCtrl;
	CDateTimeCtrl mLowDateTimeCtrl;
	CEdit mEditYAxisBase;
	CEdit mEditXAxisBase;
	CEdit mEditResult;
	afx_msg void OnBnClickedBtnCalc();
	CDateTimeCtrl mCalcDateTimeCtrl;
	CEdit mEditIncrease;
	CDateTimeCtrl mPrePointDataTimeCtrl;
	CButton mCheckAutoCalcPrePoint;
	CEdit mEditRolAdjRate;
	CSpinButtonCtrl mSpinRolAdjRate;
	afx_msg void OnDeltaposSpinRolAdjRote(NMHDR *pNMHDR, LRESULT *pResult);
};
