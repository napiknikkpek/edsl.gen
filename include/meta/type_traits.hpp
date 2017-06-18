#ifndef _709C2BBD_DCDB_4795_80DC_160C318677D7_HPP
#define _709C2BBD_DCDB_4795_80DC_160C318677D7_HPP

#include <type_traits>
#include <utility>

#include <boost/hana/type.hpp>

namespace meta {

template <typename F, typename... Args>
using invoke_result_t =
    decltype(std::declval<F&&>()(std::declval<Args&&>()...));

namespace {
template <typename T>
struct call_arguments_impl {
  static_assert(!std::is_same<T, T>::value, "'T' is not a functor");
};
;

template <typename... Args>
struct call_arguments_impl<void(Args...)> {
  using type = boost::hana::tuple<boost::hana::type<Args>...>;
};

template <typename T, typename... Args>
struct call_arguments_impl<void (T::*)(Args...)> {
  using type = boost::hana::tuple<boost::hana::type<Args>...>;
};

template <typename T, typename... Args>
struct call_arguments_impl<void (T::*)(Args...) const> {
  using type = boost::hana::tuple<boost::hana::type<Args>...>;
};
}

template <typename T>
auto call_arguments(T) {
  using NoPointer = std::remove_pointer_t<T>;
  using Decay = std::decay_t<T>;
  if
    constexpr(std::is_pointer<T>::value && std::is_function<NoPointer>::value) {
      using args_t = typename call_arguments_impl<NoPointer>::type;
      return args_t{};
    }
  else {
    using args_t =
        typename call_arguments_impl<decltype(&Decay::operator())>::type;
    return args_t{};
  }
}
}

#endif
