#include <iostream>
#include <cassert>
#include "less_than_comparable.h"
#include "counter.h"

class Number : public less_than_comparable<Number>,
               public counter<Number> {
public:
    explicit Number(int value) : m_value(value) {}
    int value() const { return m_value; }
    bool operator<(const Number& other) const {
        return m_value < other.m_value;
    }
private:
    int m_value;
};

int main() {
    Number one{1}, two{2}, three{3}, four{4};

    assert(one >= one);
    assert(three <= four);
    assert(two == two);
    assert(three > two);
    assert(one < two);

    std::cout << "Count: " << counter<Number>::count() << std::endl;
    return 0;
}