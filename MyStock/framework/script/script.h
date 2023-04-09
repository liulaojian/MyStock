#pragma once
#ifndef __SCRIPT_H__
#define __SCRIPT_H__
#include <vector>

class CScript
{

	
public:
	static CScript* GetInstance();

protected:
	CScript(void);
	~CScript(void);
public:
	typedef	std::vector<CString> VEC_LINES;
	VEC_LINES m_vecLines;		//script lines

	int LoadScript(CString strPathfile);

	int PreParseScript(void);

	int ParseScript(void);

	int ParseScriptLine(CString strLine);
	
private:
	static CScript* s_pIntance;
};



#endif