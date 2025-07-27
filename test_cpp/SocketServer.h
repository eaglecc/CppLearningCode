#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")  // 链接 Windows Socket 库

class SocketServer
{
public:
    SocketServer();
    SocketServer(int);

    ~SocketServer();
    void handleError(const char*);
    void handleClient(int);
    void multiThreadServer();
    void SelectIOmultiplexingServer();

private:
    int m_socket;
    struct sockaddr_in addr;
};

