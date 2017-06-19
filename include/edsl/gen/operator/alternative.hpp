#ifndef _A3DB1ABE_7F44_481A_80B0_AEF47BEF22D2_HPP
#define _A3DB1ABE_7F44_481A_80B0_AEF47BEF22D2_HPP

#include "edsl/gen/operand.hpp"

namespace edsl::gen {
template <typename X, typename Y, int S>
auto operator|(operand<X, S> x, operand<Y, S> y) {
  return op(boost::hana::int_<S>{}, [x, y](auto sink, auto&&... args) {
    return invoke(x, sink, std::forward<decltype(args)>(args)...) ||
           invoke(y, sink, std::forward<decltype(args)>(args)...);
  });
}
}
#endif
