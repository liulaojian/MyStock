#pragma once
#include "afxwin.h"


// CDlgSFSel �Ի���

class CDlgSFSel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSFSel)

public:
	CDlgSFSel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSFSel();

// �Ի�������
	enum { IDD = IDD_DLG_SF_SEL };

	int GetSFSel(void) {return mSFSel;}
private:
	int mSFSel;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mCmbSFSel;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
