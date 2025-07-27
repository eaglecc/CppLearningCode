#pragma once
#include <memory>
#include <iostream>

class ResourceManager
{
public:
    ResourceManager() : resource(nullptr) {};
    ResourceManager(int resource) {
        this->resource = std::make_unique<int>(resource); // 分配资源
        std::cout << "Resource allocated." << std::endl;
    };

    // 移动构造函数  ResourceManager S2(std::move(S1));
    ResourceManager(ResourceManager&& value) noexcept {
        if (&value == this)
        {
            return;
        }

        if (value.resource == nullptr)
        {
            this->resource = nullptr;
            return;
        }
        this->resource = std::move(value.resource);
        std::cout << "Resource moved." << std::endl;
    };

    // 移动赋值运算符重载  S1 = std::move(S2);
    ResourceManager& operator=(ResourceManager&& value) noexcept {
        if (&value == this)
        {
            return *this;
        }
        if (value.resource == nullptr)
        {
            this->resource = nullptr;
            return *this;
        }
        this->resource = std::move(value.resource);
        std::cout << "Resource moved." << std::endl;
        return *this;
    };

    int getValue() const {
        return *resource;
    };

    void setValue(int newValue) {
        this->resource = std::make_unique<int>(newValue);
    };

    ResourceManager(const ResourceManager& othre) = delete; // 禁用拷贝构造函数
    ResourceManager& operator=(const ResourceManager& other) = delete; // 禁用拷贝赋值运算符重载

private:
    std::unique_ptr<int> resource;
};

