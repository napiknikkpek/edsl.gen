#ifndef _16440A5B_49BD_489E_8A85_C74CDC203CA1_HPP
#define _16440A5B_49BD_489E_8A85_C74CDC203CA1_HPP

#include <type_traits>
#include <utility>

#include <boost/hana.hpp>

#include "meta/type_traits.hpp"

namespace edsl::gen {

template <typename T>
auto arguments_size(T);

template <typename T,
          int S = decltype(arguments_size(std::declval<T&&>()))::value>
struct operand : public T {
 public:
  static constexpr int size = S;

  operand(T t) : T{t} {}
};

template <typename T>
auto op(T&& t) {
  return operand<std::decay_t<T>>{std::forward<T>(t)};
}

template <int S, typename T>
auto op(boost::hana::int_<S>, T&& t) {
  return operand<std::decay_t<T>, S>{std::forward<T>(t)};
}

template <typename T>
struct is_operand {
  static constexpr bool value = false;
};

template <typename T, int S>
struct is_operand<operand<T, S>> {
  static constexpr bool value = true;
};

template <typename T>
constexpr bool is_operand_v = is_operand<T>::value;

template <typename T>
auto arguments_size(T) {
  if
    constexpr(is_operand_v<T>) { return boost::hana::int_<T::size>{}; }
  else {
    return boost::hana::size(meta::call_arguments(std::declval<T&&>()));
  }
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
