#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgDays �Ի���

class CDlgDays : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDays)

public:
	CDlgDays(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDays();

// �Ի�������
	enum { IDD = IDD_DLG_DAYS };

	int GetDayNums(void) {return mDayNums;}

private:
	int mDayNums;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit mEditDays;
	CSpinButtonCtrl mSpinDays;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
