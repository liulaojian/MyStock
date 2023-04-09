#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgTanAngle 对话框

class CDlgTanAngle : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTanAngle)

public:
	CDlgTanAngle(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTanAngle();

// 对话框数据
	enum { IDD = IDD_DLG_TAN_ANGLE };

	int GetBackDays(void) {return mBackDays;}
	int GetMaxAngle(void) {return mMaxAngle;}
	double GetMaxVolumeMultiple(void) {return f_max_volume_multiple;}
	bool IsIgnoreM5(void) {return bIgnoreM5;}
	bool IsIgnoreM60(void) {return bIgnoreM60;}

	bool IsUseAllUp(void) {return bUseAllUp;}
	int GetMaxInsBack(void) {return mMaxInsBack;}
	double GetMaxInsThes(void){return f_max_ins_thes;}

	int GetKLineType(void) { return mKType; }
private:
	int mBackDays;
	int mMaxAngle;
	double f_max_volume_multiple;
	bool bIgnoreM5;
	bool bIgnoreM60;

	bool bUseAllUp;
	int mMaxVolMul;
	int mMaxInsBack;
	int mMaxInsThes;
	int mKType = 0;
	double f_max_ins_thes;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mEditDays;
	CSpinButtonCtrl mSpinDays;
	CEdit mEditMaxAngle;
	CSpinButtonCtrl mSpinMaxAngle;
	CEdit mEditMaxVol;
	CSpinButtonCtrl mSpinMaxVol;
	afx_msg void OnBnClickedOk();
	CButton mCheckIgnoreM5;
	CButton mCheckUseAllUp;
	CEdit mEditMaxInsBack;
	CSpinButtonCtrl mSpinMaxInsBack;
	CButton mCheckIgnoreM60;
	CEdit mEditMaxInsThes;
	CSpinButtonCtrl mSpinMaxInsThes;
	CComboBox mKLineType;
};
