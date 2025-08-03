#pragma once
#include "xthread.h"
#include <string>
#include <list>
#include <mutex>

class XMsgServer: public XThread
{
public:
    void Main() override;
    
    // 给当前线程发消息
    void SendMsg(const std::string& msg);

    void Stop() override;
private:

    // 消息队列缓冲 ,std::list不是线程安全的，因此需要锁来保护
    std::list<std::string> msgs_;

    // 互斥锁，保护消息队列
    std::mutex mux_;

    // 条件变量
    std::condition_variable cv_;
};

