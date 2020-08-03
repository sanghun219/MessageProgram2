#include <iostream>
#include "SelectServer.h"
/*
	서버 매니저 -> 로그인 서버 실행 , 로비 서버랑 연결 후 클라이언트 연결 대기
	클라이언트 정보 받고 쿼리 돌린후 실행 가능하면 로비서버로 정보를 넘김
*/

int main() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		Log(L"WSAStartup Error!", LOG_TYPE::ERR);
		return 0;
	}
	SelectServer serv;
	serv.Init();
	std::thread thr([&]() {
		while (serv.Run());
		return 0;
	});
	std::cout << "서버를 종료하시려면 Y(or y)키를 입력하세요." << std::endl;
	do {
		char c;
		std::cin >> c;
		if (c == 'Y' || c == 'y') {
			break;
		}
	} while (true);

	serv.Close();
	thr.join();
	WSACleanup();

	return 0;
}