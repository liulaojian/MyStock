#include "stdafx.h"
#include "StrategyMgr.h"
#include "CommonMacro.h"


CStrategyMgr* CStrategyMgr::s_pIntance = NULL;


CStrategyMgr::CStrategyMgr()
{


}

CStrategyMgr::~CStrategyMgr()
{

}


CStrategyMgr* CStrategyMgr::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CStrategyMgr();
		CHECKF(s_pIntance);
	}

	return s_pIntance;
}


BOOL CStrategyMgr::Init(void)
{
	CmpMethodInfo * pCmpMethodInfo=NULL;

	pCmpMethodInfo=new CmpMethodInfo();
	pCmpMethodInfo->strCmpMethodName="CurveSin";
	pCmpMethodInfo->strCmpMethodDes ="历史比较法";
	vecCmpMethodInfoList.push_back(pCmpMethodInfo);
	return TRUE;
}


CString CStrategyMgr::GetCmpMethodNameByDes(CString strCmpMethodDes)
{
	CmpMethodInfo * pCmpMethodInfo=NULL;

	for(int i=0;i<vecCmpMethodInfoList.size();i++)
	{
		pCmpMethodInfo=vecCmpMethodInfoList[i];
		if(!pCmpMethodInfo)
			continue;
		if(pCmpMethodInfo->strCmpMethodDes==strCmpMethodDes)
			return pCmpMethodInfo->strCmpMethodName;
	}

	return "";
}

CCmpMethod * CStrategyMgr::NewCmpMethod(CString strCmpMethodName)
{
	if(strCmpMethodName=="CurveSin")
	{
		CCurveSinCmpMethod *pCurveSinCmpMethod=NULL;
		pCurveSinCmpMethod=new CCurveSinCmpMethod();
		return pCurveSinCmpMethod;
	}

	return NULL;
}