#define BOOST_TEST_MODULE sequence
#include <boost/test/included/unit_test.hpp>

#include "edsl/gen/operator/not_predicate.hpp"
#include "edsl/gen/operator/sequence.hpp"

using namespace edsl::gen;
namespace hana = boost::hana;
using namespace hana::literals;

BOOST_AUTO_TEST_CASE(temp) {
  int r = 0;

  auto g = op([&](int) { r += 1; }) << [&](int) { r += 2; };
  auto g2 = g << [&](int) { r += 3; };

  static_assert(!decltype(
      detail::is_valid(hana::type<decltype(g)>{}, hana::tuple<>{}))::value);

  // using X = decltype(g);
  // tuple<basic_type<int>, basic_type<int>, basic_type<int>> args;
  // auto val =
  //     *find_if(make_range(0_c, size(args) + size_t<1>{}), [&args](auto i) {
  //       return edsl::gen::detail::is_valid(type<X>{},
  //                                          slice(args, make_range(0_c, i)));
  //     });

  // auto val = *detail::args_size(g, 1, 2, 3);
  // static_assert(decltype(val)::value == 2);

  BOOST_TEST(true);
  BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(empty_case) {
  // {
  //   int r = 0;
  //   auto g = op([&]() { r += 1; }) << [&]() { r += 2; };

  //   BOOST_TEST(g());
  //   BOOST_TEST(r == 3);
  // }
  // {
  //   int r = 0;
  //   auto g = op([&]() { r += 1; }) << [&](int i) { r += i; };

  //   BOOST_TEST(g(2));
  //   BOOST_TEST(r == 3);
  // }
  // {
  //   int r = 0;
  //   auto g = op([&](int i) { r += 1; }) << [&]() { r += 2; };

  //   BOOST_TEST(g(1));
  //   BOOST_TEST(r == 3);
  // }
}

BOOST_AUTO_TEST_CASE(multi) {
  // int r = 0;

  // auto g = op([&](int) { r += 1; }) << [&](int) { r += 2; };
  // auto g2 = g << [&](int) { r += 3; };

  // BOOST_TEST(g2(1, 2, 3));
  // BOOST_TEST(r == 6);
}
