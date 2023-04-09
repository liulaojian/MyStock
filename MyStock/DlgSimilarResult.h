#pragma once

#include "zbTypeDef.h"
#include "afxwin.h"
class CDlgSimilarResult : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSimilarResult)

public:
	CDlgSimilarResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSimilarResult();

// �Ի�������
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mEditSimilar;
};
