#pragma once

#include "StockDayTable.h"
#include "afxdtctl.h"
#include "afxwin.h"
#include "afxcmn.h"

class CDlgCalcRiskLevel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCalcRiskLevel)

public:
	CDlgCalcRiskLevel(CString strCode,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCalcRiskLevel();

// �Ի�������
	enum { IDD = IDD_DLG_CALC_RISK_LEVEL };

	BOOL  doCalcResult(void);
	
	//����ǰ������
	CString CalcPrePointDate(void);



private:
	CString strStockCode;
	CStockDayTable *pStockDayTable;

	CString strRef0Date;		//�ο���0 ����
	CString strRef100Date;		//�ο���100 ����

	CString strHighDate;		//�ߵ� ����
	CString strLowDate;		//�͵� ����

	float f_x_axis_base;		//x�����

	float f_y_axis_base;		//y�����

	CString strCalcDate;		//��������

	float  f_axis_para;			//��ļ������

	float  f_sh_exp_axis_para;		//��֤����������

	BOOL bAutoCalcPrePoint;

	CString strPrePointDate;

	double  f_role_adjust_rate;		//�Ƕȵ�����

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
