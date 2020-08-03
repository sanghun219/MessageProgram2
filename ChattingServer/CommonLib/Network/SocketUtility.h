#pragma once

enum class NET_MODEL {
	SELECT,
	IOCP,
};
enum class SOCKET_OPT {
	NONBLOCK,
	REUSEADDR,
};
class SocketUtility {
public:
	inline static void SetNonBlock(SOCKET& socket) {
		u_long argp = 0;
		ioctlsocket(socket, FIONBIO, &argp);
	}

	inline static void ReuseAddr(SOCKET& socket) {
		bool optval = true;
		setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval));
	}
};
