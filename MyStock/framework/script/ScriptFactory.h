#pragma once
#ifndef __SCRIPTFACTORY_H__
#define __SCRIPTFACTORY_H__

//#include "Host2.h"
#include "ScriptHost.h"
#include "ScriptObject.h"
#include "ScriptElement.h"

class CScriptFactory
{

	
public:
	static CScriptFactory* GetInstance();
	
public:
	CScriptFactory(void);
	~CScriptFactory(void);

public:
	enum LanguageType
	{
		LANGUAGE_JS=0,
		LANGUAGE_VB
	};

	CScriptHost	m_host;
	CScriptObject	m_ScriptObj;
	
	int init(void);

	int LoadScript(CString strFileName);

	int SetLanguage(LanguageType type);

private:
	static CScriptFactory* s_pIntance;
};

#endif