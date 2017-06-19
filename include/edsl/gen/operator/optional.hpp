#ifndef _599FD4B2_BB53_443B_A041_4A71754AE3AA_HPP
#define _599FD4B2_BB53_443B_A041_4A71754AE3AA_HPP

#include "edsl/gen/operand.hpp"

namespace edsl::gen {

template <typename T, typename Size>
auto operator-(operand<T, Size> subject) {
  return op(Size{}, [subject](auto sink, auto const& arg) {
    if (arg) {
      return invoke(subject, sink, arg);
    } else {
      return true;
    }
  });
}
}
#endif
