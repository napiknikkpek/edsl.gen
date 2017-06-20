#ifndef _0D70DED7_D0BA_460D_A2FB_F6B1C9939B38_HPP
#define _0D70DED7_D0BA_460D_A2FB_F6B1C9939B38_HPP

#include <utility>

#include "edsl/gen/as_operand.hpp"

namespace edsl::gen {

template <typename Subject,
          typename = decltype(as_operand(std::declval<Subject&&>()))>
auto operator&(Subject subject) {
  auto op = as_operand(subject);
  using Size = decltype(arguments_size<decltype(op)>());

  return make_operand(
      boost::hana::int_<Size::value + 1>{},
      [op](auto /*sink*/, auto const&... args) { return invoke(op, args...); });
}
}

#endif
