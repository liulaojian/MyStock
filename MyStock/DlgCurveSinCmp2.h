#pragma once

#include "DlgCmpMethod.h"
#include "afxwin.h"
#include "afxcmn.h"

enum
{
	XSCALE_AVE_1_20=0,
	XSCALE_AVE_1_30=1,
	XSCALE_AVE_1_40=2,
};

class CDlgCurveSinCmp2 : public CDlgCmpMethod
{
	DECLARE_DYNAMIC(CDlgCurveSinCmp2)

public:
	CDlgCurveSinCmp2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCurveSinCmp2();

// �Ի�������
	enum { IDD = IDD_DLG_CURVESIN2 };

public:
	void SetCmpMethodNums(int mNums) {mCmpMethodNums=mNums;}

	BOOL ParseCmpMethodParas(void);

private:
	int  mCmpMethodNums;

	int  mXScaleMode;
	double  f_gate_percent;			//���Ƚ�ʱ�İٷֱȷ�ֵ
	int     mEquGateNums;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mCmbXScale;
	CSliderCtrl mSliderGatePercent;
	CSliderCtrl mSliderEquGateNums;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedOk();
};
