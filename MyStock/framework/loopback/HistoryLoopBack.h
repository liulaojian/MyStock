#pragma once

#include "LoopBack.h"

class CHistoryLoopBack:public CLoopBack
{
public:
	CHistoryLoopBack();
	virtual ~CHistoryLoopBack();


public:
	virtual BOOL Init(void);

	virtual BOOL doLoopBack(void);


};