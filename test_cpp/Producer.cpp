#include "Producer.h"

Producer::Producer(size_t maxSize) : maxSize(maxSize), stop(false)
{

}

Producer::~Producer()
{
    stopProcessing();
}

// ��������߳�
void Producer::start(size_t producerNum, size_t consumerNum)
{
    for (size_t i = 0; i < producerNum; ++i)
    {
        producers.emplace_back(&Producer::produce, this, i + 1);
        // �ȼ��� producers.push_back(std::thread(&ProducerConsumer::produce, this, i + 1));
    }
    for (size_t i = 0; i < consumerNum; i++)
    {
        consumers.emplace_back(&Producer::consume, this, i + 1);
    }
}

// �������̣߳����ϲ������ݣ����뻺����buffer��
void Producer::produce(int id)
{
    int item = 1;
    while (true) {
        {
            std::unique_lock<std::mutex> lock(mtx);  // ʹ�û����� mtx ������������Դ buffer��
            condVar.wait(lock, [this] { return buffer.size() < maxSize; }); // ��������δ��ʱ����ִ�У�����ȴ�

            if (stop) break; // ��� stop Ϊ true���˳�ѭ��

            buffer.push(item); // �������ݣ����뻺����
            std::cout << "Producer " << id << " produce item " << item << std::endl;
            item++;
        } // ���������������`lock` �Զ��ͷŻ�����

        condVar.notify_all();  // ֪ͨ�����ߣ������ݿ�����
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Producer::consume(int id)
{
    while (true) {
        int item;
        {
            std::unique_lock<std::mutex> lock(mtx); // ʹ�û����� mtx ������������Դ buffer��
            condVar.wait(lock, [this] { return !buffer.empty() || stop; }); // �ȴ��������� condVar��ֱ�������� buffer �ǿջ� stop ��־Ϊ true��
            if (stop && buffer.empty()) break; // ��� stop ��־Ϊ true �һ�����Ϊ�գ����˳�ѭ������ֹ�̡߳�

            item = buffer.front();
            buffer.pop();
            std::cout << "Consumer " << id << " consumed: " << item << std::endl;
        }
        condVar.notify_all(); // ֪ͨ���еȴ����������� condVar �ϵ��̣߳�������״̬�Ѹı䡣
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // ģ�������ߴ������ݵ�ʱ�䡣
    }
}

// ����ȫ��ֹ�����߳�
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
