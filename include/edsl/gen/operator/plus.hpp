#ifndef _A706DDD6_D20C_4BA3_81C9_441154DFD569_HPP
#define _A706DDD6_D20C_4BA3_81C9_441154DFD569_HPP

#include <boost/hana.hpp>

#include "edsl/gen/operand.hpp"

namespace edsl::gen {

template <typename X, typename Y>
auto operator+(X x, Y y) {
  return op([x, y](auto sink, auto&&... args) {
    return invoke(x, sink, std::forward<decltype(args)>(args)...) &&
           invoke(y, sink, std::forward<decltype(args)>(args)...);
  });
}
}
#endif
