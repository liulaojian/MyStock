#include "StdAfx.h"
#include "script.h"
#include <vector>

CScript* CScript::s_pIntance = NULL;
/////////////////////////////////////////////////////////
CScript::CScript(void)
{
	
}

CScript::~CScript(void)
{
	
}


CScript* CScript::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CScript();
		
	}
	
	return s_pIntance;
}

int  CScript:: LoadScript(CString strPathfile)
{
	CStdioFile scriptFile;
	CString strLine;
	m_vecLines.clear();
	scriptFile.Open(strPathfile,CFile::modeRead);
	while(scriptFile.ReadString(strLine))
	{
		
		strLine.TrimLeft();
		strLine.TrimRight();
		if(!strLine.IsEmpty())
			m_vecLines.push_back(strLine);
	}
	scriptFile.Close();
	return 0;
}

int  CScript::PreParseScript(void)
{
	
	return 0;
}

int  CScript::ParseScript(void)
{
	VEC_LINES::iterator it;

	for( it = m_vecLines.begin(); it != m_vecLines.end(); it++ )
	{
		ParseScriptLine(*it);

	}

	return 0;
}

int CScript::ParseScriptLine(CString strLine)
{

	
	return 0;
}