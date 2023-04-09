#pragma once

#include "resource.h"

#include "DlgCmpMethod.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "afxmenubutton.h"

class CDlgCurveSinCmp : public CDlgCmpMethod
{
	DECLARE_DYNAMIC(CDlgCurveSinCmp)

public:
	CDlgCurveSinCmp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCurveSinCmp();

// �Ի�������
	enum { IDD = IDD_DLG_CURVESIN };

public:
	BOOL ParseCmpMethodParas(void);

private:
	double  f_x_scale;			//X  ��λ����
	double  f_gate_percent;			//���Ƚ�ʱ�İٷֱȷ�ֵ
	int     mEquGateNums;

private:
	int mBeginPos;
	int mEndPos;

	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit mEditXScale;
	CSliderCtrl mSliderGatePercent;
	CSliderCtrl mSliderEquGateNums;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedOk();
	CMFCMenuButton mMenuBtnXScale;
	afx_msg void OnBnClickedMfcmenubuttonXscale();
};
