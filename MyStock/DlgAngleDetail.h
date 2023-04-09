#pragma once
#include "Algorithm.h"

// CDlgAngleDetail 对话框

class CDlgAngleDetail : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAngleDetail)

public:
	CDlgAngleDetail(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgAngleDetail();

	void SetTanAngleData(TanAngleData* pData) { pTanAngleData = pData; }

private:
	TanAngleData* pTanAngleData = NULL;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIG_ANGLE_DETARL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox mListDetail;
};
