#ifndef _A3DB1ABE_7F44_481A_80B0_AEF47BEF22D2_HPP
#define _A3DB1ABE_7F44_481A_80B0_AEF47BEF22D2_HPP

#include <boost/hana.hpp>

#include "edsl/gen/core.hpp"

namespace edsl::gen {
template <typename X, typename Y>
auto operator|(X x, Y y) {
  return op([x, y](auto&&... args) {
    return invoke(x, std::forward<decltype(args)>(args)...) ||
           invoke(y, std::forward<decltype(args)>(args)...);
  });
}
}
#endif
