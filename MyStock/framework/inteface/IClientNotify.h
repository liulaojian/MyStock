#pragma once

#include "zbTypeDef.h"
#include <vector>
#ifdef USE_WIN_THREAD
#include "ClientSocketThread.h"
#else
#include "ClientThread.h"
#endif
class IClientNotify
{
public:
	virtual void OnNotifyNewClientComing(ClientSocketThread* pClientThread,BOOL bOnLine) = 0;
	virtual void OnNotifyUpdateClientInfo(ClientSocketThread* pClientThread,BOOL bOnLine) = 0;
};

typedef	std::vector<IClientNotify * > Vec_ClientNotifyList;