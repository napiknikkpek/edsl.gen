#define BOOST_TEST_MODULE unary_plus
#include <boost/test/included/unit_test.hpp>

#include <string>
#include <vector>

#include "edsl/gen/operator/unary_plus.hpp"

using edsl::gen::as_operand;

BOOST_AUTO_TEST_CASE(empty) {
  int r = 0;
  auto g = +as_operand([](int& r, int i) { r += i; });
  BOOST_TEST(!g(std::ref(r), std::vector<int>{}));
  BOOST_TEST(r == 0);
}
