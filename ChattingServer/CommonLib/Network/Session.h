#pragma once
#include <WinSock2.h>
class Stream;
#pragma pack(push,1)
struct Session {
	bool IsConnected() { return FD != NULL ? true : false; }
	SOCKET FD = NULL;
	UINT sessionNum = 0;
	Stream* stream = nullptr;
};

#pragma pack(pop)