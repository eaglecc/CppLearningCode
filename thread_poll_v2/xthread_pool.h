#pragma once
#include <thread>
#include <mutex>
#include <vector>
#include <list>

// 任务
class XTask
{ 
public:
    virtual int Run() = 0; // 任务的执行函数
};

// 线程池
class XThreadPool
{
public:
    // 初始化线程池
    void Init(int threadNum);
    // 启动所有线程，必须先Init
    void Start();
    // 插入一个任务到线程池
    void AddTask(XTask* task);
    // 获取任务
    XTask* GetTask();

private:
    // 线程池线程的入口函数
    void Run();

    int thread_num_ = 0;
    std::mutex mux_;
    std::vector<std::thread*> threads_;
    std::list<XTask*> tasks_; // 任务队列 
    std::condition_variable cv_;
};

