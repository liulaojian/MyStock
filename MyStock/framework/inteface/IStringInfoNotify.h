#pragma once

#include "stdafx.h"
#include <vector>


class IStringInfoNotify
{
public:
	virtual void OnNotifyStringInfo(CString strInfo) = 0;

};

