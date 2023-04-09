#pragma once

#include "IndustryDataMgr.h"
// CDlgIndustrySel 对话框

class CDlgIndustrySel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgIndustrySel)

public:
	CDlgIndustrySel(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgIndustrySel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_INDUSTRY_SEL };
#endif
	IndustryData* GetSelIndustryData(void) { return pSelIndustryData; }
	BOOL  IsReVerseSel(void) { return bReVerseSel; }
private:
	IndustryData* pSelIndustryData = NULL;
	BOOL  bReVerseSel = FALSE;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox mCmbIndusry;
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
	CButton mCheckReverse;
};
