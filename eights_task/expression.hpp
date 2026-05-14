#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <map>
#include <string>
#include <iostream>
#include <stdexcept>

class Expression {
public:
    virtual void print() const = 0;
    virtual double calculate(const std::map<std::string, double>& context) const = 0;
    virtual void AddRef() {}
    virtual void Release() {}

    virtual ~Expression() = default;
};

#endif