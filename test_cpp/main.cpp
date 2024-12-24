#include <iostream>
#include "MemoryPool.h"
#include "Student.h"
#include "SimpleSharedPtr.h"
#include "ResourceManager.h"

int main() {
    {
        ResourceManager resourceManager(10);
        int res = resourceManager.getValue();
        std::cout << "Resource value: " << res << std::endl;

        resourceManager.setValue(20);
        res = resourceManager.getValue();
        std::cout << "Resource value: " << res << std::endl;

        ResourceManager resourceManager2(std::move(resourceManager));
        std::cout << "Resource value: " << resourceManager2.getValue() << std::endl;
        //std::cout << "Resource value: " << resourceManager.getValue() << std::endl;
    }

    return 0;
}