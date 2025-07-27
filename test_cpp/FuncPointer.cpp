#include "FuncPointer.h"

//int main(void) {
//    // ptrMemberFunc 是 FuncPointer 的成员函数指针, 调用成员的时候，用 .  或者  -> 成员指针运算符
//    double (FuncPointer:: * ptrMemberFunc)(double, double);
//    ptrMemberFunc = &FuncPointer::add;
//
//    FuncPointer obj;
//    double res = (obj.*ptrMemberFunc)(3, 5);
//    std::cout << res << std::endl; // 8
//
//    FuncPointer* pObj = &obj;
//    ptrMemberFunc = &FuncPointer::multiply;
//    res = (pObj->*ptrMemberFunc)(5, 5);
//    std::cout << res << std::endl; // 25
//
//    // 虚函数指针
//    void (BaseClass:: *pMemFunc)() = &BaseClass::print;
//    BaseClass* pBaseObj = new SubClass();
//    (pBaseObj->*pMemFunc)(); // Sub Class
//}