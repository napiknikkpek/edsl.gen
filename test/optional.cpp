#define BOOST_TEST_MODULE optional
#include <boost/test/included/unit_test.hpp>

#include "edsl/gen/operator/optional.hpp"

using edsl::gen::as_operand;

BOOST_AUTO_TEST_CASE(unused) {
  int r = 0;
  auto g = -as_operand([](int& r) { r += 1; });
  g(std::ref(r));
  BOOST_TEST(r == 1);
}

BOOST_AUTO_TEST_CASE(empty) {
  int r = 0;
  auto g = -as_operand([](int& r, int i) { r += i; });
  int* opt = nullptr;
  g(std::ref(r), opt);
  BOOST_TEST(r == 0);
}

BOOST_AUTO_TEST_CASE(full) {
  int r = 0;
  auto g = -as_operand([](int& r, int i) { r += i; });
  int v = 1;
  int* opt = &v;
  g(std::ref(r), opt);
  BOOST_TEST(r == 1);
}
