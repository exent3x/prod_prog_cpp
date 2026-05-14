#ifndef ARRAY_SET_IMPL_HPP
#define ARRAY_SET_IMPL_HPP

#include "set_impl.hpp"
#include <algorithm>

template <typename T>
class ArraySetImpl : public SetImpl<T> {
public:
    void add(const T& elem) override {
        if (!contains(elem))
            data.push_back(elem);
    }
    void remove(const T& elem) override {
        auto it = std::find(data.begin(), data.end(), elem);
        if (it != data.end()) data.erase(it);
    }
    bool contains(const T& elem) const override {
        return std::find(data.begin(), data.end(), elem) != data.end();
    }
    size_t size() const override { return data.size(); }
    bool empty() const override { return data.empty(); }
    std::vector<T> getElements() const override { return data; }
private:
    std::vector<T> data;
};

#endif