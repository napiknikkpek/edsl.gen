#ifndef _C6BD5F07_BAA4_4987_B08E_319373B79739_HPP
#define _C6BD5F07_BAA4_4987_B08E_319373B79739_HPP

#include <utility>

#include <boost/hana.hpp>

#include "edsl/gen/core.hpp"

namespace edsl::gen {

namespace detail {

template <typename F, typename... Args>
using invoke_result_t =
    decltype(std::declval<F&&>()(std::declval<Args&&>()...));

template <typename F, typename... Args, typename = invoke_result_t<F, Args...>>
constexpr auto is_valid_impl(int) {
  return boost::hana::true_{};
}

template <typename F, typename... Args>
constexpr auto is_valid_impl(...) {
  return boost::hana::false_{};
}

template <typename F, typename... Args>
auto is_valid(boost::hana::basic_type<F>,
              boost::hana::tuple<boost::hana::basic_type<Args>...>) {
  if
    constexpr(is_valid_impl<F, Args...>(int{})) {
      return std::is_same<invoke_result_t<F, Args...>, fail>{};
    }
  else {
    return boost::hana::false_{};
  }
}

template <typename X, typename... Args>
constexpr auto args_size(X, Args&&...) {
  using namespace boost::hana::literals;
  using boost::hana::find_if;
  using boost::hana::size;
  using boost::hana::make_range;
  using boost::hana::slice;
  using boost::hana::type;
  using boost::hana::tuple;
  using boost::hana::basic_type;
  using boost::hana::size_t;

  tuple<basic_type<Args>...> args;

  return find_if(make_range(0_c, size(args) + size_t<1>{}), [&args](auto i) {
    return is_valid(type<X>{}, slice(args, make_range(0_c, i)));
  });
}
}

template <typename... Xs>
struct sequence_impl {
  template <typename X, typename Y, typename... Ys>
  static constexpr auto apply(X x, Y y, typename Xs::type&&... xs, Ys&&... ys) {
    return invoke(x, std::forward<typename Xs::type>(xs)...) &&
           invoke(y, std::forward<Ys>(ys)...);
  }
};

template <typename X, typename Y>
auto operator<<(X x, Y y) {
  return op([x, y](auto&&... args) {
    using namespace boost::hana;
    using namespace boost::hana::literals;

    auto opt = detail::args_size(x, std::forward<decltype(args)>(args)...);
    if
      constexpr(opt == nothing) { return fail{}; }
    else {
      auto pivot = *opt;

      auto t = make_tuple(type<std::decay_t<decltype(args)>>{}...);
      auto seq = slice(t, make_range(0_c, pivot));

      return unpack(seq, [x, y, &args...](auto... xs) {
        return sequence_impl<decltype(xs)...>::apply(
            x, y, std::forward<decltype(args)>(args)...);
      });
    }
  });
}
}
#endif
