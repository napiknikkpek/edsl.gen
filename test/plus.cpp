#define BOOST_TEST_MODULE plus
#include <boost/test/included/unit_test.hpp>

#include "edsl/gen/operator/not_predicate.hpp"
#include "edsl/gen/operator/plus.hpp"

using namespace edsl::gen;

BOOST_AUTO_TEST_CASE(done) {
  int r = 0;
  auto g = op([&r](auto i) { r += i; }) + [&r](auto i) { r += 2 * i; };
  BOOST_TEST(g(1));
  BOOST_TEST(r == 3);
}

BOOST_AUTO_TEST_CASE(failed) {
  int r = 0;
  auto g = !op([&r](auto i) { r += i; }) + [&r](auto i) { r += 2 * i; };
  BOOST_TEST(!g(1));
  BOOST_TEST(r == 1);
}
