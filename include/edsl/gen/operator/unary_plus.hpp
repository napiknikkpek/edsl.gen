#ifndef _C8E6271E_F64B_4771_A06C_C5B5BE1C6C48_HPP
#define _C8E6271E_F64B_4771_A06C_C5B5BE1C6C48_HPP

#include <boost/hana.hpp>

#include "edsl/gen/operator/kleene.hpp"

namespace edsl::gen {

template <typename Subject,
          typename = decltype(as_operand(std::declval<Subject&&>()))>
auto operator+(Subject subject) {
  using namespace boost::hana::literals;

  auto kleene = *as_operand(subject);

  return make_operand(1_c, [kleene](auto sink, auto const& vec) {
    if (vec.empty()) return false;
    return kleene(sink, vec);
  });
}
}
#endif
