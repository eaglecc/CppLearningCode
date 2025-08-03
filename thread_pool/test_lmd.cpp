#include <thread>
#include <mutex>
#include <list>
#include <iostream>
#include <string>

std::mutex mtx;
std::condition_variable cv;

std::list<std::string> m_lists;

void ThreadWrite()
{
    for (int i = 0;;i++)
    {
        std::unique_lock<std::mutex> lock(mtx);
        m_lists.push_back("hello"+i);

        lock.unlock(); // 要先解锁，才能用条件变量通知等待的线程读
        cv.notify_one(); 

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void ThreadRead(int i)
{
    for (;;)
    {
        std::unique_lock<std::mutex> lock(mtx); // 读线程也需要加锁读
        // cv.wait(lock); // 等待条件变量，直到有数据
        cv.wait(lock, [] {return !m_lists.empty(); }); // 如果lambda表达式返回true，则继续执行，否则等待
        // 获取信号后锁定
        while (!m_lists.empty())
        {
            std::cout << i << "read :" << m_lists.front() << std::endl;
            m_lists.pop_front();
        }
    }

}

void main(int argc, char* argv[])
{
    std::thread th_write(ThreadWrite);
    th_write.detach();
    for (int i = 0; i < 3; i++)
    {
        std::thread th_read(ThreadRead, i);
    }

}
