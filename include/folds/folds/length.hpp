#pragma once

#include "folds/folds/fold.hpp"
#include "folds/monoids/sum.hpp"

namespace folds {
constexpr auto inline length =
    Fold{[]<typename T>(T)->detail::SumMonoid<T>{return Sum(1);
}  // namespace folds
, GetSum
}
;  // namespace folds
}
