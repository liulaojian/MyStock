#pragma once

#include "resource.h"
#include "afxdtctl.h"

class CDlgStockDateSel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStockDateSel)

public:
	CDlgStockDateSel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStockDateSel();

// �Ի�������
	enum { IDD = IDD_DLG_DATE_SEL };

	void SetBeginTime(CTime mDateTime) {mBeginTime=mDateTime;}
	
	CTime GetBeginTime(void) {return mBeginTime;}
	
	void SetEndTime(CTime mDateTime) {mEndTime=mDateTime;}

	CTime GetEndTime(void) {return mEndTime;}


private:
	CTime  mBeginTime;
	CTime  mEndTime;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl mDateTimeBegin;
	CDateTimeCtrl mDateTimeEnd;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
