#pragma once

#include "DataType.h"
// CDlgPVDetail 对话框

class CDlgPVDetail : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPVDetail)

public:
	CDlgPVDetail(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgPVDetail();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIG_PV_DETARL };
#endif

	void SetRSIData(RSIData d) { mRSIData = d; }

private:
	RSIData mRSIData;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox mListDetail;
};
