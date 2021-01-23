#pragma once

#include <utility>

namespace meta
{

template <typename TagT, typename... Types>
struct makeImpl
{
    static constexpr auto dispatch(Types&&... values)
    {
        return TagT(std::forward<Types>(values)...);
    }
};

template <typename TagT, typename... Types>
constexpr auto make(Types&&... values)
{
    return makeImpl<TagT, Types...>::dispatch(std::forward<Types>(values)...);
}


}  // namespace meta
