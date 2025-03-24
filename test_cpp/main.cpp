#include <iostream>
//#include "MemoryPool.h"
//#include "Student.h"
//#include "SimpleSharedPtr.h"
//#include "ResourceManager.h"
//#include "SocketServer.h"
#include "Producer.h"


int main() {
    Producer producer(5);
    producer.start(2, 4);  // 启动 2 个生产者 + 4 个消费者
    std::this_thread::sleep_for(std::chrono::seconds(5)); // 运行5秒
    producer.stopProcessing();  // 停止生产者线程

    std::cout << "Processing stopped." << std::endl;
    return 0;
}
