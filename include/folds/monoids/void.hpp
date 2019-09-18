#pragma once

#include <type_traits>

namespace folds {

struct Void {
    friend Void operator+(Void, Void) { return Void{}; }
};

} //

static_assert(std::is_default_constructible_v<folds::Void>);
