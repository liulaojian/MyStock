#include "stdafx.h"
#include "LoopBackMgr.h"
#include "CommonMacro.h"
CLoopBackMgr* CLoopBackMgr::s_pIntance = NULL;


CLoopBackMgr::CLoopBackMgr()
{


}

CLoopBackMgr::~CLoopBackMgr()
{

}


CLoopBackMgr* CLoopBackMgr::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CLoopBackMgr();
		CHECKF(s_pIntance);
	}

	return s_pIntance;
}


static UINT  RunLoopBackProc(LPVOID pParam)
{
	CLoopBack *pLoopBack;
	pLoopBack=(CLoopBack *)pParam;

	if(pLoopBack->Init())
		pLoopBack->doLoopBack();

	return 0;
}



BOOL  CLoopBackMgr::doRunLoopBack(CLoopBack *pLoopBack)
{
	AfxBeginThread(RunLoopBackProc,(LPVOID)pLoopBack,THREAD_PRIORITY_NORMAL,0,0,NULL);
	return TRUE;
}