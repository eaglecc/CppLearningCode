#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

// 生产者-消费者模型
class Producer
{
public:
    Producer(size_t maxSize);
    ~Producer();

public:
    void start(size_t producerNum, size_t consumerNum);
    void produce(int id);
    void consume(int id);
    void stopProcessing();

public:
    std::queue<int> buffer;             // 任务队列
    size_t maxSize;                     // 队列最大容量
    bool stop;                          // 线程停止标志

    std::mutex mtx;                     // 互斥锁
    std::condition_variable condVar;    // 条件变量

    std::vector<std::thread> producers; // 生产者线程
    std::vector<std::thread> consumers; // 消费者线程
};

