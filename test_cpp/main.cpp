#include <iostream>
#include "MemoryPool.h"
#include "Student.h"

int main() {
    CMemoryPool pool(sizeof(CStudent), 3);

    return 0;
}