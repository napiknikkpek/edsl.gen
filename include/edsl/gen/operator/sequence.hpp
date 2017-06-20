#ifndef _C6BD5F07_BAA4_4987_B08E_319373B79739_HPP
#define _C6BD5F07_BAA4_4987_B08E_319373B79739_HPP

#include <utility>

#include <boost/hana.hpp>

#include "edsl/gen/operand.hpp"
#include "meta/type_traits.hpp"

namespace edsl::gen {

template <typename... Args1>
struct sequence_impl {
  template <typename Op1, typename Op2, typename Sink, typename... Args2>
  static constexpr auto apply(Op1 op1, Op2 op2, Sink sink,
                              typename Args1::type const&... args1,
                              Args2 const&... args2) {
    return invoke(op1, sink, args1...) && invoke(op2, sink, args2...);
  }
};

template <typename Left, typename Right,
          typename = decltype(as_operand(std::declval<Left&&>())),
          typename = decltype(as_operand(std::declval<Right&&>()))>
auto operator<<(Left left, Right right) {
  auto op1 = as_operand(left);
  auto op2 = as_operand(right);
  using Size1 = decltype(arguments_size<decltype(op1)>());
  using Size2 = decltype(arguments_size<decltype(op2)>());

  return make_operand(
      boost::hana::int_<Size1::value + Size2::value - 1>{},
      [op1, op2](auto sink, auto const&... args) {
        using namespace boost::hana;
        using namespace boost::hana::literals;

        auto seq1 = slice(make_tuple(type<decltype(args)>{}...),
                          make_range(0_c, int_<Size1::value - 1>{}));

        return unpack(seq1, [op1, op2, sink, &args...](auto... xs) {
          return sequence_impl<decltype(xs)...>::apply(op1, op2, sink, args...);
        });
      });
}
}
#endif
