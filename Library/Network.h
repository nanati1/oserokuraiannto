#pragma once
#include "WinSockFix.h"
#include <string>

class Network {
public:
    bool Connect(const char* ip, int port);
    void Send(const std::string& msg);
    bool Recv(std::string& out);

private:
    SOCKET sock = INVALID_SOCKET;
};
