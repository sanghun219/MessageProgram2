#pragma once
#include "../framework.h"

// ���� �ð�, �ð� ���� ����, ���� �ð� ��µ��
enum class DAYS {
	SUN,
	MON,
	TUE,
	WED,
	THURS,
	FRI,
	SAT,
	NONE = -1,
};
class Clock {
public:
	void PrintCurrentClock();
	inline tm GetTm() { return m_tm; }
public:
	void GetCurrentClock(std::string& str, const char* fmt = "%Y-%m-%d.%X");
	DAYS GetCurrentDay();
	void GetMinToMillSec(std::string& str);
private:
	time_t m_current;
	tm m_tm;
};
