#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "expression.hpp"
#include <string>

class ExpressionFactory;

class Variable : public Expression {
    friend class ExpressionFactory;
public:
    void AddRef() override { ++refCount; }
    void Release() override;
    void print() const override;
    double calculate(const std::map<std::string, double>& context) const override;

private:
    Variable(const std::string& name, ExpressionFactory& factory);
    std::string name;
    int refCount = 0;
    ExpressionFactory& factory;
};

#endif