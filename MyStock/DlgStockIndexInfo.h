#pragma once


// CDlgStockIndexInfo 对话框

class CDlgStockIndexInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStockIndexInfo)

public:
	CDlgStockIndexInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgStockIndexInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_STOCK_INDEX_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
