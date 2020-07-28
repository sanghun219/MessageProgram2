#include "Clock.h"
#include <cstring>
void Clock::PrintCurrentClock()
{
	time_t now = time(0);
	localtime_s(&m_tm, &now);
	char tempbuf[80] = { 0, };
	std::strftime(tempbuf, 80, "%Y-%m-%d.%X", &m_tm);
	printf("%s", tempbuf);
}

void Clock::GetCurrentClock(std::string& str, const char* fmt)
{
	time_t now = time(0);
	localtime_s(&m_tm, &now);
	char tempbuf[80] = { 0, };
	std::strftime(tempbuf, sizeof(tempbuf), fmt, &m_tm);
	str.assign(tempbuf);
}

DAYS Clock::GetCurrentDay()
{
	DAYS days = DAYS::NONE;
	time_t now = time(0);
	localtime_s(&m_tm, &now);
	switch (m_tm.tm_wday)
	{
	case 0:
		days = DAYS::SUN;
		break;
	case 1:
		days = DAYS::MON;
		break;
	case 2:
		days = DAYS::TUE;
		break;
	case 3:
		days = DAYS::WED;
		break;
	case 4:
		days = DAYS::THURS;
		break;
	case 5:
		days = DAYS::FRI;
		break;
	case 6:
		days = DAYS::SAT;
		break;
	default:
		days = DAYS::NONE;
		break;
	}

	return days;
}

void Clock::GetMinToMillSec(std::string& str)
{
	SYSTEMTIME cur_time;
	GetLocalTime(&cur_time);

	char tempbuf[80] = { 0, };
	sprintf_s(tempbuf, "%02d:%02d.%03d", cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds);
	str.assign(tempbuf);
}