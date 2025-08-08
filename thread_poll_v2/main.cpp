#include "xthread_pool.h"
#include <iostream>

class MyTask : public XTask {
public:
    int Run() override {
        std::unique_lock<std::mutex> lock(mux_);
        std::cout << "==========================begin=========================" << std::endl;
        std::cout << "MyTask is running in thread: " << std::this_thread::get_id() << "-- name is: " << name << std::endl;
        std::cout << "==========================end=======================" << std::endl;
        for (size_t i = 0; i < 10; i++)
        {
            if (is_exit())
                break;
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        return 0;
    }
    std::string name = "";
private:
    std::mutex mux_;
};


int main(int argc, char *argv[]) {
    XThreadPool pool;
    pool.Init(16);
    pool.Start();

    MyTask task1;
    task1.name = "Task 1";
    pool.AddTask(&task1);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    pool.Stop();

    getchar();
    return 0;
}
