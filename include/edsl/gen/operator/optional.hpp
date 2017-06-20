#ifndef _599FD4B2_BB53_443B_A041_4A71754AE3AA_HPP
#define _599FD4B2_BB53_443B_A041_4A71754AE3AA_HPP

#include <utility>

#include "edsl/gen/as_operand.hpp"

namespace edsl::gen {

template <typename Subject,
          typename = decltype(as_operand(std::declval<Subject&&>()))>
auto operator-(Subject subject) {
  auto op = as_operand(subject);
  using Size = decltype(arguments_size<decltype(op)>());

  if
    constexpr(Size::value == 1) {
      return make_operand(Size{}, [op](auto sink) { return invoke(op, sink); });
    }
  else {
    return make_operand(Size{}, [op](auto sink, auto const& arg) {
      if (arg) {
        return invoke(op, sink, *arg);
      } else {
        return true;
      }
    });
  }
}
}
#endif
