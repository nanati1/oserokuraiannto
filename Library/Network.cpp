#include "WinSockFix.h"
#include "Network.h"
#pragma comment(lib, "ws2_32.lib")

Network gNet;

bool Network::Connect(const char* ip, int port) {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &addr.sin_addr);

    return connect(sock, (sockaddr*)&addr, sizeof(addr)) == 0;
}

void Network::Send(const std::string& msg) {
    send(sock, msg.c_str(), (int)msg.size(), 0);
}

bool Network::Recv(std::string& out) {
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(sock, &fds);

    timeval tv{};
    if (select(0, &fds, nullptr, nullptr, &tv) <= 0)
        return false;

    char buf[512];
    int r = recv(sock, buf, sizeof(buf) - 1, 0);
    if (r <= 0) return false;

    buf[r] = 0;
    out = buf;
    return true;
}