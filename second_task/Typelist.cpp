#include <type_traits>
#include <cstddef>

namespace typelist {

template <typename... Ts>
struct TypeList {};

namespace detail {

    template <typename List, std::size_t Index>
    struct AtHelper;

    template <typename Head, typename... Tail, std::size_t Index>
    struct AtHelper<TypeList<Head, Tail...>, Index>
        : AtHelper<TypeList<Tail...>, Index - 1> {};

    template <typename Head, typename... Tail>
    struct AtHelper<TypeList<Head, Tail...>, 0> {
        using type = Head;
    };

    template <typename List, typename T, std::size_t Start = 0>
    struct IndexOfHelper;

    template <typename T, typename... Tail, std::size_t Start>
    struct IndexOfHelper<TypeList<T, Tail...>, T, Start>
        : std::integral_constant<std::size_t, Start> {};

    template <typename T, typename U, typename... Tail, std::size_t Start>
    struct IndexOfHelper<TypeList<U, Tail...>, T, Start>
        : IndexOfHelper<TypeList<Tail...>, T, Start + 1> {};

}

template <typename List, std::size_t Index>
using At = typename detail::AtHelper<List, Index>::type;

template <typename List>
struct Size;

template <typename... Ts>
struct Size<TypeList<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)> {};

template <typename List, typename T>
struct Contains : std::false_type {};

template <typename T, typename... Ts>
struct Contains<TypeList<T, Ts...>, T> : std::true_type {};

template <typename T, typename U, typename... Ts>
struct Contains<TypeList<U, Ts...>, T> : Contains<TypeList<Ts...>, T> {};

template <typename List, typename T>
struct IndexOf : detail::IndexOfHelper<List, T> {};

template <typename List, typename T>
struct Append;

template <typename... Ts, typename T>
struct Append<TypeList<Ts...>, T> {
    using type = TypeList<Ts..., T>;
};

template <typename List, typename T>
struct Prepend;

template <typename... Ts, typename T>
struct Prepend<TypeList<Ts...>, T> {
    using type = TypeList<T, Ts...>;
};

}

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