// 相同的价格方向  历史 比较法   相同方向指的是 价格涨幅 正负 方向相同

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