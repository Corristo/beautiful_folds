#pragma once

#include <functional>

#include "folds/monoids/void.hpp"
#include "folds/utility/tuple.hpp"
#include "folds/utility/type_traits.hpp"

namespace folds {

template <typename InputFn, typename OutputFn>
class Fold;

namespace detail {

template <typename T>
struct is_fold : std::false_type {};

template <typename InputFn, typename OutputFn>
struct is_fold<Fold<InputFn, OutputFn>> : std::true_type {};

template <typename T>
constexpr inline bool is_fold_v = is_fold<T>::value;

template <typename T>
constexpr auto inline pure_fold(T val) {
  return Fold{[](auto) { return Void{}; }, [val](auto) { return val; }};
}

template <typename OutputFn, bool is_empty = false>
class SummarizeEbo {
 public:
  constexpr SummarizeEbo(OutputFn f) : m_OutputFn{std::move(f)} {}

  template <typename M>
  constexpr auto summarize(M m) const noexcept(noexcept(this->m_OutputFn(m))) {
    return m_OutputFn(m);
  }

 private:
  OutputFn m_OutputFn;
};

template <typename OutputFn>
class SummarizeEbo<OutputFn, true> {
 public:
  constexpr SummarizeEbo() = default;
  constexpr SummarizeEbo(OutputFn) {}

  template <typename M>
  constexpr auto summarize(M m) const noexcept(noexcept(OutputFn{}(m))) {
    return OutputFn{}(m);
  }
};

template <typename InputFn, bool is_empty = false>
class TallyEbo {
 public:
  constexpr TallyEbo(InputFn f) : m_InputFn{std::move(f)} {}

  template <typename I>
  constexpr auto tally(I i) const noexcept(noexcept(this->m_InputFn(i))) {
    return m_InputFn(i);
  }

 private:
  InputFn m_InputFn;
};

template <typename InputFn>
class TallyEbo<InputFn, true> {
 public:
  constexpr TallyEbo() = default;
  constexpr TallyEbo(InputFn) {}

  template <typename I>
  constexpr auto tally(I i) const noexcept(noexcept(InputFn{}(i))) {
    return InputFn{}(i);
  }
};

struct FoldLikeTag {};

template <typename InputFn, typename OutputFn>
class FoldImpl : public TallyEbo<InputFn, std::is_empty_v<InputFn>>,
                 public SummarizeEbo<OutputFn, std::is_empty_v<OutputFn>> {
 public:
  explicit constexpr FoldImpl() requires(
      std::is_default_constructible_v<
          TallyEbo<InputFn, std::is_empty_v<InputFn>>>&&
          std::is_default_constructible_v<
              SummarizeEbo<OutputFn, std::is_empty_v<OutputFn>>>) = default;

  explicit constexpr FoldImpl(InputFn in, OutputFn o)
      : TallyEbo<InputFn, std::is_empty_v<InputFn>>{in},
        SummarizeEbo<OutputFn, std::is_empty_v<OutputFn>>{o} {}

  using TallyEbo<InputFn, std::is_empty_v<InputFn>>::tally;
  using SummarizeEbo<OutputFn, std::is_empty_v<OutputFn>>::summarize;
};

template <typename Foldlike>
class FoldImpl<Foldlike, FoldLikeTag> : public Foldlike {
 public:
  explicit constexpr FoldImpl() requires(
      std::is_default_constructible_v<Foldlike>) = default;
  explicit constexpr FoldImpl(Foldlike f) : Foldlike{std::move(f)} {}

  using Foldlike::summarize;
  using Foldlike::tally;
};

template <typename F>
struct lift_t;
}  // namespace detail

template <typename F>
constexpr inline detail::lift_t<remove_cvref_t<F>> lift(F&&);

template <typename InputFn, typename OutputFn>
class Fold : public detail::FoldImpl<InputFn, OutputFn> {
 public:
  explicit constexpr Fold() /* requires std::is_default_constructible_v<
      detail::FoldImpl<InputFn, OutputFn>> */
      = default;

  explicit constexpr Fold(InputFn in, OutputFn out) requires(
      !std::is_same_v<OutputFn, detail::FoldLikeTag>)
      : detail::FoldImpl<InputFn, OutputFn>{std::move(in), std::move(out)} {}

  explicit constexpr Fold(InputFn in) requires(
      std::is_same_v<OutputFn, detail::FoldLikeTag>)
      : detail::FoldImpl<InputFn, detail::FoldLikeTag>{std::move(in)} {}

  using detail::FoldImpl<InputFn, OutputFn>::tally;
  using detail::FoldImpl<InputFn, OutputFn>::summarize;

  template <typename F>
  constexpr auto map(F f) const;

 private:
  template <typename G1, typename G2>
  friend constexpr auto inline operator+(Fold f1, Fold<G1, G2> f2) {
    return lift(std::plus<>{})(f1, f2);
  }

  template <typename Num,
            std::enable_if_t<!detail::is_fold_v<remove_cvref_t<Num>>, int> = 0>
  friend constexpr auto inline operator+(Num n, Fold f) {
    return lift(std::plus<>{})(detail::pure_fold(n), f);
  }

