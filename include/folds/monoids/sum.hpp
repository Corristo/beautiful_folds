#pragma once

namespace folds {

namespace detail {

template <typename T>
struct SumMonoid {
    T _value{};

    friend SumMonoid<T> __attribute__((always_inline)) operator+(
        SumMonoid<T> lhs, SumMonoid<T> rhs) {
        return SumMonoid<T>{lhs._value + rhs._value};
    }
};

}  // namespace detail

constexpr auto inline Sum = []<typename T>(T i) -> detail::SumMonoid<T> {
    return detail::SumMonoid<T>{i};
};
constexpr auto inline GetSum = []<typename T>(detail::SumMonoid<T> s) -> T {
    return s._value;
};

}  // namespace folds
