#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

class XMutex
{
public:
    XMutex(mutex& mux): m_mux(mux){
        std::cout << "Lock ... " << std::endl;
        mux.lock();
    }
    ~XMutex() {
        cout << "UnLock ..." << endl;
        m_mux.unlock();
    }

private:
    mutex& m_mux; // ������Ҫ�ڳ�ʼ����ʱ��ֵ
};

static mutex mux;
void TestMutex() {
    XMutex lock(mux); // ջ�е���Դ��������ʱ�����
    // һЩ��ʱ��ҵ���߼�...
    // �Ҵ����� ������ʱ�� lock �ᱻ�Զ��ͷţ�Ȼ�������������������
}

int main(int argc, char* argv[] )
{

}