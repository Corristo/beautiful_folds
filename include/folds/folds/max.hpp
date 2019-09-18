#pragma once

#include "folds/folds/fold.hpp"
#include "folds/monoids/max.hpp"

namespace folds {

constexpr auto inline max = Fold{Max, GetMax};

}
