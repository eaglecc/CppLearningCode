#pragma once
#include <iostream>

class FuncPointer
{
public:
    double add(double a, double b) {
        return a + b;
    }
    double multiply(double a, double b) {
        return a * b;
    }
};

class BaseClass
{
public:
    virtual void print() { std::cout << "Base Class"; }
};

class SubClass : public BaseClass 
{
public:
    void print() override { std::cout << "Sub Class"; }
};