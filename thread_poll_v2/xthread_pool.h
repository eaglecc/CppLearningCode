#pragma once
#include <thread>
#include <mutex>
#include <vector>
#include <list>
#include <functional>
#include <atomic>
#include <future>

// 任务
class XTask
{ 
public:
    virtual int Run() = 0; // 任务的执行函数
    std::function<bool()> is_exit = nullptr;

    auto GetReturn()
    {
        return p_.get_future().get(); // 获取返回值的 future 对象
    }
    void SetValue(int v)
    {
        p_.set_value(v); // 设置返回值
    }
    

private:
    std::promise<int> p_; //用来接受返回值
};

// 线程池
class XThreadPool
{
public:
    // 初始化线程池
    void Init(int threadNum);
    // 启动所有线程，必须先Init
    void Start();
    // 线程池退出
    void Stop();

    // 插入一个任务到线程池
    //void AddTask(XTask* task);
    void AddTask(std::shared_ptr<XTask> task);

    // 获取任务
    //XTask* GetTask();
    std::shared_ptr<XTask> GetTask();

    // 线程池是否退出
    bool is_exit() const { return is_exit_; }

    // 获取正在运行的任务数量
    int task_run_count() const { return task_run_count_.load(); }

private:
    // 线程池线程的入口函数
    void Run();

    int thread_num_ = 0;
    std::mutex mux_;
    //std::vector<std::thread*> threads_;
    std::vector<std::shared_ptr<std::thread>> threads_; // 使用智能指针管理线程

    //std::list<XTask*> tasks_; // 任务队列 
    std::list<std::shared_ptr<XTask>> tasks_; // 任务队列，使用智能指针管理任务
    std::condition_variable cv_;
    bool is_exit_{ false }; // 线程是否退出
    std::atomic<int> task_run_count_{ 0 }; // 正在运行的任务数量
};

