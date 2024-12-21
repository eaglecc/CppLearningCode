#pragma once
#include <stack>

class CMemoryPool
{
public:
    CMemoryPool(size_t objSize, size_t totalSize);
    ~CMemoryPool();
    void* Allocate(); // 分配内存
    void Free(void* p); // 释放内存

private:
    size_t objSize; // 对象大小
    size_t totalSize; // 总大小
    char* pool; // 内存池指针
    std::stack<void*> freeList; // 空闲链表
};

