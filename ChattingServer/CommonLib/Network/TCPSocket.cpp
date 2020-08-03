#include "TCPSocket.h"

DWORD TCPSocket::m_SocketNumber = 0;
TCPSocket::TCPSocket(SOCKET& _socket, const NET_MODEL& _netModel) :m_TCPSocket(_socket)
{
	SetNetModel(_netModel);
	m_SocketNumber++;
	m_TCPSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_TCPSocket == INVALID_SOCKET) {
		Log("TCPSocket init error!", LOG_TYPE::ERR);
	}
}

TCPSocket::~TCPSocket()
{
	closesocket(m_TCPSocket);
}

void TCPSocket::SetSockOpt(SOCKET_OPT opt)
{
	switch (opt)
	{
	case SOCKET_OPT::NONBLOCK:
		SocketUtility::SetNonBlock(m_TCPSocket);
		break;
	case SOCKET_OPT::REUSEADDR:
		SocketUtility::ReuseAddr(m_TCPSocket);
		break;
	default:
		break;
	}
}

BOOL TCPSocket::ListenNBindSocket()
{
	if (m_TCPSocket == INVALID_SOCKET) {
		Log("TCPSocket is Invalid Socket!", LOG_TYPE::ERR);
		return FALSE;
	}

	ZeroMemory(&m_sockAddrin, sizeof(m_sockAddrin));
	m_sockAddrin.sin_family = AF_INET;
	m_sockAddrin.sin_port = htons(32000);
	m_sockAddrin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(m_TCPSocket, (const sockaddr*)&m_sockAddrin, sizeof(m_sockAddrin))
		== SOCKET_ERROR)
	{
		Log("TCPSocket Bind Error!", LOG_TYPE::ERR);
		return FALSE;
	}

	if (listen(m_TCPSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		Log("TCPSocket Listen Error!", LOG_TYPE::ERR);
		return FALSE;
	}

	return TRUE;
}

int TCPSocket::Send(const char* buf)
{
	if (m_IsSelectModel == false) return -1;
	int sendln = send(m_TCPSocket, buf, strlen(buf), 0);
	return sendln;
}

int TCPSocket::Recv(char* buf)
{
	if (m_IsSelectModel == false) return -1;
	int recvln = recv(m_TCPSocket, buf, sizeof(buf), 0);
	return recvln;
}

SOCKET& TCPSocket::Accept()
{
	if (m_IsSelectModel == false) {
		Log("Is NOT IOCP SOCKET!");
		exit(1);
	}
	SOCKADDR_IN clint_addr;
	ZeroMemory(&clint_addr, sizeof(clint_addr));
	int adrrln = sizeof(clint_addr);
	while (true) {
		SOCKET socket = accept(m_TCPSocket, (sockaddr*)&clint_addr, &adrrln);
		if (socket == SOCKET_ERROR) {
			if (WSAGetLastError() == WSAEWOULDBLOCK) {
			}
			else {
				Log("TCPSocket Accept Error!", LOG_TYPE::ERR);
				exit(1);
				break;
			}
		}
		else
			return socket;
	}
}

BOOL TCPSocket::Connect()
{
	if (m_IsSelectModel == false) {
		Log("IS NOT SELECT MODEL!");
		return false;
	}
	if (connect(m_TCPSocket, (const sockaddr*)&m_sockAddrin, sizeof(m_sockAddrin))
		== SOCKET_ERROR)
	{
		Log("TCPSocket Connect Error!", LOG_TYPE::ERR);
		return FALSE;
	}
	return TRUE;
}

int TCPSocket::WSATCPSend(LPWSABUF& lpwsabuf, LPWSAOVERLAPPED& lpwsaoverlapped)
{
	if (m_IsSelectModel == TRUE) {
		Log("IS NOT IOCP MODEL!");
		return -1;
	}
	int sendln = WSASend(m_TCPSocket, lpwsabuf, 1, &(lpwsabuf->len), 0, lpwsaoverlapped
		, NULL);
	if (sendln == SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			Log("WSATCPSend Error!", LOG_TYPE::ERR);
			return -1;
		}
	}
	return sendln;
}

int TCPSocket::WSATCPRecv(LPWSABUF& lpwsabuf, LPWSAOVERLAPPED& lpwsaoverlapped)
{
	int recvln = 0;

	if (WSARecv(m_TCPSocket, lpwsabuf, 1, &lpwsabuf->len, 0, lpwsaoverlapped, NULL)
		== SOCKET_ERROR) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			Log("TCP WSARecv Error!", LOG_TYPE::ERR);
			return -1;
		}
	}
	return recvln;
}

BOOL TCPSocket::WSATCPAccept(SOCKET& clntSocket)
{
	if (m_IsSelectModel == TRUE) {
		Log("IS NOT IOCP MODEL!");
		return FALSE;
	}
	SOCKADDR_IN clnt_addr;
	ZeroMemory(&clnt_addr, sizeof(clnt_addr));
	int addrln = sizeof(clnt_addr);

	clntSocket = WSAAccept(m_TCPSocket, (sockaddr*)&clnt_addr, &addrln, NULL, NULL);
	if (clntSocket == INVALID_SOCKET) {
		Log("TCP Accept Error!", LOG_TYPE::ERR);
		return FALSE;
	}

	return TRUE;
}

BOOL TCPSocket::WSATCPConnect()
{
	if (m_IsSelectModel == TRUE) {
		Log("IS NOT IOCP MODEL!", LOG_TYPE::ERR);
		return FALSE;
	}
	if (WSAConnect(m_TCPSocket, (const sockaddr*)&m_sockAddrin, sizeof(m_sockAddrin)
		, NULL, NULL, NULL, NULL) == SOCKET_ERROR)
	{
		Log("TCP Connect Error!");
		return FALSE;
	}
	return TRUE;
}

TCPSocket::TCPSocket(const TCPSocket& rhs)
	:m_IsSelectModel(rhs.m_IsSelectModel),
	m_sockAddrin(rhs.m_sockAddrin),
	m_TCPSocket(rhs.m_TCPSocket)
{
}

TCPSocket& TCPSocket::operator=(const TCPSocket& rhs)
{
	// TODO: 여기에 return 문을 삽입합니다.
	if (this == &rhs) return *this;
	m_IsSelectModel = rhs.m_IsSelectModel;
	m_sockAddrin = rhs.m_sockAddrin;
	m_TCPSocket = rhs.m_TCPSocket;
	return *this;
}