#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgM5M10Para 对话框

class CDlgM5M10Para : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgM5M10Para)

public:
	CDlgM5M10Para(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgM5M10Para();

// 对话框数据
	enum { IDD = IDD_DLG_M5_M10_PARA };

	int GetM5M10Period(void) {return m_m5_m10_period;}
	int GetM5M10_20_25_Nums(void) {return m_m5_m10_20_25_nums;}
	int GetM5M10_Big25_Nums(void) {return m_m5_m10_big25_nums;}
	int GetCloseM10_10_20_Nums(void) {return m_close_m10_10_20_nums;}
	int GetCloseM10_20_25_Nums(void) {return m_close_m10_20_25_nums;}
	int GetCloseM10_Big25_Nums(void) {return m_close_m10_big25_nums;}
private:
	int m_m5_m10_period;
	int m_m5_m10_20_25_nums;
	int m_m5_m10_big25_nums;
	int m_close_m10_10_20_nums;
	int m_close_m10_20_25_nums;
	int m_close_m10_big25_nums;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mEditPeriod;
	CSpinButtonCtrl mSpinPeriod;
	CEdit mEditM5M10_20_25;
	CSpinButtonCtrl mSpinM5M10_20_25;
	CEdit mEditM5M10_Big25;
	CSpinButtonCtrl mSpinM5M10_Big25;
	CEdit mEditCloseM10_10_20;
	CSpinButtonCtrl mSpinCloseM10_10_20;
	CSpinButtonCtrl mSpinCloseM10_20_25;
	CSpinButtonCtrl mSpinCloseM10_Big25;
	CEdit mEditCloseM10_20_25;
	CEdit mEditCloseM10_Big25;
	afx_msg void OnBnClickedOk();
};
