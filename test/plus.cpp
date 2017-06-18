#define BOOST_TEST_MODULE plus
#include <boost/test/included/unit_test.hpp>

#include "edsl/gen/operator/not_predicate.hpp"
#include "edsl/gen/operator/plus.hpp"

using edsl::gen::wrap;

BOOST_AUTO_TEST_CASE(done) {
  int r = 0;
  auto g =
      wrap([](int& r, auto i) { r += i; }) + [](int& r, auto i) { r += 2 * i; };
  BOOST_TEST(g(std::ref(r), 1));
  BOOST_TEST(r == 3);
}

BOOST_AUTO_TEST_CASE(failed) {
  int r = 0;
  auto g = !wrap([](int& r, auto i) { r += i; }) +
           [](int& r, auto i) { r += 2 * i; };
  BOOST_TEST(!g(std::ref(r), 1));
  BOOST_TEST(r == 1);
}
