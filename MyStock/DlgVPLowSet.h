#pragma once


// CDlgVPLowSet 对话框

class CDlgVPLowSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVPLowSet)

public:
	CDlgVPLowSet(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgVPLowSet();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_VP_LOWSET };
#endif
	int GetMinMfiValue(void) { return mMinMfiValue; }
	int GetMinMfiDay(void) { return mMinMfiDay; }

	bool IsMfiCurMaxEqu(void) { return bIsMfiCurMaxEqu; }
	int GetMfiDifCurMax(void) { return mMfiDifCurMax; }
private:
	int mMinMfiValue=20;
	int mMinMfiDay = 10;

	bool bIsMfiCurMaxEqu = false;

	int mMfiDifCurMax = 1;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit mEditMinMfi;
	CSpinButtonCtrl mSpinMinMfi;
	CEdit mEditMinMfiDay;
	CSpinButtonCtrl mSpinMinMfiDay;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
	CButton mCheckEqu;
	CEdit mEditDifCurMax;
	CSpinButtonCtrl mSpinDifCurMax;
};
