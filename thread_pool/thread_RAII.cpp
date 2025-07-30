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
    mutex& m_mux; // 引用需要在初始化的时候赋值
};

static mutex mux;
void TestMutex() {
    XMutex lock(mux); // 栈中的资源，创建的时候加锁
    // 一些耗时的业务逻辑...
    // 右大括号 结束的时候 lock 会被自动释放，然后调用析构函数，解锁
}

int main(int argc, char* argv[] )
{

}