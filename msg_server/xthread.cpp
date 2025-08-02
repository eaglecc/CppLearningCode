#include "xthread.h"
using namespace std;

void XThread::Start()
{
    is_exit_ = false;
    th_ = thread(&XThread::Main, this); // 启动线程，绑定成员函数
}

void XThread::Stop()
{
    is_exit_ = true;
    Wait();
}

void XThread::Wait()
{
    if (th_.joinable())
    {
        th_.join();
    }
}

bool XThread::is_exit()
{
    return is_exit_;
}

