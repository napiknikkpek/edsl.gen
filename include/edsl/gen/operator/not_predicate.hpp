#ifndef _80167005_92F9_41D0_8D46_76FF25FED73B_HPP
#define _80167005_92F9_41D0_8D46_76FF25FED73B_HPP

#include <utility>

#include "edsl/gen/as_operand.hpp"

namespace edsl::gen {

template <typename Subject,
          typename = decltype(as_operand(std::declval<Subject&&>()))>
auto operator!(Subject subject) {
  auto op = as_operand(subject);
  auto size = arguments_size<decltype(op)>();
  return make_operand(size, [op](auto sink, auto const&... args) {
    return !invoke(op, sink, args...);
  });
}
}
#endif
