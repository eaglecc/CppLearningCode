#pragma once
#include <stack>

class CMemoryPool
{
public:
    CMemoryPool(size_t objSize, size_t totalSize);
    ~CMemoryPool();
    void* Allocate(); // �����ڴ�
    void Free(void* p); // �ͷ��ڴ�

private:
    size_t objSize; // �����С
    size_t totalSize; // �ܴ�С
    char* pool; // �ڴ��ָ��
    std::stack<void*> freeList; // ��������
};

