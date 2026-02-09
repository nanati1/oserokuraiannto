#include "Network.h"
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

Network gNet;

Network::Network() {
    // Winsock ÇÕç≈èâÇÃ Connect Ç≈èâä˙âª
}

Network::~Network() {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
        sock = INVALID_SOCKET;
    }
}

bool Network::Connect(const char* ip, int port) {
    static bool wsaDone = false;
    if (!wsaDone) {
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return false;
        wsaDone = true;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) return false;

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) != 0) {
        closesocket(sock);
        sock = INVALID_SOCKET;
        return false;
    }

    return true;
}

void Network::Send(const std::string& msg) {
    if (sock == INVALID_SOCKET) return;
    send(sock, msg.c_str(), (int)msg.size(), 0);
}

bool Network::Recv(std::string& out) {
    if (sock == INVALID_SOCKET) return false;

    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(sock, &fds);

    timeval tv{};
    int maxSock = (int)sock + 1;
    int sel = select(maxSock, &fds, nullptr, nullptr, &tv);
    if (sel <= 0) return false;

    char buf[512];
    int r = recv(sock, buf, sizeof(buf) - 1, 0);
    if (r <= 0) {
        closesocket(sock);
        sock = INVALID_SOCKET;
        return false;
    }

    buf[r] = 0;
    out = buf;
    return true;
}