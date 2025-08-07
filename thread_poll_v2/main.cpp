#include "xthread_pool.h"
#include <iostream>

class MyTask : public XTask {
public:
    int Run() override {
        std::cout << "MyTask is running in thread: " << std::this_thread::get_id() << std::endl;
        return 0;
    }
};


int main(int argc, char *argv[]) {
    XThreadPool pool;
    pool.Init(4);
    pool.Start();



    getchar();
    return 0;
}
