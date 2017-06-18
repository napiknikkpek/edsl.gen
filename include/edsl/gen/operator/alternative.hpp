#ifndef _A3DB1ABE_7F44_481A_80B0_AEF47BEF22D2_HPP
#define _A3DB1ABE_7F44_481A_80B0_AEF47BEF22D2_HPP

#include <boost/hana.hpp>

#include "edsl/gen/operand.hpp"

namespace edsl::gen {
template <typename X, typename Y>
auto operator|(wrapper<X> x, wrapper<Y> y) {
  return op([x, y](auto sink, auto&&... args) {
    return invoke(x, sink, std::forward<decltype(args)>(args)...) ||
           invoke(y, sink, std::forward<decltype(args)>(args)...);
  });
}
}
#endif
