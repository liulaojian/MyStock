#pragma once

#include "zbTypeDef.h"

class IMySocketNotify
{
public:
	virtual void NotifyMySocketReceived(char *pData,int len) = 0;
	virtual void NotifyMySocketOnClose(int mSocketId)=0;
};
