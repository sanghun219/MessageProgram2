#pragma once
#include "../framework.h"

enum class SERV_MODEL {
	SELECT,
	IOCP,
};

enum class PROTOCOL_TYPE {
	TCP = SOCK_STREAM,
	UDP = SOCK_DGRAM,
};

class MySocket {
public:
	MySocket(SERV_MODEL servType, PROTOCOL_TYPE protoType) {
		switch (servType) {
		case SERV_MODEL::SELECT:
			m_socket = socket(AF_INET, static_cast<int>(protoType), 0);
			break;
		case SERV_MODEL::IOCP:
			m_socket = WSASocket(AF_INET, static_cast<int>(protoType), 0, NULL, NULL, WSA_FLAG_OVERLAPPED);
			break;
		}
		if (m_socket == INVALID_SOCKET) {
			Logger::GetInstance()->Log("Init Socket Error!", LOG_TYPE::ERR);
		}
	}
	~MySocket() {
		CloseSocket();
	}
public:
	void CloseSocket();
	const SOCKET& GetSocket() { return m_socket; }
private:
	SOCKET m_socket;
};