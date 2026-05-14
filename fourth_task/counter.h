#ifndef COUNTER_H
#define COUNTER_H

#include <cstddef>

template <typename Derived>
class counter {
private:
    static std::size_t count_;
protected:
    counter() { ++count_; }
    counter(const counter&) { ++count_; }
    counter(counter&&) noexcept { ++count_; }
    ~counter() { --count_; }
public:
    static std::size_t count() { return count_; }
};

template <typename Derived>
std::size_t counter<Derived>::count_ = 0;

#endif