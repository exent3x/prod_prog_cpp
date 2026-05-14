#ifndef HASH_SET_IMPL_HPP
#define HASH_SET_IMPL_HPP

#include "set_impl.hpp"
#include <unordered_set>

template <typename T>
class HashSetImpl : public SetImpl<T> {
public:
    void add(const T& elem) override { data.insert(elem); }
    void remove(const T& elem) override { data.erase(elem); }
    bool contains(const T& elem) const override {
        return data.find(elem) != data.end();
    }
    size_t size() const override { return data.size(); }
    bool empty() const override { return data.empty(); }
    std::vector<T> getElements() const override {
        return {data.begin(), data.end()};
    }
private:
    std::unordered_set<T> data;
};

#endif