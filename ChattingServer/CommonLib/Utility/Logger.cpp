#include "Logger.h"

void Logger::Log(const WCHAR* msg, LOG_TYPE type)
{
	std::lock_guard<std::recursive_mutex> lock(m_rm);
	char copymsg[1024];
	switch (type)
	{
	case LOG_TYPE::SYS:

		UniConverter::GetInstance()->ConvUnicodeToMulti(msg, copymsg);
		std::cout << copymsg << std::endl;
		break;
	case LOG_TYPE::ERR:
		std::cout << "ERROR Num : " << WSAGetLastError() << std::endl;
		UniConverter::GetInstance()->ConvUnicodeToMulti(msg, copymsg);
		std::wcout << copymsg << std::endl;
		exit(0);
		break;
	default:
		break;
	}
}

void Logger::Log(const char* msg, LOG_TYPE type)
{
	std::lock_guard<std::recursive_mutex> lock(m_rm);
	switch (type)
	{
	case LOG_TYPE::SYS:

		std::cout << msg << std::endl;
		break;
	case LOG_TYPE::ERR:
		std::cout << "ERROR Num : " << WSAGetLastError() << std::endl;
		std::cout << msg << std::endl;
		exit(0);
		break;
	default:
		break;
	}
}