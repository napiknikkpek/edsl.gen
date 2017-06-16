#ifndef _16440A5B_49BD_489E_8A85_C74CDC203CA1_HPP
#define _16440A5B_49BD_489E_8A85_C74CDC203CA1_HPP

#include <type_traits>
#include <utility>

#include <boost/hana.hpp>

namespace edsl::gen {

struct fail {};

template <typename T>
struct operand : public T {};

template <typename T>
auto op(T&& t) {
  return operand<std::decay_t<T>>{std::forward<T>(t)};
}

template <typename F, typename... Args>
bool invoke(F f, Args&&... args) {
  static_assert(
      decltype(boost::hana::is_valid(f)(std::forward<Args>(args)...))::value);
  using return_t = decltype(std::declval<F>()(std::declval<Args>()...));
  if
    constexpr(std::is_same<return_t, void>::value) {
      f(std::forward<Args>(args)...);
      return true;
    }
  else {
    return f(std::forward<Args>(args)...);
  }
}
}

#endif
