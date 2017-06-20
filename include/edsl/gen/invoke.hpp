#ifndef _419D40BE_72C1_4D77_A5A6_11D8F31195ED_HPP
#define _419D40BE_72C1_4D77_A5A6_11D8F31195ED_HPP

#include <type_traits>

#include <boost/hana/type.hpp>

#include "detail/invoke_result.hpp"

namespace edsl::gen {

template <typename F, typename Sink, typename... Args>
bool invoke(F f, Sink sink, Args const&... args) {
  static_assert(decltype(boost::hana::is_valid(f)(sink, args...))::value);

  using return_t = detail::invoke_result_t<F, Sink, Args const&...>;
  if
    constexpr(std::is_same<return_t, void>::value) {
      f(sink, args...);
      return true;
    }
  else {
    return f(sink, args...);
  }
}
}
#endif
