#include <thread>
#include <iostream>

using namespace std;

class MyThread {
public:
    // 线程入口
    void Main() {
        cout << "MyThread Main..." << this->name << ": " << this->age;
    }

    string name{ "" };
    int age{ 20 };
};

class XThread {
public:
    virtual void Start() {
        is_exit_ = false;
        th_ = std::thread(&XThread::Main, this);
    }
    virtual void Wait() {
        if (th_.joinable())
        {
            th_.join();
        }
    }
    virtual void () {
        is_exit_ = true;
        Wait();
    }
    bool is_exit(){ return this->is_exit_; }
private:
    virtual void Main() = 0;
    std::thread th_;
    bool is_exit_{ false };
};

class TestXThread: public XThread {
public:
    void Main() {
        cout << "TestXThread Main: "<< endl;
        while (!is_exit()) {
            this_thread::sleep_for(100ms);
            cout << "." << flush;
        }
    }
    string name;
};

int main(int argc, char* argv[])
{
    TestXThread testth;
    testth.name = "小飞鱼";
    testth.Start();
    testth.Wait();


    //MyThread myth;
    //myth.name = "张飞";
    //myth.age = 18;

    //thread th(&MyThread::Main, &myth); // 成员函数的指针，子线程是不能直接访问的，需要有当前对象的地址 &myth作为参数传递
    //th.join();
    return 0;
}