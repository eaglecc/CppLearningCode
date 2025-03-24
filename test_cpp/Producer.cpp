#include "Producer.h"

Producer::Producer(size_t maxSize) : maxSize(maxSize), stop(false)
{

}

Producer::~Producer()
{
    stopProcessing();
}

// 启动多个线程
void Producer::start(size_t producerNum, size_t consumerNum)
{
    for (size_t i = 0; i < producerNum; ++i)
    {
        producers.emplace_back(&Producer::produce, this, i + 1);
        // 等价于 producers.push_back(std::thread(&ProducerConsumer::produce, this, i + 1));
    }
    for (size_t i = 0; i < consumerNum; i++)
    {
        consumers.emplace_back(&Producer::consume, this, i + 1);
    }
}

// 生产者线程：不断产生数据，放入缓冲区buffer中
void Producer::produce(int id)
{
    int item = 1;
    while (true) {
        {
            std::unique_lock<std::mutex> lock(mtx);  // 使用互斥锁 mtx 来保护共享资源 buffer。
            condVar.wait(lock, [this] { return buffer.size() < maxSize; }); // 当缓冲区未满时继续执行，否则等待

            if (stop) break; // 如果 stop 为 true，退出循环

            buffer.push(item); // 生产数据，放入缓冲区
            std::cout << "Producer " << id << " produce item " << item << std::endl;
            item++;
        } // 这里作用域结束，`lock` 自动释放互斥锁

        condVar.notify_all();  // 通知消费者，有数据可消费
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Producer::consume(int id)
{
    while (true) {
        int item;
        {
            std::unique_lock<std::mutex> lock(mtx); // 使用互斥锁 mtx 来保护共享资源 buffer。
            condVar.wait(lock, [this] { return !buffer.empty() || stop; }); // 等待条件变量 condVar，直到缓冲区 buffer 非空或 stop 标志为 true。
            if (stop && buffer.empty()) break; // 如果 stop 标志为 true 且缓冲区为空，则退出循环，终止线程。

            item = buffer.front();
            buffer.pop();
            std::cout << "Consumer " << id << " consumed: " << item << std::endl;
        }
        condVar.notify_all(); // 通知所有等待在条件变量 condVar 上的线程，缓冲区状态已改变。
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 模拟消费者处理数据的时间。
    }
}

// 负责安全终止所有线程
void Producer::stopProcessing()
{
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;
    }
    condVar.notify_all();

    for (auto& t : producers) if (t.joinable()) t.join();
    for (auto& t : consumers) if (t.joinable()) t.join();
}
