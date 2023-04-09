#pragma once

class IListenSocketNotify
{
public:
	virtual void OnSocketAccept(int nErrorCode)=0;
	virtual void OnSocketClose(int nErrorCode)=0;
	virtual void OnSocketConnect(int nErrorCode)=0;
	virtual void OnSocketReceive(int nErrorCode)=0;
	virtual void OnSocketnSend(int nErrorCode)=0;
};

