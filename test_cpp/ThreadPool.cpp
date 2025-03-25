#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threadCount) : stop(false) {
    for (size_t i = 0; i < threadCount; ++i) {
        workers.emplace_back(&ThreadPool::worker, this);
    }
}

ThreadPool::~ThreadPool() {
    stop.store(true);
    condition.notify_all();  // ���������̣߳��������˳�

    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();  // �ȴ��߳�ִ�����
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

    condition.notify_one();  // ����һ���߳�ִ������
}

void ThreadPool::worker() {
    while (true) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return stop.load() || !tasks.empty(); });

            if (stop.load() && tasks.empty()) return;  // �̳߳�ֹͣ���������Ϊ��ʱ�˳�

            task = tasks.front();
            tasks.pop();
        }

        task();  // ִ������
    }
}