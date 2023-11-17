#include <algorithm>
#include <cassert>
#include <utility>

// https://godbolt.org/z/eTbsxcq96
// https://github.com/alvmiller/simple_min_and_sum_examples_cpp/blob/main/min_and_sum.cpp

// -----------------------------------------------------------------------------

template<typename T>
constexpr auto min(T&& arg)
{
    return std::forward<T>(arg);
}

template<typename T, typename ... Ts>
constexpr auto min(T&& arg, Ts&& ... args)
{
    return std::min(std::forward<T>(arg), min(std::forward<Ts>(args)...));
}

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

constexpr auto sum()
{
    return 0;
}

template <typename T, typename ... Ts>
constexpr auto sum(T&& arg, Ts&& ... args) {
    return arg + sum(std::forward<Ts>(args)...);
}

// -----------------------------------------------------------------------------

int main()
{
    // -------------------------------------------------------------------------

    static_assert(min(3, 1, 2) == 1, "Bad minimum result"); // CT check
    assert(min(3, 1, 2) == 1); // RT(dbg) check

    // -------------------------------------------------------------------------

    static_assert(sum(1, 2, 3) == 6, "Bad compile time summary"); // CT check
    assert(sum(1, 2, 3) == 6); // RT(dbg) check

    // -------------------------------------------------------------------------

    return 0;
}
