#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgTanAnglePara 对话框

class CDlgTanAnglePara : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTanAnglePara)

public:
	CDlgTanAnglePara(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTanAnglePara();

// 对话框数据
	enum { IDD = IDD_DLG_TAN_PARA };

	int GetTan60AngleMin(void) {return mTan60AngleMin;}

	int GetTan60AngleMax(void) {return mTan60AngleMax;}

	double GetAveVolMulMin(void) {return f_AveVolMulMin;}

	double GetAveVolMulMax(void) {return f_AveVolMulMax;}

	
	double GetMaxVolMulMin(void) {return f_MaxVolMulMin;}
	double GetMaxVolMulMax(void) {return f_MaxVolMulMax;}

	double GetPriceIncrease(void) {return fPriceIncrease;}

	int GetMaxTanAngle(void) {return mMaxTanAngle;}

	int GetMinMaxTanAngle(void) {return mMinMaxTanAngle;}

	bool IsTanAngleOrderUp(void) {return bTanAngleOrderUp;}
	bool IsTanAngleM60UpLessM20(void) {return bTanAngleM60UpLessM20;}
	bool IsTanAngleM60AllUp(void) {return bTanAngleM60AllUp;}

private:
	int mTan60AngleMin;
	int mTan60AngleMax;

	int mAveVolMulMin;
	double f_AveVolMulMin;

	int mAveVolMulMax;
	double f_AveVolMulMax;


	int mMaxVolMulMin;
	double f_MaxVolMulMin;

	int mMaxVolMulMax;
	double f_MaxVolMulMax;

	int mMaxTanAngle;
	int mMinMaxTanAngle;


	bool bTanAngleOrderUp;

	bool bTanAngleM60UpLessM20;

	bool bTanAngleM60AllUp;

	int  mPriceIncrease;
	double fPriceIncrease;

	BOOL  bNormalMode;

private:
	void SetTanMode(void);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mEditTanAngleMin;
	CSpinButtonCtrl mSpinTanAngleMin;
	CEdit mEditTanAngleMax;
	CSpinButtonCtrl mSpinTanAngleMax;
	CEdit mEditAveVolMulMin;
	CSpinButtonCtrl mSpinAveVolMulMin;
	CEdit mEditAveVolMulMax;
	CSpinButtonCtrl mSpinAveVolMulMax;
	afx_msg void OnBnClickedOk();
	CButton mCheckTanOrderUp;
	CButton mCheckM60UpNumsLessM20;
	CButton mCheckM60AllUp;
	CEdit mEditMaxVolMulMin;
	CSpinButtonCtrl mSpinMaxVolMulMin;
	CEdit mEditMaxVolMulMax;
	CSpinButtonCtrl mSpinMaxVolMulMax;
	CEdit mEditMaxTan;
	CSpinButtonCtrl mSpinMaxTan;
	CEdit mEditPriceIncrease;
	CSpinButtonCtrl mSpinPriceIncrease;
	CEdit mEditMinMaxTan;
	CSpinButtonCtrl mSpinMinMaxTan;
	afx_msg void OnBnClickedBtnTanMode();
};
