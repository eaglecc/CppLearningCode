#pragma once

struct ControlBlock {
    int ref_count;
    ControlBlock() : ref_count(1) {}
};

template <typename T>
class SimpleSharedPtr
{
private:
    T* ptr;
    ControlBlock* control_block;
    void Release() {
        --control_block->ref_count;
        if (control_block->ref_count == 0) {
            delete ptr;
            ptr = nullptr;
            delete control_block;
            control_block = nullptr;
        }
    }
public:
    SimpleSharedPtr() : ptr(nullptr), control_block(nullptr) {}
    explicit SimpleSharedPtr(T* p) : ptr(p) {
        if (p)
        {
            control_block = new ControlBlock();
        }
        else {
            control_block = nullptr;
        }
    }
    ~SimpleSharedPtr() {
        if (ptr) {
            Release();
        }
    }

    // 拷贝构造函数重载 SimpleSharedPtr S2(S1);
    SimpleSharedPtr(const SimpleSharedPtr& other) : ptr(other.ptr), control_block(other.control_block) {
        if (control_block) {
            ++control_block->ref_count;
        }
    }

    // 赋值运算符重载 S1 = S2; 赋值完了S2还在，S1和S2指向同一块内存，引用计数加1
    SimpleSharedPtr& operator=(const SimpleSharedPtr& other) {
        if (this != &other) {
            if (ptr) {
                Release();
            }
            ptr = other.ptr;
            control_block = other.control_block;
            if (control_block) {
                ++control_block->ref_count;
            }
        }
        return *this;
    }

    // 移动构造函数  SimpleSharedPtr S2(std::move(S1));
    SimpleSharedPtr(SimpleSharedPtr&& other) : ptr(other.ptr), control_block(other.control_block) {
        other.ptr = nullptr;
        other.control_block = nullptr;
    }

    // 移动赋值运算符重载 S1 = std::move(S2); 复制完了S2不在了，S2指向nullptr，S1指向原来的内存，引用计数不变
    SimpleSharedPtr& operator=(SimpleSharedPtr&& other) noexcept {
        if (this != &other) {
            if (ptr) {
                Release();
            }
            ptr = other.ptr;
            control_block = other.control_block;
            other.ptr = nullptr;
            other.control_block = nullptr;
        }
        return *this;
    }

    // SimpleSharedPtr S2(new Student()); S2->name = "tom";  S2.ptr->name = "tom";
    T* operator->() {
        return ptr;
    }

    // SimpleSharedPtr S2(new Student()); (*S2).name = "tom";
    T& operator*() const {
        return *ptr;
    }

    // Student* p = S2.get();
    T* get() const {
        return ptr;
    }

    int use_count() const {
        return control_block ? control_block->ref_count : 0;
    }

    // S2.reset(new Student());
    void reset(T* p = nullptr) {
        if (ptr) {
            Release();
        }
        ptr = p;
        if (p) {
            control_block = new ControlBlock();
        }
        else {
            control_block = nullptr;
        }
    }
};