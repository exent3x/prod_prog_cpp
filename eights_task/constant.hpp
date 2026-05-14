#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include "expression.hpp"

class ExpressionFactory;

class Constant : public Expression {
    friend class ExpressionFactory;
public:
    void AddRef() override { ++refCount; }
    void Release() override;
    void print() const override;
    double calculate(const std::map<std::string, double>&) const override;

private:
    Constant(int value, ExpressionFactory& factory);
    int value;
    int refCount = 0;
    ExpressionFactory& factory;
};

#endif