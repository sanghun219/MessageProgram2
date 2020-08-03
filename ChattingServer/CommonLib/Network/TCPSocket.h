#pragma once
#include "../framework.h"
#include "SocketUtility.h"
class TCPSocket {
public:
	TCPSocket(SOCKET& socket, const NET_MODEL& netModel);
	~TCPSocket();
	void SetSockOpt(SOCKET_OPT opt);
	// SELECT MODEL
	BOOL ListenNBindSocket();
	int Send(const char* buf);
	int Recv(char* buf);
	SOCKET& Accept();
	BOOL Connect();
	// IOCP MODEL
	int WSATCPSend(LPWSABUF& lpwsabuf, LPWSAOVERLAPPED& lpwsaoverlapped);
	int WSATCPRecv(LPWSABUF& lpwsabuf, LPWSAOVERLAPPED& lpwsaoverlapped);
	BOOL WSATCPAccept(SOCKET& clntSocket);
	BOOL WSATCPConnect();
	const int GetSocketNum()const { return m_SocketNumber; }
	SOCKET& GetSocket() { return m_TCPSocket; }
	SOCKADDR_IN& GetSockAddr() { return m_sockAddrin; }
private:

	inline	void SetNetModel(NET_MODEL model)
	{
		if (model == NET_MODEL::IOCP) {
			m_IsSelectModel = false;
		}
		else
		{
			m_IsSelectModel = true;
		}
	}
public:
	TCPSocket(const TCPSocket& rhs);
	TCPSocket& operator = (const TCPSocket& rhs);
private:
	SOCKET m_TCPSocket;
	static DWORD m_SocketNumber;
	SOCKADDR_IN m_sockAddrin;
	BOOL m_IsSelectModel;
};
