#include <iostream>
#include <mutex>
//#include "MemoryPool.h"
//#include "Student.h"
//#include "SimpleSharedPtr.h"
//#include "ResourceManager.h"
//#include "SocketServer.h"
//#include "Producer.h"
#include "ThreadPool.h"

std::mutex printMutex;

void testFunction(int id) {
    std::lock_guard<std::mutex> lock(printMutex);
    std::cout << "Task " << id << " is executing on thread "
        << std::this_thread::get_id() << std::endl;
}

int main() {
    ThreadPool pool(4);
    // ģ�����10������
    for (size_t i = 0; i < 100; i++)
    {
        pool.enqueue([i]() {testFunction(i); });
    }
    std::this_thread::sleep_for(std::chrono::seconds(2)); // �ȴ�����ִ��

    return 0;
}
