#include "SelectServer.h"
#include "../CommonLib/Network/DBManager.h"
void SelectServer::Init()
{
	// db 초기화, 소켓 생성
	DBManager::GetInstance()->InitDBManager("LoginServer");
	m_close = false;
	SOCKET listnsocket;

	m_tcpSocket = new TCPSocket(listnsocket, NET_MODEL::SELECT);
	if (!m_tcpSocket->ListenNBindSocket()) {
		m_close = true;
		return;
	}

	// Option 설정 (논블록,비동기)
	m_tcpSocket->SetSockOpt(SOCKET_OPT::NONBLOCK);
	m_tcpSocket->SetSockOpt(SOCKET_OPT::REUSEADDR);
}

BOOL SelectServer::Run()
{
	// 세션 받고, db 이용해서 로그인 정보 확인후 해당 정보를 다른 서버에 넘겨줘야함.
	while (true) {
	}

	return FALSE;
}

void SelectServer::Close()
{
	m_close = true;
}