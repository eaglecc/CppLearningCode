#include "Student.h"
#include <iostream>

CStudent::CStudent(std::string name, int age, std::string className) : name(name), age(age), className(className) {
    std::cout << "CStudent���캯��" << std::endl;
}

CStudent::~CStudent()
{
}