#include <complex>
#include <iostream>

#include "edsl/gen/gen.hpp"

// using edsl::gen::eps;
using edsl::gen::wrap;

auto double_ = wrap([](std::ostream& out, double v) { out << v; });

auto lit(char ch) {
  return wrap([=](std::ostream& out) { out << ch; });
}

int main() {
  // auto is_real = eps([](auto const& c) { return c.imag() == 0; });
  auto get_real = [](auto const& c) { return c.real(); };
  auto get_imag = [](auto const& c) { return c.imag(); };

  auto g =
      /*!is_real +*/ lit('(')
          << double_[get_real] + lit(',') + double_[get_imag] << lit(')') |
      double_[get_real];

  std::complex<double> c{1, 2};
  g(std::ref(std::cout), c);
}
