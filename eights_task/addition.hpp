#ifndef ADDITION_HPP
#define ADDITION_HPP

#include "binary_operator.hpp"
#include <iostream>

class Addition : public BinaryOperator {
public:
    Addition(Expression* l, Expression* r) : BinaryOperator(l, r) {}

    void print() const override {
        std::cout << "(";
        left->print();
        std::cout << "+";
        right->print();
        std::cout << ")";
    }

    double calculate(const std::map<std::string, double>& ctx) const override {
        return left->calculate(ctx) + right->calculate(ctx);
    }
};

#endif