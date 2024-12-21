/*
* MemoryPool.cpp
* ʹ��ջʵ��һ���ڴ��
* Created on: 2024-12-21
*/
#include "MemoryPool.h"

CMemoryPool::CMemoryPool(size_t objSize, size_t totalSize) : objSize(objSize), totalSize(totalSize) {
    pool = (char*)malloc(objSize * totalSize);
    if (pool == nullptr) {
        throw std::bad_alloc();
    }
    // ��ʼ����������
    for (size_t i = 0; i < totalSize; i++) {
        freeList.push(pool + i * objSize);
    }
}

CMemoryPool::~CMemoryPool()
{
    free(pool);
}

// �û�����Allocate���������ڴ�
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
