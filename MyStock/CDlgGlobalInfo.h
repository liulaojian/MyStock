#pragma once

#include <vector>
// CDlgGlobalInfo 对话框


enum
{
	GLOBAL_REFRESH_DATA = 0x1100,
	GLOBAL_REFRESH_DATA_DAY = 0x1101,
};

typedef struct
{
	CString  strStockDate;
	double   f_Tan_Per_5;
	double   f_Tan_Per_8;
}StockGlobalInfo;

typedef std::vector<StockGlobalInfo*> Vec_StockGlobalInfoList;


enum
{
	GLOBALINFO_COLUMN_ID = 0,				//ID
	GLOBALINFO_COLUMN_DATE,
	GLOBALINFO_COLUMN_TAN_5,
	GLOBALINFO_COLUMN_TAN_8
};


class CDlgGlobalInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGlobalInfo)

public:
	CDlgGlobalInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgGlobalInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_GLOBAL_INFO };
#endif


public:
	void SetStockDateTime(CTime time) { mStockDateTime = time; }
	void doRunInfo(void);
	void doRunDayInfo(void);
	BOOL RefreshData(void);
private:
	CTime mStockDateTime;
	CString strNowDate;
	CString strNowInfo;

	CString strPre5Date;
	CString strPre5Info;

	CString strPre10Date;
	CString strPre10Info;

	CString strPre15Date;
	CString strPre15Info;

	CString strPre20Date;
	CString strPre20Info;

	CString strPre25Date;
	CString strPre25Info;

	CString strPre30Date;
	CString strPre30Info;

	CString strPre35Date;
	CString strPre35Info;

	CString strPre40Date;
	CString strPre40Info;


	CWinThread* pThread=NULL;

	Vec_StockGlobalInfoList  vecStockGlobalInfoDayList;
	Vec_StockGlobalInfoList  vecStockGlobalInfoM5List;

	CWinThread* pThreadAll = NULL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnBegin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit mEditNow;
	CEdit mEditPre5;
	CEdit mEditPre25;
	CEdit mEditPre20;
	CEdit mEditPre15;
	CEdit mEditPre10;
	CEdit mEditPre30;
	CEdit mEditPre35;
	CEdit mEditPre40;
	afx_msg void OnBnClickedBtnBeginDay();
	CListCtrl mListGlobalInfoDay;
	CComboBox mCmbGlobalInfo;
	afx_msg void OnBnClickedBtnOk();
};
