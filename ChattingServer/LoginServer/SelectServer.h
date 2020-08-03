#pragma once
#include "../CommonLib/Network/TCPSocket.h"
class SelectServer
{
public:
	void Init();
	BOOL Run();
	void Close();
	BOOL GetIsClose() { return m_close; }
private:
	TCPSocket* m_tcpSocket;
	BOOL m_close;
};
