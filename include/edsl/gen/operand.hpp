#ifndef _16440A5B_49BD_489E_8A85_C74CDC203CA1_HPP
#define _16440A5B_49BD_489E_8A85_C74CDC203CA1_HPP

#include <type_traits>
#include <utility>

#include <boost/hana.hpp>

#include "meta/arguments.hpp"
#include "meta/result.hpp"
#include "meta/type_traits.hpp"

namespace edsl::gen {

template <typename T>
auto arguments_size();

template <typename Functor>
auto as_operand(Functor&&);

template <typename Size, typename Functor>
auto as_operand(Size, Functor&&);

// template <typename T>
// auto result_type_size() {
//   using namespace boost::hana::literals;

//   using result = typename decltype(meta::result<T>())::type;

//   if
//     constexpr(boost::hana::Foldable<result>::value) {
//       return decltype(boost::hana::size(std::declval<result&&>())){};
//     }
//   else {
//     return 1_c;
//   }
// }

template <typename T, typename S = decltype(arguments_size<T>())>
struct operand : public T {
  static constexpr int size = S::value;

  template <typename Converter>
  auto operator[](Converter conv) {
    using namespace boost::hana;

    auto s = boost::hana::size(meta::arguments<Converter>());
    auto subject = *this;
    return op(s, [subject, conv](auto sink, auto&&... args) {
      auto seq = conv(std::forward<decltype(args)>(args)...);
      if
        constexpr(Foldable<decltype(seq)>::value) {
          return unpack(seq, [subject, sink](auto... xs) {
            return subject(sink, xs...);
          });
        }
      else {
        return subject(sink, seq);
      }
    });
  }
};

template <typename Functor>
auto op(Functor&& f) {
  return operand<std::decay_t<Functor>>{std::forward<Functor>(f)};
}

template <typename Size, typename Functor>
auto op(Size, Functor&& f) {
  return operand<std::decay_t<Functor>, Size>{std::forward<Functor>(f)};
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
auto arguments_size() {
  if
    constexpr(is_operand_v<T>) { return boost::hana::int_<T::size>{}; }
  else {
    return boost::hana::size(meta::arguments<T>());
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
