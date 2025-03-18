#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")  // ���� Windows Socket ��

class SocketServer
{
public:
    SocketServer();
    SocketServer(int);
    ~SocketServer();
    void handleError(const char*);
    void handleClient(int);

private:
    int m_socket;
    struct sockaddr_in addr;
};

