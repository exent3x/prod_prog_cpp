#include "expression_factory.hpp"
#include "constant.hpp"
#include "variable.hpp"
#include<iostream>
Constant::Constant(int v, ExpressionFactory& f) : value(v), factory(f) {}

void Constant::print() const {
    std::cout << value;
}

double Constant::calculate(const std::map<std::string, double>&) const {
    return value;
}

void Constant::Release() {
    factory.releaseConstant(this);
}

Variable::Variable(const std::string& n, ExpressionFactory& f) : name(n), factory(f) {}

void Variable::print() const {
    std::cout << name;
}

double Variable::calculate(const std::map<std::string, double>& ctx) const {
    auto it = ctx.find(name);
    if (it != ctx.end()) return it->second;
    throw std::runtime_error("Неизвестная переменная: " + name);
}

void Variable::Release() {
    factory.releaseVariable(this);
}


ExpressionFactory::ExpressionFactory() {
    for (int i = -5; i <= 256; ++i) {
        Constant* c = new Constant(i, *this);
        c->AddRef();
        constants[i] = c;
    }
}

ExpressionFactory::~ExpressionFactory() {
    for (auto& pair : variables) delete pair.second;
    for (auto& pair : constants) delete pair.second;
}

Variable* ExpressionFactory::createVariable(const std::string& name) {
    auto it = variables.find(name);
    if (it != variables.end()) {
        it->second->AddRef();
        return it->second;
    }
    Variable* v = new Variable(name, *this);
    v->AddRef();
    variables[name] = v;
    return v;
}

Constant* ExpressionFactory::createConstant(int value) {
    auto it = constants.find(value);
    if (it != constants.end()) {
        it->second->AddRef();
        return it->second;
    }
    Constant* c = new Constant(value, *this);
    c->AddRef();
    constants[value] = c;
    return c;
}

void ExpressionFactory::releaseVariable(Variable* v) {
    v->refCount--;
    if (v->refCount <= 0) {
        auto it = variables.find(v->name);
        if (it != variables.end() && it->second == v) {
            variables.erase(it);
        }
        delete v;
    }
}

void ExpressionFactory::releaseConstant(Constant* c) {
    if (c->value >= -5 && c->value <= 256) {
        c->refCount--;
        return;
    }
    c->refCount--;
    if (c->refCount <= 0) {
        auto it = constants.find(c->value);
        if (it != constants.end() && it->second == c) {
            constants.erase(it);
        }
        delete c;
    }
}