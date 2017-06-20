#ifndef _4696D78D_5318_4728_A49F_BEBBD4D87A43_HPP
#define _4696D78D_5318_4728_A49F_BEBBD4D87A43_HPP

#include <boost/hana.hpp>

#include "edsl/gen/as_operand.hpp"
#include "edsl/gen/invoke.hpp"

namespace edsl::gen {

template <typename Subject,
          typename = decltype(as_operand(std::declval<Subject&&>()))>
auto operator*(Subject subject) {
  using namespace boost::hana::literals;

  auto op = as_operand(subject);
  using Size = decltype(operand_arguments_size<decltype(op)>());

  return make_operand(1_c, [op](auto sink, auto const& vec) {
    for (auto& e : vec) {
      if
        constexpr(boost::hana::Foldable<std::decay_t<decltype(e)>>::value) {
          if (!boost::hana::unpack(e, [op, sink](auto const&... xs) {
                return invoke(op, sink, xs...);
              }))
            return false;
        }
      else {
        if (!invoke(op, sink, e)) return false;
      }
    }
    return true;
  });
}
}

#endif
