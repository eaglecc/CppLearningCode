#include "ClientSocket.h"

ClientSocket::ClientSocket()
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
    std::cout << "client Socket.." << m_socket << std::endl;
    // 2. connect
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9527);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    if (connect(m_socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Connect 失败: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        WSACleanup();
    }
    // 3. send
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    strcpy_s(buf, "Hello, Server!");
    send(m_socket, buf, sizeof(buf), 0);
    std::cout << "客户端发送消息：" << buf << std::endl;
    // 4. recv
    memset(buf, 0, sizeof(buf));
    recv(m_socket, buf, sizeof(buf), 0);
    std::cout << "客户端接收消息：" << buf << std::endl;

    Sleep(10000); // 测试客户端退出时间 是否会组织服务器端退出
}

ClientSocket::~ClientSocket()
{
    closesocket(m_socket);
    WSACleanup();
}
