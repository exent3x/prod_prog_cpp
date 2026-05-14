#ifndef SET_HPP
#define SET_HPP

#include <memory>
#include <vector>
#include "array_set_impl.hpp"
#include "hash_set_impl.hpp"

template <typename T>
class Set {
public:
    static constexpr size_t Threshold = 10;

    Set() : impl_(std::make_unique<ArraySetImpl<T>>()) {}

    void add(const T& elem) {
        if (impl_->size() >= Threshold)
            switchToHash();
        impl_->add(elem);
    }

    void remove(const T& elem) {
        impl_->remove(elem);
        if (impl_->size() < Threshold && dynamic_cast<HashSetImpl<T>*>(impl_.get()))
            switchToArray();
    }

    bool contains(const T& elem) const { return impl_->contains(elem); }
    size_t size() const { return impl_->size(); }
    bool empty() const { return impl_->empty(); }

    Set unionSet(const Set& other) const {
        Set result;
        for (const auto& e : impl_->getElements()) result.add(e);
        for (const auto& e : other.impl_->getElements()) result.add(e);
        return result;
    }

    Set intersectSet(const Set& other) const {
        Set result;
        for (const auto& e : impl_->getElements())
            if (other.contains(e)) result.add(e);
        return result;
    }

private:
    void switchToHash() {
        if (dynamic_cast<HashSetImpl<T>*>(impl_.get())) return;
        auto newImpl = std::make_unique<HashSetImpl<T>>();
        for (const auto& e : impl_->getElements()) newImpl->add(e);
        impl_ = std::move(newImpl);
    }

    void switchToArray() {
        if (dynamic_cast<ArraySetImpl<T>*>(impl_.get())) return;
        auto newImpl = std::make_unique<ArraySetImpl<T>>();
        for (const auto& e : impl_->getElements()) newImpl->add(e);
        impl_ = std::move(newImpl);
    }

    std::unique_ptr<SetImpl<T>> impl_;
};

#endif