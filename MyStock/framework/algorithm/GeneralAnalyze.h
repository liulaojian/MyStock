#pragma once
#include "Algorithm.h"



class CGeneralAnalyze
{

public:
	CGeneralAnalyze();
	virtual ~CGeneralAnalyze();

	CString  doAnalyze(CTime mDropOffTime,CString strStockCode);

	Vec_GeneraDataDivid doAnalyzeVec(CTime mDropOffTime,CString strStockCode);
private:

	Vec_GeneraDataDivid vecGeneraDataDivid;

};
