#pragma once
#include "afxwin.h"


// CDlgSetting �Ի���

class CDlgSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSetting)

public:
	CDlgSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSetting();

// �Ի�������
	enum { IDD = IDD_DLG_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpen();
	CEdit mEditXmlFile;
	virtual BOOL OnInitDialog();
	CEdit mEditTdxDir;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnOpenTdx();
};
