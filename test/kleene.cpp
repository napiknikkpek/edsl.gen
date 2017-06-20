#define BOOST_TEST_MODULE kleene
#include <boost/test/included/unit_test.hpp>

#include <string>
#include <vector>

#include "edsl/gen/operator/kleene.hpp"

using edsl::gen::as_operand;

BOOST_AUTO_TEST_CASE(empty) {
  int r = 0;
  auto g = *as_operand([](int& r, int i) { r += i; });
  BOOST_TEST(g(std::ref(r), std::vector<int>{}));
  BOOST_TEST(r == 0);
}

BOOST_AUTO_TEST_CASE(interrupted) {
  int r = 0;
  auto g = *as_operand([](int& r, int i) {
    if (i == 2) return false;
    r += i;
    return true;
  });
  BOOST_TEST(!g(std::ref(r), std::vector<int>{1, 2, 3}));
  BOOST_TEST(r == 1);
}

BOOST_AUTO_TEST_CASE(done) {
  int r = 0;
  auto g = *as_operand([](int& r, int i) { r += i; });
  BOOST_TEST(g(std::ref(r), std::vector<int>{1, 2, 3}));
  BOOST_TEST(r == 6);
}

BOOST_AUTO_TEST_CASE(multi) {
  using namespace boost::hana;

  int r = 0;
  auto g = *as_operand([](int& r, int i, std::string const& str) {
    r += i;
    r += str.size();
  });
  BOOST_TEST(g(std::ref(r), std::vector<tuple<int, std::string>>{
                                make_tuple(1, "a"), make_tuple(2, "ab")}));
  BOOST_TEST(r == 6);
}
