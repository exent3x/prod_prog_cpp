#include <iostream>
#include "set.hpp"

int main() {
    Set<int> s;
    s.add(1);
    s.add(2);
    s.add(3);

    Set<int> t;
    t.add(2);
    t.add(3);
    t.add(4);

    auto u = s.unionSet(t);
    auto i = s.intersectSet(t);

    std::cout << "Union size: " << u.size() << std::endl;    // 4
    std::cout << "Intersection size: " << i.size() << std::endl; // 2
    return 0;
}