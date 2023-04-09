
#include "stdafx.h"
#include "ClientSocket.h"

CClientSocket::CClientSocket():bCreate(false),bConnect(false),pSocketNotify(NULL)
{

}

CClientSocket::~CClientSocket()
{


}

void CClientSocket::OnAccept(int nErrorCode)
{


}

void CClientSocket::OnClose(int nErrorCode)
{

}

void CClientSocket::OnConnect(int nErrorCode)
{

}

void CClientSocket::OnReceive(int nErrorCode)
{
	char buff[4096]={0};
	int bufflen=4096;

	int nLen = CSocket::Receive(buff,bufflen);

	if(pSocketNotify)
		pSocketNotify->NotifyUserSocketReceived(buff,nLen);

	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnSend(int nErrorCode)
{

}

//---------------------------------------------------------------------------------
bool  CClientSocket::SocketCreate(void)
{
	CSocket::Create();
	bCreate=true;
	return bCreate;
}
bool  CClientSocket::SocketConnect(LPCTSTR strIpAddr,int Port)
{
	if(!CSocket::Connect(strIpAddr,Port))
		bConnect=false;
	else
		bConnect=true;
	return bConnect;
}
bool  CClientSocket::SocketClose(void)
{
	if(bCreate)
	{
		CSocket::Close();
		bCreate=false;
		bConnect=false;
	}
	return true;
}

