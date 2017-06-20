#ifndef _A3DB1ABE_7F44_481A_80B0_AEF47BEF22D2_HPP
#define _A3DB1ABE_7F44_481A_80B0_AEF47BEF22D2_HPP

#include <utility>

#include "edsl/gen/as_operand.hpp"
#include "edsl/gen/invoke.hpp"

namespace edsl::gen {

template <typename Left, typename Right,
          typename = decltype(as_operand(std::declval<Left&&>())),
          typename = decltype(as_operand(std::declval<Right&&>()))>
auto operator|(Left left, Right right) {
  auto op1 = as_operand(left);
  auto op2 = as_operand(right);
  auto size = operand_arguments_size<decltype(op1)>();
  return make_operand(size, [op1, op2](auto sink, auto const&... args) {
    return invoke(op1, sink, args...) || invoke(op2, sink, args...);
  });
}
}
#endif
