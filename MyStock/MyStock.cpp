
// MyStock.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MyStock.h"
#include "MyStockDlg.h"
#include "Util.h"
#include   <io.h>
#include   <fcntl.h>
#include "DlgXLH.h"
#include "SystemMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyStockApp

BEGIN_MESSAGE_MAP(CMyStockApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyStockApp ����

CMyStockApp::CMyStockApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMyStockApp ����

CMyStockApp theApp;


static bool bAllocConsole=false;
void   OpenConsole()
{
	AllocConsole();
	HANDLE   handle   =   GetStdHandle(STD_OUTPUT_HANDLE);
	int   hCrt   =   _open_osfhandle((long)handle,_O_TEXT);
	FILE   *   hf   =   _fdopen(   hCrt,   "w"   );
	*stdout   =   *hf;
	bAllocConsole=true;
}


void CloseConsole()
{
	if(bAllocConsole)
	{
		HANDLE   handle   =   GetStdHandle(STD_OUTPUT_HANDLE);
		CloseHandle(handle);
		FreeConsole();
		bAllocConsole=false;
	}

}

// CMyStockApp ��ʼ��

BOOL CMyStockApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

//#ifdef _DEBUG
	//OpenConsole();
//#endif

	if (!AfxSocketInit())
	{
		AfxMessageBox("socket fail");
		return FALSE;
	}


	AfxEnableControlContainer();

	::CoInitialize(NULL);

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

#ifdef CHECK_USER
	CString strDomain=AnalysisDomain("hao1.jfiresoft.com");
	if(strDomain!="47.99.157.65")
	{
		if(strDomain!="47.99.157.66")
			return FALSE;
			//SystemMgr()->SetFakeMode(TRUE);
	}
	
	if(!SystemMgr()->CheckXuLieHao())
	{
		CDlgXLH dlgxlh;
		if(dlgxlh.DoModal()==IDCANCEL)
		{
			AfxMessageBox("���кŲ���ȷ");
			return FALSE;
		}
	}
#endif

	CMyStockDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

