#pragma once

#include "folds/folds/fold.hpp"
#include "folds/monoids/sum.hpp"

namespace folds {

constexpr auto inline sum = Fold{Sum, GetSum};

}
