#pragma once
#include <thread>

/* 线程基类 */
class XThread
{
public:
    // 启动线程
    virtual void Start();

    // 请求线程退出，并阻塞等待其结束
    virtual void Stop();

    // 等待线程退出（阻塞）    
    virtual void Wait();

    bool is_exit();

protected:
    bool is_exit_{ false }; // 派生类可以访问

private:
    virtual void Main() = 0; // 线程主入口

    std::thread th_;
};

