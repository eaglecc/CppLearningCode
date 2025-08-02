#include "xmsg_server.h"
#include <iostream>

// 处理消息队列，线程入口函数
void XMsgServer::Main()
{
    while (!is_exit())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟处理间隔
        std::unique_lock<std::mutex> lock(mux_); // 构造的时候就会加锁
        // std::unique_lock<std::mutex> lock(mux_, std::defer_lock); // 构造的时候不加锁，需要手动加锁（手动lock）

        if (msgs_.empty())
            continue;
        // 可以在处理消息队列的时候，把锁释放掉
        while (!msgs_.empty())
        {
            std::cout << "recv: " << msgs_.front() << std::endl;
            msgs_.pop_front();
        }
    } // unique_lock 离开作用域的时候会解锁
}

void XMsgServer::SendMsg(const std::string &msg)
{
    std::unique_lock<std::mutex> lock(mux_);
    msgs_.push_back(msg);
}