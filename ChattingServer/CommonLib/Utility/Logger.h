#pragma once
#include "../framework.h"

enum class LOG_TYPE {
	SYS,
	ERR,
};
void Log(const WCHAR* msg, LOG_TYPE type = LOG_TYPE::SYS);
void Log(const char* msg, LOG_TYPE type = LOG_TYPE::SYS);
void LogA(const WCHAR* msg, ...);
void LogA(const char* msg, ...);