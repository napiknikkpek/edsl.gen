#ifndef _80167005_92F9_41D0_8D46_76FF25FED73B_HPP
#define _80167005_92F9_41D0_8D46_76FF25FED73B_HPP

#include <utility>

#include "edsl/gen/operand.hpp"

namespace edsl::gen {

template <typename T, typename Size>
auto operator!(operand<T, Size> subject) {
  return op(Size{}, [subject](auto sink, auto&&... args) {
    return !invoke(subject, sink, std::forward<decltype(args)>(args)...);
  });
}
}
#endif
