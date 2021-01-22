#include <containers/Tuple.hpp>

#include <type_traits>

int main()
{
    constexpr meta::Tuple<int, char, double> tuple{1, '2', 3.3};
    static_assert(tuple.SIZE == 3);
    // constexpr auto ys = meta::make<meta::TupleTag>(1, '2', 3.3);
    // constexpr auto zs = meta::make_tuple(1, '2', 3.3);

    // static_assert(std::is_same<decltype(ys), decltype(xs)>::value, "");
    // static_assert(std::is_same<decltype(zs), decltype(xs)>::value, "");

    static_assert(meta::get<0>(tuple) == 1);
    static_assert(meta::get<1>(tuple) == '2');
    static_assert(meta::get<2>(tuple) == 3.3);
}
