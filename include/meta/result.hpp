#ifndef _3C9B4D4A_9E10_4B06_9B46_682B66140BBC_HPP
#define _3C9B4D4A_9E10_4B06_9B46_682B66140BBC_HPP

#include <type_traits>
#include <utility>

#include <boost/hana/type.hpp>

namespace meta {

template <typename T>
struct result_impl {
  static_assert(!std::is_same<T, T>::value, "T is not a functor");
};

template <typename R, typename... Args>
struct result_impl<R(Args...)> {
  using type = boost::hana::type<R>;
};

template <typename T, typename R, typename... Args>
struct result_impl<R (T::*)(Args...)> {
  using type = boost::hana::type<R>;
};

template <typename T, typename R, typename... Args>
struct result_impl<R (T::*)(Args...) const> {
  using type = boost::hana::type<R>;
};

template <typename T>
auto result() {
  using NoPointer = std::remove_pointer_t<T>;
  using Decay = std::decay_t<T>;
  if
    constexpr(std::is_pointer<T>::value && std::is_function<NoPointer>::value) {
      using res = typename result_impl<NoPointer>::type;
      return res{};
    }
  else {
    using res = typename result_impl<decltype(&Decay::operator())>::type;
    return res{};
  }
}
}
#endif
