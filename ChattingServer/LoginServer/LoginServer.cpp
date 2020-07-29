#include <iostream>
#include "../CommonLib/Network/DBManager.h"
void Init();
void Update();
/*
	서버 매니저 -> 로그인 서버 실행 , 로비 서버랑 연결 후 클라이언트 연결 대기
	클라이언트 정보 받고 쿼리 돌린후 실행 가능하면 로비서버로 정보를 넘김
*/

int main() {
}

void Init()
{
	DBManager::GetInstance()->InitDBManager("LoginServer");
}

void Update()
{
}