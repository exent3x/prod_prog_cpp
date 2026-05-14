#ifndef SET_IMPL_H
#define SET_IMPL_H

#include <vector>
#include <cstddef>

template <typename T>
class SetImpl {
public:
    virtual ~SetImpl() = default;
    virtual void add(const T& elem) = 0;
    virtual void remove(const T& elem) = 0;
    virtual bool contains(const T& elem) const = 0;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual std::vector<T> getElements() const = 0;
};

#endif