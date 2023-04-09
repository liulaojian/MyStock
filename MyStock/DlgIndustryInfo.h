#pragma once

#include <vector>
#include <map>
#include <string>
// CDlgIndustryInfo 对话框

typedef struct
{
	CString  strStockDate;
	std::map<std::string, double> mapIndustryInfo;
}IndustryInfoData;

typedef std::vector<IndustryInfoData*> Vec_IndustryInfoDataList;


typedef struct
{
	CString  strStockDate;	
	double   f_per;
}IndustryFilterDayData;

typedef struct
{
	CString  strIndustryName;
	std::vector< IndustryFilterDayData*> vecIndustryFilterDayData;
}IndustryFilterData;
typedef std::vector<IndustryFilterData*> Vec_IndustryFilterData;




class CDlgIndustryInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgIndustryInfo)

public:
	CDlgIndustryInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgIndustryInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_INDUSTRY_INFO };
#endif
	void SetStockDateTime(CTime time) { mStockDateTime = time; }


public:
	void  doRunFindInfo(void);

private:
	CTime mStockDateTime;
	CWinThread* pThread = NULL;
	Vec_IndustryInfoDataList vecIndustryInfoDataList;
	int mPeridNums = 0;
	bool bIndustryFilter = false;
	bool bIndustryAllLow = false;
	bool bIndustryAllList = false;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox mCmbPeriod;
	CComboBox mCmbPerLow;
	CComboBox mCmbPerHigh;
	afx_msg void OnBnClickedBtnFind();
	CComboBox mCmbIndustry;
	afx_msg void OnBnClickedBtnShow();
	afx_msg void OnBnClickedBtnFind2();
	afx_msg void OnBnClickedBtnFind3();
};
