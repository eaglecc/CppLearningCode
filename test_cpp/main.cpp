#include <iostream>
#include "MemoryPool.h"
#include "Student.h"
#include "SimpleSharedPtr.h"

int main() {
    std::cout << "SimpleSharedPtr..." << std::endl;
    SimpleSharedPtr<CStudent> ptr1; // 默认构造函数
    std::cout << "ptr1.use_count() = " << ptr1.use_count() << std::endl;

    SimpleSharedPtr<CStudent> ptr2(new CStudent("Tom", 14, "Class1")); // 带参构造函数
    std::cout << "ptr2.use_count() = " << ptr2.use_count() << std::endl;

    SimpleSharedPtr<CStudent> ptr3(ptr2); // 拷贝构造函数
    std::cout << "ptr3.use_count() = " << ptr3.use_count() << std::endl;

    SimpleSharedPtr<CStudent> ptr4 = ptr2; // 赋值运算符重载
    std::cout << "ptr4.use_count() = " << ptr4.use_count() << std::endl;

    SimpleSharedPtr<CStudent> ptr5 = std::move(ptr2); // 移动构造函数
    std::cout << "ptr5.use_count() = " << ptr5.use_count() << std::endl;

    //std::cout << "ptr2.use_count() = " << ptr2.use_count() << std::endl;
    //std::cout << "ptr3.use_count() = " << ptr3.use_count() << std::endl;
    //std::cout << "ptr4.use_count() = " << ptr4.use_count() << std::endl;

    ptr5.reset(new CStudent("Ray", 14, "Class1"));
    //std::cout << "ptr2.use_count() = " << ptr2.use_count() << std::endl;
    //std::cout << "ptr3.use_count() = " << ptr3.use_count() << std::endl;
    //std::cout << "ptr4.use_count() = " << ptr4.use_count() << std::endl;
    //std::cout << "ptr5.use_count() = " << ptr5.use_count() << std::endl;

    return 0;
}