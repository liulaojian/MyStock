// ��ͬ�ļ۸���  ��ʷ �ȽϷ�   ��ͬ����ָ���� �۸��Ƿ� ���� ������ͬ

#pragma once

#include "HistoryCmpMethod.h"

class CSameDirectCmpMethod :public CHistoryCmpMethod
{
public:
	CSameDirectCmpMethod(CString strName);
	virtual ~CSameDirectCmpMethod();

public:
	virtual BOOL Init(void);
	virtual BOOL TraverseData(void);

};