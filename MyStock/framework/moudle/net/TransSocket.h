//转发socket类 ,连接远程的server 转发

#pragma once

#include "IUserSocketNotify.h"
class CTransSocket : public CSocket
{
public:
	CTransSocket();
	virtual ~CTransSocket();
public:
	void SetNotify(IUserSocketNotify *notify) {pSocketNotify=notify;}

	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
public:
public:
	bool SocketCreate(void);
	bool SocketConnect(LPCTSTR strIpAddr,int Port);
	bool SocketClose(void);
	

	bool IsCreate(void) {return bCreate;}
	bool IsConnect(void) {return bConnect;}

private:
	IUserSocketNotify *pSocketNotify;
	bool bCreate;
	bool bConnect;
};

