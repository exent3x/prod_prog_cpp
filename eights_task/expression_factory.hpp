#ifndef EXPRESSION_FACTORY_HPP
#define EXPRESSION_FACTORY_HPP

#include <string>
#include <unordered_map>

class ExpressionFactory;

#include "constant.hpp"
#include "variable.hpp"

class ExpressionFactory {
public:
    ExpressionFactory();
    ~ExpressionFactory();

    Variable* createVariable(const std::string& name);
    Constant* createConstant(int value);

    void releaseVariable(Variable* v);
    void releaseConstant(Constant* c);

private:
    std::unordered_map<std::string, Variable*> variables;
    std::unordered_map<int, Constant*> constants;
};

#endif