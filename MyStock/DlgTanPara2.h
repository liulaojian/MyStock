#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgTanPara2 对话框

class CDlgTanPara2 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTanPara2)

public:
	CDlgTanPara2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTanPara2();

// 对话框数据
	enum { IDD = IDD_DLG_TAN_PARA2 };
public:
	double GetAveVolMulMin(void) {return f_AveVolMulMin;}

	double GetAveVolMulMax(void) {return f_AveVolMulMax;}

	BOOL IsIgnorM5Angle(void) {return bIgnorM5Angle;}

	BOOL IsUserUseContiUpNums(void) {return bUseContiUpNums;}

private:
	int mAveVolMulMin;
	double f_AveVolMulMin;

	int mAveVolMulMax;
	double f_AveVolMulMax;


	BOOL bIgnorM5Angle;
	BOOL bUseContiUpNums;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mEditAveVolMulMin;
	CSpinButtonCtrl mSpinAveVolMulMin;
	CEdit mEditAveVolMulMax;
	CSpinButtonCtrl mSpinAveVolMulMax;
	afx_msg void OnBnClickedOk();
	CButton mCheckIgnorM5Angle;
	CButton mCheckUseContiUp;
};
