#include "SelectServer.h"
#include "../CommonLib/Network/DBManager.h"
void SelectServer::Init()
{
	// db �ʱ�ȭ, ���� ����
	DBManager::GetInstance()->InitDBManager("LoginServer");
	m_close = false;
	SOCKET listnsocket;

	m_tcpSocket = new TCPSocket(listnsocket, NET_MODEL::SELECT);
	if (!m_tcpSocket->ListenNBindSocket()) {
		m_close = true;
		return;
	}

	// Option ���� (����,�񵿱�)
	m_tcpSocket->SetSockOpt(SOCKET_OPT::NONBLOCK);
	m_tcpSocket->SetSockOpt(SOCKET_OPT::REUSEADDR);
}

BOOL SelectServer::Run()
{
	// ���� �ް�, db �̿��ؼ� �α��� ���� Ȯ���� �ش� ������ �ٸ� ������ �Ѱ������.
	while (true) {
	}

	return FALSE;
}

void SelectServer::Close()
{
	m_close = true;
}