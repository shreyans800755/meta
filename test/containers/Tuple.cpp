#include <containers/Tuple.hpp>
#include <core/make.hpp>

#include <type_traits>

int main()
{
    constexpr meta::Tuple<int, char, double> tuple{1, '2', 3.3};
    static_assert(tuple.SIZE == 3);

    static_assert(meta::get<0>(tuple) == 1);
    static_assert(meta::get<1>(tuple) == '2');
    static_assert(meta::get<2>(tuple) == 3.3);

    constexpr auto tupleCopy = tuple;
    static_assert(meta::get<0>(tupleCopy) == 1);
    static_assert(meta::get<1>(tupleCopy) == '2');
    static_assert(meta::get<2>(tupleCopy) == 3.3);

    constexpr auto tupleUsingMakeTag = meta::make<meta::TupleTag>(1, '2', 3.3);
    constexpr auto tupleUsingMakeTuple = meta::makeTuple(1, '2', 3.3);

    static_assert(std::is_same_v<decltype(tuple), decltype(tupleUsingMakeTuple)>, "");
    static_assert(std::is_same_v<decltype(tuple), decltype(tupleUsingMakeTag)>, "");
}
