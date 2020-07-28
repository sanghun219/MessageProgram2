#pragma once
#include "../framework.h"
#include "Singleton.h"

enum class LOG_TYPE {
	SYS,
	ERR,
};

class Logger : public Singleton<Logger> {
public:
	void Log(const WCHAR* msg, LOG_TYPE type = LOG_TYPE::SYS);
	void Log(const char* msg, LOG_TYPE type = LOG_TYPE::SYS);
	void LogA(const WCHAR* msg, ...);
	void LogA(const char* msg, ...);
private:
	std::recursive_mutex m_rm;
};
