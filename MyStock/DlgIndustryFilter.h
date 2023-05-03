#pragma once
#include <vector>
enum
{
	INDUSTRYFILTER_COLUMN_ID = 0,				//ID
	INDUSTRYFILTER_COLUMN_CODE,
	INDUSTRYFILTER_COLUMN_NAME,
};


enum
{
	INDUSTRYFILTER_REFRESH_DATA = 0x1100,
};

typedef struct
{
	CString strStockCode;
	CString strStockName;
} IndustryFilterInfo;
typedef std::vector<IndustryFilterInfo*> Vec_IndustryFilterInfo;

// CDlgIndustryFilter 对话框

class CDlgIndustryFilter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgIndustryFilter)

public:
	CDlgIndustryFilter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgIndustryFilter();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_INDUSTRY_FILTER };
#endif
	void SetStockDateTime(CTime time) { mStockDateTime = time; }
	BOOL RefreshData(void);

	Vec_IndustryFilterInfo GetResultFilterInfo(void) { return vecResultFilterInfo; }
private:
	CTime mStockDateTime;
	Vec_IndustryFilterInfo vecResultFilterInfo;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mCmbFirstPos;
	CComboBox mCmbSecondPos;
	CListCtrl mList1;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnFilter();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
};
