#ifndef _16440A5B_49BD_489E_8A85_C74CDC203CA1_HPP
#define _16440A5B_49BD_489E_8A85_C74CDC203CA1_HPP

#include <type_traits>
#include <utility>

#include <boost/hana.hpp>

#include "meta/type_traits.hpp"

namespace edsl::gen {

struct fail {};

template <typename T>
class operand {
 public:
  operand(T&& t) : func(std::forward<T>(t)) {}

  template <typename... Args>
  bool operator()(Args&&... args) {
    auto result = func(std::forward<Args>(args)...);

    static_assert(!std::is_same<decltype(result), fail>::value,
                  "invalid argument types");

    return result;
  }

  using functor_type = T;

 private:
  T func;
};

template <typename T>
auto op(T&& t) {
  return operand<T>{std::forward<T>(t)};
}

template <typename T>
struct wrapper : public T {};

template <typename T>
auto wrap(T&& t) {
  return wrapper<T>{std::forward<T>(t)};
}

template <typename F, typename Sink, typename... Args>
bool invoke(F f, Sink sink, Args&&... args) {
  static_assert(decltype(
      boost::hana::is_valid(f)(sink, std::forward<Args>(args)...))::value);
  using return_t = meta::invoke_result_t<F, Sink, Args...>;
  if
    constexpr(std::is_same<return_t, void>::value) {
      f(sink, std::forward<Args>(args)...);
      return true;
    }
  else {
    return f(sink, std::forward<Args>(args)...);
  }
}
}

#endif
