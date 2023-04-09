#pragma once

#include <map>
#include <vector>
typedef std:: map<CString,   CString>   CmpMethodParas; 

typedef struct 
{
	CString  strBeginDate;
	CString  strEndDate;
}HistoryResult;
typedef std::vector<HistoryResult *> Vec_HistoryResultList;

class CDlgCmpMethod;

class CCmpMethod
{
public:
	CCmpMethod(CString strName);
	virtual ~CCmpMethod();

public:
	virtual BOOL Init(void)=0;
	virtual BOOL TraverseData(void)=0;

public:
	CString GetCmpMethodName(void) {return strCmpMethodName;}

	CDlgCmpMethod* GetDlgCmpMethod(void) {return pDlgCmpMethod;}

	void  SetDlgCmpMethod(CDlgCmpMethod* pDlg)  {pDlgCmpMethod=pDlg;}

	void SetCmpMethodParas(CmpMethodParas Paras) {mapCmpMethodParas=Paras;}



protected:
	CString strCmpMethodName;
	CDlgCmpMethod *pDlgCmpMethod;

	CmpMethodParas   mapCmpMethodParas;

};