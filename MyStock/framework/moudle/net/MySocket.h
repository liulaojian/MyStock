#pragma once

#include <winsock2.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif
#include "IMySocketNotify.h"
class CMySocket
{
public:
	enum
	{
		MAX_SEND_BUF = 64 * 1024,			// 最大发送缓冲
		MAX_RECV_BUF = 4 * 1024,			// 最大接收缓冲
	};

public:
	static CMySocket* CreateNew();

protected:
	CMySocket();
	virtual ~CMySocket();

	bool Create();
	void InitData();

public:
	void SetNotify(IMySocketNotify *notify) {pSocketNotify=notify;}
	// client initialization
	bool Connect (const std::string host, const int port);
	// server initialization
	void Accept(int sock);

	// data handle
	bool SendData();
	bool Send(const char* data, int len);
	const char* Recv( int& dataLen);
	bool ClearRecvData(int len = MAX_RECV_BUF);

	void SetNonBlocking(const bool b);
	bool Select();
	void Close();

	int GetSocketId(void) {return mSocketId;}
	void SetSocketId(int id) {mSocketId=id;}

	// inline functions
public:
	int Socket() { return m_sock; }
	void Release() { delete this; }
	bool IsValid() const { return m_sock != INVALID_SOCKET; }
	bool HasRecvData() const { return m_recvDataLen > 0; }
	bool CanRead() const { return m_canRead; }
	bool CanWrite() const { return m_canWrite; }
	void SetConnected(bool b) { m_isConnected = b; }
	bool IsConnected() { return m_isConnected; }

private:
	IMySocketNotify *pSocketNotify;
	int mSocketId;
	int m_sock;
	bool m_beInit;
	bool m_isConnected;
	bool m_canRead;
	bool m_canWrite;
	int m_sendDataLen;
	int m_recvDataLen;
	char m_sendBuf[MAX_SEND_BUF];
	char m_recvBuf[MAX_RECV_BUF];
};
