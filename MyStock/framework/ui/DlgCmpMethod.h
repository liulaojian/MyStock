#pragma once

#include "afxdtctl.h"

#include "CmpMethod.h"

#include "StockDayTable.h"
class CDlgCmpMethod : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCmpMethod)

public:
	CDlgCmpMethod(UINT nIDTemplate,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgCmpMethod();

	CmpMethodParas  GetCmpMethodParas(void) {return mapCmpMethodParas; }

	BOOL  SetCmpMethodParas(CString strParaKey,CString strParaValue);

	void SetStockDayTable(CStockDayTable *pTable) {pStockDayTable=pTable;}

	void SetBeginDayDate(CString strVal)  {strBeginDayDate=strVal;}

	void SetEndDayDate(CString strVal) {strEndDayDate=strVal;}


protected:
	CmpMethodParas   mapCmpMethodParas;

	CStockDayTable *pStockDayTable;
	CString strBeginDayDate;
	CString strEndDayDate;

	
protected:
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:


};