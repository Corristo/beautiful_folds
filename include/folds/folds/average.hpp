#pragma once

#include "folds/folds/fold.hpp"
#include "folds/monoids/average.hpp"

namespace folds {

template <typename FP = double>
constexpr auto inline average =
    Fold{[]<typename T>(T val){return Average(static_cast<FP>(std::move(val)));
}  // namespace folds
, GetAverage
}
;
}
