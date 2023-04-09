#pragma once
#include "afxwin.h"


// CDlgKLineModeSel �Ի���

class CDlgKLineModeSel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgKLineModeSel)

public:
	CDlgKLineModeSel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgKLineModeSel();

// �Ի�������
	enum { IDD = IDD_DLG_KLINE_MODE };

	int GetKLineMode(void) {return mKLineMode;}

private:
	int mKLineMode;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mCmbKLineMode;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
