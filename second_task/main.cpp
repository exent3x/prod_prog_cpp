#include "typelist.hpp"

int main() {
    using list = typelist::TypeList<int, double, char>;

    static_assert(typelist::Size<list>::value == 3);

    static_assert(std::is_same_v<typelist::At<list, 0>, int>);
    static_assert(std::is_same_v<typelist::At<list, 2>, char>);

    static_assert(typelist::Contains<list, double>::value);
    static_assert(!typelist::Contains<list, float>::value);

    static_assert(typelist::IndexOf<list, int>::value == 0);
    static_assert(typelist::IndexOf<list, char>::value == 2);

    using appended = typelist::Append<list, float>::type;
    static_assert(std::is_same_v<appended, typelist::TypeList<int, double, char, float>>);

    using prepended = typelist::Prepend<list, bool>::type;
    static_assert(std::is_same_v<prepended, typelist::TypeList<bool, int, double, char>>);

    return 0;
}