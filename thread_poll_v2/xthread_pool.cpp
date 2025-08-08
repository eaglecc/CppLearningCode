#include "xthread_pool.h"
#include <iostream>

void XThreadPool::Init(int threadNum)
{
    std::unique_lock<std::mutex> lock(mux_);
    thread_num_ = threadNum;
    std::cout << "ThreadPool Init Success..." << thread_num_ << std::endl;
}

// Start：会创建指定数量的线程，并让它们开始执行任务
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
        std::thread* th = new std::thread(&XThreadPool::Run, this); // new 完了之后，会立即启动Run函数，所以这里创建了 thread_num_ 个线程，每个线程都会执行 Run 函数
        threads_.push_back(th);
    }
}

void XThreadPool::AddTask(XTask* task)
{
    std::unique_lock<std::mutex> lock(mux_);
    tasks_.push_back(task);
    lock.unlock(); // 释放锁
    cv_.notify_one(); // 通知一个等待的线程有新任务到来
}

XTask* XThreadPool::GetTask()
{
    std::unique_lock<std::mutex> lock(mux_);
    if (tasks_.empty())
    {
        cv_.wait(lock); // 等待任务到来
    }
    if (tasks_.empty())
        return nullptr;
    auto task = tasks_.front();
    tasks_.pop_front();
    return task;
}

// 线程池线程的入口函数
void XThreadPool::Run()
{
    std::cout << "ThreadPool Run..." << std::this_thread::get_id() << std::endl;
    // 每个工作线程都会不断地从任务队列中获取任务并执行，直到线程池被销毁或停止
    while (true) {
        auto task = GetTask();
        if (!task) continue; // 如果没有任务，继续等待
        try {
            task->Run();
        }
        catch (...) {
            // 处理任务执行中的异常
        }
    }
}
