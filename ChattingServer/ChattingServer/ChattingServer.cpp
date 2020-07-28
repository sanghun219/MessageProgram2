#include "../CommonLib/framework.h"
int main() {
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		Logger::GetInstance()->Log("wsastartup error!");
	}

	SOCKET listnsock = socket(AF_INET, SOCK_STREAM, 0);
	if (listnsock == INVALID_SOCKET) {
		Logger::GetInstance()->Log("listn sock error!");
	}

	sockaddr_in addr_in;
	memset(&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(32000);
	addr_in.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	if (bind(listnsock, (const sockaddr*)&addr_in, sizeof(addr_in)) == SOCKET_ERROR) {
		Logger::GetInstance()->Log("bind", LOG_TYPE::ERR);
	}

	if (listen(listnsock, 5) == SOCKET_ERROR) {
		Logger::GetInstance()->Log("listn", LOG_TYPE::ERR);
	}

	sockaddr_in cli_addr;
	memset(&cli_addr, 0, sizeof(cli_addr));
	int lenaddr = sizeof(cli_addr);
	while (true) {
		SOCKET socket = accept(listnsock, (sockaddr*)&cli_addr, &lenaddr);
		if (socket == INVALID_SOCKET) {
			Logger::GetInstance()->Log("ACCEPT", LOG_TYPE::ERR);
		}
		char buf[1024] = { 0, };
		int re = recv(socket, buf, sizeof(buf), 0);

		std::cout << buf << std::endl;
	}
}