#ifndef _709C2BBD_DCDB_4795_80DC_160C318677D7_HPP
#define _709C2BBD_DCDB_4795_80DC_160C318677D7_HPP

#include <type_traits>
#include <utility>

#include <boost/hana/type.hpp>

namespace meta {

namespace {
template <typename T>
struct arguments_impl {
  static_assert(!std::is_same<T, T>::value, "'T' is not a functor");
};
;

template <typename R, typename... Args>
struct arguments_impl<R(Args...)> {
  using type = boost::hana::tuple<boost::hana::type<Args>...>;
};

template <typename T, typename R, typename... Args>
struct arguments_impl<R (T::*)(Args...)> {
  using type = boost::hana::tuple<boost::hana::type<Args>...>;
};

template <typename T, typename R, typename... Args>
struct arguments_impl<R (T::*)(Args...) const> {
  using type = boost::hana::tuple<boost::hana::type<Args>...>;
};
}

template <typename T>
auto arguments() {
  using NoPointer = std::remove_pointer_t<T>;
  using Decay = std::decay_t<T>;
  if
    constexpr(std::is_pointer<T>::value && std::is_function<NoPointer>::value) {
      using args = typename arguments_impl<NoPointer>::type;
      return args{};
    }
  else {
    using args = typename arguments_impl<decltype(&Decay::operator())>::type;
    return args{};
  }
}
}

#endif
