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

    // �������캯������ SimpleSharedPtr S2(S1);
    SimpleSharedPtr(const SimpleSharedPtr& other) : ptr(other.ptr), control_block(other.control_block) {
        if (control_block) {
            ++control_block->ref_count;
        }
    }

    // ��ֵ��������� S1 = S2; ��ֵ����S2���ڣ�S1��S2ָ��ͬһ���ڴ棬���ü�����1
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

    // �ƶ����캯��  SimpleSharedPtr S2(std::move(S1));
    SimpleSharedPtr(SimpleSharedPtr&& other) : ptr(other.ptr), control_block(other.control_block) {
        other.ptr = nullptr;
        other.control_block = nullptr;
    }

    // �ƶ���ֵ��������� S1 = std::move(S2); ��������S2�����ˣ�S2ָ��nullptr��S1ָ��ԭ�����ڴ棬���ü�������
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