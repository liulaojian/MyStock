#pragma once

// CUserSocket ÃüÁîÄ¿±ê
#include "IUserSocketNotify.h"
class CUserSocket : public CSocket
{
public:
	CUserSocket();
	virtual ~CUserSocket();
public:
	void SetNotify(IUserSocketNotify *notify) {pSocketNotify=notify;}

	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);
private:
	IUserSocketNotify *pSocketNotify;
};


