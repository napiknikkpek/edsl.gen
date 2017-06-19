#ifndef _A3DB1ABE_7F44_481A_80B0_AEF47BEF22D2_HPP
#define _A3DB1ABE_7F44_481A_80B0_AEF47BEF22D2_HPP

#include "edsl/gen/operand.hpp"

namespace edsl::gen {
template <typename Lhs, typename Rhs, typename Size>
auto operator|(operand<Lhs, Size> lhs, operand<Rhs, Size> rhs) {
  return op(Size{}, [lhs, rhs](auto sink, auto&&... args) {
    return invoke(lhs, sink, std::forward<decltype(args)>(args)...) ||
           invoke(rhs, sink, std::forward<decltype(args)>(args)...);
  });
}
}
#endif
