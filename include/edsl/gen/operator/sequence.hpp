#ifndef _C6BD5F07_BAA4_4987_B08E_319373B79739_HPP
#define _C6BD5F07_BAA4_4987_B08E_319373B79739_HPP

#include <utility>

#include <boost/hana.hpp>

#include "edsl/gen/operand.hpp"
#include "meta/type_traits.hpp"

namespace edsl::gen {

template <typename... Xs>
struct sequence_impl {
  template <typename X, typename Y, typename Sink, typename... Ys>
  static constexpr auto apply(X x, Y y, Sink sink, typename Xs::type&&... xs,
                              Ys&&... ys) {
    return invoke(x, sink, std::forward<typename Xs::type>(xs)...) &&
           invoke(y, sink, std::forward<Ys>(ys)...);
  }
};

template <typename X, typename Y>
auto operator<<(operand<X> x, operand<Y> y) {
  return op([x, y](auto sink, auto&&... args) {
    using namespace boost::hana;
    using namespace boost::hana::literals;

    auto seq1 = drop_front(meta::call_arguments(x));
    auto seq2 = drop_front(meta::call_arguments(y));

    static_assert(decltype(size(seq1) + size(seq2))::value == sizeof...(args),
                  "invalid argument types");

    return unpack(seq1, [x, y, sink, &args...](auto... xs) {
      return sequence_impl<decltype(xs)...>::apply(
          x, y, sink, std::forward<decltype(args)>(args)...);
    });
  });
}
}
#endif
