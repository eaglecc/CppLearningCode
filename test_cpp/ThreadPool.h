#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    explicit ThreadPool(size_t threadCount);
    ~ThreadPool();

    void enqueue(std::function<void()> task);  // 添加任务

private:
    void worker();  // 线程执行的任务

    std::vector<std::thread> workers;       // 线程池
    std::queue<std::function<void()>> tasks; // 任务队列

    std::mutex queueMutex;                  // 互斥锁保护任务队列
    std::condition_variable condition;      // 条件变量控制任务调度
    std::atomic<bool> stop;                 // 是否停止线程池
};
