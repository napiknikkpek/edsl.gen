#ifndef _16440A5B_49BD_489E_8A85_C74CDC203CA1_HPP
#define _16440A5B_49BD_489E_8A85_C74CDC203CA1_HPP

#include <type_traits>
#include <utility>

#include <boost/hana.hpp>

#include "arguments.hpp"
#include "detail/invoke_result.hpp"

namespace edsl::gen {

template <typename T>
auto operand_arguments_size();

template <typename T, typename S = decltype(operand_arguments_size<T>())>
struct operand : public T {
  static constexpr int size = S::value;

  template <typename Converter>
  auto operator[](Converter conv);
};

template <typename T>
auto make_operand(T t) {
  return operand<T>{t};
}

template <typename Size, typename T>
auto make_operand(Size, T t) {
  return operand<T, Size>{t};
}

template <typename T, typename S>
template <typename Converter>
auto operand<T, S>::operator[](Converter conv) {
  using namespace boost::hana;

  auto s = boost::hana::size(arguments<Converter>());
  auto op = *this;
  return make_operand(s, [op, conv](auto sink, auto const&... args) {
    auto seq = conv(args...);
    if
      constexpr(Foldable<decltype(seq)>::value) {
        return unpack(
            seq, [op, sink](auto const&... xs) { return op(sink, xs...); });
      }
    else {
      return op(sink, seq);
    }
  });
}

template <typename T>
struct is_operand {
  static constexpr bool value = false;
};

template <typename T, typename S>
struct is_operand<operand<T, S>> {
  static constexpr bool value = true;
};

template <typename T>
constexpr bool is_operand_v = is_operand<T>::value;

template <typename T>
auto operand_arguments_size() {
  if
    constexpr(is_operand_v<T>) { return boost::hana::int_<T::size>{}; }
  else {
    return boost::hana::size(arguments<T>());
  }
}
}

#endif
