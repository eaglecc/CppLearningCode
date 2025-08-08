#include "xthread_pool.h"
#include <iostream>

class MyTask : public XTask {
public:
    int Run() override {
        std::cout << "MyTask is running in thread: " << std::this_thread::get_id() << "-- name is: " << name << std::endl;
        return 0;
    }
    std::string name = "";
};


int main(int argc, char *argv[]) {
    XThreadPool pool;
    pool.Init(16);
    pool.Start();

    MyTask task1;
    task1.name = "Task 1";
    pool.AddTask(&task1);

    getchar();
    return 0;
}
