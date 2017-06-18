#ifndef _C6BD5F07_BAA4_4987_B08E_319373B79739_HPP
#define _C6BD5F07_BAA4_4987_B08E_319373B79739_HPP

#include <utility>

#include <boost/hana.hpp>

#include "edsl/gen/operand.hpp"
#include "meta/type_traits.hpp"

namespace edsl::gen {

namespace detail {

template <typename F, typename... Args,
          typename = meta::invoke_result_t<F, Args...>>
constexpr auto is_valid_impl(int) {
  return boost::hana::true_{};
}

template <typename F, typename... Args>
constexpr auto is_valid_impl(...) {
  return boost::hana::false_{};
}

template <typename T>
struct is_operand {
  static constexpr bool value = false;
};

template <typename T>
struct is_operand<operand<T>> {
  static constexpr bool value = true;
};

template <typename T>
constexpr bool is_operand_v = is_operand<T>::value;

template <typename F, typename Sink, typename... Args>
auto is_valid(boost::hana::basic_type<F>, boost::hana::basic_type<Sink>,
              boost::hana::tuple<boost::hana::basic_type<Args>...> args) {
  if
    constexpr(is_operand_v<F>) {
      return boost::hana::not_(
          std::is_same<
              meta::invoke_result_t<typename F::functor_type, Sink, Args...>,
              fail>{});
    }
  else {
    return is_valid_impl<F, Sink, Args...>(int{});
  }
}

template <typename X, typename Sink, typename Args>
constexpr auto args_size(X, Sink sink, Args args) {
  using namespace boost::hana::literals;
  using namespace boost::hana;

  return find_if(make_range(0_c, size(args) + size_t<1>{}), [&](auto i) {
    return detail::is_valid(type<X>{}, sink, slice(args, make_range(0_c, i)));
  });
}
}

template <typename... Xs>
struct sequence_invoke {
  template <typename X, typename Y, typename Sink, typename... Ys>
  static constexpr auto apply(X x, Y y, Sink sink, typename Xs::type&&... xs,
                              Ys&&... ys) {
    return invoke(x, sink, std::forward<typename Xs::type>(xs)...) &&
           invoke(y, sink, std::forward<Ys>(ys)...);
  }
};

template <typename X, typename Y>
auto operator<<(X x, Y y) {
  return op([x, y](auto sink, auto&&... args) {
    using namespace boost::hana;
    using namespace boost::hana::literals;

    auto st = type<decltype(sink)>{};
    auto seq = make_tuple(basic_type<std::decay_t<decltype(args)>>{}...);

    auto opt = detail::args_size(x, st, seq);
    if
      constexpr(opt == nothing) { return fail{}; }
    else {
      auto pivot = *opt;

      auto seq1 = slice(seq, make_range(0_c, pivot));
      auto seq2 = slice(seq, make_range(pivot, size(seq)));

      if
        constexpr(!decltype(detail::is_valid(type<Y>{}, st, seq2))::value) {
          return fail{};
        }
      else {
        return unpack(seq1, [x, y, sink, &args...](auto... xs) {
          return sequence_invoke<decltype(xs)...>::apply(
              x, y, sink, std::forward<decltype(args)>(args)...);
        });
      }
    }
  });
}
}
#endif
