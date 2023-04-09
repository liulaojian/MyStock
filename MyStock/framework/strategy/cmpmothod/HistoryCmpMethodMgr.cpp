#include "stdafx.h"
#include "HistoryCmpMethodMgr.h"
#include "CommonMacro.h"

CHistoryCmpMethodMgr* CHistoryCmpMethodMgr::s_pIntance = NULL;
CHistoryCmpMethodMgr::CHistoryCmpMethodMgr()
{

}

CHistoryCmpMethodMgr::~CHistoryCmpMethodMgr()
{


}


CHistoryCmpMethodMgr* CHistoryCmpMethodMgr::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CHistoryCmpMethodMgr();
		CHECKF(s_pIntance);
	}

	return s_pIntance;
}


CHistoryCmpMethod * CHistoryCmpMethodMgr::CreateHistoryCmpMethod(CString strName)
{
	CHistoryCmpMethod * pHistoryCmpMethod=NULL;




	return pHistoryCmpMethod;
}