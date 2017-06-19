#ifndef _9026FE3D_F44E_4653_810E_5630C228A4D8_HPP
#define _9026FE3D_F44E_4653_810E_5630C228A4D8_HPP

#include <utility>

#include <boost/hana.hpp>

namespace edsl::gen {

template <typename T, typename = decltype(&T::operator())>
boost::hana::true_ is_callable_impl(int);

template <typename T>
boost::hana::false_ is_callable_impl(...);

template <typename T>
constexpr bool is_callable_v = decltype(is_callable_impl<T>(int{}))::value;
}

#endif
