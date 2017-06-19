#include <complex>
#include <iostream>

#include "edsl/gen/operand.hpp"
#include "edsl/gen/operator/alternative.hpp"
#include "edsl/gen/operator/and_predicate.hpp"
#include "edsl/gen/operator/sequence.hpp"

#include <boost/hana.hpp>

using edsl::gen::as_operand;

auto double_ = [](std::ostream& out, double v) { out << v; };

auto true_ = as_operand([](bool v) { return v == true; });

auto as_operand(char ch) {
  return as_operand([=](std::ostream& out) { out << ch; });
}

int main() {
  auto check_real_imag = [](std::complex<double> const& c) {
    return boost::hana::make_tuple(c.imag() != 0, c.real(), c.imag());
  };
  auto real = [](std::complex<double> const& c) { return c.real(); };

  auto g =
      (&true_ << '(' << double_ << ',' << double_ << ')')[check_real_imag] |
      double_[real];

  std::complex<double> c{1, 2};
  g(std::ref(std::cout), c);
}
