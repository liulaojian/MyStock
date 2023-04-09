#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgRsiFilter 对话框

class CDlgRsiFilter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRsiFilter)

public:
	CDlgRsiFilter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgRsiFilter();

// 对话框数据
	enum { IDD = IDD_DLG_RSI_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	float GetRsi1Low(void) {return f_rsi1_low;}
	float GetRsi1High(void) {return f_rsi1_high;}

	float GetRsi2Low(void) {return f_rsi2_low;}
	float GetRsi2High(void) {return f_rsi2_high;}

	float GetRsi3Low(void) {return f_rsi3_low;}
	float GetRsi3High(void) {return f_rsi3_high;}

	int GetRsiDist(void) {return m_risi_dist;}

private:
	float f_rsi1_low;
	float f_rsi1_high;
	
	float f_rsi2_low;
	float f_rsi2_high;

	float f_rsi3_low;
	float f_rsi3_high;

	int m_risi_dist;


public:
	virtual BOOL OnInitDialog();
	CEdit mEditRsi1Low;
	CSpinButtonCtrl mSpinRsi1Low;
	CEdit mEditRsi1High;
	CSpinButtonCtrl mSpinRsi1High;
	CEdit mEditRsi2Low;
	CEdit mEditRsi2High;
	CEdit mEditRsi3Low;
	CSpinButtonCtrl mSpinRsi2Low;
	CSpinButtonCtrl mSpinRsi2High;
	CSpinButtonCtrl mSpinRsi3Low;
	CEdit mEditRsi3High;
	CSpinButtonCtrl mSpinRsi3High;
	CEdit mEditRsiDist;
	CSpinButtonCtrl mSpinRsiDist;
	afx_msg void OnBnClickedOk();
};
