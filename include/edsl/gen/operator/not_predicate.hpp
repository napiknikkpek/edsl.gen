#ifndef _80167005_92F9_41D0_8D46_76FF25FED73B_HPP
#define _80167005_92F9_41D0_8D46_76FF25FED73B_HPP

#include <utility>

#include "edsl/gen/operand.hpp"

namespace edsl::gen {

template <typename X, int S>
auto operator!(operand<X, S> x) {
  return op(boost::hana::int_<S>{}, [x](auto sink, auto&&... args) {
    return !invoke(x, sink, std::forward<decltype(args)>(args)...);
  });
}
}
#endif