  template <typename Num,
            std::enable_if_t<!detail::is_fold_v<remove_cvref_t<Num>>, int> = 0>
  friend constexpr auto inline operator+(Fold f, Num n) {
    return lift(std::plus<>{})(f, detail::pure_fold(n));
  }

  template <typename F, typename G>
  friend constexpr auto inline operator/(Fold f1, Fold<F, G> f2) {
    return lift(std::divides<>{})(f1, f2);
  }

  template <typename Num,
            std::enable_if_t<!detail::is_fold_v<remove_cvref_t<Num>>, int> = 0>
  friend constexpr auto inline operator/(Num n, Fold f) {
    return lift(std::divides<>{})(detail::pure_fold(n), f);
  }

  template <typename Num,
            std::enable_if_t<!detail::is_fold_v<remove_cvref_t<Num>>, int> = 0>
  friend constexpr auto inline operator/(Fold f, Num n) {
    return lift(std::divides<>{})(f, detail::pure_fold(n));
  }

  template <typename F, typename G>
  friend constexpr auto inline operator*(Fold f1, Fold<F, G> f2) {
    return lift(std::multiplies<>{})(f1, f2);
  }

  template <typename Num,
            std::enable_if_t<!detail::is_fold_v<remove_cvref_t<Num>>, int> = 0>
  friend constexpr auto inline operator*(Num n, Fold f) {
    return lift(std::multiplies<>{})(detail::pure_fold(n), f);
  }

  template <typename Num,
            std::enable_if_t<!detail::is_fold_v<remove_cvref_t<Num>>, int> = 0>
  friend constexpr auto inline operator*(Fold f, Num n) {
    return lift(std::multiplies<>{})(f, detail::pure_fold(n));
  }

  template <typename G1, typename G2>
  friend constexpr auto inline operator-(Fold f1, Fold<G1, G2> f2) {
    return lift(std::minus<>{})(f1, f2);
  }

  template <typename Num,
            std::enable_if_t<!detail::is_fold_v<remove_cvref_t<Num>>, int> = 0>
  friend constexpr auto inline operator-(Num n, Fold f) {
    return lift(std::minus<>{})(detail::pure_fold(n), f);
  }

  template <typename Num,
            std::enable_if_t<!detail::is_fold_v<remove_cvref_t<Num>>, int> = 0>
  friend constexpr auto inline operator-(Fold f, Num n) {
    return lift(std::minus<>{})(f, detail::pure_fold(n));
  }

  friend constexpr auto inline operator-(Fold f1) {
    return f1.map(std::negate<>{});
  }

  friend constexpr auto inline operator+(Fold f1) {
    return f1.map([](auto val) { return +val; });
  }
};

template <typename F1, typename F2>
Fold(F1, F2)->Fold<remove_cvref_t<F1>, remove_cvref_t<F2>>;

namespace detail {

template <typename FoldsTupleT, typename F, typename MonoidT, std::size_t... I>
constexpr auto lift_summarize_impl(FoldsTupleT const& folds, F fn, MonoidT m,
                                   std::index_sequence<I...>) {
  return fn((get<I>(folds).summarize(get<I>(m)))...);
}

template <typename FoldsTupleT, typename T, std::size_t... I>
constexpr auto lift_tally_impl(FoldsTupleT const& folds, T in,
                               std::index_sequence<I...>) {
  return folds::make_tuple((get<I>(folds).tally(in))...);
}

template <typename F, typename... Folds>
struct lift_impl_t {
  explicit constexpr lift_impl_t() = default;

  explicit constexpr lift_impl_t(F f, Folds... folds)
      : _f{std::move(f)}, _folds{folds::make_tuple(std::move(folds)...)} {}

  template <typename T>
  constexpr auto tally(T const& v) const {
    return lift_tally_impl(_folds, v,
                           std::make_index_sequence<sizeof...(Folds)>{});
  }

  template <typename MonoidT>
  constexpr auto summarize(MonoidT const& m) const {
    return lift_summarize_impl(_folds, _f, m,
                               std::make_index_sequence<sizeof...(Folds)>{});
  }

  [[no_unique_address]] F _f;
  [[no_unique_address]] tuple<Folds...> _folds;
};

template <typename F, typename... Folds>
lift_impl_t(F, Folds...)
    ->lift_impl_t<remove_cvref_t<F>, remove_cvref_t<Folds>...>;

template <typename F>
struct lift_t {
  explicit constexpr lift_t(F f) : _f{std::move(f)} {}

  template <typename... Folds>
  constexpr auto operator()(Folds... folds) const {
    return Fold<lift_impl_t<remove_cvref_t<F>, remove_cvref_t<Folds>...>,
                FoldLikeTag>{lift_impl_t{_f, std::move(folds)...}};
  }

  [[no_unique_address]] F _f;
};

template <typename F>
lift_t(F)->lift_t<remove_cvref_t<F>>;

}  // namespace detail

template <typename F>
constexpr detail::lift_t<remove_cvref_t<F>> inline lift(F&& f) {
  return detail::lift_t{std::forward<F>(f)};
};

template <typename InputFn, typename OutputFn>
template <typename F>
constexpr auto Fold<InputFn, OutputFn>::map(F f) const {
  return lift(f)(*this);
}

}  // namespace folds
