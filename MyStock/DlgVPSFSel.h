#pragma once


// CDlgVPSFSel 对话框

class CDlgVPSFSel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVPSFSel)

public:
	CDlgVPSFSel(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgVPSFSel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_VPSF_SEL };
#endif
	int GetSFSel(void) { return mSFSel; }
private:
	int mSFSel;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mCmbSFSel;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
