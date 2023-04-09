#include "stdafx.h"
#include "Global.h"
#include "CommonMacro.h"

CGlobalMgr* CGlobalMgr::s_pIntance = NULL;
CGlobalMgr::CGlobalMgr()
{

}

CGlobalMgr::~CGlobalMgr()
{

}

CGlobalMgr* CGlobalMgr::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CGlobalMgr();
		CHECKF(s_pIntance);
	}

	return s_pIntance;
}

