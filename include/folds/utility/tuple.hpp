#pragma once

#include <metal.hpp>

#include "folds/utility/type_traits.hpp"

namespace folds {
namespace detail {

template <typename T>
using empty = metal::number<(std::is_empty_v<T>)>;

template <typename I, typename T, typename = empty<T>>
struct element_holder {
 public:
  constexpr element_holder() : _elem{} {}

  template <typename R>
  constexpr element_holder(R&& elem) : _elem{std::forward<R>(elem)} {}

  constexpr T get() const { return _elem; }

  friend constexpr T get(element_holder const& holder) { return holder._elem; }

 private:
  T _elem;
};

template <typename I, typename T>
struct element_holder<I, T, metal::true_> {
  constexpr element_holder() = default;

  template <typename R>
  constexpr element_holder(R&&) {}

  constexpr T get() const { return T(); }

  friend constexpr T get(element_holder const&) { return T(); }
};

template <typename... Ts>
struct tuple_base : public Ts... {
  constexpr tuple_base() requires(sizeof...(Ts) > 0) = default;
  constexpr tuple_base(Ts... ts) : Ts{std::move(ts)}... {}
};

template <typename... Ts>
using index_to_type_map =
    metal::transform<metal::lambda<metal::list>,
                     metal::indices<metal::list<Ts...>>, metal::list<Ts...>>;

template <typename... Ts>
using tuple_base_type = metal::apply<
    metal::lambda<tuple_base>,
    metal::transform<metal::lambda<element_holder>,
                     metal::indices<metal::list<Ts...>>, metal::list<Ts...>>>;

template <std::size_t I, typename T>
using tuple_element = metal::at_key<T, metal::number<I>>;

}  // namespace detail

template <typename... Ts>
class tuple : private detail::tuple_base_type<Ts...> {
 public:
  constexpr explicit tuple() requires(sizeof...(Ts) > 0) = default;
  constexpr explicit tuple(Ts... ts)
      : detail::tuple_base_type<Ts...>{std::move(ts)...} {}

  template <std::size_t I>
  constexpr auto get() const {
    return static_cast<detail::element_holder<
        metal::number<I>,
        detail::tuple_element<I, detail::index_to_type_map<Ts...>>> const&>(
               *this)
        .get();
  }
};

template <std::size_t I, typename... Ts>
auto constexpr get(tuple<Ts...> const& t) {
  return t.template get<I>();
}

template <typename... Ts>
tuple(Ts...)->tuple<remove_cvref_t<Ts>...>;

tuple()->tuple<>;

}  // namespace folds

namespace std {
template <typename... Ts>
struct tuple_size<folds::tuple<Ts...>> {
  static constexpr std::size_t value = sizeof...(Ts);
};

template <std::size_t I, typename... Ts>
struct tuple_element<I, folds::tuple<Ts...>> {
  using type =
      folds::detail::tuple_element<I, folds::detail::index_to_type_map<Ts...>>;
};

}  // namespace std

namespace folds {
namespace detail {

template <typename Tuple, std::size_t... I>
auto mappend_impl(Tuple const& t1, Tuple const& t2, std::index_sequence<I...>) {
  return Tuple{(folds::get<I>(t1) + folds::get<I>(t2))...};
}

}  // namespace detail

template <typename... Ts>
tuple<Ts...> operator+(tuple<Ts...> const& t1, tuple<Ts...> const& t2) {
  return detail::mappend_impl(t1, t2,
                              std::make_index_sequence<sizeof...(Ts)>{});
}

template <typename... Ts>
auto make_tuple(Ts&&... ts) {
  return tuple<remove_cvref_t<Ts>...>{std::forward<Ts>(ts)...};
}

}  // namespace folds
