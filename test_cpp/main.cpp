#include <iostream>
//#include "MemoryPool.h"
//#include "Student.h"
//#include "SimpleSharedPtr.h"
//#include "ResourceManager.h"
//#include "SocketServer.h"
#include "Producer.h"


int main() {
    Producer producer(5);
    producer.start(2, 4);  // ���� 2 �������� + 4 ��������
    std::this_thread::sleep_for(std::chrono::seconds(5)); // ����5��
    producer.stopProcessing();  // ֹͣ�������߳�

    std::cout << "Processing stopped." << std::endl;
    return 0;
}
