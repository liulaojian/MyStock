#pragma once


// CDlgFilterIncrease 对话框

class CDlgFilterIncrease : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFilterIncrease)

public:
	CDlgFilterIncrease(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgFilterIncrease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FILTER_INCREASE };
#endif

	float GetIncrease(void) { return fIncrease; }

private:
	float fIncrease = 10.0;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mEditIncrease;
	CSpinButtonCtrl mSpinIncrease;
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
};
