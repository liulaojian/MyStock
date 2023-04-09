#pragma once

#include "zbTypeDef.h"
#include "afxwin.h"
class CDlgSimilarResult : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSimilarResult)

public:
	CDlgSimilarResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSimilarResult();

// 对话框数据
	enum { IDD = IDD_DLG_SIMILAR_RESULT };

	void SetStockCode(CString strVal) {strStockCode=strVal;}

	void SetSimilarResult(CString strResult) {strSimilarResult=strResult;}

	CString CalcNext3DayRange(CString strResultStockCode,CString strResultDate);

	CString CalcExpPowerValue(CString strResultDate);

	void SetEndDate(CString strVal) { strEndDate=strVal; }

private:
	CString strSimilarResult;
	CString strStockCode;
	CString strEndDate;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mEditSimilar;
};
