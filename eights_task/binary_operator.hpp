#ifndef BINARY_OPERATOR_HPP
#define BINARY_OPERATOR_HPP

#include "expression.hpp"

class BinaryOperator : public Expression {
protected:
    Expression* left;
    Expression* right;

    BinaryOperator(Expression* l, Expression* r) : left(l), right(r) {
        left->AddRef();
        right->AddRef();
    }

public:
    virtual ~BinaryOperator() {
        left->Release();
        right->Release();
    }

    BinaryOperator(const BinaryOperator&) = delete;
    BinaryOperator& operator=(const BinaryOperator&) = delete;
};

#endif