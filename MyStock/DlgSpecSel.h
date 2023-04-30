#pragma once


// CDlgSpecSel 对话框

class CDlgSpecSel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSpecSel)

public:
	CDlgSpecSel(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgSpecSel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SPEC_SEL };
#endif

	int GetSfSel(void) { return mSFSel; }


private:
	int mSFSel = 0;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox mCmbSfSel;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
