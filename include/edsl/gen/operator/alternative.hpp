#ifndef _A3DB1ABE_7F44_481A_80B0_AEF47BEF22D2_HPP
#define _A3DB1ABE_7F44_481A_80B0_AEF47BEF22D2_HPP

#include "edsl/gen/operand.hpp"

namespace edsl::gen {

template <typename Left, typename Right, typename Size>
auto alternative(operand<Left, Size> left, operand<Right, Size> right) {
  return as_operand(Size{}, [left, right](auto sink, auto const&... args) {
    return invoke(left, sink, args...) || invoke(right, sink, args...);
  });
}

template <typename Left, typename Right>
decltype(alternative(as_operand(std::declval<Left&&>()),
                     as_operand(std::declval<Right&&>())))
operator|(Left left, Right right) {
  return alternative(as_operand(left), as_operand(right));
}

template <typename Left, typename Right, typename Size>
auto operator|(operand<Left, Size> left, operand<Right, Size> right) {
  return op(Size{}, [left, right](auto sink, auto const&... args) {
    return invoke(left, sink, args...) || invoke(right, sink, args...);
  });
}
}
#endif
