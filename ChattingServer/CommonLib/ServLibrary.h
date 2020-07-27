#pragma once

#pragma comment (lib,"ws2_32.lib")
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <memory>
#include <process.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <thread>
#include <mutex>

#include "Utility/Define.h"

// 순서 중요!
#include "Utility/Singleton.h"
#include "Utility/UniConverter.h"
#include "Utility/Logger.h"