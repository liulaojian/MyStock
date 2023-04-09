// DlgLoopBackLog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgLoopBackLog.h"
#include "afxdialogex.h"

#include "CommonMacro.h"
// CDlgLoopBackLog �Ի���

IMPLEMENT_DYNAMIC(CDlgLoopBackLog, CDlgLoopBackCallBack)

CDlgLoopBackLog::CDlgLoopBackLog(CWnd* pParent /*=NULL*/)
	: CDlgLoopBackCallBack(CDlgLoopBackLog::IDD, pParent)
{

}

CDlgLoopBackLog::~CDlgLoopBackLog()
{
}

void CDlgLoopBackLog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, mListLog);
}


BEGIN_MESSAGE_MAP(CDlgLoopBackLog, CDlgLoopBackCallBack)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgLoopBackLog ��Ϣ�������


BOOL CDlgLoopBackLog::OnInitDialog()
{
	CDlgLoopBackCallBack::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetTimer(TIMER_EVENT_LOG,1000,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgLoopBackLog::OnTimer(UINT_PTR nIDEvent)
{
	if(TIMER_EVENT_LOG==nIDEvent)
	{
		LoopBackLogInfo *pLoopBackLogInfo=NULL;

		pLoopBackLogInfo=PopLoopBackLogInfo();

		if(pLoopBackLogInfo)
		{
			CString strTag=pLoopBackLogInfo->strLogTag;
			if(strTag=="title")
			{
				SetWindowText(pLoopBackLogInfo->strLogInfo);
			}
			else if(strTag=="info")
			{
				mListLog.AddString(pLoopBackLogInfo->strLogInfo);
			}

			SAFE_DELETE(pLoopBackLogInfo);
			mListLog.SendMessage(WM_VSCROLL, SB_BOTTOM, NULL);
		}
		
	}

	CDlgLoopBackCallBack::OnTimer(nIDEvent);
}
