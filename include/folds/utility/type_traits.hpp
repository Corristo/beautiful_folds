#pragma once

#include <type_traits>

namespace folds {

// missing C++2a type trait
template <typename T>
using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

}  // namespace folds
