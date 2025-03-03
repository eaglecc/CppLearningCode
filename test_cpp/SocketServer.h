#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")  // Á´½Ó Windows Socket ¿â

class SocketServer
{
public:
    SocketServer();
    ~SocketServer();


private:
    int m_socket;
    sockaddr_in addr;
};

