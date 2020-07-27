#pragma once
#include "MySocket.h"

inline void ReuseAddrOpt(MySocket sock, const int onoff) {
	int optval = onoff;
	setsockopt(sock.GetSocket(), SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval));
}

inline void SetBufSize(MySocket sock) {
	int RcvBuf;
	setsockopt(sock.GetSocket(), SOL_SOCKET, SO_RCVBUF, (const char*)&RcvBuf, sizeof(RcvBuf));
	setsockopt(sock.GetSocket(), SOL_SOCKET, SO_SNDBUF, (const char*)&RcvBuf, sizeof(RcvBuf));
}

inline void SetLinger(MySocket sock, int onoff, int timeout) {
	linger lg;
	lg.l_onoff = 1;
	lg.l_linger = timeout; // 비정상 즉각 종료
	setsockopt(sock.GetSocket(), SOL_SOCKET, SO_LINGER, (const char*)&lg, sizeof(lg));
}