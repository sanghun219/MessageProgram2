#include "MySocket.h"

void MySocket::CloseSocket()
{
	closesocket(m_socket);
}