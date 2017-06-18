#ifndef _80167005_92F9_41D0_8D46_76FF25FED73B_HPP
#define _80167005_92F9_41D0_8D46_76FF25FED73B_HPP

#include <utility>

#include "edsl/gen/operand.hpp"

namespace edsl::gen {

template <typename X>
auto operator!(X x) {
  return op([x](auto sink, auto&&... args) {
    return !invoke(x, sink, std::forward<decltype(args)>(args)...);
  });
}
}
#endif
