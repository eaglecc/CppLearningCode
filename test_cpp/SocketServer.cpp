#include "SocketServer.h"

SocketServer::SocketServer() : m_socket(INVALID_SOCKET)
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed: %d\n", result);
    }
    // 1. create socket
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
    }
    // 2. bind socket
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9527);
    if (bind(m_socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Bind 失败: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        WSACleanup();
        return;
    }
    // 3. listen
    if (listen(m_socket, 5) == SOCKET_ERROR) {
        std::cerr << "Listen 失败: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        WSACleanup();
        return;
    }
    std::cout << "服务器监听端口 9527..." << std::endl;
    // 4. accept
    int new_socket;
    sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    new_socket = accept(m_socket, (SOCKADDR*)&client_addr, &client_addr_len);
    if (new_socket == INVALID_SOCKET) {
        std::cerr << "Accept 失败: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        WSACleanup();
        return;
    }

    std::cout << "客户端已连接！" << std::endl;
    char buf[1024];
    for (;;)
    {
        // 5. recv
        memset(buf, 0, sizeof(buf));
        recv(new_socket, buf, sizeof(buf), 0);
        std::cout << "服务器接收消息：" << buf << std::endl;
        // 6. send
        for (size_t i = 0; buf[i] != '\0'; i++)
        {
            buf[i] = std::toupper(buf[i]);
        }
        send(new_socket, buf, sizeof(buf), 0);
        memset(buf, 0, sizeof(buf));
        Sleep(3000);
    }

    closesocket(new_socket);
    return;
}

SocketServer::~SocketServer()
{
    closesocket(m_socket);
    WSACleanup();
}
