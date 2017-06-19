#ifndef _260007F8_D2D8_49D7_947C_FC6AE54FC6E4_HPP
#define _260007F8_D2D8_49D7_947C_FC6AE54FC6E4_HPP

#include <type_traits>
#include <utility>

#include "is_callable.hpp"
#include "operand.hpp"

namespace edsl::gen {

template <typename T, typename S>
auto as_operand(operand<T, S> op) {
  return op;
}

template <typename Callable,
          typename = std::enable_if_t<is_callable_v<Callable>>>
auto as_operand(Callable callable) {
  return make_operand(callable);
}
}
#endif
