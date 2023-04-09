
// MyStock.cpp : 定义应用程序的类行为。
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


// CMyStockApp 构造

CMyStockApp::CMyStockApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CMyStockApp 对象

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

// CMyStockApp 初始化

BOOL CMyStockApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
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

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

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
			AfxMessageBox("序列号不正确");
			return FALSE;
		}
	}
#endif

	CMyStockDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

