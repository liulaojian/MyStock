#include "StdAfx.h"
#include "ScriptFactory.h"


CScriptFactory* CScriptFactory::s_pIntance = NULL;
/////////////////////////////////////////////////////////
CScriptFactory::CScriptFactory(void)
{
	
}

CScriptFactory::~CScriptFactory(void)
{
	
}


CScriptFactory* CScriptFactory::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CScriptFactory();
		
	}
	
	return s_pIntance;
}


int CScriptFactory::init(void)
{
	BOOL bOK=m_ScriptObj.AddObject("app",m_host.GetIDispatch(FALSE),TRUE);
	m_ScriptObj.SetTimeout(-1);
	m_host.p_ScriptElement=CScriptElement::GetInstance();
	
	return 0;
}

int CScriptFactory::LoadScript(CString strFileName)
{
	m_ScriptObj.Reset();
	m_ScriptObj.LoadScript( strFileName );
	return 0;
}

int CScriptFactory::SetLanguage(LanguageType type)
{
	if(type==LANGUAGE_JS)
	{
		m_ScriptObj.SetLanguage( "JScript" );
	}
	else if(type==LANGUAGE_VB)
	{
		m_ScriptObj.SetLanguage( "VBScript" );
	}
	return 0;
}