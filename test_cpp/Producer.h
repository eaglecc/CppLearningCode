#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

// ������-������ģ��
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
    std::queue<int> buffer;             // �������
    size_t maxSize;                     // �����������
    bool stop;                          // �߳�ֹͣ��־

    std::mutex mtx;                     // ������
    std::condition_variable condVar;    // ��������

    std::vector<std::thread> producers; // �������߳�
    std::vector<std::thread> consumers; // �������߳�
};

