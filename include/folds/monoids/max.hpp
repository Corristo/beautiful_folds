#pragma once

#include <cmath>
#include <limits>

namespace folds {
namespace detail {
template <typename T>
struct MaxMonoid {
    T _value{std::numeric_limits<T>::min()};

    friend MaxMonoid<T> operator+(MaxMonoid<T> lhs, MaxMonoid<T> rhs) {
        return MaxMonoid<T>{std::max(lhs._value, rhs._value)};
    }
};
}  // namespace detail

constexpr auto inline Max = []<typename T>(T val) -> detail::MaxMonoid<T> {
    return detail::MaxMonoid<T>{val};
};

constexpr auto inline GetMax =
    []<typename T>(detail::MaxMonoid<T> const& m) -> T {
    return m._value;
};

}  // namespace folds
