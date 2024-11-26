#pragma once

// ∂‡Ã¨—ßœ∞
class Calculator
{
public:

    virtual double add(double, double) { return 0; }
    virtual double sub(double, double) { return 0; }
    virtual double mul(double, double) { return 0; }
    virtual double div(double, double) { return 0; }

};

class Add :public Calculator
{
public:
    double add(double a, double b) override {
        return a + b;
    }
};

class Sub : public Calculator {
public:
    double sub(double a, double b) override {
        return a - b;
    };
};

class Mul :public Calculator {
public:
    double mul(double a, double b) override{
        return a * b;
    };
};

class Div : public Calculator {
public:
    double div(double a, double b) override{
        if (b == 0)
        {
            return 0;
        }
        return a / b;
    };
};