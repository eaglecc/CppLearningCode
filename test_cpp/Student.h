#pragma once
#include <string>

class CStudent
{
public:
    CStudent(std::string name, int age, std::string className);
    ~CStudent();
    std::string GetName() const {
        return name;
    };
    int GetAge() const {
        return age;
    };
    std::string GetClassName() const {
        return className;
    };
    void SetName(std::string name) {
        this->name = name;
    };
    void SetAge(int age) {
        this->age = age;
    };
    void SetClassName(std::string className) {
        this->className = className;
    };
private:
    std::string name;
    int age;
    std::string className;
};

