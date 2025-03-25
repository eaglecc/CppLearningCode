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

    void enqueue(std::function<void()> task);  // �������

private:
    void worker();  // �߳�ִ�е�����

    std::vector<std::thread> workers;       // �̳߳�
    std::queue<std::function<void()>> tasks; // �������

    std::mutex queueMutex;                  // �����������������
    std::condition_variable condition;      // �������������������
    std::atomic<bool> stop;                 // �Ƿ�ֹͣ�̳߳�
};
