#pragma once
#include "../framework.h"
#include "SocketUtility.h"

class UDPSocket {
public:
	UDPSocket(SOCKET& socket, const NET_MODEL& netModel);
	~UDPSocket();
	// SELECT MODEL
	BOOL ListenNBindSocket();
	int SendTo(const char* buf);
	int RecvFrom(char* buf);
	SOCKET& Accept();
	// IOCP MODEL
	int WSAUDPSendTo(LPWSABUF& lpwsabuf, LPWSAOVERLAPPED& lpwsaoverlapped);
	int WSAUDPRecvFrom(LPWSABUF& lpwsabuf, LPWSAOVERLAPPED& lpwsaoverlapped);
	BOOL WSAUDPAccept(SOCKET& clntSocket);
	const int GetSocketNum()const { return m_SocketNumber; }
	SOCKET& GetSocket() { return m_UDPSocket; }
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
	UDPSocket(const UDPSocket& rhs);
	UDPSocket& operator = (const UDPSocket& rhs);
private:
	SOCKET m_UDPSocket;
	static DWORD m_SocketNumber;
	SOCKADDR_IN m_sockAddrin;
	BOOL m_IsSelectModel;
};