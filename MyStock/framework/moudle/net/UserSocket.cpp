#include "stdafx.h"
#include "UserSocket.h"


CUserSocket::CUserSocket():pSocketNotify(NULL)
{

}

CUserSocket::~CUserSocket()
{


}

void CUserSocket::OnAccept(int nErrorCode)
{


	CSocket::OnAccept(nErrorCode);
}


void CUserSocket::OnClose(int nErrorCode)
{
	if(pSocketNotify)
		pSocketNotify->NotifyUserSocketOnClose(nErrorCode);

	CSocket::OnClose(nErrorCode);
}


void CUserSocket::OnReceive(int nErrorCode)
{
	
	char buff[1024];
	int bufflen=1024;
	memset(buff,0,1024);
	int nLen = CSocket::Receive(buff,bufflen);

	if(pSocketNotify)
		pSocketNotify->NotifyUserSocketReceived(buff,nLen);
	CSocket::OnReceive(nErrorCode);
}


void CUserSocket::OnConnect(int nErrorCode)
{
	

	CSocket::OnConnect(nErrorCode);
}


void CUserSocket::OnSend(int nErrorCode)
{
	
	CSocket::OnSend(nErrorCode);
}
