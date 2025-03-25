#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threadCount) : stop(false) {
    for (size_t i = 0; i < threadCount; ++i) {
        workers.emplace_back(&ThreadPool::worker, this);
    }
}

ThreadPool::~ThreadPool() {
    stop.store(true);
    condition.notify_all();  // 唤醒所有线程，让它们退出

    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();  // 等待线程执行完毕
        }
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (stop.load()) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        tasks.push(task);
    }

    condition.notify_one();  // 唤醒一个线程执行任务
}

void ThreadPool::worker() {
    while (true) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return stop.load() || !tasks.empty(); });

            if (stop.load() && tasks.empty()) return;  // 线程池停止且任务队列为空时退出

            task = tasks.front();
            tasks.pop();
        }

        task();  // 执行任务
    }
}