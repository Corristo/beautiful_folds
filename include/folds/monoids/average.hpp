#pragma once

namespace folds {
namespace detail {
template <typename T = double>
struct AverageMonoid {
    std::size_t _num_samples{0};
    T _value{0};

    friend AverageMonoid<T> operator+(AverageMonoid<T> lhs,
                                      AverageMonoid<T> rhs) {
        return AverageMonoid{
            lhs._num_samples + rhs._num_samples,
            (lhs._value * lhs._num_samples + rhs._value * rhs._num_samples) /
                (lhs._num_samples + rhs._num_samples)};
    }
};
}  // namespace detail

constexpr auto inline Average =
    []<typename T>(T val) -> detail::AverageMonoid<T> {
    return detail::AverageMonoid<T>{1ull, std::move(val)};
};

constexpr auto inline GetAverage =
    []<typename T>(detail::AverageMonoid<T> const& m) -> T {
    return m._value;
};

}  // namespace folds
