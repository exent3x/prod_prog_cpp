#ifndef TYPELIST_HPP
#define TYPELIST_HPP

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

#endif // TYPELIST_HPP