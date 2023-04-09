#include "stdafx.h"
#include "DlgCmpMethod.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CDlgCmpMethod, CDialogEx)

CDlgCmpMethod::CDlgCmpMethod(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
	: CDialogEx(nIDTemplate, pParent)
{
	pStockDayTable=NULL;
	strBeginDayDate="";;
	strEndDayDate="";
}

CDlgCmpMethod::~CDlgCmpMethod()
{
}




BEGIN_MESSAGE_MAP(CDlgCmpMethod, CDialogEx)
END_MESSAGE_MAP()


BOOL  CDlgCmpMethod::SetCmpMethodParas(CString strParaKey,CString strParaValue)
{
	mapCmpMethodParas[strParaKey]=strParaValue;
	return TRUE;
}


void CDlgCmpMethod::OnOK()
{
	CDialogEx::OnOK();
}