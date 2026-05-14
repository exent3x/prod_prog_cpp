#ifndef DIVIDE_HPP
#define DIVIDE_HPP

#include "binary_operator.hpp"

class Divide : public BinaryOperator {
public:
    Divide(Expression* l, Expression* r) : BinaryOperator(l, r) {}

    void print() const override {
        std::cout << "(";
        left->print();
        std::cout << "/";
        right->print();
        std::cout << ")";
    }

    double calculate(const std::map<std::string, double>& ctx) const override {
        double divisor = right->calculate(ctx);
        if (divisor == 0.0)
            throw std::runtime_error("Деление на ноль");
        return left->calculate(ctx) / divisor;
    }
};

#endif