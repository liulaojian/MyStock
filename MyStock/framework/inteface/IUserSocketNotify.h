#pragma once

#include "zbTypeDef.h"

class IUserSocketNotify
{
public:
	virtual void NotifyUserSocketReceived(char *pData,int len) = 0;
	virtual void NotifyUserSocketOnClose(int nErrorCode)=0;
};


