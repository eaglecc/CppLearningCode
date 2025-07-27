#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")  // 链接 Windows Socket 库


class ClientSocket
{
public:
    ClientSocket();
    ~ClientSocket();
private:
    int m_socket;
    sockaddr_in addr;
};

