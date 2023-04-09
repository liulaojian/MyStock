#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgKdjPara �Ի���

class CDlgKdjPara : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgKdjPara)

public:
	CDlgKdjPara(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgKdjPara();

// �Ի�������
	enum { IDD = IDD_DLG_KDJ_PARA };

	int GetKDJNums(void) {return mKdjNums;}

	int GetKDJMuls(void) {return mKdjMuls;}

	int GetRsiPreNums(void) {return mRsiPreNums;}
private:
	int mKdjNums;

	int mKdjMuls;

	int mRsiPreNums;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit mEditKdjNums;
	CSpinButtonCtrl mSpinKdjNums;
	CEdit mEditKdjMuls;
	CSpinButtonCtrl mSpinKdjMuls;
	afx_msg void OnBnClickedOk();
	CEdit mEditRsiPreNums;
	CSpinButtonCtrl mSpinRsiPreNums;
};
