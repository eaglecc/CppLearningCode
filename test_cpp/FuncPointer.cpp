#include "FuncPointer.h"

//int main(void) {
//    // ptrMemberFunc �� FuncPointer �ĳ�Ա����ָ��, ���ó�Ա��ʱ���� .  ����  -> ��Աָ�������
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
//    // �麯��ָ��
//    void (BaseClass:: *pMemFunc)() = &BaseClass::print;
//    BaseClass* pBaseObj = new SubClass();
//    (pBaseObj->*pMemFunc)(); // Sub Class
//}