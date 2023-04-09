#pragma once

#include "IListenSocketNotify.h"
// CListenSocket ÃüÁîÄ¿±ê

class CListenSocket : public CSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
public:
	void SetNotify(IListenSocketNotify *notify) {pSocketNotify=notify;}
private:
	IListenSocketNotify *pSocketNotify;
public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
};


