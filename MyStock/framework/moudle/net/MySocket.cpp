#include "stdafx.h"
#include "MySocket.h"

#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include "CommonMacro.h"
#include "Log.h"

CMySocket::CMySocket()
	: m_beInit(false),pSocketNotify(NULL),mSocketId(-1)
{
	InitData();
}

CMySocket::~CMySocket()
{
	Close();
}

CMySocket* CMySocket::CreateNew()
{
	CMySocket* pNew = new CMySocket();
	//CHECKF(pNew);
	return pNew;
}

void CMySocket::InitData()
{
	if (m_beInit)
	{
		return;
	}

	m_sock = INVALID_SOCKET;
	m_isConnected = false;
	m_canRead = false;
	m_canWrite = false;
	m_sendDataLen = 0;
	m_recvDataLen = 0;
	memset(m_sendBuf, 0, sizeof(m_sendBuf));
	memset(m_recvBuf, 0, sizeof(m_recvBuf));

	m_beInit = true;
}

bool CMySocket::Create()
{
	m_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (!IsValid())
	{
		PrintfDebug("socket failed");
		return false;
	}

	// TIME_WAIT
	int on = 1;
	if (setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (const char*) &on, sizeof(on)) == -1)
	{
		PrintfDebug("setsockopt(SO_REUSEADDR) failed");
		Close();
		return false;
	}

	SetNonBlocking(true);

	return true;
}

