#include "xthread_pool.h"
#include <iostream>

void XThreadPool::Init(int threadNum)
{
    std::unique_lock<std::mutex> lock(mux_);
    thread_num_ = threadNum;
    std::cout << "ThreadPool Init Success..." << thread_num_ << std::endl;
}

void XThreadPool::Start()
{
    std::unique_lock<std::mutex> lock(mux_);
    if (thread_num_ <= 0)
    {
        std::cerr << "Please Init XThreadPool!" << std::endl;
        return;
    }
    if (!threads_.empty())
    {
        std::cerr << "Thread pool has start!" << std::endl;
        return;
    }

    for (size_t i = 0; i < thread_num_; i++)
    {
        std::thread* th = new std::thread(&XThreadPool::Run, this);
        threads_.push_back(th);
    }
}

void XThreadPool::AddTask(XTask* task)
{
    std::unique_lock<std::mutex> lock(mux_);
    tasks_.push_back(task);
}

// 线程池线程的入口函数
void XThreadPool::Run()
{
    std::cout << "ThreadPool Run..." << std::this_thread::get_id() << std::endl;
}
