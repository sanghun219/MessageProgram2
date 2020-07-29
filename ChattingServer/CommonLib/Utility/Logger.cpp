#include "Logger.h"

void Log(const WCHAR* msg, LOG_TYPE type)
{
	std::recursive_mutex m_rm;
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

void Log(const char* msg, LOG_TYPE type)
{
	std::recursive_mutex m_rm;
	std::lock_guard<std::recursive_mutex> lock(m_rm);
	switch (type)
	{
	case LOG_TYPE::SYS:

		std::cout << msg << std::endl;
		break;
	case LOG_TYPE::ERR:
		std::cout << "ERROR Num : " << WSAGetLastError() << std::endl;
		std::cout << msg << std::endl;
		break;
	default:
		break;
	}
}

void LogA(const WCHAR* msg, ...)
{
	std::recursive_mutex m_rm;
	std::lock_guard<std::recursive_mutex> lock(m_rm);
	char copymsg[1024];
	ZeroMemory(copymsg, sizeof(copymsg));
	UniConverter::GetInstance()->ConvUnicodeToMulti(msg, copymsg);

	char buf[1024];
	va_list ap;
	va_start(ap, copymsg);
	vsprintf_s(buf, sizeof(buf), copymsg, ap);
	va_end(ap);

	puts(buf);
}

void LogA(const char* msg, ...)
{
	std::recursive_mutex m_rm;
	char buf[1024];
	va_list ap;
	va_start(ap, msg);
	vsprintf_s(buf, sizeof(buf), msg, ap);
	va_end(ap);

	puts(buf);
}