#ifndef _C6BD5F07_BAA4_4987_B08E_319373B79739_HPP
#define _C6BD5F07_BAA4_4987_B08E_319373B79739_HPP

#include <type_traits>
#include <utility>

#include <boost/hana.hpp>

#include "edsl/gen/as_operand.hpp"
#include "edsl/gen/invoke.hpp"

namespace edsl::gen {

namespace {

template <typename, typename>
struct sequence_impl;

using boost::hana::tuple;
using boost::hana::basic_type;

template <typename... Args1, typename... Args2>
struct sequence_impl<tuple<basic_type<Args1>...>, tuple<basic_type<Args2>...>> {
  template <typename Op1, typename Op2, typename Sink>
  static auto apply(Op1 op1, Op2 op2, Sink sink, Args1 const&... args1,
                    Args2 const&... args2) {
    return invoke(op1, sink, args1...) && invoke(op2, sink, args2...);
  }
};
}

template <typename Left, typename Right,
          typename = decltype(as_operand(std::declval<Left&&>())),
          typename = decltype(as_operand(std::declval<Right&&>()))>
auto operator<<(Left left, Right right) {
  auto op1 = as_operand(left);
  auto op2 = as_operand(right);
  using Size1 = decltype(operand_arguments_size<decltype(op1)>());
  using Size2 = decltype(operand_arguments_size<decltype(op2)>());

  return make_operand(
      boost::hana::int_<Size1::value + Size2::value - 1>{},
      [op1, op2](auto sink, auto const&... args) {
        using namespace boost::hana;
        using namespace boost::hana::literals;

        auto all = make_tuple(basic_type<std::decay_t<decltype(args)>>{}...);
        auto pivot = int_<Size1::value - 1>{};
        using Seq1 = decltype(slice(all, make_range(0_c, pivot)));
        using Seq2 =
            decltype(slice(all, make_range(pivot, int_<sizeof...(args)>{})));

        return sequence_impl<Seq1, Seq2>::apply(op1, op2, sink, args...);
      });
}
}
#endif
