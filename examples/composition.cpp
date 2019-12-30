#include <array>
#include <cmath>
#include <functional>
#include <iostream>

#include "folds/drivers/reduce.hpp"
#include "folds/folds/average.hpp"
#include "folds/folds/fold.hpp"
#include "folds/folds/length.hpp"
#include "folds/folds/max.hpp"
#include "folds/folds/sum.hpp"
#include "folds/monoids/void.hpp"
#include "folds/utility/tuple.hpp"
#include "folds/utility/type_traits.hpp"

namespace folds {

template <typename InputFn, typename OutputFn>
constexpr auto inline square(Fold<InputFn, OutputFn> f) {
  return lift(std::multiplies<>{})(f, f);
};

template <typename InputFn, typename OutputFn>
constexpr auto inline sqrt(Fold<InputFn, OutputFn> f) {
  return f.map([](auto i) { return std::sqrt(i); });
};

constexpr auto inline sum_of_squares =
    Fold{[](auto i) { return Sum(i * i); }, GetSum};

}  // namespace folds

constexpr std::array<int, 10> input{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

int main() {
  using folds::average;
  using folds::length;
  using folds::sum_of_squares;

  auto standard_deviation =
      sqrt(1.0 * sum_of_squares / length - square(average<>));

  auto [sum, max, std_dev] =
      reduce(folds::sum, folds::max, standard_deviation)(input);

  std::cout << "max: " << max << ", sum: " << sum
            << ", standard_deviation: " << std_dev << '\n';

  return reduce(folds::sum)(input);
}
