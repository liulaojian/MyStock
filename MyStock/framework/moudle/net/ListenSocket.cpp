// ListenSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ListenSocket.h"


// CListenSocket

CListenSocket::CListenSocket():pSocketNotify(NULL)
{
}

CListenSocket::~CListenSocket()
{
}


// CListenSocket ��Ա����


void CListenSocket::OnAccept(int nErrorCode)
{
	if(pSocketNotify)
		pSocketNotify->OnSocketAccept(nErrorCode);
	CSocket::OnAccept(nErrorCode);
}


void CListenSocket::OnClose(int nErrorCode)
{
	if(pSocketNotify)
		pSocketNotify->OnSocketClose(nErrorCode);
	CSocket::OnClose(nErrorCode);
}


void CListenSocket::OnConnect(int nErrorCode)
{
	if(pSocketNotify)
		pSocketNotify->OnSocketConnect(nErrorCode);

	CSocket::OnConnect(nErrorCode);
}


void CListenSocket::OnReceive(int nErrorCode)
{
	if(pSocketNotify)
		pSocketNotify->OnSocketReceive(nErrorCode);

	CSocket::OnReceive(nErrorCode);
}


void CListenSocket::OnSend(int nErrorCode)
{
	if(pSocketNotify)
		pSocketNotify->OnSocketnSend(nErrorCode);
	CSocket::OnSend(nErrorCode);
}
