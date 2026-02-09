#pragma once
#include "WinSockFix.h"
#include <string>

class Network {
public:
    Network();
    ~Network();

    bool Connect(const char* ip, int port);
    void Send(const std::string& msg);
    bool Recv(std::string& out);
    bool IsConnected() const { return sock != INVALID_SOCKET; }

private:
    SOCKET sock = INVALID_SOCKET;
};
extern Network gNet;