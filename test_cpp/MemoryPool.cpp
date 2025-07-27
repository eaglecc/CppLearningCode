/*
* MemoryPool.cpp
* 使用栈实现一个内存池
* Created on: 2024-12-21
*/
#include "MemoryPool.h"

CMemoryPool::CMemoryPool(size_t objSize, size_t totalSize) : objSize(objSize), totalSize(totalSize) {
    pool = (char*)malloc(objSize * totalSize);
    if (pool == nullptr) {
        throw std::bad_alloc();
    }
    // 初始化空闲链表
    for (size_t i = 0; i < totalSize; i++) {
        freeList.push(pool + i * objSize);
    }
}

CMemoryPool::~CMemoryPool()
{
    free(pool);
}

// 用户调用Allocate函数分配内存
void* CMemoryPool::Allocate()
{
    if (freeList.empty()) {
        throw std::bad_alloc();
    }
    auto res = freeList.top();
    if (res == nullptr) {
        throw std::bad_alloc();
    }
    freeList.pop();
    return res;
}

void CMemoryPool::Free(void* p)
{
    freeList.push(p);
}
