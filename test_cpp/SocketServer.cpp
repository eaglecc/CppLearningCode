#include "SocketServer.h"
#include <thread>

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
        std::cerr << "Bind ʧ��: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        WSACleanup();
        return;
    }
    // 3. listen
    if (listen(m_socket, 5) == SOCKET_ERROR) {
        std::cerr << "Listen ʧ��: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        WSACleanup();
        return;
    }
    std::cout << "�����������˿� 9527..." << std::endl;
    // 4. accept
    int new_socket;
    sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    new_socket = accept(m_socket, (SOCKADDR*)&client_addr, &client_addr_len);
    if (new_socket == INVALID_SOCKET) {
        std::cerr << "Accept ʧ��: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        WSACleanup();
        return;
    }

    std::cout << "�ͻ��������ӣ�" << std::endl;
    char buf[1024];
    for (;;)
    {
        // 5. recv
        memset(buf, 0, sizeof(buf));
        recv(new_socket, buf, sizeof(buf), 0);
        std::cout << "������������Ϣ��" << buf << std::endl;
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

// ���̲߳���������
SocketServer::SocketServer(int serverType)
{
    switch (serverType)
    {
    case 1:
        std::cout << "���̲߳���������" << std::endl;
        multiThreadServer();
        break;
    case 2:
        std::cout << "IO���ò���������--Select" << std::endl;
        break;
    default:
        break;
    }
    
}



SocketServer::~SocketServer()
{
    closesocket(m_socket);
    WSACleanup();
}

void SocketServer::handleError(const char*s)
{
    perror(s);
    exit(-1);
}

void SocketServer::handleClient(int cli_socket)
{
    std::cout << "�ͻ���������, clisocket id��" << cli_socket << std::endl;
    char buf[1024];
    for (;;) {
        // 5. recv
        memset(buf, 0, sizeof(buf));
        int bytesReceived = recv(cli_socket, buf, sizeof(buf), 0);
        if (bytesReceived <= 0) {
            std::cerr << "����ʧ�ܻ�ͻ��˶Ͽ�����" << std::endl;
            closesocket(cli_socket);
            return;
        }
        std::cout << "������������Ϣ��" << buf << std::endl;
        // 6. send
        for (size_t i = 0; buf[i] != '\0'; i++)
        {
            buf[i] = std::toupper(buf[i]);
        }
        send(cli_socket, buf, sizeof(buf), 0);
        memset(buf, 0, sizeof(buf));
    }

    closesocket(cli_socket);
}

void SocketServer::multiThreadServer()
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
        std::cerr << "Bind ʧ��: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        WSACleanup();
        return;
    }
    // 3. listen
    if (listen(m_socket, 5) == SOCKET_ERROR) {
        std::cerr << "Listen ʧ��: " << WSAGetLastError() << std::endl;
        closesocket(m_socket);
        WSACleanup();
        return;
    }
    std::cout << "�����������˿� 9527..." << std::endl;
    // 4. accept ���̲߳���������
    while (1) {
        std::cout << "�ȴ��ͻ�������..." << std::endl;
        int new_socket;
        sockaddr_in client_addr;
        int client_addr_len = sizeof(client_addr);
        new_socket = accept(m_socket, (SOCKADDR*)&client_addr, &client_addr_len);
        if (new_socket == INVALID_SOCKET) {
            std::cerr << "Accept ʧ��: " << WSAGetLastError() << std::endl;
            closesocket(m_socket);
            WSACleanup();
            return;
        }
        std::cout << "�ͻ��������ӣ�" << std::endl;
        std::thread t(&SocketServer::handleClient, this, new_socket);
        t.detach();
    }
    return;
}

// select IO���÷�����
void SocketServer::SelectIOmultiplexingServer()
{

}
