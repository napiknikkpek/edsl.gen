#define BOOST_TEST_MODULE sequence
#include <boost/test/included/unit_test.hpp>

#include "edsl/gen/operand.hpp"
#include "edsl/gen/operator/sequence.hpp"

using edsl::gen::op;

template <typename R, typename G, typename... Args>
void check(R expected, G g, Args&&... args) {
  R result = 0;

  BOOST_TEST(g(std::ref(result), std::forward<Args>(args)...));
  BOOST_TEST(result == expected);
}

BOOST_AUTO_TEST_CASE(empty) {
  check(3, op([](int& r) { r += 1; }) << op([](int& r) { r += 2; }));
  check(3, op([](int& r) { r += 1; }) << op([](int& r, int i) { r += i; }), 2);
  check(3, op([](int& r, int i) { r += i; }) << op([](int& r) { r += 2; }), 1);
}

BOOST_AUTO_TEST_CASE(multi) {
  check(6, op([](int& r, int i) { r += 1; }) << op([](int& r, int i) {
             r += i;
           }) << op([](int& r, int i) { r += i; }),
        1, 2, 3);
}

BOOST_AUTO_TEST_CASE(variadic) {
  check(6, op([](int& r, double i, unsigned j) {
             r += i;
             r += j;
           }) << op([](int& r, int i) { r += i; }),
        1, 2, 3);
}