bool CMySocket::Connect ( const std::string host, const int port )
{
	
	InitData();

	if ( !Create() )
	{
		PrintfDebug("Create failed");
		return false;
	}

	// 域名->IP地址
	UINT nAddr = inet_addr(host.c_str());			// 必须为 UINT, 以便与in_addr兼容
	if (nAddr == INADDR_NONE)
	{
		hostent	* hp = gethostbyname(host.c_str());
		if (hp == 0)
		{
			PrintfDebug("error in domain name of account server");
			Close();
			return false;
		}
		nAddr = *(UINT*)(hp->h_addr_list[0]);	// 或 h_addr
	}

	sockaddr_in	addr;
	memset((void *)&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = nAddr;
	int ret = connect(m_sock, (sockaddr *)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		int errorno = WSAGetLastError();
		if (errorno != WSAEWOULDBLOCK)
		{
			PrintfDebug("connect failed, errorno=%d", errorno);
			Close();
			return false;
		}
	}

	return true;

	
}

void CMySocket::Accept( int sock )
{
	InitData();
	m_sock = sock;
}

bool CMySocket::SendData()
{
	if (!IsValid() )		//|| !CanWrite()
	{
		PrintfDebug("the socket closed or cannot write");
		Close();
		return false;
	}

	int ret = send(m_sock, (const char *)m_sendBuf, m_sendDataLen, 0);
	if (ret == SOCKET_ERROR)
	{
		int errorno = WSAGetLastError();
		PrintfDebug("send failed, errorno=%d", errorno);
		if (errorno != WSAEWOULDBLOCK)
		{				
			Close();
		}

		return false;
	}

	m_sendDataLen -= ret;
	if (m_sendDataLen > 0)
	{
		memmove(m_sendBuf, m_sendBuf + ret, m_sendDataLen);
	}

	return true;	
}

bool CMySocket::Send(const char* data, int len)
{
	if(data==NULL || len > MAX_SEND_BUF)
		return false;
	if(m_sendDataLen <0 || m_sendDataLen > MAX_SEND_BUF)
		return false;

	ULONG loopCount = 0;
	while (m_sendDataLen + len > MAX_SEND_BUF)
	{
		//DEAD_LOOP_BREAK(loopCount, 1000000);

		// 发送缓存不够，发送数据释放缓存
		if (!SendData())
		{
			PrintfDebug("SendData failed!");
			return false;
		}
	}

	// 添加发送数据
	memcpy(m_sendBuf + m_sendDataLen, data, len);
	m_sendDataLen += len;

	SendData();

	return true;

	
}

const char* CMySocket::Recv(int& rDataLen)
{
	
	/*CHECKF(m_recvDataLen >= 0 && m_recvDataLen <= MAX_RECV_BUF);

	rDataLen = 0;

	if (m_recvDataLen < MAX_RECV_BUF
		&& IsValid() && CanRead())
	{
		char buf[MAX_RECV_BUF];
		memset(buf, 0, MAX_RECV_BUF);

		int ret = ::recv(m_sock, buf, MAX_RECV_BUF - m_recvDataLen, 0);
		if ( ret > 0 )
		{
			memcpy(m_recvBuf + m_recvDataLen, buf, ret);
			m_recvDataLen += ret;
		}
		else if ( ret == 0 )
		{
			// 正常关闭
			PrintfDebug("socket closed");
			Close();
		}
		else if ( ret == SOCKET_ERROR )
		{
			// 发生错误
			PrintfDebug("socket closed, errno=%d", errno);
			Close();
		}
	}

	rDataLen = m_recvDataLen;

	
	return m_recvBuf;*/

	rDataLen=0;
	if (IsValid() && CanRead())
	{
		memset(m_recvBuf, 0, MAX_RECV_BUF);
		int ret = ::recv(m_sock, m_recvBuf, MAX_RECV_BUF , 0);
		if ( ret > 0 )
		{
			rDataLen=ret;

		}
		else if ( ret == 0 )
		{
			// 正常关闭
			PrintfDebug("socket closed");
			Close();
		}
		else if ( ret == SOCKET_ERROR )
		{
			// 发生错误
			PrintfDebug("socket closed, errno=%d", errno);
			Close();
		}

	}

	return m_recvBuf;
}

bool CMySocket::ClearRecvData(int len /*= MAX_RECV_BUF*/)
{
	if (len == MAX_RECV_BUF)
	{
			// 清空数据
		m_recvDataLen = 0;
		return true;
	}

	if (m_recvDataLen - len > 0)
	{
		memmove(m_recvBuf, m_recvBuf + len, m_recvDataLen - len);
	}

	m_recvDataLen -= len;
	if (m_recvDataLen < 0)
	{
		m_recvDataLen = 0;
		return false;
	}

	return true;	
}

void CMySocket::SetNonBlocking ( const bool b )
{
	unsigned long i = b ? 1 : 0;
	if (ioctlsocket(m_sock, FIONBIO, &i))
	{
		PrintfDebug("ioctlsocket failed!");
		Close();
	}

}

bool CMySocket::Select()
{


		if (!IsValid())
		{
			return false;
		}

		timeval timeout;
		timeout.tv_sec	= 0;
		timeout.tv_usec	= 0;
		fd_set readfds, writefds, exceptfds;
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_ZERO(&exceptfds);
		FD_SET(m_sock, &readfds);
		FD_SET(m_sock, &writefds);
		FD_SET(m_sock, &exceptfds);

		int ret = select(FD_SETSIZE, &readfds, &writefds, &exceptfds, &timeout);
		if (ret <= 0)
		{
			if (ret == SOCKET_ERROR)
			{
				PrintfDebug("select failed, errno=%u", errno);
				Close();
				return false;
			}

			// no event
			return false;
		}

		if (ret > 0)
		{
			if (FD_ISSET(m_sock, &exceptfds))
			{
				PrintfDebug("select exception");
				Close();
				return false;
			}

			m_canRead = (FD_ISSET(m_sock, &readfds) != 0);
			m_canWrite = (FD_ISSET(m_sock, &writefds) != 0);
		}

		//LOG_SYS_DEBUG("CSocket::Select(): ret=%d, m_canRead=%d, m_canWrite=%d", ret, m_canRead, m_canWrite);

		return true;

	
}

void CMySocket::Close()
{
	if (IsValid())
	{
		PrintfDebug("close socket[id=%d]", m_sock);
		::closesocket(m_sock);

		m_sock = INVALID_SOCKET;
	}

	m_sendDataLen = 0;
	m_isConnected = false;
	m_beInit = false;	

	if(pSocketNotify)
	{
		try
		{
			CObject *pObject=dynamic_cast<CObject*>(pSocketNotify);
			if(pObject)
				pSocketNotify->NotifyMySocketOnClose(mSocketId);
		}
		catch (...)
		{
		}
	}
}
