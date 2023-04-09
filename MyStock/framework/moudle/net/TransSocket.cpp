
#include "stdafx.h"
#include "TransSocket.h"

CTransSocket::CTransSocket():bCreate(false),bConnect(false),pSocketNotify(NULL)
{

}

CTransSocket::~CTransSocket()
{


}

void CTransSocket::OnAccept(int nErrorCode)
{


}

void CTransSocket::OnClose(int nErrorCode)
{

}

void CTransSocket::OnConnect(int nErrorCode)
{

}

void CTransSocket::OnReceive(int nErrorCode)
{
	char buff[1024];
	int bufflen=1024;

	int nLen = CSocket::Receive(buff,bufflen);

	if(pSocketNotify)
		pSocketNotify->NotifyUserSocketReceived(buff,nLen);

	CSocket::OnReceive(nErrorCode);
}

void CTransSocket::OnSend(int nErrorCode)
{

}

//---------------------------------------------------------------------------------
bool  CTransSocket::SocketCreate(void)
{
	CSocket::Create();
	bCreate=true;
	return bCreate;
}
bool  CTransSocket::SocketConnect(LPCTSTR strIpAddr,int Port)
{
	if(!CSocket::Connect(strIpAddr,Port))
		bConnect=false;
	else
		bConnect=true;
	return bConnect;
}
bool  CTransSocket::SocketClose(void)
{
	if(bCreate)
	{
		CSocket::Close();
		bCreate=false;
		bConnect=false;
	}
	return true;
}

