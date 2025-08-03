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

        cv_.wait(lock, [this]() {
            if (is_exit()) return true; // 如果线程已经退出了，直接返回
            return !msgs_.empty(); 
        });

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

    lock.unlock();
    cv_.notify_one(); // 通知等待的线程有新消息到来
}

void XMsgServer::Stop()
{
    is_exit_ = true;
    cv_.notify_all(); // 通知所有等待的线程退出
    Wait();
}
