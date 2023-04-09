#include "stdafx.h"
#include "LoopBack.h"

CLoopBack::CLoopBack()
{
	pDlgLoopBackCallBack=NULL;
	mStockBuyedNums=0;
	f_buy_space=0.8;
}


CLoopBack::~CLoopBack()
{

}


BOOL  CLoopBack::doSendLogInfo(CString strInfo)
{
	if(!pDlgLoopBackCallBack)
		return FALSE;
	if(!pDlgLoopBackCallBack->GetSafeHwnd())
		return FALSE;

	LoopBackLogInfo *pLoopBackLogInfo=new LoopBackLogInfo();
	pLoopBackLogInfo->strLogTag="info";
	pLoopBackLogInfo->strLogInfo=strInfo;
	pDlgLoopBackCallBack->PushRLoopBackLogInfo(pLoopBackLogInfo);
	return TRUE;
}

BOOL  CLoopBack::doSendLogTitle(CString strTitle)
{
	if(!pDlgLoopBackCallBack)
		return FALSE;
	if(!pDlgLoopBackCallBack->GetSafeHwnd())
		return FALSE;

	LoopBackLogInfo *pLoopBackLogInfo=new LoopBackLogInfo();
	pLoopBackLogInfo->strLogTag="title";
	pLoopBackLogInfo->strLogInfo=strTitle;
	pDlgLoopBackCallBack->PushRLoopBackLogInfo(pLoopBackLogInfo);
	return TRUE;
}