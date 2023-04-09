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
	CDlgCurveSinCmp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCurveSinCmp();

// 对话框数据
	enum { IDD = IDD_DLG_CURVESIN };

public:
	BOOL ParseCmpMethodParas(void);

private:
	double  f_x_scale;			//X  单位基数
	double  f_gate_percent;			//最后比较时的百分比阀值
	int     mEquGateNums;

private:
	int mBeginPos;
	int mEndPos;

	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
