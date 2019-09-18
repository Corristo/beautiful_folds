#pragma once

#include "folds/utility/tuple.hpp"

namespace folds {
namespace detail {
template <typename TupleT, typename... FoldsT, std::size_t... Is>
auto apply_piecewise(TupleT m, std::index_sequence<Is...>, FoldsT... fs) {
  return folds::make_tuple((fs.summarize(get<Is>(m)))...);
}

}  // namespace detail

template <typename... Fs>
constexpr auto inline reduce(Fs... fs) {
  static_assert(sizeof...(Fs) > 0);
  return [fs...](auto const& range) {
    folds::tuple<decltype(fs.tally(*range.begin()))...> intermediate{};
    for (auto v : range) {
      intermediate = intermediate + folds::make_tuple(fs.tally(v)...);
    }
    if constexpr (sizeof...(Fs) > 1) {
      return detail::apply_piecewise(
          intermediate, std::make_index_sequence<sizeof...(fs)>{}, fs...);
    } else {
      return get<0>(detail::apply_piecewise(
          intermediate, std::make_index_sequence<sizeof...(fs)>{}, fs...));
    }
  };
}

}  // namespace folds
