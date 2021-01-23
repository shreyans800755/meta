#include <core/make.hpp>

#include <cstddef>
#include <utility>

#pragma once

namespace meta
{

struct TupleTag
{
};

template <typename... Types>
struct Tuple;

template <>
struct Tuple<>
{
    static constexpr auto SIZE = 0;
};

template <typename HeadT, typename... TailTs>
struct Tuple<HeadT, TailTs...> : Tuple<TailTs...>
{
    using Base = Tuple<TailTs...>;

    static constexpr auto SIZE = 1 + Base::SIZE;

    constexpr Tuple() = default;

    constexpr Tuple(HeadT&& head, TailTs&&... tails)
        : Base(std::forward<TailTs>(tails)...), value(std::forward<HeadT>(head))
    {
    }

    HeadT value;
};


namespace detail
{

template <size_t INDEX, typename HeadT, typename... TailTs>
constexpr auto& getImpl(const Tuple<HeadT, TailTs...>& tuple)
{
    if constexpr (INDEX == 0)
    {
        return tuple.value;
    }
    else
    {
        return getImpl<INDEX - 1, TailTs...>(tuple);
    }
}

}  // namespace detail

template <size_t INDEX, typename... Types>
constexpr auto& get(const Tuple<Types...>& tuple)
{
    static_assert(INDEX >= 0 && INDEX < tuple.SIZE,
                  "Index must be between [0, SIZE)");
    return detail::getImpl<INDEX>(tuple);
}

template <typename... Types>
struct makeImpl<TupleTag, Types...>
{
    static constexpr auto dispatch(Types&&... values)
    {
        return Tuple<Types...>(std::forward<Types>(values)...);
    }
};

template <typename... Types>
constexpr auto makeTuple(Types&&... values)
{
    return make<TupleTag>(std::forward<Types>(values)...);
}


}  // namespace meta
