#include "UDPSocket.h"

UDPSocket::UDPSocket(SOCKET& socket, const NET_MODEL& netModel)
	:m_UDPSocket(socket)
{
	SetNetModel(netModel);
	m_SocketNumber++;
}

UDPSocket::~UDPSocket()
{
	closesocket(m_UDPSocket);
}

BOOL UDPSocket::ListenNBindSocket()
{
	if (m_UDPSocket == INVALID_SOCKET) {
		Log("TCPSocket is Invalid Socket!", LOG_TYPE::ERR);
		return FALSE;
	}

	ZeroMemory(&m_sockAddrin, sizeof(m_sockAddrin));
	m_sockAddrin.sin_family = AF_INET;
	m_sockAddrin.sin_port = htons(32000);
	m_sockAddrin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(m_UDPSocket, (const sockaddr*)&m_sockAddrin, sizeof(m_sockAddrin))
		== SOCKET_ERROR)
	{
		Log("TCPSocket Bind Error!", LOG_TYPE::ERR);
		return FALSE;
	}

	if (listen(m_UDPSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		Log("TCPSocket Listen Error!", LOG_TYPE::ERR);
		return FALSE;
	}

	return TRUE;
}

int UDPSocket::SendTo(const char* buf)
{
	SOCKADDR_IN clnt_addr;
	memset(&clnt_addr, 0, sizeof(clnt_addr));
	int addrln = sizeof(clnt_addr);
	int sendln = sendto(m_UDPSocket, buf, strlen(buf), 0, (const sockaddr*)&clnt_addr, addrln);
	if (sendln == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			Log("UDP Sendto Error!", LOG_TYPE::ERR);
			exit(1);
		}
	}
	return sendln;
}

int UDPSocket::RecvFrom(char* buf)
{
	SOCKADDR_IN clnt_addr;
	memset(&clnt_addr, 0, sizeof(clnt_addr));
	int addrln = sizeof(clnt_addr);
	int recvln = recvfrom(m_UDPSocket, buf, sizeof(buf), 0, (sockaddr*)&clnt_addr, &addrln);
	if (recvln == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			Log("UDP Recvfrom Error!", LOG_TYPE::ERR);
			exit(1);
		}
	}
	return recvln;
}

SOCKET& UDPSocket::Accept()
{
	if (m_IsSelectModel == false) {
		Log("Is NOT IOCP SOCKET!");
		exit(1);
	}
	SOCKADDR_IN clint_addr;
	ZeroMemory(&clint_addr, sizeof(clint_addr));
	int adrrln = sizeof(clint_addr);
	while (true) {
		SOCKET socket = accept(m_UDPSocket, (sockaddr*)&clint_addr, &adrrln);
		if (socket == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAEWOULDBLOCK) {
			}
			else {
				Log("UDPSocket Accept Error!", LOG_TYPE::ERR);
				exit(1);
				break;
			}
		}
		else
			return socket;
	}
}

int UDPSocket::WSAUDPSendTo(LPWSABUF& lpwsabuf, LPWSAOVERLAPPED& lpwsaoverlapped)
{
	SOCKADDR_IN clnt_addr;
	memset(&clnt_addr, 0, sizeof(clnt_addr));
	int addrln = sizeof(clnt_addr);
	int sendln = WSASendTo(m_UDPSocket, lpwsabuf, 1, &lpwsabuf->len, 0, (const sockaddr*)&clnt_addr
		, addrln, lpwsaoverlapped, NULL);
	if (sendln == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			Log("UDP WSASendto Error!", LOG_TYPE::ERR);
			exit(1);
		}
	}
	return sendln;
}

int UDPSocket::WSAUDPRecvFrom(LPWSABUF& lpwsabuf, LPWSAOVERLAPPED& lpwsaoverlapped)
{
	SOCKADDR_IN clnt_addr;
	memset(&clnt_addr, 0, sizeof(clnt_addr));
	int addrln = sizeof(clnt_addr);
	DWORD recvln = 0;
	if (WSARecvFrom(m_UDPSocket, lpwsabuf, 1, &recvln, NULL, (sockaddr*)&clnt_addr, &addrln
		, lpwsaoverlapped, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING) {
			Log("UDP RecvFrom Error!");
			return -1;
		}
	}

	return recvln;
}

BOOL UDPSocket::WSAUDPAccept(SOCKET& clntSocket)
{
	SOCKADDR_IN clint_addr;
	ZeroMemory(&clint_addr, sizeof(clint_addr));
	int adrrln = sizeof(clint_addr);
	while (true) {
		SOCKET socket = WSAAccept(m_UDPSocket, (sockaddr*)&clint_addr, &adrrln, NULL, NULL);
		if (socket == SOCKET_ERROR) {
			if (WSAGetLastError() == WSA_IO_PENDING) {
			}
			else {
				Log("UDPSocket Accept Error!", LOG_TYPE::ERR);
				exit(1);
				break;
			}
		}
		else
			return socket;
	}

	return 0;
}

UDPSocket::UDPSocket(const UDPSocket& rhs)
	:m_IsSelectModel(rhs.m_IsSelectModel),
	m_sockAddrin(rhs.m_sockAddrin),
	m_UDPSocket(rhs.m_UDPSocket)
{
}

UDPSocket& UDPSocket::operator=(const UDPSocket& rhs)
{
	// TODO: 여기에 return 문을 삽입합니다.
	if (this == &rhs) return *this;

	m_IsSelectModel = rhs.m_IsSelectModel;
	m_sockAddrin = rhs.m_sockAddrin;
	m_SocketNumber = rhs.m_SocketNumber;
	m_UDPSocket = rhs.m_UDPSocket;

	return *this;
}