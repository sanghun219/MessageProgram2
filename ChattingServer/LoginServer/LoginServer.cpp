#include <iostream>
#include "../CommonLib/Network/DBManager.h"

int main() {
	DBManager::GetInstance()->InitDBManager("LoginServer");
}