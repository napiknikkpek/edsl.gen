#define BOOST_TEST_MODULE alternative
#include <boost/test/included/unit_test.hpp>

#include "edsl/gen/operator/alternative.hpp"
#include "edsl/gen/operator/not_predicate.hpp"

using namespace edsl::gen;

BOOST_AUTO_TEST_CASE(first) {
  int r = 0;
  auto g = op([&r](auto i) { r += i; }) | [&r](auto i) { r += 2 * i; };
  BOOST_TEST(g(1));
  BOOST_TEST(r == 1);
}

BOOST_AUTO_TEST_CASE(second) {
  int r = 0;
  auto g = !op([&r](auto i) { r += i; }) | [&r](auto i) { r += 2 * i; };
  BOOST_TEST(g(1));
  BOOST_TEST(r == 3);
}

BOOST_AUTO_TEST_CASE(failed) {
  int r = 0;
  auto g = !op([&r](auto i) { r += i; }) | ![&r](auto i) { r += 2 * i; };
  BOOST_TEST(!g(1));
  BOOST_TEST(r == 3);
}
