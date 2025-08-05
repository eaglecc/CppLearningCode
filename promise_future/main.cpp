#include <thread>
#include <mutex>
#include <future>
#include <string>
#include <iostream>

void TestFunc(std::promise<std::string> p) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟一些工作
    p.set_value("Hello from thread!"); // 设置promise的值
}
 
int main(int argc, char* argv[]) {
    std::promise<std::string> p;

    auto fu = p.get_future(); // 绑定future 

    std::thread t(TestFunc, std::move(p)); // 将promise传递给线程
    t.detach();

    auto res = fu.get(); // 会阻塞，直到promise被设置值

    std::cout << "Result: " << res << std::endl;
    getchar();
    return 0;
}