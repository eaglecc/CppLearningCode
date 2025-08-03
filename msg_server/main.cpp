#include "xmsg_server.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
    XMsgServer server;
    server.Start(); // 启动消息服务器线程
    for (int i = 0; i < 10; i++)
    {
        stringstream ss;
        ss << "msg: " << i + 1;
        server.SendMsg(ss.str());
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    server.Stop();
    cout << "Server stopped." << endl;
    return 0;
}