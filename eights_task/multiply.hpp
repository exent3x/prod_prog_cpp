#ifndef MULTIPLY_HPP
#define MULTIPLY_HPP

#include "binary_operator.hpp"

class Multiply : public BinaryOperator {
public:
    Multiply(Expression* l, Expression* r) : BinaryOperator(l, r) {}

    void print() const override {
        std::cout << "(";
        left->print();
        std::cout << "*";
        right->print();
        std::cout << ")";
    }

    double calculate(const std::map<std::string, double>& ctx) const override {
        return left->calculate(ctx) * right->calculate(ctx);
    }
};

#endif